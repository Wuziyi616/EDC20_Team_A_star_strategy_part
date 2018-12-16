#ifndef DECODE_H
#define DECODE_H

#include "stm32f1xx_hal.h"

struct Position;
struct Edge;
struct Section;
struct InterSection;
struct Path;
struct RoundInfo;
struct PassengerInfo;

// TODO: change these values
#define INVALID_ARG -1
#define RECEIVE_QUEUE_LENTH 216

#define PositionNum 40
#define EdgeNum 26
#define SectionNum 12
#define InterSectionNum 4
#define PositionStart 0
#define EdgeStart 50
#define SectionStart 80
#define InterSectionStart 100
#define MaxPassengerNum 5

#define MaxEdgesPerSection 4
#define MaxPositionsPerSection 5
#define MaxSectionsPerPath 5
#define MaxPositionsPerPath 20

#define WeightForAngle 100  // cm distance per pi rad (3.14 rad)

extern volatile uint8_t messageReceive[72];
extern volatile uint8_t whole_message[72];
extern volatile int message_index;
extern volatile int message_head;

extern volatile struct CarInfo CarAinformation;
extern volatile struct CarInfo CarBinformation;
extern volatile struct RoundInfo roundInformation;

/**************************************** Structs about the map ****************************************/
/* Position */
struct Position
{
	char name;
	int X;
	int Y;
	volatile struct Section *curSection;
	volatile struct InterSection *curInterSection;
	volatile struct Edge *curEdge;
	char is_InSection;
};

void set_position(volatile struct Position *p, int x, int y, char name);
int get_distance(volatile struct Position *p1, volatile struct Position *p2);
int dot_product(volatile struct Position *p1, volatile struct Position *p2, volatile struct Position *p3, volatile struct Position *p4);  // (p1 -> p2) dot_product (p3 -> p4)
char is_front_position(volatile struct Position *p, volatile struct Position *front);  // determine whether p is in front of front
float get_angle(volatile struct Position *p1, volatile struct Position *p2, volatile struct Position *p3, volatile struct Position *p4);  // angle between (p1 -> p2) and (p3 -> p4)
																																																																					// note that angle is between 0 and +pi

/* Edge */

struct Edge
{
	char(*in_Edge)(int x, int y);
	char name;
	volatile struct Position *start;  // start point
	volatile struct Position *end;    // end point
	int length;
};

void set_edge(volatile struct Edge *e, char(*in_Edge)(int x, int y), char name, volatile struct Position *start, volatile struct Position *end, int length);

/* InterSection */

struct InterSection
{
	char(*in_InterSection)(int x, int y);
	char name;
};

void set_intersection(volatile struct InterSection *i, char(*in_InterSection)(int x, int y), char name);

/* Section */

struct Section
{
	char name;
	int length;
	volatile struct Position *positions[MaxPositionsPerSection];   // all key points in it
	volatile struct Edge *edges[MaxEdgesPerSection];               // all edges in it
	volatile struct InterSection *start_intersection;  // the intersection before it
	volatile struct InterSection *end_intersection;    // the intersection after it
};

void set_section(volatile struct Section *s, char name, int length, volatile struct Position *positions[MaxPositionsPerSection], 
	volatile struct Edge *edges[MaxEdgesPerSection], volatile struct InterSection *start_intersection, volatile struct InterSection *end_intersection);
char in_Section(volatile struct Section *s, int x, int y);

/* Path */

struct Path
{
	volatile struct Position *key_points[MaxPositionsPerPath];
	volatile struct Section *sections[MaxSectionsPerPath];
	int length;
};

void set_path(volatile struct Path *p, int length, volatile struct Section *sections[MaxSectionsPerPath]);
void clear_path(volatile struct Path *p);

/**************************************** Structs about the game ****************************************/
/* RoundInfo */

/* Game States */
enum GameStateEnum
{
	GameNotStart,
	GameGoing,
	GamePause,
	GameOver
};

struct RoundInfo
{
	uint8_t GameState;  // 00 not start yet, 01 going, 10 pause, 11 end
	uint16_t Round;
	uint8_t passengersNum;  // current passengers number on the court
};

/* PassengerInfo */

/* Passenger States */
enum PassengerStateEnum
{
	Not_Abord,
	On_CarA,
	On_CarB
};

struct PassengerInfo
{
	uint8_t Num;               // ID
	struct Position start_pos;
	struct Position end_pos;
	int point;                 // the reward for this passenger
	struct Path start_to_end;  // nearest path for this passenger
	uint8_t State;             // 00 not aboard, 01 on carA, 10 on carB
};

/* CarInfo */

struct CarInfo
{
	char Num;
	uint8_t FaultTimes;
	uint16_t Score;
	
	struct Position pos;      // current position
	struct Position *target;  // next position to go
	int passenger_num;        // the passenger it wants to load (0/1/2/3/4)
	struct Path curPath;      // nearest path working on now
	float  point_per_cm;      // the distance_average score for curPath
};

void clear_car(volatile struct CarInfo *car);

/* Decode Functions */
void DecodeRoundInfo(void);
void DecodeCarAInfo(void);
void DecodeCarBInfo(void);
void DecodePassenger1(void);
void DecodePassenger2(void);
void DecodePassenger3(void);
void DecodePassenger4(void);
void DecodePassenger5(void);
void DecodePassengers(void);

void DecodeAll(void);
void calculatePassengersScore_Path(void);
void DecodePassengers(void);
//int getMessage(void);
int checkBeginningNew(void);
int receiveIndexMinus(int,int);
int receiveIndexAdd(int,int);

/************** Interface Functions *****************/
enum GameStateEnum getGameState(void);
uint16_t getGameRound(void);
uint8_t getPassengersNum(void);

uint16_t getCarA_X(void);
uint16_t getCarA_Y(void);
uint16_t getCarB_X(void);
uint16_t getCarB_Y(void);
struct Position getCarA_pos(void);
struct Position getCarB_pos(void);
uint8_t getCarA_FaultTimes(void);
uint8_t getCarB_FaultTimes(void);
uint16_t getCarA_RawScore(void);
uint16_t getCarB_RawScore(void);

uint16_t getPassengerXstart_X(uint8_t px);
uint16_t getPassengerXstart_Y(uint8_t px);
uint16_t getPassengerXend_X(uint8_t px);
uint16_t getPassengerXend_Y(uint8_t px);
struct Position getPassengerXstart_pos(uint8_t px);
struct Position getPassengerXend_pos(uint8_t px);

enum PassengerStateEnum getPasseengerX_state(uint8_t px);

#endif
