#ifndef DRAWING_H
#define DRAWING_H

#include "setting.h"

class Drawing {
public:
	Drawing(HDC hdc, HWND hwnd);
	~Drawing();

	void drawBackground(int game_mode);
	void drawScore();
	void drawBlock();
	BLOCKMAP screen;
	
protected:
	HDC hdc;
	HWND hwnd;
	PII init;
	//BLOCKMAP screen;
};

#endif
