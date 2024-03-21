#include <iostream>
#include <string> 
#include <cstdlib> 
#include <ctime>
#include <string.h>
#include <stdio.h>
#include <deque>
#include <algorithm>
#include <Windows.h>
#include <vector>
#include <deque>
#include "setting.h"
#include "Drawing.h"
#include "Blocks.h"
#include "Game.h"
#include "Ai.h"
using namespace std;
// 82 , 45

unsigned int score = 0;
WCHAR word[1024];
unsigned int gameMode = SOLOMODE;
unsigned int game_speed = 1000;
Drawing* drawing;
Game* game;
Ai* ai;
thread playerThread;
thread computerThread;
//Blocks* block;
RECT playerOrb = { POS(0) , POS(0), POS(WIDTH_LINE), POS(HEIGHT_LINE)};
RECT computerOrb = { AIPOS(0), POS(0), AIPOS(WIDTH_LINE), POS(HEIGHT_LINE)};
RECT playerUIOrb = { POS(WIDTH_LINE + OPTION_BOX / 2) , POS(HEIGHT_LINE / 3), POS(WIDTH_LINE + OPTION_BOX / 2 + 4), POS(HEIGHT_LINE / 3 + 7) };
RECT computerUIOrb = { AIPOS(WIDTH_LINE + OPTION_BOX / 2), POS(HEIGHT_LINE / 3), AIPOS(WIDTH_LINE + OPTION_BOX / 2 + 4), POS(HEIGHT_LINE / 3 + 4) };
LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
int WINAPI main(HINSTANCE hIns, HINSTANCE hPrevIns, LPSTR lpCmdLine, int nCmdShow);





LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	
	HDC hdc;
	//PAINTSTRUCT ps;
	
	if (umsg == WM_CREATE) {
		hdc = GetDC(hwnd);
		drawing = new Drawing(hdc, hwnd);
		if (MessageBox(hwnd, L"게임 모드를 선택하세요 \n YES : 1vs1 대전 / NO : vs AI", L"게임모드 선택", MB_YESNO) == IDYES) {
			cout << "solo" << endl;
			gameMode = SOLOMODE;
		}
		else {
			//t1 = thread(ai, *drawing);
			//t1.detach();
			ai = new Ai(*drawing);
			gameMode = AIMODE;
			SetWindowPos(hwnd, NULL, 0, 0, (3 * WHITE_SPACE + WIDTH_LINE * INTERVAL + OPTION_BOX * INTERVAL) * 2, 2.5 * WHITE_SPACE + HEIGHT_LINE * INTERVAL, 0);
			cout << "ai" << endl;
		}
		//block = new Blocks();
		
		game = new Game(*drawing);
		SetTimer(hwnd, 1, game_speed, NULL);
		ReleaseDC(hwnd, hdc);
	} else if (umsg == WM_PAINT) {
		drawing->drawBackground(gameMode);
		if (gameMode == AIMODE) {
			drawing->drawAiBackground();
		}
	}
	else if (umsg == WM_CHAR) {
		if (drawing->pause == true) {
			
		} else if (wparam == 'r') {
			game->rotate(wparam);
		}
		else if (wparam == 'w') {
			game->fall(wparam);
		}
		else {
			game->move(wparam);
		}
		
		//drawing->drawScreen(); 
		InvalidateRect(hwnd, &playerOrb, true);
		//InvalidateRect(hwnd, NULL, true);
	}
	else if (umsg == WM_TIMER) {
		if (game->time == true) {
			InvalidateRect(hwnd, &playerOrb, true);
		}
		if (game->updatePlayerUI == true) {
			game->updatePlayerUI = false;
			InvalidateRect(hwnd, &playerUIOrb, true);
		}
		if (ai->time == true) {
			InvalidateRect(hwnd, &computerOrb, true);
		}
		if (ai->updateComputerUI == true) {
			ai->updateComputerUI = false;
			InvalidateRect(hwnd, &computerUIOrb, true);
		}
		//cout << game->pause << endl;
	/*	if (game->pause == false) {
			//playerThread = thread(&Game::timeUpdate, game);
			//playerThread.detach();
			game->timeUpdate();
			InvalidateRect(hwnd, &playerOrb, true);
			//RECT orb = { POS(0) , POS(0), 3 * WHITE_SPACE + WIDTH_LINE * INTERVAL + OPTION_BOX * INTERVAL, 2.5 * WHITE_SPACE + HEIGHT_LINE * INTERVAL };
			//InvalidateRect(hwnd, &orb, true);
			if (gameMode == AIMODE) {
				//computerThread = thread(&Ai::timeUpdateAi, ai);
			//	computerThread.detach();
				ai->timeUpdateAi();
				InvalidateRect(hwnd, &computerOrb, true);
			}
			
			
			//InvalidateRect(hwnd, NULL, true);
		}*/
	}
	else if (umsg == WM_DESTROY) {
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
	}

	return DefWindowProc(hwnd, umsg, wparam, lparam);
}

int WINAPI main(HINSTANCE hIns, HINSTANCE hPrevIns, LPSTR lpCmdLine, int nCmdShow) {

	WNDCLASS wc;
	wchar_t class_name[] = L"Tetris";

	HBRUSH background = CreateSolidBrush(RGB(0, 0, 0));

	wc.cbClsExtra = NULL;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)background;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hIns;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = class_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);
	
	HWND hwnd = CreateWindow(class_name, class_name, WS_OVERLAPPEDWINDOW, 0, 0,
		3 * WHITE_SPACE + WIDTH_LINE * INTERVAL + OPTION_BOX * INTERVAL, 2.5 * WHITE_SPACE + HEIGHT_LINE * INTERVAL,
		NULL, NULL, hIns, NULL);
	
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);


	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DeleteObject(background);

	return (int)msg.wParam;

}