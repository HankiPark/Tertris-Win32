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
	
	// ���� y��ǥ , ���� x��ǥ, ��������, ȸ�� Ƚ��
	vector<int> start;
	vector<int> now;
	DWORD speed;
	DWORD prevTime;
	
};


#endif