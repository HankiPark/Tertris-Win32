#include <iostream>
#include <string> 
#include <cstdlib> 
#include <ctime>
#include <string.h>
#include <stdio.h>
#include <deque>
#include <algorithm>
#include <Windows.h>
#include <vector>
#include <deque>
using namespace std;

#define WIDTH_LINE		15
#define HEIGHT_LINE		25

#define WHITE_SPACE		50

#define OPTION_BOX		WIDTH_LINE / 2

#define INTERVAL		20
#define RADIUS			(INTERVAL / 2)

#define POS(x)			(WHITE_SPACE + (x) * INTERVAL)

#define AIPOS(x)		(3 * WHITE_SPACE + (x + WIDTH_LINE * 3 / 2) * INTERVAL)

#define PII				pair<int, int>


#define RIGHT			1
#define LEFT			2
#define UP				3
#define DOWN			4

#define BLOCKMAP		vector<vector<int>>

#define OBLOCKCOLOR		1
#define IBLOCKCOLOR		2
#define SBLOCKCOLOR		3
#define ZBLOCKCOLOR		4
#define LBLOCKCOLOR		5
#define JBLOCKCOLOR		6
#define TBLOCKCOLOR		7




#define CLEAN			1
#define DRAW			2
#define LINECLEAR		3

#define SOLOMODE		1
#define	AIMODE			2
