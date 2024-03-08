#ifndef GAME_H
#define GAME_H

#include "setting.h"
#include "Drawing.h"
#include "Blocks.h"

class Game {
public:
	Game(Drawing& drawing);
	~Game();
	void move(int input);
	void rotate(int input);
	bool checkCrash();
	void getNewControl();
	void timeUpdate();
	void updateScreen( int type);

protected:
	Drawing &drawing;
	Blocks *block;
	// 현재 y좌표 , 현재 x좌표, 도형종류, 회전 횟수
	vector<int> start;
	vector<int> now;
	int speed;
	int prev_time;
};


#endif