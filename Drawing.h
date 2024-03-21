#ifndef DRAWING_H
#define DRAWING_H

#include "setting.h"
#include "Blocks.h"

class Drawing {
public:
	Drawing(HDC hdc, HWND hwnd);
	~Drawing();
	void isGameOver();
	void drawBackground(int gameMode);
	void drawAiBackground();
	void drawScore();
	void drawBlock(double h, double w, int color);
	void drawAiBlock(double h, double w, int color);
	void drawScreen();
	void drawAiScreen();
	void drawNextBlock();
	void drawAiNextBlock();
	BLOCKMAP screen;
	BLOCKMAP aiScreen;

	bool pause;
	int nextBlock;
	int aiNextBlock;
	int score;
	int aiScore;
	queue<pair<int, int>> debt;
	queue<pair<int, int>> aiDebt;
	Blocks* block;
protected:
	WCHAR word[1024];
	HDC hdc;
	HWND hwnd;
	PII init;
	RECT playerScore;
	//PAINTSTRUCT ps;
	//BLOCKMAP screen;
};

#endif
