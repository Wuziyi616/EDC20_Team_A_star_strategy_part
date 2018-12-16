#include "urkax.h"

uint8_t huanchong[1];
volatile int GetValidData = 0;
volatile struct Position aimp, myp;
char myCar='B';
volatile char copyFlag = 1;
char first_passenger_flag=1;
volatile char start_transimit=0;

extern volatile struct PassengerInfo passengers[MaxPassengerNum];

char inInterSection_0_explicit(int x, int y);
char inInterSection_1_explicit(int x, int y);
char inInterSection_2_explicit(int x, int y);
char inInterSection_3_explicit(int x, int y);

//跳线帽接PC11 PC12则返回'A',否则返回B
char what_car_type(void)
{
	if(HAL_GPIO_ReadPin(CAR_TYPE_INPUT_GPIO_Port, CAR_TYPE_INPUT_Pin) == GPIO_PIN_SET)
	{
		return 'A';
	}
	else
	{
		return 'B';
	}
}

char ifToAvoidCircle_extend(volatile struct Position *from, volatile struct Position *to, volatile struct Position *circle, int circle_r, int plus_r, volatile struct Position *temp)
{
	if (get_distance(from, circle) >= 50 && get_distance(to, circle) >= 50)
	{
		return 0;
	}

	int m_a_x = to->X - from->X;
	int m_a_y = to->Y - from->Y;

	int m_o_x = circle->X - from->X;
	int m_o_y = circle->Y - from->Y;

	int a_o_x = circle->X - to->X;
	int a_o_y = circle->Y - to->Y;

	int ao_ma_dian_ji = a_o_x * m_a_x + a_o_y * m_a_y;
	int ma_mo_dian_ji = m_o_x * m_a_x + m_o_y * m_a_y;

	if (ao_ma_dian_ji >= 0 || ma_mo_dian_ji <= 0)
	{
		return 0;
	}

	int cha_ji = m_a_x * m_o_y - m_a_y * m_o_x;
	int cha_ji_abs = cha_ji > 0 ? cha_ji : -cha_ji;

	double m_a_dis = (double)sqrtf(m_a_x * m_a_x + m_a_y * m_a_y);

	int distance = (double)cha_ji_abs / (m_a_dis + 1e-2);

	if (distance >= circle_r)
	{
		return 0;
	}

	int m_a_ver_x = m_a_y;
	int m_a_ver_y = -m_a_x;

	int o_t_x = (double)m_a_ver_x * (double)plus_r / (m_a_dis + 1e-2);
	int o_t_y = (double)m_a_ver_y * (double)plus_r / (m_a_dis + 1e-2);

	if (cha_ji < 0)
	{
		o_t_x = -o_t_x;
		o_t_y = -o_t_y;
	}

	temp->X = circle->X + o_t_x;
	temp->Y = circle->Y + o_t_y;

	return 1;
}

// 返回0表示不用避让，返回1表示可以避让，返回2表示不可避让
char ifToAvoidEnemy_extend(volatile struct Position *myp, volatile struct Position *aimp, volatile struct Position *circleO,int to_avoid_circle_r, int plus_r,volatile struct Position *temp_aimp)
{
	*temp_aimp = *aimp;

	if (get_distance(myp, circleO) >= 50 && get_distance(aimp, circleO) >= 50)//myp?aimp??circle_o??
	{
		return 0;
	}
	
	int m_a_x = aimp->X - myp->X;
	int m_a_y = aimp->Y - myp->Y;

	int m_o_x = circleO->X - myp->X;
	int m_o_y = circleO->Y - myp->Y;

	int a_o_x = circleO->X - aimp->X;
	int a_o_y = circleO->Y - aimp->Y;

	double m_o_dis=(double)sqrt(m_o_x*m_o_x+m_o_y*m_o_y);
	double m_a_dis = (double)sqrt(m_a_x*m_a_x + m_a_y * m_a_y);
	double a_o_dis = (double)sqrt(a_o_x*a_o_x + a_o_y * a_o_y);
	
	int ao_ma_dian_ji = a_o_x * m_a_x + a_o_y * m_a_y;
	int ma_mo_dian_ji = m_o_x * m_a_x + m_o_y * m_a_y;

	if (ao_ma_dian_ji >= 0 || ma_mo_dian_ji <= 0)
	{
		return 0;
	}

	int cha_ji = (m_a_x*m_o_y - m_a_y * m_o_x);
	int cha_ji_abs = (cha_ji>0 ? cha_ji : (-cha_ji));
	
	int distance = (double)cha_ji_abs / (m_a_dis + 1e-2);

	if (distance >= to_avoid_circle_r)
	{
		return 0;
	}

	if(m_o_dis<=to_avoid_circle_r)
	{
		*temp_aimp = *myp;
		return 2; //can not avoid
	}
	else
	{
		return 0;
	}
	/*
	if (!locate(myp) || !locate(circleO)) return 0;
	
	if (myp->is_InSection && circleO->is_InSection && myp->curSection != circleO->curSection)
	{
		return 0;
	}
	
	if(m_o_dis<to_avoid_circle_r)
	{
		*temp_aimp = *myp;
		return 2; //can not avoid
	}

	if(myp->is_InSection)
	{
		*temp_aimp = *myp;
		return 2; //can not avoid
	}
	
	
	int m_a_ver_x = m_a_y;
	int m_a_ver_y = -m_a_x;

	int o_t_x = (double)m_a_ver_x*(double)plus_r / (m_a_dis + 1e-2);
	int o_t_y = (double)m_a_ver_y*(double)plus_r / (m_a_dis + 1e-2);

	if (cha_ji < 0)
	{
		o_t_x = -o_t_x;
		o_t_y = -o_t_y;
	}

	temp_aimp->X = circleO->X + o_t_x;
	temp_aimp->Y = circleO->Y + o_t_y;
	
	
	if((!inInterSection_0_explicit(temp_aimp->X, temp_aimp->Y))
	 &&(!inInterSection_1_explicit(temp_aimp->X, temp_aimp->Y))
	 &&(!inInterSection_2_explicit(temp_aimp->X, temp_aimp->Y))
	 &&(!inInterSection_3_explicit(temp_aimp->X, temp_aimp->Y))
		)
	{
		temp_aimp->X = circleO->X - o_t_x;
		temp_aimp->Y = circleO->Y - o_t_y;
		
		if((!inInterSection_0_explicit(temp_aimp->X, temp_aimp->Y))
		 &&(!inInterSection_1_explicit(temp_aimp->X, temp_aimp->Y))
		 &&(!inInterSection_2_explicit(temp_aimp->X, temp_aimp->Y))
		 &&(!inInterSection_3_explicit(temp_aimp->X, temp_aimp->Y))
			)
		{
			*temp_aimp = *myp;
			return 2; //can not avoid
		}
	}
	
	return 1;*/
}


char passengersInfoChange(void)
{
	static volatile uint8_t last_passengerNum = 0;
	static volatile struct PassengerInfo lastPassengers[MaxPassengerNum];
	
	int changeFlag = 0;
	
	if(last_passengerNum != 0)
	{
		if(last_passengerNum != getPassengersNum())
		{
			changeFlag = 1;
		}
		else
		{
			for(int i=0; i<getPassengersNum();i++)
			{
				if(lastPassengers[i].State != passengers[i].State)
				{
					changeFlag = 2;
				}
				
				else if(  (lastPassengers[i].start_pos.X != passengers[i].start_pos.X)
					|| (lastPassengers[i].start_pos.Y != passengers[i].start_pos.Y))
				{
					changeFlag = 3;
				}
				
				else if(  (lastPassengers[i].end_pos.X != passengers[i].end_pos.X)
					|| (lastPassengers[i].end_pos.Y != passengers[i].end_pos.Y))
				{
					changeFlag = 4;
				}
			}
		}
	}
	
	for(int i=0;i<MaxPassengerNum;i++)
	{
		lastPassengers[i]=passengers[i];
	}
	
	last_passengerNum = getPassengersNum();
	
	return changeFlag;
}

struct Position getEnemyP(void)
{
	if(myCar=='A')
	{
		DecodeCarBInfo();
		return getCarB_pos();
	}
	else if(myCar=='B')
	{
		DecodeCarAInfo();
		return getCarA_pos();
	}
	
	DecodeCarBInfo();
	return getCarB_pos();
}

struct Position getMyP(void)
{
	if(myCar=='A')
	{
		DecodeCarAInfo();
		return getCarA_pos();
	}
	else if(myCar=='B')
	{
		DecodeCarBInfo();
		return getCarB_pos();
	}
	
	DecodeCarBInfo();
	return getCarB_pos();
}

//1表示角度初始值为-90；0表示角度初始值为179；
int startAngleAndAim(volatile struct Position *myp, volatile struct Position *aimp)
{
	struct Position RightDownStartPos, LeftUpStartPos;
	RightDownStartPos.X=187; RightDownStartPos.Y=66;
	LeftUpStartPos.X=68; LeftUpStartPos.Y=185;
	
	if(get_distance(&RightDownStartPos, myp) <= 30)
	{
		(*aimp).X=185; (*aimp).Y=30;
		return 1;
	}
	else if(get_distance(&LeftUpStartPos, myp)<=30)
	{
		(*aimp).X=30; (*aimp).Y=185;
		return 0;
	}
	//25 20
	return -1;
}

//return 1 to 5
char enemy_get_passengerX(void)
{
	for(int i=0;i<getPassengersNum();i++)
	{
		if(passengers[i].State == On_CarB && myCar == 'A')
		{
			return i+1;
		}
		else if(passengers[i].State == On_CarA && myCar == 'B')
		{
			return i+1;
		}
	}
	
	return 0;
}
