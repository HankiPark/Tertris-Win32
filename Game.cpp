#include "Game.h"

Game::Game(Drawing& drawing) :
	drawing(drawing)
{
	// 화면의 가운데서 블록이 등장하게끔
	start = { 0, WIDTH_LINE / 2 - 2, rand() % 7 + 1, 0 };
	// 초기 세팅 저장
	now = start;
	// 블록 속도 지정
	speed = 800;
	
	// 등장 블록 업데이트
	updateScreen(DRAW);

	// 시간에 따라 화면이 변경되게끔 스레드 실행 
	timeThread = thread(&Game::timeUpdate, this);
	timeThread.detach();
	time = false;
	control = false;
}

Game::~Game() {

}

bool Game::move(int input) {
	control = true;
	if (input == 'a') {
		updateScreen(CLEAN);
		now[1]--;
		if (checkCrash()) {
			now[1]++;
			updateScreen(DRAW);
			return false;
		}
		else {
			updateScreen(DRAW);
			return true;
		}
	}
	if (input == 'd') {
		updateScreen(CLEAN);
		now[1]++;
		if (checkCrash()) {
			now[1]--;
			updateScreen(DRAW);
			return false;
		}
		else {
			updateScreen(DRAW);
			return true;
		}
	}
	if (input == 's') {
		updateScreen(CLEAN);
		now[0]++;
		if (checkCrash()) {
			now[0]--;
			updateScreen(DRAW);
			updateScreen(LINECLEAR);
			getNewControl();
			if (!isGameOver()) {
				updateScreen(DRAW);
			}
			return false;
		}
		else {
			updateScreen(DRAW);
			return true;
		}
	}
	control = false;
	return false;
}

void Game::getNewControl() {
	now = { start[0], start[1], drawing.nextBlock - 1, 0 };
	drawing.nextBlock = rand() % 7 + 1;
	drawing.drawNextBlock();
}



void Game::rotate(int input) {
	if (input == 'r') {
		control = true;
		updateScreen(CLEAN);
		int prev = now[3];
		now[3]++;
		if (now[3] > 3) {
			now[3] = 0;
		}
		if (checkCrash()) {
			now[3] = prev;
		}
		updateScreen(DRAW);
	}
}

void Game::updateScreen(int type) {
	int height = now[0];
	int width = now[1];
	int figure = now[2];
	int rotate = now[3];

	BLOCKMAP loc = drawing.block->getBlock(figure)[rotate];
	if (type == CLEAN) {
		for (int h = 0; h < 4; h++) {
			for (int w = 0; w < 4; w++) {
				if (loc[h][w] == 0) {
					continue;
				}
				drawing.screen[h + height][w + width] -= loc[h][w];
			}
		}
	}

	else if (type == DRAW) {
		for (int h = 0; h < 4; h++) {
			for (int w = 0; w < 4; w++) {
				if (loc[h][w] == 0) {
					continue;
				}
				drawing.screen[h + height][w + width] += loc[h][w];
			}
		}
		control = false;
	}
	else if (type == LINECLEAR) {
		control = true;
		for (int h = 0; h < 4; h++) {
			if (h + height >= HEIGHT_LINE) {
				break;
			}
			int check_zero = 0;			
			for (int i = 0; i < WIDTH_LINE; i++) {
				if (drawing.screen[h + height][i] == 0) {
					check_zero = 1;
					break;
				}
			}
			if (check_zero == 0) {
				drawing.screen.erase(drawing.screen.begin() + h + height);
				drawing.screen.insert(drawing.screen.begin(), vector<int>(WIDTH_LINE, 0));
				drawing.score++;
				drawing.aiDebt.push(pair<int, int>(rand() % 3, rand() % WIDTH_LINE));
			}
		}
		control = false;
	}
}

bool Game::checkCrash() {
	int height = now[0];
	int width = now[1];
	int figure = now[2];
	int rotate = now[3];

	BLOCKMAP loc = drawing.block->getBlock(figure)[rotate];

	for (int h = 0; h < 4; h++) {
		for (int w = 0; w < 4; w++) {
			if (loc[h][w] == 0) {
				continue;
			}
			if (h + height >= HEIGHT_LINE || w + width < 0 || w + width >= WIDTH_LINE) {
				return true;
			}
			if (drawing.screen[h + height][w + width] != 0) {
				return true;
			}
		}
	}
	return false;
}

void Game::timeUpdate() {
	while (drawing.pause == false) {
		if (drawing.debt.empty()) {
			time = true;
			this_thread::sleep_for(chrono::milliseconds(speed));
			while (control == true) {
				this_thread::sleep_for(chrono::milliseconds(10));
			}
			
			
			move('s');
			time = false;
		}
		else {
			payOff();
		}
	}
}

void Game::fall(int input) {
	if (input == 'w') {
		updateScreen(CLEAN);
		int prev = now[0];
		for (int h = prev; h <= HEIGHT_LINE; h++) {
			now[0] = h;
			if (checkCrash()) {
				now[0]--;
				updateScreen(DRAW);
				updateScreen(LINECLEAR);
				getNewControl();
				if (!isGameOver()) {
					updateScreen(DRAW);
				}
				break;
			}
		}
		
	}
}


bool Game::isGameOver() {
	if (checkCrash()) {
		drawing.pause = true;
		drawing.isGameOver();
		return true;
	}
	return false;
}

/*
RECT Game::getNowLoc() {
	RECT rec = {POS(now[1] - 4), POS(now[0] - 4), POS(now[1] + 4), POS(now[0] + 4)};
	return rec;
}*/

void Game::payOff() {
	updateScreen(CLEAN);
	pair<int, int> de = drawing.debt.front();
	drawing.debt.pop();
	vector<int> ad(WIDTH_LINE, TRASHCOLOR);
	ad[de.second] = 0;
	for (int i = 0; i < de.first; i++) {
		drawing.screen.insert(drawing.screen.begin() + HEIGHT_LINE, ad);
		drawing.screen.erase(drawing.screen.begin());
	}
	updateScreen(DRAW);
}

