#ifndef URKAX_H
#define URKAX_H

#include "stm32f1xx_hal.h"
#include "Decode.h"	
#include "Core.h"
#include <math.h>

extern uint8_t huanchong[1];
extern volatile int GetValidData;
extern volatile struct Position aimp, myp;
extern char myCar;
extern volatile char copyFlag;
extern char first_passenger_flag;
extern volatile char start_transimit;

int startAngleAndAim(volatile struct Position *myp, volatile struct Position *aimp);
struct Position getMyP(void); 
struct Position getEnemyP(void);
char passengersInfoChange(void);
char ifToAvoidEnemy_extend(volatile struct Position *myp, volatile struct Position *aimp, volatile struct Position *circleO, int to_avoid_circle_r, int plus_r, volatile struct Position *temp_aimp);
char ifToAvoidCircle_extend(volatile struct Position *from, volatile struct Position *to, volatile struct Position *circle, int circle_r, int plus_r, volatile struct Position *temp);
char what_car_type(void);
char enemy_get_passengerX(void);

#endif
