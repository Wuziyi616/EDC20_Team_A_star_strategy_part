#include "Core.h"

/* Information about the map */
extern volatile struct Position allPositions[PositionNum];                    // key points
extern volatile struct Edge allEdges[EdgeNum];                                // simple way
extern volatile struct Section allSections[SectionNum];                       // section contains points and edges
extern volatile struct InterSection allInterSections[InterSectionNum];        // interpart between sections
extern volatile struct Path allPaths[InterSectionNum][InterSectionNum];       // pre calculated paths between intersections
extern volatile struct Position TransformPosition;                            // the position used to avoid circle

/* Information about the game */
extern volatile struct RoundInfo roundInformation;
extern volatile struct CarInfo CarAinformation;
extern volatile struct CarInfo CarBinformation;
extern volatile struct PassengerInfo passengers[MaxPassengerNum];

/**************************************** Edge Locate Function ****************************************/
char inEdge_0(int x, int y)
{
	return (y <= 1.73 * x - 142.2 && y >= 1.67 * x - 166.4 && y <= -0.57 * x + 90.0 && y >= -0.57 * x + 50)
		|| (y <= 1.67 * x - 166.4 && x <= 131 && (x - 131.3) * (x - 131.3) + (y - 55) * (y - 55) >= 1225);
}

char inEdge_1(int x, int y)
{
	return (x >= 131.3 && x <= 235 && y >= -15 && y <= 20)
		|| (x >= 235 && x <= 255 && y >= -15 && y <= -x + 270 && (x - 235) * (x - 235) + (y - 35) * (y - 35) >= 225)
	  || (x >= 255 && y <= -x + 270 && (x - 255) * (x - 255) + (y - 15) * (y - 15) <= 900);
}

char inEdge_2(int x, int y)
{
	return (x >= 250 && x <= 285 && y >= 35 && y <= 68)
		|| (y >= 15 && y <= 35 && x <= 285 && y >= -x + 270 && (x - 235) * (x - 235) + (y - 35) * (y - 35) >= 225)
	  || (y >= -x + 270 && y <= 15 && (x - 255) * (x - 255) + (y - 15) * (y - 15) <= 900);
}

char inEdge_3(int x, int y)
{
	return (y <= 1.73 * x - 142.2 && y >= 1.67 * x - 166.4 && y <= -0.57 * x + 130 && y >= -0.57 * x + 90.0)
		|| (y <= 1.67 * x - 166.4 && x <= 131 && (x - 131.2) * (x - 131.2) + (y - 54.8) * (y - 54.8) <= 1225);
}

char inEdge_4(int x, int y)
{
	return (x >= 131 && x <= 215 && y >= 20 && y <= 50)
		|| (x >= 215 && x <= 235 && y >= 20 && y <= -x + 270)
	  || (x >= 235 && y <= -x + 270 && (x - 235) * (x - 235) + (y - 35) * (y - 35) <= 225);
}

char inEdge_5(int x, int y)
{
	return (x >= 215 && x <= 250 && y >= 55 && y <= 68)
		|| (y >= 35 && y <= 55 && x <= 250 && y >= -x + 270)
	  || (y <= 35 && y >= -x + 270 && (x - 235) * (x - 235) + (y - 35) * (y - 35) <= 225);
}

char inEdge_6(int x, int y)
{
	return y >= x - 132 && y <= x - 50 && y >= -x + 275 && y <= -x + 324;
}

char inEdge_7(int x, int y)
{
	return y >= x - 132 && y <= x - 50 && y >= -x + 324 && y <= -x + 365;
}

char inEdge_8(int x, int y)
{
	return x >= 240 && x <= 285 && y >= 120 && y <= 184;
}

char inEdge_9(int x, int y)
{
	return y >= 184 && y <= 2.43 * x - 386.2 && (x - 235) * (x - 235) + (y - 184) * (y - 184) < 3025;
}

char inEdge_10(int x, int y)
{
	return y >= -x + 420 && y >= 2.43 * x - 386.2 && y <= x && (x - 235) * (x - 235) + (y - 184) * (y - 184) < 3025;
}

char inEdge_11(int x, int y)
{
	return y <= x && y >= x - 50 && x + y >= 373 && x + y <= 420;
}

char inEdge_12(int x, int y)
{
	return y <= x && y >= x - 50 && x + y >= 170 && x + y <= 274;
}

char inEdge_13(int x, int y)
{
	return inEdge_12(y, x);
}

char inEdge_14(int x, int y)
{
	return inEdge_11(y, x);
}

char inEdge_15(int x, int y)
{
	return inEdge_10(y, x);
}

char inEdge_16(int x, int y)
{
	return inEdge_9(y, x);
}

char inEdge_17(int x, int y)
{
	return inEdge_8(y, x);
}
char inEdge_18(int x, int y)
{
	return inEdge_7(y, x);
}
char inEdge_19(int x, int y)
{
	return inEdge_6(y, x);
}

char inEdge_20(int x, int y)
{
	return inEdge_5(y, x);
}

char inEdge_21(int x, int y)
{
	return inEdge_4(y, x);
}
char inEdge_22(int x, int y)
{
	return inEdge_3(y, x);
}

char inEdge_23(int x, int y)
{
	return inEdge_2(y, x);
}

char inEdge_24(int x, int y)
{
	return inEdge_1(y, x);
}

char inEdge_25(int x, int y)
{
	return inEdge_0(y, x);
}

/**************************************** Dashed Area Judgement ****************************************/
char inDashed_0(volatile struct Position *p)
{
	return p->is_InSection && p->curSection == &allSections[0] && p->X < 205;
}

char inDashed_1(volatile struct Position *p)
{
	return p->is_InSection && p->curSection == &allSections[1] && p->X > 165;
}

char inDashed_2(volatile struct Position *p)
{
	return p->is_InSection && p->curSection == &allSections[10] && p->Y < 205;
}

char inDashed_3(volatile struct Position *p)
{
	return p->is_InSection && p->curSection == &allSections[11] && p->Y > 165;
}

char inDashed(volatile struct Position *p)
{
	if (inDashed_0(p)) return 1;
	if (inDashed_1(p)) return 2;
	if (inDashed_2(p)) return 3;
	if (inDashed_3(p)) return 4;
	return 0;
}

/**************************************** InterSection Locate Function ****************************************/
char inInterSection_0(int x, int y)
{
	return (x - 50) * (x - 50) + (y - 50) * (y - 50) < 3700
		&& !inEdge_0(x, y) && !inEdge_3(x, y) && !inEdge_12(x, y) && !inEdge_13(x, y) && !inEdge_22(x, y) && !inEdge_25(x, y);
}

char inInterSection_1(int x, int y)
{
	return x + y > 274 && x + y < 374 && y > x - 50 && y < x + 50;
}

char inInterSection_2(int x, int y)
{
	return y > 68 && y < 120 && x < 285 && y < x - 132;
}

char inInterSection_3(int x, int y)
{
	return inInterSection_2(y, x);
}

/**************************************** Explicit InterSection Locate Function for avoiding enCar ****************************************/
char inInterSection_0_explicit(int x, int y)
{
	return (x - 50) * (x - 50) + (y - 50) * (y - 50) < 2500 && (x - 50) * (x - 50) + (y - 50) * (y - 50) > 100;
}

char inInterSection_1_explicit(int x, int y)
{
	return x + y > 274 && x + y < 374 && y > x - 50 && y < x + 50 
		&& (x - 212) * (x - 212) + (y - 162) * (y - 162) > 225 && (x - 112) * (x - 112) + (y - 162) * (y - 162) > 225 
	  && (x - 162) * (x - 162) + (y - 112) * (y - 112) > 225 && (x - 162) * (x - 162) + (y - 212) * (y - 212) > 225;
}

char inInterSection_2_explicit(int x, int y)
{
	return y > 68 && y < 120 && x < 270 && y < x - 132 && x + y > 296;
}

char inInterSection_3_explicit(int x, int y)
{
	return inInterSection_2_explicit(y, x);
}

void init(void)
{
	/* Generate all key positions */
	set_position(&allPositions[0] , 86 , 29 , PositionStart + 0 );  // change back
	set_position(&allPositions[1] , 118, 12 , PositionStart + 1 );
	set_position(&allPositions[2] , 255, 14 , PositionStart + 2 );
	set_position(&allPositions[3] , 260, 80 , PositionStart + 3 );  // change front
	set_position(&allPositions[4] , 85 , 55 , PositionStart + 4 );  // change front
	set_position(&allPositions[5] , 122, 32 , PositionStart + 5 );
	set_position(&allPositions[6] , 236, 34 , PositionStart + 6 );
	set_position(&allPositions[7] , 239, 75 , PositionStart + 7 );  // change back
	set_position(&allPositions[8] , 230, 80 , PositionStart + 8 );  // change front
	set_position(&allPositions[9] , 246, 94 , PositionStart + 9 );  // change back
	set_position(&allPositions[10], 260, 105, PositionStart + 10);  // change front
	set_position(&allPositions[11], 260, 184, PositionStart + 11);
	set_position(&allPositions[12], 245, 207, PositionStart + 12);
	set_position(&allPositions[13], 218, 203, PositionStart + 13);
	set_position(&allPositions[14], 184, 169, PositionStart + 14);  // change back
	set_position(&allPositions[15], 182, 156, PositionStart + 15);  // change front
	set_position(&allPositions[16], 170, 140, PositionStart + 16);  // change back
	set_position(&allPositions[17], 152, 138, PositionStart + 17);  // change front
	set_position(&allPositions[18], 82 , 68 , PositionStart + 18);  // change back
	set_position(&allPositions[19], 185, 20 , PositionStart + 19);  // dashed transform point
	set_position(&allPositions[20], 20 , 185, PositionStart + 20);  // dashed transform point
	set_position(&allPositions[21], 67 , 81 , PositionStart + 21);  // change front
	set_position(&allPositions[22], 140, 154, PositionStart + 22);  // change back
	set_position(&allPositions[23], 140, 169, PositionStart + 23);  // change front
	set_position(&allPositions[24], 154, 184, PositionStart + 24);  // change back
	set_position(&allPositions[25], 170, 183, PositionStart + 25);  // change front
	set_position(&allPositions[26], 204, 217, PositionStart + 26);
	set_position(&allPositions[27], 210, 245, PositionStart + 27);
	set_position(&allPositions[28], 187, 260, PositionStart + 28);
	set_position(&allPositions[29], 105, 260, PositionStart + 29);  // change back
	set_position(&allPositions[30], 98 , 240, PositionStart + 30);  // change front
	set_position(&allPositions[31], 83 , 226, PositionStart + 31);  // change back
	set_position(&allPositions[32], 72 , 240, PositionStart + 32);  // change front
	set_position(&allPositions[33], 34 , 236, PositionStart + 33);
	set_position(&allPositions[34], 32 , 122, PositionStart + 34);
	set_position(&allPositions[35], 55 , 85 , PositionStart + 35);  // change back
	set_position(&allPositions[36], 70 , 260, PositionStart + 36);  // change back
	set_position(&allPositions[37], 15 , 256, PositionStart + 37);
	set_position(&allPositions[38], 12 , 118, PositionStart + 38);
	set_position(&allPositions[39], 29 , 85 , PositionStart + 39);  // change front

	/* Generate all simple ways */
	set_edge(&allEdges[0] , &inEdge_0 , EdgeStart + 0 , &allPositions[0] , &allPositions[1] , 38);
	set_edge(&allEdges[1] , &inEdge_1 , EdgeStart + 1 , &allPositions[1] , &allPositions[2] , 120);
	set_edge(&allEdges[2] , &inEdge_2 , EdgeStart + 2 , &allPositions[2] , &allPositions[3] , 50 );
	set_edge(&allEdges[3] , &inEdge_3 , EdgeStart + 3 , &allPositions[5] , &allPositions[4] , 27 );
	set_edge(&allEdges[4] , &inEdge_4 , EdgeStart + 4 , &allPositions[6] , &allPositions[5] , 104);
	set_edge(&allEdges[5] , &inEdge_5 , EdgeStart + 5 , &allPositions[7] , &allPositions[6] , 34 );
	set_edge(&allEdges[6] , &inEdge_6 , EdgeStart + 6 , &allPositions[16], &allPositions[8] , 51 );
	set_edge(&allEdges[7] , &inEdge_7 , EdgeStart + 7 , &allPositions[9] , &allPositions[15], 51 );
	set_edge(&allEdges[8] , &inEdge_8 , EdgeStart + 8 , &allPositions[11], &allPositions[10], 64 );
	set_edge(&allEdges[9] , &inEdge_9 , EdgeStart + 9 , &allPositions[12], &allPositions[11], 26 );
	set_edge(&allEdges[10], &inEdge_10, EdgeStart + 10, &allPositions[13], &allPositions[12], 26 );
	set_edge(&allEdges[11], &inEdge_11, EdgeStart + 11, &allPositions[14], &allPositions[13], 33 );
	set_edge(&allEdges[12], &inEdge_12, EdgeStart + 12, &allPositions[18], &allPositions[17], 74 );
	set_edge(&allEdges[13], &inEdge_13, EdgeStart + 13, &allPositions[22], &allPositions[21], 74 );
	set_edge(&allEdges[14], &inEdge_14, EdgeStart + 14, &allPositions[26], &allPositions[25], 33 );
	set_edge(&allEdges[15], &inEdge_15, EdgeStart + 15, &allPositions[27], &allPositions[26], 26 );
	set_edge(&allEdges[16], &inEdge_16, EdgeStart + 16, &allPositions[28], &allPositions[27], 26 );
	set_edge(&allEdges[17], &inEdge_17, EdgeStart + 17, &allPositions[29], &allPositions[28], 64 );
	set_edge(&allEdges[18], &inEdge_18, EdgeStart + 18, &allPositions[24], &allPositions[30], 51 );
	set_edge(&allEdges[19], &inEdge_19, EdgeStart + 19, &allPositions[31], &allPositions[23], 51 );
	set_edge(&allEdges[20], &inEdge_20, EdgeStart + 20, &allPositions[33], &allPositions[32], 34 );
	set_edge(&allEdges[21], &inEdge_21, EdgeStart + 21, &allPositions[34], &allPositions[33], 104);
	set_edge(&allEdges[22], &inEdge_22, EdgeStart + 22, &allPositions[35], &allPositions[34], 27 );
	set_edge(&allEdges[23], &inEdge_23, EdgeStart + 23, &allPositions[36], &allPositions[37], 50 );
	set_edge(&allEdges[24], &inEdge_24, EdgeStart + 24, &allPositions[37], &allPositions[38], 120);
	set_edge(&allEdges[25], &inEdge_25, EdgeStart + 25, &allPositions[38], &allPositions[39], 38 );

	/* Generate all intersections */
	set_intersection(&allInterSections[0], &inInterSection_0, InterSectionStart + 0);
	set_intersection(&allInterSections[1], &inInterSection_1, InterSectionStart + 1);
	set_intersection(&allInterSections[2], &inInterSection_2, InterSectionStart + 2);
	set_intersection(&allInterSections[3], &inInterSection_3, InterSectionStart + 3);
	
	/* Generate all sections */
	volatile struct Position *positions[MaxPositionsPerSection] = {0}; volatile struct Edge *edges[MaxEdgesPerSection] = {0};
	positions[0] = &allPositions[0]; positions[1] = &allPositions[1]; positions[2] = &allPositions[2]; positions[3] = &allPositions[3];
	edges[0] = &allEdges[0];         edges[1] = &allEdges[1];         edges[2] = &allEdges[2];
	set_section(&allSections[0], SectionStart + 0, 208, positions, edges, &allInterSections[0], &allInterSections[2]);
	
	for (int i = 0; i < MaxPositionsPerSection; i++) positions[i] = 0; for (int i = 0; i < MaxEdgesPerSection; i++) edges[i] = 0;
	positions[0] = &allPositions[7]; positions[1] = &allPositions[6]; positions[2] = &allPositions[5]; positions[3] = &allPositions[4];
	edges[0] = &allEdges[5];         edges[1] = &allEdges[4];         edges[2] = &allEdges[3];
	set_section(&allSections[1], SectionStart + 1, 165, positions, edges, &allInterSections[2], &allInterSections[0]);
	
	for (int i = 0; i < MaxPositionsPerSection; i++) positions[i] = 0; for (int i = 0; i < MaxEdgesPerSection; i++) edges[i] = 0;
	positions[0] = &allPositions[16]; positions[1] = &allPositions[8];
	edges[0] = &allEdges[6];
	set_section(&allSections[2], SectionStart + 2, 51, positions, edges, &allInterSections[1], &allInterSections[2]);
	
	for (int i = 0; i < MaxPositionsPerSection; i++) positions[i] = 0; for (int i = 0; i < MaxEdgesPerSection; i++) edges[i] = 0;
	positions[0] = &allPositions[9]; positions[1] = &allPositions[15];
	edges[0] = &allEdges[7];
	set_section(&allSections[3], SectionStart + 3, 51, positions, edges, &allInterSections[2], &allInterSections[1]);
	
	for (int i = 0; i < MaxPositionsPerSection; i++) positions[i] = 0; for (int i = 0; i < MaxEdgesPerSection; i++) edges[i] = 0;
	positions[0] = &allPositions[14]; positions[1] = &allPositions[13]; positions[2] = &allPositions[12]; positions[3] = &allPositions[11]; positions[4] = &allPositions[10];
	edges[0] = &allEdges[11];         edges[1] = &allEdges[10];         edges[2] = &allEdges[9];          edges[3] = &allEdges[8];
	set_section(&allSections[4], SectionStart + 4, 149, positions, edges, &allInterSections[1], &allInterSections[2]);
	
	for (int i = 0; i < MaxPositionsPerSection; i++) positions[i] = 0; for (int i = 0; i < MaxEdgesPerSection; i++) edges[i] = 0;
	positions[0] = &allPositions[18]; positions[1] = &allPositions[17];
	edges[0] = &allEdges[12];
	set_section(&allSections[5], SectionStart + 5, 74, positions, edges, &allInterSections[0], &allInterSections[1]);
	
	for (int i = 0; i < MaxPositionsPerSection; i++) positions[i] = 0; for (int i = 0; i < MaxEdgesPerSection; i++) edges[i] = 0;
	positions[0] = &allPositions[22]; positions[1] = &allPositions[21];
	edges[0] = &allEdges[13];
	set_section(&allSections[6], SectionStart + 6, 74, positions, edges, &allInterSections[1], &allInterSections[0]);
	
	for (int i = 0; i < MaxPositionsPerSection; i++) positions[i] = 0; for (int i = 0; i < MaxEdgesPerSection; i++) edges[i] = 0;
	positions[0] = &allPositions[29]; positions[1] = &allPositions[28]; positions[2] = &allPositions[27]; positions[3] = &allPositions[26]; positions[4] = &allPositions[25];
	edges[0] = &allEdges[17];         edges[1] = &allEdges[16];         edges[2] = &allEdges[15];          edges[3] = &allEdges[14];
	set_section(&allSections[7], SectionStart + 7, 149, positions, edges, &allInterSections[3], &allInterSections[1]);
	
	for (int i = 0; i < MaxPositionsPerSection; i++) positions[i] = 0; for (int i = 0; i < MaxEdgesPerSection; i++) edges[i] = 0;
	positions[0] = &allPositions[24]; positions[1] = &allPositions[30];
	edges[0] = &allEdges[18];
	set_section(&allSections[8], SectionStart + 8, 51, positions, edges, &allInterSections[1], &allInterSections[3]);
	
	for (int i = 0; i < MaxPositionsPerSection; i++) positions[i] = 0; for (int i = 0; i < MaxEdgesPerSection; i++) edges[i] = 0;
	positions[0] = &allPositions[31]; positions[1] = &allPositions[23];
	edges[0] = &allEdges[19];
	set_section(&allSections[9], SectionStart + 9, 51, positions, edges, &allInterSections[3], &allInterSections[1]);
	
	for (int i = 0; i < MaxPositionsPerSection; i++) positions[i] = 0; for (int i = 0; i < MaxEdgesPerSection; i++) edges[i] = 0;
	positions[0] = &allPositions[35]; positions[1] = &allPositions[34]; positions[2] = &allPositions[33]; positions[3] = &allPositions[32];
	edges[0] = &allEdges[22];         edges[1] = &allEdges[21];         edges[2] = &allEdges[20];
	set_section(&allSections[10], SectionStart + 10, 165, positions, edges, &allInterSections[0], &allInterSections[3]);
	
	for (int i = 0; i < MaxPositionsPerSection; i++) positions[i] = 0; for (int i = 0; i < MaxEdgesPerSection; i++) edges[i] = 0;
	positions[0] = &allPositions[36]; positions[1] = &allPositions[37]; positions[2] = &allPositions[38]; positions[3] = &allPositions[39];
	edges[0] = &allEdges[23];         edges[1] = &allEdges[24];         edges[2] = &allEdges[25];
	set_section(&allSections[11], SectionStart + 11, 208, positions, edges, &allInterSections[3], &allInterSections[0]);
	
	/* Generate all paths */
	allPaths[0][0].length = allPaths[1][1].length = allPaths[2][2].length = allPaths[3][3].length = 0;
	volatile struct Section *sections[MaxSectionsPerPath] = {0};
	sections[0] = &allSections[5];
	set_path(&allPaths[0][1], 74, sections);
	allPaths[0][1].key_points[0] = &allPositions[18]; allPaths[0][1].key_points[1] = &allPositions[17];
	
	for (int i = 0; i < MaxSectionsPerPath; i++) sections[i] = 0;
	sections[0] = &allSections[5]; sections[1] = &allSections[2];
	set_path(&allPaths[0][2], 165, sections);
	allPaths[0][2].key_points[0] = &allPositions[0]; allPaths[0][2].key_points[1] = &allPositions[1];
	allPaths[0][2].key_points[2] = &allPositions[2]; allPaths[0][2].key_points[3] = &allPositions[3];

	for (int i = 0; i < MaxSectionsPerPath; i++) sections[i] = 0;
	sections[0] = &allSections[10];
	set_path(&allPaths[0][3], 165, sections);
	allPaths[0][3].key_points[0] = &allPositions[35]; allPaths[0][3].key_points[1] = &allPositions[34];
	allPaths[0][3].key_points[2] = &allPositions[33]; allPaths[0][3].key_points[3] = &allPositions[32];

	for (int i = 0; i < MaxSectionsPerPath; i++) sections[i] = 0;
	sections[0] = &allSections[6];
	set_path(&allPaths[1][0], 74, sections);
	allPaths[1][0].key_points[0] = &allPositions[22]; allPaths[1][0].key_points[1] = &allPositions[21];

	for (int i = 0; i < MaxSectionsPerPath; i++) sections[i] = 0;
	sections[0] = &allSections[2];
	set_path(&allPaths[1][2], 51, sections);
	allPaths[1][2].key_points[0] = &allPositions[16]; allPaths[1][2].key_points[1] = &allPositions[8];

	for (int i = 0; i < MaxSectionsPerPath; i++) sections[i] = 0;
	sections[0] = &allSections[8];
	set_path(&allPaths[1][3], 51, sections);
	allPaths[1][3].key_points[0] = &allPositions[24]; allPaths[1][3].key_points[1] = &allPositions[30];

	for (int i = 0; i < MaxSectionsPerPath; i++) sections[i] = 0;
	sections[0] = &allSections[1];
	set_path(&allPaths[2][0], 165, sections);
	allPaths[2][0].key_points[0] = &allPositions[7]; allPaths[2][0].key_points[1] = &allPositions[6];
	allPaths[2][0].key_points[2] = &allPositions[5]; allPaths[2][0].key_points[3] = &allPositions[4];

	for (int i = 0; i < MaxSectionsPerPath; i++) sections[i] = 0;
	sections[0] = &allSections[3];
	set_path(&allPaths[2][1], 51, sections);
	allPaths[2][1].key_points[0] = &allPositions[9]; allPaths[2][1].key_points[1] = &allPositions[15];

	for (int i = 0; i < MaxSectionsPerPath; i++) sections[i] = 0;
	sections[0] = &allSections[3]; sections[1] = &allSections[8];
	set_path(&allPaths[2][3], 173, sections);
	allPaths[2][3].key_points[0] = &allPositions[9]; allPaths[2][3].key_points[1] = &allPositions[30];

	for (int i = 0; i < MaxSectionsPerPath; i++) sections[i] = 0;
	sections[0] = &allSections[9]; sections[1] = &allSections[6];
	set_path(&allPaths[3][0], 165, sections);
	allPaths[3][0].key_points[0] = &allPositions[36]; allPaths[3][0].key_points[1] = &allPositions[37];
	allPaths[3][0].key_points[2] = &allPositions[38]; allPaths[3][0].key_points[3] = &allPositions[39];

	for (int i = 0; i < MaxSectionsPerPath; i++) sections[i] = 0;
	sections[0] = &allSections[9];
	set_path(&allPaths[3][1],  51, sections);
	allPaths[3][1].key_points[0] = &allPositions[31]; allPaths[3][1].key_points[1] = &allPositions[23];

	for (int i = 0; i < MaxSectionsPerPath; i++) sections[i] = 0;
	sections[0] = &allSections[9]; sections[1] = &allSections[2];
	set_path(&allPaths[3][2], 173, sections);
	allPaths[3][2].key_points[0] = &allPositions[31]; allPaths[3][2].key_points[1] = &allPositions[8];
	
	for (int i = 0; i < PositionNum; i++) locate(&allPositions[i]);
}

char locate(volatile struct Position *p)
{
	int x = p->X, y = p->Y;
	if (x < 0 || x > 290 || y < 0 || y > 290) return 0;
	for (int i = 0; i < EdgeNum; i++)
	{
		if (allEdges[i].in_Edge(x, y))
		{
			p->curEdge = &allEdges[i];
			break;
		}
	}
	if (p->curEdge)
	{
		for (int i = 0; i < SectionNum; i++)
		{
			if (in_Section(&allSections[i], x, y))
			{
				p->is_InSection = 1;
				p->curSection = &allSections[i];
				p->curInterSection = 0;
				return 1;
			}
		}
	}
	for (int i = 0; i < InterSectionNum; i++)
	{
		if (allInterSections[i].in_InterSection(x, y))
		{
			p->is_InSection = 0;
			p->curInterSection = &allInterSections[i];
			p->curSection = 0;
			p->curEdge = 0;
			return 1;
		}
	}
	return 0;
}

int calculate_length(volatile struct Position *points[MaxPositionsPerPath])
{
	int length = 0;
	for (int i = 1; i < MaxPositionsPerPath; i++)
	{
		if (!points[i]) break;
		length += get_distance(points[i - 1], points[i]);
		if (points[i + 1])  // consider the time-cosuming turning angle
		{
			float angle = get_angle(points[i - 1], points[i], points[i], points[i + 1]);
			length += angle / 3.14 * WeightForAngle;
		}
	}
	return length;
}

char get_nearest_path(volatile struct Path *path, volatile struct Position start_pos, volatile struct Position *end_pos)
{
	//SerialPrintNewChar("in get_nearest_path111:\nstart_pos\n", &huart1);
	//SerialPrintPoint(start_pos, &huart1);
	
	clear_path(path);
	char flag1 = locate(&start_pos);
	char flag2 = locate(end_pos);
	if (!flag1 || !flag2) return 0;
	int length = 0, pos_size = 0;
	//SerialPrintNewChar("in get_nearest_path222:\nstart_pos\n", &huart1);
	//SerialPrintPoint(start_pos, &huart1);
	if (start_pos.is_InSection && end_pos->is_InSection && start_pos.curSection == end_pos->curSection)  // In the same section?
	{
		int i, j;  // Get the position of two points
		for (i = 0; i < MaxEdgesPerSection; i++)
		{
			if (start_pos.curSection->edges[i] == start_pos.curEdge) break;
		}
		for (j = 0; j < MaxEdgesPerSection; j++)
		{
			if (end_pos->curSection->edges[j] == end_pos->curEdge) break;
		}
		
		if (i < j || (i == j && dot_product(start_pos.curEdge->start, start_pos.curEdge->end, &start_pos, end_pos) > 0))  // start_pos is before end_pos, can go directly
		{
			int m;
			for (m = 0; m < MaxPositionsPerSection; m++)
			{
				if (start_pos.curSection->positions[m] == start_pos.curEdge->end) break;
			}
			for (; start_pos.curSection->positions[m] != end_pos->curEdge->end; m++)
			{
				path->key_points[pos_size++] = start_pos.curSection->positions[m];
			}
			length -= start_pos.curSection->edges[i]->length; length -= start_pos.curSection->edges[j]->length;  // pre-processing, avoid double adding
			for (; i <= j; i++)
			{
				length += start_pos.curSection->edges[i]->length;
			}
			path->key_points[pos_size++] = end_pos;
			length += get_distance(&start_pos, path->key_points[0]);
			length += get_distance(end_pos, path->key_points[--pos_size]);
			path->length = length;
			return path->key_points[0] != 0;
		}
	}
	//SerialPrintNewChar("in get_nearest_path333:\nstart_pos\n", &huart1);
	//SerialPrintPoint(start_pos, &huart1);
	volatile struct InterSection *start_nearest_intersection = 0, *end_nearest_intersection = 0;
	// Determine the main part of the path, which is pre-calculated in &allPaths.
	start_nearest_intersection = start_pos.is_InSection ? start_pos.curSection->end_intersection : start_pos.curInterSection;
	end_nearest_intersection = end_pos->is_InSection ? end_pos->curSection->start_intersection : end_pos->curInterSection;
	volatile struct Path *temp_path = &allPaths[start_nearest_intersection->name - InterSectionStart][end_nearest_intersection->name - InterSectionStart];
	// Determine the transformation parts of the path.
	int i, j, section_size = 0;
	// i and j identify the ith and jth element in positions and edges corresponding to the pos.
	// Just in order to calculate length easier.
	if (start_pos.is_InSection)
	{
		path->sections[section_size++] = start_pos.curSection;
		for (i = 0; i < MaxEdgesPerSection; i++)
		{
			if (start_pos.curSection->edges[i] == start_pos.curEdge) break;
		}
		for (j = 0; j < MaxPositionsPerSection; j++)
		{
			if (start_pos.curSection->positions[j] == start_pos.curEdge->end) break;
		}
		for (; j < MaxPositionsPerSection; j++)
		{
			if (!start_pos.curSection->positions[j]) break;
			path->key_points[pos_size++] = start_pos.curSection->positions[j];
		}
	}
	//SerialPrintNewChar("in get_nearest_path444:\nstart_pos\n", &huart1);
	//SerialPrintPoint(start_pos, &huart1);
	if (temp_path->length > 0)
	{
		for (i = 0; i < MaxPositionsPerPath; i++)
		{
			if (!temp_path->key_points[i]) break;
			path->key_points[pos_size++] = temp_path->key_points[i];
		}
		for (i = 0; i < MaxSectionsPerPath; i++)
		{
			if (!temp_path->sections[i]) break;
			path->sections[section_size++] = temp_path->sections[i];
		}
	}
	//SerialPrintNewChar("in get_nearest_path555:\nstart_pos\n", &huart1);
	//SerialPrintPoint(start_pos, &huart1);
	if (end_pos->is_InSection)
	{
		path->sections[section_size++] = end_pos->curSection;
		for (i = 0; i < MaxEdgesPerSection; i++)
		{
			if (end_pos->curSection->edges[i] == end_pos->curEdge) break;
		}
		for (j = 0; j < MaxPositionsPerSection; j++)
		{
			if (end_pos->curSection->positions[j] == end_pos->curEdge->start) break;
		}
		for (int k = 0; k <= j; k++)
		{
			path->key_points[pos_size++] = end_pos->curSection->positions[k];
		}
	}
	//SerialPrintNewChar("in get_nearest_path666:\nstart_pos\n", &huart1);
	//SerialPrintPoint(start_pos, &huart1);
	path->key_points[pos_size++] = end_pos;
	
	cross_dashed(path, &start_pos);
	
	//SerialPrintNewChar("cross dash\n", &huart1);
	
	avoid_circle(path, &start_pos);
	
	//SerialPrintNewChar("avoid circle\n", &huart1);
	//SerialPrintNewChar("in get_nearest_path777:\nstart_pos\n", &huart1);
	//SerialPrintPoint(start_pos, &huart1);
	length += get_distance(&start_pos, path->key_points[0]);
	length += calculate_length(path->key_points);
	path->length = length;
	//SerialPrintNewChar("ending get_nearest_path:\nstart_pos\n", &huart1);
	//SerialPrintPoint(start_pos, &huart1);
	for (int i = 0; i < MaxPositionsPerPath; i++)
	{
		if (!path->key_points[i]) break;
		//SerialPrintNewChar("in get_nearest_path:\n",&huart1);
		//SerialPrintNum(i, &huart1);
		//SerialPrintPoint(*path->key_points[i], &huart1);
	}
	return path->key_points[0] != 0;
}

void cross_dashed(volatile struct Path *path, volatile struct Position *start_pos)
{
	for (int i = -1; i < MaxPositionsPerPath; i++)
	{
		int flag = 0;
		if (i == -1)
		{
			flag = inDashed(start_pos);
		}
		else
		{
			if (!path->key_points[i]) return;
			flag = inDashed(path->key_points[i]);
		}
		if (!flag) continue;
		switch (flag)
		{
			case 1:
				if (path->key_points[i + 1] == &allPositions[2] && path->key_points[i + 2] == &allPositions[3] 
					&& path->key_points[i + 3] == &allPositions[7] && path->key_points[i + 4] == &allPositions[6] 
				  && path->key_points[i + 5]->X < 208)
				{
					if (path->key_points[i + 5]->X > 165) allPositions[19].X = path->key_points[i + 5]->X + 2;
					else allPositions[19].X = 170;
					path->key_points[i + 1] = &allPositions[19];
					for (int j = i + 2; j < MaxPositionsPerPath; j++)
					{
						if (!path->key_points[j]) break;
						if (j + 3 >= MaxPositionsPerPath)
						{
							path->key_points[j] = 0;
							break;
						}
						path->key_points[j] = path->key_points[j + 3];
					}
				}
				return;
			case 2:
				if (path->key_points[i + 1] == &allPositions[5] && path->key_points[i + 2] == &allPositions[4] 
					&& path->key_points[i + 3] == &allPositions[0] && path->key_points[i + 4] == &allPositions[1] 
				  && path->key_points[i + 5]->X > 162)
				{
					if (path->key_points[i + 5]->X < 205) allPositions[19].X = path->key_points[i + 5]->X - 2;
					else allPositions[19].X = 200;
					path->key_points[i + 1] = &allPositions[19];
					for (int j = i + 2; j < MaxPositionsPerPath; j++)
					{
						if (!path->key_points[j]) break;
						if (j + 3 >= MaxPositionsPerPath)
						{
							path->key_points[j] = 0;
							break;
						}
						path->key_points[j] = path->key_points[j + 3];
					}
				}
				return;
			case 3:
				if (path->key_points[i + 1] == &allPositions[33] && path->key_points[i + 2] == &allPositions[32] 
					&& path->key_points[i + 3] == &allPositions[36] && path->key_points[i + 4] == &allPositions[37] 
				  && path->key_points[i + 5]->Y < 208)
				{
					if (path->key_points[i + 5]->Y > 165) allPositions[20].Y = path->key_points[i + 5]->Y + 2;
					else allPositions[20].Y = 170;
					path->key_points[i + 1] = &allPositions[20];
					for (int j = i + 2; j < MaxPositionsPerPath; j++)
					{
						if (!path->key_points[j]) break;
						if (j + 3 >= MaxPositionsPerPath)
						{
							path->key_points[j] = 0;
							break;
						}
						path->key_points[j] = path->key_points[j + 3];
					}
				}
				return;
			case 4:
				if (path->key_points[i + 1] == &allPositions[38] && path->key_points[i + 2] == &allPositions[39] 
					&& path->key_points[i + 3] == &allPositions[35] && path->key_points[i + 4] == &allPositions[34] 
				  && path->key_points[i + 5]->Y > 162)
				{
					if (path->key_points[i + 5]->Y < 205) allPositions[20].Y = path->key_points[i + 5]->Y - 2;
					else allPositions[20].Y = 200;
					path->key_points[i + 1] = &allPositions[20];
					for (int j = i + 2; j < MaxPositionsPerPath; j++)
					{
						if (!path->key_points[j]) break;
						if (j + 3 >= MaxPositionsPerPath)
						{
							path->key_points[j] = 0;
							break;
						}
						path->key_points[j] = path->key_points[j + 3];
					}
				}
				return;
			default:
				break;
		}
	}
}

void avoid_circle(volatile struct Path *path, volatile struct Position *start_pos)
{
	int flag;
	struct Position circle;
	circle.X = circle.Y = 50;
	if (ifToAvoidCircle_extend(start_pos, path->key_points[0], &circle, 15, 20, &TransformPosition))
	{
		for (flag = 0; flag < MaxPositionsPerPath; flag++)
		{
			if (!path->key_points[flag]) break;
		}
		for (; flag > 0; flag--)
		{
			path->key_points[flag] = path->key_points[flag - 1];
		}
		path->key_points[0] = &TransformPosition;
		return;
	}
	for (int i = 0; i < MaxPositionsPerPath - 1; i++)
	{
		if (!path->key_points[i + 1]) return;
		if (ifToAvoidCircle_extend(path->key_points[i], path->key_points[i + 1], &circle, 15, 20, &TransformPosition))
		{
			for (flag = i + 1; flag < MaxPositionsPerPath; flag++)
			{
				if (!path->key_points[flag]) break;
			}
			for (; flag > i + 1; flag--)
			{
				path->key_points[flag] = path->key_points[flag - 1];
			}
			path->key_points[i + 1] = &TransformPosition;
			return;
		}
	}
}

char Searching_Passenger()
{
	if (myCar == 'A')
	{
		int Num = -1;
		float max_point = 0;
		volatile struct Path path_to_passenger;
		volatile struct Position myp = CarAinformation.pos;
		for (int i = 0; i < getPassengersNum(); i++)
		{
			if (passengers[i].State == Not_Abord)
			{
				clear_path(&path_to_passenger);
				if (!get_nearest_path(&path_to_passenger, myp, &passengers[i].start_pos)) continue;
				
				if ((float)passengers[i].point / (float)(passengers[i].start_to_end.length + path_to_passenger.length + 1e-2) > max_point)
				{
					Num = i;
					max_point = (float)passengers[i].point / (float)(passengers[i].start_to_end.length + path_to_passenger.length + 1e-2);
				}
			}
		}

		//SerialPrintNewChar("search& num:\n",&huart1);
		//SerialPrintNum(Num, &huart1);

		if (Num == -1) return 0;
		CarAinformation.passenger_num = Num;
		int pos_size = 0, section_size = 0;
		clear_path(&path_to_passenger);
		
		if (!get_nearest_path(&path_to_passenger, myp, &passengers[Num].start_pos)) return 0;
		
		for (int i = 0; i < MaxPositionsPerPath; i++)
		{
			if (!path_to_passenger.key_points[i]) break;
			CarAinformation.curPath.key_points[pos_size++] = path_to_passenger.key_points[i];
			//SerialPrintNewChar("our next path:\n",&huart1);
			//SerialPrintNum(i, &huart1);
			//SerialPrintPoint(*path_to_passenger.key_points[i], &huart1);
		}
		if (!get_nearest_path(&passengers[CarAinformation.passenger_num].start_to_end, passengers[CarAinformation.passenger_num].start_pos, 
													&passengers[CarAinformation.passenger_num].end_pos)) return 0;
		for (int i = 0; i < MaxPositionsPerPath; i++)
		{
			if (!passengers[CarAinformation.passenger_num].start_to_end.key_points[i]) break;
			CarAinformation.curPath.key_points[pos_size++] = passengers[CarAinformation.passenger_num].start_to_end.key_points[i];
			//SerialPrintNewChar("our next path:\n",&huart1);
			//SerialPrintNum(i, &huart1);
			//SerialPrintPoint(*passengers[CarAinformation.passenger_num].start_to_end.key_points[i], &huart1);
		}
		
		for (int i = 0; i < MaxSectionsPerPath; i++)
		{
			if (!path_to_passenger.sections[i]) break;
			CarAinformation.curPath.sections[section_size++] = path_to_passenger.sections[i];
		}
		if ((passengers[CarAinformation.passenger_num].start_pos.is_InSection) && !(passengers[CarAinformation.passenger_num].start_pos.is_InSection && passengers[CarAinformation.passenger_num].end_pos.is_InSection 
			&& passengers[CarAinformation.passenger_num].start_pos.curSection == passengers[CarAinformation.passenger_num].end_pos.curSection))
		{
			CarAinformation.curPath.sections[section_size++] = passengers[CarAinformation.passenger_num].start_pos.curSection;
		}
		for (int i = 0; i < MaxSectionsPerPath; i++)
		{
			if (!passengers[CarAinformation.passenger_num].start_to_end.sections[i]) break;
			CarAinformation.curPath.sections[section_size++] = passengers[CarAinformation.passenger_num].start_to_end.sections[i];
		}
		CarAinformation.curPath.length = path_to_passenger.length + passengers[CarAinformation.passenger_num].start_to_end.length;
		CarAinformation.point_per_cm = max_point;
		return CarAinformation.curPath.length > 0;
	}
	else if (myCar == 'B')
	{
		int Num = -1;
		float max_point = 0;
		volatile struct Path path_to_passenger;
		volatile struct Position myp = CarBinformation.pos;
		for (int i = 0; i < getPassengersNum(); i++)
		{
			if (passengers[i].State == Not_Abord)
			{
				clear_path(&path_to_passenger);
				if (!get_nearest_path(&path_to_passenger, myp, &passengers[i].start_pos)) continue;
				
				if ((float)passengers[i].point / (float)(passengers[i].start_to_end.length + path_to_passenger.length + 1e-2) > max_point)
				{
					Num = i;
					max_point = (float)passengers[i].point / (float)(passengers[i].start_to_end.length + path_to_passenger.length + 1e-2);
				}
			}
		}

		//SerialPrintNewChar("search& num:\n",&huart1);
		//SerialPrintNum(Num, &huart1);

		if (Num == -1) return 0;
		CarBinformation.passenger_num = Num;
		int pos_size = 0, section_size = 0;
		clear_path(&path_to_passenger);
		
		if (!get_nearest_path(&path_to_passenger, myp, &passengers[Num].start_pos)) return 0;
		
		for (int i = 0; i < MaxPositionsPerPath; i++)
		{
			if (!path_to_passenger.key_points[i]) break;
			CarBinformation.curPath.key_points[pos_size++] = path_to_passenger.key_points[i];
			//SerialPrintNewChar("our next path:\n",&huart1);
			//SerialPrintNum(i, &huart1);
			//SerialPrintPoint(*path_to_passenger.key_points[i], &huart1);
		}
		if (!get_nearest_path(&passengers[CarBinformation.passenger_num].start_to_end, passengers[CarBinformation.passenger_num].start_pos, 
													&passengers[CarBinformation.passenger_num].end_pos)) return 0;
		for (int i = 0; i < MaxPositionsPerPath; i++)
		{
			if (!passengers[CarBinformation.passenger_num].start_to_end.key_points[i]) break;
			CarBinformation.curPath.key_points[pos_size++] = passengers[CarBinformation.passenger_num].start_to_end.key_points[i];
			//SerialPrintNewChar("our next path:\n",&huart1);
			//SerialPrintNum(i, &huart1);
			//SerialPrintPoint(*passengers[CarBinformation.passenger_num].start_to_end.key_points[i], &huart1);
		}
		
		for (int i = 0; i < MaxSectionsPerPath; i++)
		{
			if (!path_to_passenger.sections[i]) break;
			CarBinformation.curPath.sections[section_size++] = path_to_passenger.sections[i];
		}
		if ((passengers[CarBinformation.passenger_num].start_pos.is_InSection) && !(passengers[CarBinformation.passenger_num].start_pos.is_InSection && passengers[CarBinformation.passenger_num].end_pos.is_InSection 
			&& passengers[CarBinformation.passenger_num].start_pos.curSection == passengers[CarBinformation.passenger_num].end_pos.curSection))
		{
			CarBinformation.curPath.sections[section_size++] = passengers[CarBinformation.passenger_num].start_pos.curSection;
		}
		for (int i = 0; i < MaxSectionsPerPath; i++)
		{
			if (!passengers[CarBinformation.passenger_num].start_to_end.sections[i]) break;
			CarBinformation.curPath.sections[section_size++] = passengers[CarBinformation.passenger_num].start_to_end.sections[i];
		}
		CarBinformation.curPath.length = path_to_passenger.length + passengers[CarBinformation.passenger_num].start_to_end.length;
		CarBinformation.point_per_cm = max_point;
		return CarBinformation.curPath.length > 0;
	}
	return 0;
}
