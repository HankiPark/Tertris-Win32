#ifndef GAME_H
#define GAME_H

#include "setting.h"
#include "Drawing.h"

class Game {
public:
	// 초기 설정
	Game(Drawing& drawing);
	~Game();

	// 플레이어 이동 관련
	bool move(int input);
	void rotate(int input);
	void fall(int input);

	// 블록 충돌 감지
	bool checkCrash();
	// 새로운 블록 
	void getNewControl();
	
	// 시간에 따른 블록 이동
	void timeUpdate();

	// 게임 오버 감지
	bool isGameOver();

	// 화면 값 변경 ( 그리기 / 지우기 / 줄 지우기)
	void updateScreen( int type);
	
	// ai 모드 전용 (처리해야할 벌칙 블록이 있는지 체크)
	void payOff();

	// WM_TIMER 에 따른 값 변경 체크 인수
	bool time;

//	RECT getNowLoc();
protected:
	Drawing &drawing;
	// 플레이어의 시간 관련 스레드
	thread timeThread;
	// 현재 y좌표 , 현재 x좌표, 도형종류, 회전 횟수
	vector<int> start;
	vector<int> now;
	// 플레이어 블록 속도 관련 인수 (millisecond)
	DWORD speed;
	
};


#endif