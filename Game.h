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
	// ���� y��ǥ , ���� x��ǥ, ��������, ȸ�� Ƚ��
	vector<int> start;
	vector<int> now;
	int speed;
	int prev_time;
};


#endif