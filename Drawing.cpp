#include "Drawing.h"

Drawing::Drawing(HDC hdc, HWND hwnd) :
	hdc(hdc), hwnd(hwnd)
{
	for (int h = 0; h < HEIGHT_LINE + 1; h++) {
		screen.push_back(vector<int>());
		aiScreen.push_back(vector<int>());
		for (int w = 0; w < WIDTH_LINE + 1; w++) {
			screen[h].push_back(0);
			aiScreen[h].push_back(0);
		}
	}
	block = new Blocks();
	score = 0;
	aiScore = 0;
	nextBlock = rand() % 7 + 1;
	aiNextBlock = rand() % 7 + 1;
	pause = false;
}

void Drawing::drawAiBackground() {
	drawAiScreen();
	drawAiNextBlock();
}

void Drawing::drawBackground(int gameMode) {
	PAINTSTRUCT ps;

	HDC MemDC, tmpDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;

	hdc = BeginPaint(hwnd, &ps);
	GetClientRect(hwnd, &bufferRT);
	MemDC = CreateCompatibleDC(hdc);
	BackBit = CreateCompatibleBitmap(hdc, bufferRT.right, bufferRT.bottom);
	oldBackBit = (HBITMAP)SelectObject(MemDC, BackBit);
	PatBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, PATCOPY);
	tmpDC = hdc;
	hdc = MemDC;
	MemDC = tmpDC;
	
	TextOut(hdc, POS(0), POS(HEIGHT_LINE + 1), L"s : down / a : left / d : right / r : rotate / w : bottommost", lstrlen(L"s : down / a : left / d : right / r : rotate / w : bottommost"));
	drawScreen();
	drawNextBlock();
	drawScore();

	if (gameMode == AIMODE) {
		drawAiBackground();
	}
	
	tmpDC = hdc;
	hdc = MemDC;
	MemDC = tmpDC;
	GetClientRect(hwnd, &bufferRT);
	BitBlt(hdc, 0, 0, bufferRT.right, bufferRT.bottom, MemDC, 0, 0, SRCCOPY);
	SelectObject(MemDC, oldBackBit);
	DeleteObject(BackBit);
	DeleteDC(MemDC); 
	EndPaint(hwnd, &ps);
}

void Drawing::drawScore() {
	wsprintfW(word, L"score : %d", score * 10);
	TextOut(hdc, POS(WIDTH_LINE + OPTION_BOX / 2), POS(HEIGHT_LINE / 3 + 5), word, lstrlen(word));

}

void Drawing::drawNextBlock() {

	BLOCKMAP loc = block->getBlock(nextBlock - 1)[0];
	for (int h = 0; h < 4; h++) {
		for (int w = 0; w < 4; w++) {
			//cout << nextBlock << endl;
			if (loc[h][w] == 0) {
				continue;
			}
			if (nextBlock == OBLOCKCOLOR) {
				drawBlock(HEIGHT_LINE / 3 + h, WIDTH_LINE + OPTION_BOX / 2 + w, nextBlock);
			}
			else if (nextBlock == IBLOCKCOLOR) {
				drawBlock(HEIGHT_LINE / 3 + h + 0.5, WIDTH_LINE + OPTION_BOX / 2 + w, nextBlock);
			}
			else {
				drawBlock(HEIGHT_LINE / 3 + h, WIDTH_LINE + OPTION_BOX / 2 + w - 0.5, nextBlock);
			}	
		}
	}
	
}

void Drawing::drawAiNextBlock() {

	BLOCKMAP loc = block->getBlock(aiNextBlock - 1)[0];
	for (int h = 0; h < 4; h++) {
		for (int w = 0; w < 4; w++) {
			//cout << nextBlock << endl;
			if (loc[h][w] == 0) {
				continue;
			}
			if (aiNextBlock == OBLOCKCOLOR) {
				drawAiBlock(HEIGHT_LINE / 3 + h, WIDTH_LINE + OPTION_BOX / 2 + w, aiNextBlock);
			}
			else if (aiNextBlock == IBLOCKCOLOR) {
				drawAiBlock(HEIGHT_LINE / 3 + h + 0.5, WIDTH_LINE + OPTION_BOX / 2 + w, aiNextBlock);
			}
			else {
				drawAiBlock(HEIGHT_LINE / 3 + h, WIDTH_LINE + OPTION_BOX / 2 + w - 0.5, aiNextBlock);
			}
		}
	}

}

void Drawing::drawBlock(double h, double w, int color) {

	HBRUSH brush = NULL;
	switch (color) {
	case OBLOCKCOLOR:
		brush = CreateSolidBrush(RGB(255, 0, 0));
		break;
	case IBLOCKCOLOR:
		brush = CreateSolidBrush(RGB(255, 127, 39));
		break;
	case SBLOCKCOLOR:
		brush = CreateSolidBrush(RGB(255, 242, 0));
		break;
	case ZBLOCKCOLOR:
		brush = CreateSolidBrush(RGB(34, 177, 76));
		break;
	case LBLOCKCOLOR:
		brush = CreateSolidBrush(RGB(0, 162, 232));
		break;
	case JBLOCKCOLOR:
		brush = CreateSolidBrush(RGB(63, 72, 204));
		break;
	case TBLOCKCOLOR:
		brush = CreateSolidBrush(RGB(128, 128, 255));
		break;
	case TRASHCOLOR:
		brush = CreateSolidBrush(RGB(127, 127, 127));
		break;
	default:
		brush = CreateSolidBrush(RGB(255, 255, 255));
		break;
	}

	HBRUSH border = CreateSolidBrush(RGB(0, 0, 0));
	RECT r = { POS(w), POS(h), POS(w + 1), POS(h + 1) };

	FillRect(hdc, &r, brush);
	FrameRect(hdc, &r, border);

	DeleteObject(brush);
	DeleteObject(border);
	return;
}

void Drawing::drawAiBlock(double h, double w, int color) {

	HBRUSH brush = NULL;
	switch (color) {
	case OBLOCKCOLOR:
		brush = CreateSolidBrush(RGB(255, 0, 0));
		break;
	case IBLOCKCOLOR:
		brush = CreateSolidBrush(RGB(255, 127, 39));
		break;
	case SBLOCKCOLOR:
		brush = CreateSolidBrush(RGB(255, 242, 0));
		break;
	case ZBLOCKCOLOR:
		brush = CreateSolidBrush(RGB(34, 177, 76));
		break;
	case LBLOCKCOLOR:
		brush = CreateSolidBrush(RGB(0, 162, 232));
		break;
	case JBLOCKCOLOR:
		brush = CreateSolidBrush(RGB(63, 72, 204));
		break;
	case TBLOCKCOLOR:
		brush = CreateSolidBrush(RGB(128, 128, 255));
		break;
	case TRASHCOLOR:
		brush = CreateSolidBrush(RGB(127, 127, 127));
		break;
	default:
		brush = CreateSolidBrush(RGB(255, 255, 255));
		break;
	}

	HBRUSH border = CreateSolidBrush(RGB(0, 0, 0));
	RECT r = { AIPOS(w), POS(h), AIPOS(w + 1), POS(h + 1) };

	FillRect(hdc, &r, brush);
	FrameRect(hdc, &r, border);
	DeleteObject(brush);
	DeleteObject(border);
	return;
}

void Drawing::drawScreen() {

	// 게임 틀
	/*HPEN hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, POS(0) - RADIUS, POS(0), NULL);
	LineTo(hdc, POS(0) - RADIUS, POS(HEIGHT_LINE));
	MoveToEx(hdc, POS(WIDTH_LINE) + RADIUS, POS(0), NULL);
	LineTo(hdc, POS(WIDTH_LINE) + RADIUS, POS(HEIGHT_LINE));
	MoveToEx(hdc, POS(0), POS(HEIGHT_LINE), NULL);
	LineTo(hdc, POS(WIDTH_LINE), POS(HEIGHT_LINE));
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);*/
	// 점수판
	TextOut(hdc, POS(WIDTH_LINE + OPTION_BOX / 2), POS(HEIGHT_LINE / 3 - 1), L"Next :", lstrlen(L"Next :"));
	HBRUSH optionBackground = CreateSolidBrush(RGB(0, 0, 0));
	RECT orb = { POS(WIDTH_LINE + OPTION_BOX / 2) , POS(HEIGHT_LINE / 3), POS(WIDTH_LINE + 4 + OPTION_BOX / 2), POS(HEIGHT_LINE / 3 + 4) };
	FrameRect(hdc, &orb, optionBackground);
	DeleteObject(optionBackground);


	for (int i = 0; i < HEIGHT_LINE; i++) {
		for (int j = 0; j < WIDTH_LINE; j++) {
		//	cout << screen[i][j] << " ";
			drawBlock(i, j, screen[i][j]);
		}
	}
}

void Drawing::drawAiScreen() {
	//게임 틀
	/*HPEN hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, AIPOS(0) - RADIUS, POS(0), NULL);
	LineTo(hdc, AIPOS(0) - RADIUS, POS(HEIGHT_LINE));
	MoveToEx(hdc, AIPOS(WIDTH_LINE) + RADIUS, POS(0), NULL);
	LineTo(hdc, AIPOS(WIDTH_LINE) + RADIUS, POS(HEIGHT_LINE));
	MoveToEx(hdc, AIPOS(0), POS(HEIGHT_LINE), NULL);
	LineTo(hdc, AIPOS(WIDTH_LINE), POS(HEIGHT_LINE));
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen); */

	// 점수판
	TextOut(hdc, AIPOS(WIDTH_LINE + OPTION_BOX / 2), POS(HEIGHT_LINE / 3 - 1), L"Next :", lstrlen(L"Next :"));
	HBRUSH optionBackground = CreateSolidBrush(RGB(0, 0, 0));
	RECT orb = { AIPOS(WIDTH_LINE + OPTION_BOX / 2) , POS(HEIGHT_LINE / 3), AIPOS(WIDTH_LINE + 4 + OPTION_BOX / 2), POS(HEIGHT_LINE / 3 + 4) };
	FrameRect(hdc, &orb, optionBackground);
	DeleteObject(optionBackground);

	for (int i = 0; i < HEIGHT_LINE; i++) {
		for (int j = 0; j < WIDTH_LINE; j++) {
			drawAiBlock(i, j, aiScreen[i][j]);
		}
	}
}

void Drawing::isGameOver() {
	cout << "game over" << endl;
	MessageBox(hwnd, L"게임 종료", L"게임 끝!", MB_OK);

}