#ifndef CORE_H_
#define CORE_H_

#include "Decode.h"
#include "Output.h"
#include "urkax.h"
#include "Decode.h"
#include "math.h"

void init(void);  // Initialize map information
char get_nearest_path(volatile struct Path *path, volatile struct Position start_pos, volatile struct Position *end_pos);  // Get the nearest path between two positions
void cross_dashed(volatile struct Path *path, volatile struct Position *start_pos);  // Take advantages of the dashed between (S1 & S2) and (S11 & S12)
void avoid_circle(volatile struct Path *path, volatile struct Position *start_pos);
int calculate_length(volatile struct Position *points[MaxPositionsPerPath]);  // Calculate the length of a row of points
char locate(volatile struct Position *p);  // Locate a position, find which edge/section/intersection it belongs to
char Searching_Passenger(void);  // Get the highest reward passenger
char inInterSection_0(int x, int y);
char inInterSection_1(int x, int y);
char inInterSection_2(int x, int y);
char inInterSection_3(int x, int y);
char inInterSection_0_explicit(int x, int y);
char inInterSection_1_explicit(int x, int y);
char inInterSection_2_explicit(int x, int y);
char inInterSection_3_explicit(int x, int y);
char ifToAvoidCircle_extend(volatile struct Position *from, volatile struct Position *to, volatile struct Position *circle, int circle_r, int plus_r, volatile struct Position *temp);

extern UART_HandleTypeDef huart1;

#endif
