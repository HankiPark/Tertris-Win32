#ifndef DRAWING_H
#define DRAWING_H

#include "setting.h"
#include "Blocks.h"

class Drawing {
public:
	Drawing(HDC hdc, HWND hwnd);
	~Drawing();
	void isGameOver();
	void drawBackground(int game_mode);
	void drawScore();
	void drawBlock(double h, double w, int color);
	void drawScreen();
	void drawNextBlock();
	BLOCKMAP screen;
	int nextBlock;
	int score;
	Blocks* block;
protected:
	WCHAR word[1024];
	HDC hdc;
	HWND hwnd;
	PII init;
	
	//BLOCKMAP screen;
};

#endif
