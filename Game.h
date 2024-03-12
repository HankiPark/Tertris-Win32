#ifndef GAME_H
#define GAME_H

#include "setting.h"
#include "Drawing.h"

class Game {
public:
	Game(Drawing& drawing);
	~Game();
	bool move(int input);
	void rotate(int input);
	void fall(int input);
	bool checkCrash();
	void getNewControl();
	void timeUpdate();
	bool isGameOver();
	void updateScreen( int type);
	bool pause;
protected:
	Drawing &drawing;
	
	// 현재 y좌표 , 현재 x좌표, 도형종류, 회전 횟수
	vector<int> start;
	vector<int> now;
	DWORD speed;
	DWORD prevTime;
	
};


#endif