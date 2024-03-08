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
using namespace std;
// 82 , 45





unsigned int score = 0;
WCHAR word[1024];
unsigned int game_mode = 1;
unsigned int game_speed = 1000;
Drawing* drawing;
Game* game;
//Blocks* block;


void drawMap(HWND hand);

LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
int WINAPI main(HINSTANCE hIns, HINSTANCE hPrevIns, LPSTR lpCmdLine, int nCmdShow);




void drawMap(HWND hwnd) {
	
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	
	HDC hdc;
	PAINTSTRUCT ps;

	
	
	if (umsg == WM_CREATE) {
		hdc = GetDC(hwnd);
		if (MessageBox(hwnd, L"게임 모드를 선택하세요 \n YES : 1vs1 대전 / NO : vs AI", L"게임모드 선택", MB_YESNO) == IDYES) {
			cout << "solo" << endl;
			game_mode = 1;
		}
		else {
			game_mode = 2;
			cout << "ai" << endl;
		}
		//block = new Blocks();
		drawing = new Drawing(hdc, hwnd);
		game = new Game(*drawing);
		SetTimer(hwnd, 1, game_speed, NULL);
		ReleaseDC(hwnd, hdc);
	} else if (umsg == WM_PAINT) {
		drawing->drawBackground(game_mode);
		
	}
	else if (umsg == WM_CHAR) {
		if (wparam == 'r') {
			game->rotate(wparam);
		}
		else {
			game->move(wparam);
		}
		
		//drawing->drawBlock(); 
		InvalidateRect(hwnd, NULL, true);
	}
	else if (umsg == WM_TIMER) {
		game->timeUpdate();
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
		2 * WHITE_SPACE + WIDTH_LINE * INTERVAL, 2.5 * WHITE_SPACE + HEIGHT_LINE * INTERVAL,
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