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


unsigned int gameMode = SOLOMODE;
unsigned int game_speed = 1000;
Drawing* drawing;
Game* game;
Ai* ai;
thread playerThread;
thread computerThread;
bool control;

// �÷��̾��� ȭ���� UI
RECT playerOrb = { POS(0) , POS(0), POS(WIDTH_LINE + OPTION_BOX / 2 + 4), POS(HEIGHT_LINE) };
// ��ǻ���� ȭ���� UI
RECT computerOrb = { AIPOS(0), POS(0), AIPOS(WIDTH_LINE + OPTION_BOX / 2 + 4), POS(HEIGHT_LINE) };
LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
int WINAPI main(HINSTANCE hIns, HINSTANCE hPrevIns, LPSTR lpCmdLine, int nCmdShow);





LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	
	HDC hdc;
	HDC backMemDC;
	if (umsg == WM_CREATE) {
		hdc = GetDC(hwnd);
		drawing = new Drawing(hdc, hwnd);
		if (MessageBox(hwnd, L"���� ��带 �����ϼ��� \n YES : 1vs1 ���� / NO : vs AI", L"���Ӹ�� ����", MB_YESNO) == IDYES) {
			gameMode = SOLOMODE;
		}
		else {
			ai = new Ai(*drawing);
			gameMode = AIMODE;
			SetWindowPos(hwnd, NULL, 0, 0, (3 * WHITE_SPACE + WIDTH_LINE * INTERVAL + OPTION_BOX * INTERVAL) * 2, 2.5 * WHITE_SPACE + HEIGHT_LINE * INTERVAL, 0);
		}
		game = new Game(*drawing);
		SetTimer(hwnd, 1, game_speed, NULL);
		ReleaseDC(hwnd, hdc);
	} else if (umsg == WM_PAINT) {

		// �÷��̾��� ȭ�� �׸���
		drawing->drawBackground(gameMode);
		// vs ai�� ��� ��ǻ���� ȭ�鵵 �׸���
		if (gameMode == AIMODE) {
			drawing->drawAiBackground();
		}
	}
	else if (umsg == WM_CHAR) {
		// aimode���� ��Ģ ����� �����Ұ��, �ڿ� �浹������ ���� ��� ����
		if (gameMode == AIMODE) {
			while (!drawing->debt.empty() || !drawing->aiDebt.empty()) {
				this_thread::sleep_for(chrono::milliseconds(100));
			}
		}
		// ������ �����Ǿ� ������ 
		if (drawing->pause == false) {
			// ȸ��
			if (wparam == 'r') {
				game->rotate(wparam);
			}
			// ���� ����
			else if (wparam == 'w') {
				game->fall(wparam);
			}
			// ���� �̵� ó��
			else {
				game->move(wparam);
			}
		}
		InvalidateRect(hwnd, &playerOrb, true);
		control = true;
	}
	else if (umsg == WM_TIMER) {
		// �÷��̾��� ���� �ӵ��� ���� ȭ�� ����
		if (game->time == true) {
			if (control == false) {
				InvalidateRect(hwnd, NULL, true);
			}
			else {
				control = true;
				InvalidateRect(hwnd, &computerOrb, true);
			}
			
		}
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