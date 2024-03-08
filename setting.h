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

#define WIDTH_LINE		10
#define HEIGHT_LINE		20

#define WHITE_SPACE 50

#define INTERVAL	10
#define RADIUS		(INTERVAL / 2)

#define POS(x)		(WHITE_SPACE + (x) * INTERVAL)

#define PII			pair<int, int>


#define RIGHT		1
#define LEFT		2
#define UP			3
#define DOWN		4

#define BLOCKMAP	vector<vector<int>>

#define OBLOCKCOLOR	1
#define IBLOCKCOLOR	2
#define SBLOCKCOLOR	3
#define ZBLOCKCOLOR	4
#define LBLOCKCOLOR	5
#define JBLOCKCOLOR	6
#define TBLOCKCOLOR	7


#define CLEAN		1
#define DRAW		2
#define LINECLEAN	3



