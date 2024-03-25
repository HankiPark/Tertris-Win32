#ifndef GAME_H
#define GAME_H

#include "setting.h"
#include "Drawing.h"

class Game {
public:
	// �ʱ� ����
	Game(Drawing& drawing);
	~Game();

	// �÷��̾� �̵� ����
	bool move(int input);
	void rotate(int input);
	void fall(int input);

	// ��� �浹 ����
	bool checkCrash();
	// ���ο� ��� 
	void getNewControl();
	
	// �ð��� ���� ��� �̵�
	void timeUpdate();

	// ���� ���� ����
	bool isGameOver();

	// ȭ�� �� ���� ( �׸��� / ����� / �� �����)
	void updateScreen( int type);
	
	// ai ��� ���� (ó���ؾ��� ��Ģ ����� �ִ��� üũ)
	void payOff();

	// WM_TIMER �� ���� �� ���� üũ �μ�
	bool time;

//	RECT getNowLoc();
protected:
	Drawing &drawing;
	// �÷��̾��� �ð� ���� ������
	thread timeThread;
	// ���� y��ǥ , ���� x��ǥ, ��������, ȸ�� Ƚ��
	vector<int> start;
	vector<int> now;
	// �÷��̾� ��� �ӵ� ���� �μ� (millisecond)
	DWORD speed;
	
};


#endif