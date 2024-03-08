#include "Drawing.h"

Drawing::Drawing(HDC hdc, HWND hwnd) :
	hdc(hdc), hwnd(hwnd), init({POS(WIDTH_LINE / 2) - POS(2), POS(0)})
{
	for (int h = 0; h < HEIGHT_LINE + 1; h++) {
		screen.push_back(vector<int>());
		for (int w = 0; w < WIDTH_LINE + 1; w++) {
			screen[h].push_back(0);
		}
	}
	//screen = vector <int> ;
	//SaveDC(hdc);
}


void Drawing::drawBackground(int game_mode) {

	PAINTSTRUCT ps;
	hdc = BeginPaint(hwnd, &ps);
	int check_line = 0;

	HPEN hPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, POS(0) - RADIUS, POS(0), NULL);
	LineTo(hdc, POS(0) - RADIUS, POS(HEIGHT_LINE));
	MoveToEx(hdc, POS(WIDTH_LINE) + RADIUS, POS(0), NULL);
	LineTo(hdc, POS(WIDTH_LINE) + RADIUS, POS(HEIGHT_LINE));

	//MoveToEx(hdc, POS(0), POS(0), NULL);
	//LineTo(hdc, POS(WIDTH_LINE - 1), POS(0));
	MoveToEx(hdc, POS(0), POS(HEIGHT_LINE), NULL);
	LineTo(hdc, POS(WIDTH_LINE), POS(HEIGHT_LINE));
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);

	
	TextOut(hdc, POS(0), POS(HEIGHT_LINE + 1), L"w : up / s : down / a : left / d : right", lstrlen(L"w : up / s : down / a : left / d : right"));
	drawBlock();

	EndPaint(hwnd, &ps);
}
void Drawing::drawScore() {
}

void Drawing::drawBlock() {
	//HDC hdc = GetDC(hwnd);
	for (int i = 0; i < HEIGHT_LINE; i++) {
		for (int j = 0; j < WIDTH_LINE; j++) {
		//	cout << screen[i][j] << " ";
			if (screen[i][j] == OBLOCKCOLOR) {
				//cout << " y" ;
				HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));

				RECT r = { POS(j), POS(i), POS(j + 1), POS(i + 1) };

				FillRect(hdc, &r, brush);
				DeleteObject(brush);

			}
			else if (screen[i][j] == IBLOCKCOLOR) {
				//cout << " y" ;
				HBRUSH brush = CreateSolidBrush(RGB(255, 127, 39));

				RECT r = { POS(j), POS(i), POS(j + 1), POS(i + 1) };

				FillRect(hdc, &r, brush);
				DeleteObject(brush);
			}
			else if (screen[i][j] == SBLOCKCOLOR) {
				//	cout << " y";
				HBRUSH brush = CreateSolidBrush(RGB(255, 242, 0));

				RECT r = { POS(j), POS(i), POS(j + 1), POS(i + 1) };

				FillRect(hdc, &r, brush);
				DeleteObject(brush);
			}
			else if (screen[i][j] == ZBLOCKCOLOR) {
				//cout << " y" ;
				HBRUSH brush = CreateSolidBrush(RGB(34, 177, 76));

				RECT r = { POS(j), POS(i), POS(j + 1), POS(i + 1) };

				FillRect(hdc, &r, brush);
				DeleteObject(brush);
			}
			else if (screen[i][j] == LBLOCKCOLOR) {
				//	cout << " y" ;
				HBRUSH brush = CreateSolidBrush(RGB(0, 162, 232));

				RECT r = { POS(j), POS(i), POS(j + 1), POS(i + 1) };

				FillRect(hdc, &r, brush);
				DeleteObject(brush);
			}
			else if (screen[i][j] == JBLOCKCOLOR) {
				//	cout << " y" ;
				HBRUSH brush = CreateSolidBrush(RGB(63, 72, 204));

				RECT r = { POS(j), POS(i), POS(j + 1), POS(i + 1) };

				FillRect(hdc, &r, brush);
				DeleteObject(brush);
			}
			else if (screen[i][j] == TBLOCKCOLOR) {
				//	cout << " y" ;
				HBRUSH brush = CreateSolidBrush(RGB(128, 128, 255));

				RECT r = { POS(j), POS(i), POS(j + 1), POS(i + 1) };

				FillRect(hdc, &r, brush);
				DeleteObject(brush);
			}
		}
	//	cout << endl;
	}
	
	//	ReleaseDC(hwnd, hdc);
		//InvalidateRect(hwnd, NULL, true);
		//SendMessage(hwnd, WM_PAINT, NULL, NULL);
		//RECT r = { POS(0), POS(0), POS(WIDTH_LINE), POS(HEIGHT_LINE) };

}