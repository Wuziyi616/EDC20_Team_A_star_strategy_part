#include "Decode.h"
#include "math.h"
#include "Core.h"
#include <stdlib.h>

volatile uint8_t messageReceive[72];
volatile uint8_t whole_message[72];
volatile int message_index=0;
volatile int message_head=-1;

/* Information about the match */
volatile struct RoundInfo roundInformation;
volatile struct CarInfo CarAinformation;
volatile struct CarInfo CarBinformation;
volatile struct PassengerInfo passengers[MaxPassengerNum];
volatile char passengerChangeFlag[MaxPassengerNum];

/* Map Information */
volatile struct Position allPositions[PositionNum];                    // all key points
volatile struct Edge allEdges[EdgeNum];                                // all edges
volatile struct Section allSections[SectionNum];                       // all sections
volatile struct InterSection allInterSections[InterSectionNum];        // all intersections
volatile struct Path allPaths[InterSectionNum][InterSectionNum];       // all pre-calculated paths between intersections
volatile struct Position TransformPosition;                            // the position used to avoid circle

/* Position */

void set_position(volatile struct Position *p, int x, int y, char name)
{
	p->X = x;
	p->Y = y;
	p->name = name;
}

int get_distance(volatile struct Position *p1, volatile struct Position *p2)
{
	int distance = sqrtf((p1->X - p2->X) * (p1->X - p2->X) + (p1->Y - p2->Y) * (p1->Y - p2->Y));
	distance = distance > 0 ? distance: -distance;
	return distance;
}

int dot_product(volatile struct Position *p1, volatile struct Position *p2, volatile struct Position *p3, volatile struct Position *p4)
{
	int dx1, dx2, dy1, dy2;
	dx1 = p1->X - p2->X; dx2 = p3->X - p4->X;
	dy1 = p1->Y - p2->Y; dy2 = p3->Y - p4->Y;
	return dx1 * dx2 + dy1 * dy2;
}

char is_front_position(volatile struct Position *p, volatile struct Position *front)
{
	if (p->is_InSection && front->is_InSection)
	{
		return p->curEdge->start == front;  // judge directly by positions
	}
	return 0;
}

float get_angle(volatile struct Position *p1, volatile struct Position *p2, volatile struct Position *p3, volatile struct Position *p4)
{
	return acos(dot_product(p1, p2, p3, p4) / (get_distance(p1, p2) * get_distance(p3, p4)));
}

/* Edge */

void set_edge(volatile struct Edge *e, char(*in_Edge)(int x, int y), char name, volatile struct Position *start, volatile struct Position *end, int length)
{
	e->in_Edge = in_Edge;
	e->name = name;
	e->start = start;
	e->end = end;
	e->length = length;
}

/* Intersection */

void set_intersection(volatile struct InterSection *i, char(*in_InterSection)(int x, int y), char name)
{
	i->in_InterSection = in_InterSection;
	i->name = name;
}

/* Section */

void set_section(volatile struct Section *s, char name, int length, volatile struct Position *positions[MaxPositionsPerSection], 
	volatile struct Edge *edges[MaxEdgesPerSection], volatile struct InterSection *start_intersection, volatile struct InterSection *end_intersection)
{
	s->name = name;
	s->length = length;
	for (int i = 0; i < MaxPositionsPerSection; i++) s->positions[i] = positions[i];
	for (int i = 0; i < MaxEdgesPerSection; i++) s->edges[i] = edges[i];
	s->start_intersection = start_intersection;
	s->end_intersection = end_intersection;
}

char in_Section(volatile struct Section *s, int x, int y)
{
	for (int i = 0; i < MaxEdgesPerSection; i++)
	{
		if (!s->edges[i]) return 0;
		if (s->edges[i]->in_Edge(x, y)) return 1;
	}
	return 0;
}

/* Path */

void set_path(volatile struct Path *p, int length, volatile struct Section *sections[MaxSectionsPerPath])
{
	for (int i = 0; i < MaxPositionsPerPath; i++)
	{
		p->key_points[i] = 0;
	}
	p->length = length;
	for (int i = 0; i < MaxSectionsPerPath; i++) p->sections[i] = sections[i];
}

void clear_path(volatile struct Path *p)
{
		for (int i = 0; i < MaxPositionsPerPath; i++)
	{
		p->key_points[i] = 0;
	}
	p->length = 0;
	for (int i = 0; i < MaxSectionsPerPath; i++) p->sections[i] = 0;
}

/* Decode */
void DecodeRoundInfo()
{
	roundInformation.GameState = (messageReceive[0] & 0xC0) >> 6;
	roundInformation.Round = ((messageReceive[0] & 0x3F) << 8) + messageReceive[1];
	roundInformation.passengersNum = (messageReceive[9] & 0xFC) >> 2;
}

void DecodeCarAInfo()
{
	CarAinformation.Num = 'A';
	
	CarAinformation.pos.X = ((messageReceive[2] & 0x80) << 1) + messageReceive[5];
	CarAinformation.pos.Y = ((messageReceive[2] & 0x40) << 2) + messageReceive[6];
	
	CarAinformation.pos.X = CarAinformation.pos.X > 300 ? 0: CarAinformation.pos.X;
	CarAinformation.pos.Y = CarAinformation.pos.Y > 300 ? 0: CarAinformation.pos.Y;
	
	CarAinformation.FaultTimes= messageReceive[31];
	CarAinformation.Score = (messageReceive[33] << 8) + messageReceive[34];
}

void DecodeCarBInfo()
{
	CarBinformation.Num = 'B';
	
	CarBinformation.pos.X = ((messageReceive[2] & 0x20) << 3) + messageReceive[7];
	CarBinformation.pos.Y = ((messageReceive[2] & 0x10) << 4) + messageReceive[8];
	
	CarBinformation.pos.X = CarBinformation.pos.X > 300 ? 0: CarBinformation.pos.X;
	CarBinformation.pos.Y = CarBinformation.pos.Y > 300 ? 0: CarBinformation.pos.Y;
	
	CarBinformation.FaultTimes= messageReceive[32];
	CarBinformation.Score = (messageReceive[35] << 8) + messageReceive[36];
}

void clear_car(volatile struct CarInfo *car)
{
	car->passenger_num = -1;
	car->point_per_cm = 0;
	clear_path(&car->curPath);
	car->target = NULL;
}

void calculate_passenger_score(volatile struct PassengerInfo *passenger)
{
	int distance = get_distance(&passenger->start_pos, &passenger->end_pos);
	if (distance < 68)
	{
		passenger->point = 20;
		return;
	}
	if (distance < 158)
	{
		passenger->point = 40;
		return;
	}
	if (distance < 270)
	{
		passenger->point = 80;
		return;
	}
	if (distance < 381)
	{
		passenger->point = 100;
		return;
	}
	passenger->point = 100;
}

void DecodePassenger1()
{
	passengers[0].Num = 1;
	
	passengers[0].start_pos.X = ((messageReceive[2] & 0x08) << 5) + messageReceive[11];
	passengers[0].start_pos.Y = ((messageReceive[2] & 0x04) << 6) + messageReceive[12];
	
	passengers[0].end_pos.X = ((messageReceive[2] & 0x02) << 7) + messageReceive[13];
	passengers[0].end_pos.Y = ((messageReceive[2] & 0x01) << 8) + messageReceive[14];
	
	passengers[0].State = messageReceive[9] & 0x03;
}

void DecodePassenger2()
{
	passengers[1].Num = 2;
	
	passengers[1].start_pos.X = ((messageReceive[3] & 0x80) << 1) + messageReceive[15];
	passengers[1].start_pos.Y = ((messageReceive[3] & 0x40) << 2) + messageReceive[16];
	
	passengers[1].end_pos.X = ((messageReceive[3] & 0x20) << 3) + messageReceive[17];
	passengers[1].end_pos.Y = ((messageReceive[3] & 0x10) << 4) + messageReceive[18];
	
	passengers[1].State = (messageReceive[10] & 0xC0) >> 6;
}

void DecodePassenger3()
{
	passengers[2].Num = 3;
	
	passengers[2].start_pos.X = ((messageReceive[3] & 0x08) << 5) + messageReceive[19];;
	passengers[2].start_pos.Y = ((messageReceive[3] & 0x04) << 6) + messageReceive[20];
	
	passengers[2].end_pos.X = ((messageReceive[3] & 0x02) << 7) + messageReceive[21];
	passengers[2].end_pos.Y = ((messageReceive[3] & 0x01) << 8) + messageReceive[22];
	
	passengers[2].State = (messageReceive[10] & 0x30) >> 4;
}

void DecodePassenger4()
{
	passengers[3].Num = 4;
	
	passengers[3].start_pos.X = ((messageReceive[4] & 0x80) << 1) + messageReceive[23];
	passengers[3].start_pos.Y = ((messageReceive[4] & 0x40) << 2) + messageReceive[24];
	
	passengers[3].end_pos.X = ((messageReceive[4] & 0x20) << 3) + messageReceive[25];
	passengers[3].end_pos.Y = ((messageReceive[4] & 0x10) << 4) + messageReceive[26];
	
	passengers[3].State = (messageReceive[10] & 0x0C) >> 2;
}

void DecodePassenger5()
{
	passengers[4].Num = 5;
	
	passengers[4].start_pos.X = ((messageReceive[4] & 0x08) << 5) + messageReceive[27];
	passengers[4].start_pos.Y = ((messageReceive[4] & 0x04) << 6) + messageReceive[28];
	
	passengers[4].end_pos.X = ((messageReceive[4] & 0x02) << 7) + messageReceive[29];
	passengers[4].end_pos.Y = ((messageReceive[4] & 0x01) << 8) + messageReceive[30];
	
	passengers[4].State = messageReceive[10] & 0x03;
}

void DecodePassengers(void)
{
	DecodeRoundInfo();
	
	int num=getPassengersNum();
	
	switch(num)
	{
		case 5: DecodePassenger5();
		case 4: DecodePassenger4();
		case 3: DecodePassenger3();
		case 2: DecodePassenger2();
		case 1: DecodePassenger1();
	}
	
	for(int i=0;i<num;i++)
	{
		if(passengers[i].State==0)
		{
			passengers[i].State=Not_Abord;
		}
		else if(passengers[i].State==1)
		{
			passengers[i].State=On_CarA;
		}
		else if(passengers[i].State==1)
		{
			passengers[i].State=On_CarB;
		}
	}
}

void calculatePassengersScore_Path(void)
{
	DecodeRoundInfo();
	
	int num=getPassengersNum();
	
	switch(num)
	{
		case 5: 
			calculate_passenger_score(&passengers[4]);
			passengers[4].point *= 1.5;
			//SerialPrintNewChar("get near 5 s\n",&huart1);
			get_nearest_path(&passengers[4].start_to_end, passengers[4].start_pos, &passengers[4].end_pos);
			//SerialPrintNewChar("get near 5 e\n",&huart1);
		case 4:
			calculate_passenger_score(&passengers[3]);
			//SerialPrintNewChar("get near 4 s\n",&huart1);
			get_nearest_path(&passengers[3].start_to_end, passengers[3].start_pos, &passengers[3].end_pos);
			//SerialPrintNewChar("get near 4 e\n",&huart1);
		case 3:
			calculate_passenger_score(&passengers[2]);
			//SerialPrintNewChar("get near 3 s\n",&huart1);
			get_nearest_path(&passengers[2].start_to_end, passengers[2].start_pos, &passengers[2].end_pos);
			//SerialPrintNewChar("get near 3 e\n",&huart1);
		case 2:
			calculate_passenger_score(&passengers[1]);
			//SerialPrintNewChar("get near 2 s\n",&huart1);
			get_nearest_path(&passengers[1].start_to_end, passengers[1].start_pos, &passengers[1].end_pos);
			//SerialPrintNewChar("get near 2 e\n",&huart1);
		case 1:
			calculate_passenger_score(&passengers[0]);	
			//SerialPrintNewChar("get near 1 s\n",&huart1);
			get_nearest_path(&passengers[0].start_to_end, passengers[0].start_pos, &passengers[0].end_pos);
			//SerialPrintNewChar("get near 1 e\n",&huart1);
	}

}

uint8_t CodeCheck()
{
	if((messageReceive[62] == 0x0D) && messageReceive[63] == 0x0A)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void DecodeAll()
{
	DecodeRoundInfo();
	DecodeCarAInfo();
	DecodeCarBInfo();
	DecodePassenger1();
	DecodePassenger2();
	DecodePassenger3();
	DecodePassenger4();
	DecodePassenger5();
}

int checkBeginningNew(void)
{
	//2B 49 50 44 2C 36 34 3A
  //2B 49 50 44 2C 31 32 38 3A
	if(whole_message[receiveIndexMinus(message_index,3)] == 0x36
		&& whole_message[receiveIndexMinus(message_index,2)] == 0x34
		&& whole_message[receiveIndexMinus(message_index,1)] == 0x3A)
	{
		return 1;
	}
	else if(whole_message[receiveIndexMinus(message_index,4)] == 0x31
				&& whole_message[receiveIndexMinus(message_index,3)] == 0x32
				&& whole_message[receiveIndexMinus(message_index,2)] == 0x38
				&& whole_message[receiveIndexMinus(message_index,1)] == 0x3A)
	{
		return 1;
	}	
	else
	{
		return 0;
	}
}

int receiveIndexMinus(int index_h,int num)
{
	if(index_h-num>=0)
	{
		return index_h-num;
	}
	else
	{
		return index_h-num+RECEIVE_QUEUE_LENTH;
	}
}

int receiveIndexAdd(int index_h,int num)
{
	if(index_h+num<RECEIVE_QUEUE_LENTH)
	{
		return index_h+num;
	}
	else
	{
		return index_h+num-RECEIVE_QUEUE_LENTH;
	}
}


/***************** ?? *****************/
enum GameStateEnum getGameState(void)
{
	uint8_t state = roundInformation.GameState;
	if(state == 0)
	{
		return GameNotStart;
	}
	else if(state == 1)
	{
		return GameGoing;
	}
	else if(state == 2)
	{
		return GamePause;
	}
	else if(state == 3)
	{
		return GameOver;
	}
	
	return GameNotStart;
}	

uint16_t getGameRound(void)
{
	return roundInformation.Round;
}

uint8_t getPassengersNum(void)
{
	return roundInformation.passengersNum;
}

uint16_t getCarA_X()
{
	return CarAinformation.pos.X;
}

uint16_t getCarA_Y()
{
	return CarAinformation.pos.Y;
}

uint16_t getCarB_X()
{
	return CarBinformation.pos.X;
}

uint16_t getCarB_Y()
{
	return CarBinformation.pos.Y;
}

struct Position getCarA_pos(void)
{
	return CarAinformation.pos;
}

struct Position getCarB_pos(void)
{
	return CarBinformation.pos;
}

uint8_t getCarA_FaultTimes(void) //????
{
	return CarAinformation.FaultTimes;
}

uint8_t getCarB_FaultTimes(void)
{
	return CarBinformation.FaultTimes;
}

uint16_t getCarA_RawScore(void) //??????????
{
	return CarAinformation.Score;
}

uint16_t getCarB_RawScore(void)
{
	return CarBinformation.Score;
}

//????x(1?5)?????,??x????????,???INVALID_ARG
uint16_t getPassengerXstart_X(uint8_t px)
{
	if(px>getPassengersNum())
	{
		return (uint16_t)INVALID_ARG;
	}
	
	return passengers[px-1].start_pos.X;
}

uint16_t getPassengerXstart_Y(uint8_t px)
{
	if(px>getPassengersNum())
	{
		return (uint16_t)INVALID_ARG;
	}
	
	return passengers[px-1].start_pos.Y;
}

uint16_t getPassengerXend_X(uint8_t px)
{
	if(px>getPassengersNum())
	{
		return (uint16_t)INVALID_ARG;
	}
	
	return passengers[px-1].end_pos.X;
}

uint16_t getPassengerXend_Y(uint8_t px)
{
	if(px>getPassengersNum())
	{
		return (uint16_t)INVALID_ARG;
	}
	
	return passengers[px-1].end_pos.Y;
}

enum PassengerStateEnum getPasseengerX_state(uint8_t px)
{
	if(px>getPassengersNum())
	{
		return (enum PassengerStateEnum)INVALID_ARG;
	}
	
	uint8_t state = passengers[px-1].State;
	
	//????,00???,01?A?,10?B?
	if(state == 0)
	{
		return Not_Abord;
	}
	else if(state == 1)
	{
		return On_CarA;
	}
	else if(state == 2)
	{
		return On_CarB;
	}
	
	return Not_Abord;
}

struct Position getPassengerXstart_pos(uint8_t px)
{
	return passengers[px-1].start_pos;
}

struct Position getPassengerXend_pos(uint8_t px)
{
	return passengers[px-1].end_pos;
}
