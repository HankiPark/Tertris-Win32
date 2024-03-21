#include "Game.h"

Game::Game(Drawing& drawing) :
	drawing(drawing)
{
	
	start = { 0, WIDTH_LINE / 2 - 2, rand() % 7 + 1, 0 };
	//cout << start[0] << start[1] << start[2] << start[3] << endl;
	now = start;
	speed = 800;
	//prevTime = timeGetTime();
	
	updateScreen(DRAW);
	timeThread = thread(&Game::timeUpdate, this);
	timeThread.detach();
	time = false;
	updatePlayerUI = true;
}

bool Game::move(int input) {
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
		//cout << "right" << endl;
	}
	if (input == 'w') {
		//now[1]++;
	//	cout << "up" << endl;
	}
	if (input == 's') {
		updateScreen(CLEAN);
		now[0]++;
		if (checkCrash()) {
			now[0]--;
			updateScreen(DRAW);
			updateScreen(LINECLEAR);
			getNewControl();
			updatePlayerUI = true;
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
	return false;
}

void Game::getNewControl() {

	now = { start[0], start[1], drawing.nextBlock - 1, 0 };
	drawing.nextBlock = rand() % 7 + 1;
	drawing.drawNextBlock();
}



void Game::rotate(int input) {
	if (input == 'r') {
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

	//cout << &screen[0][0] << endl;
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
	}
	else if (type == LINECLEAR) {
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
			//	cout << "erase" << endl;
				drawing.screen.erase(drawing.screen.begin() + h + height);
				drawing.screen.insert(drawing.screen.begin(), vector<int>(WIDTH_LINE, 0));
				drawing.score++;
			}
		}
	}
/*	for (int i = 0; i < HEIGHT_LINE; i++) {
		for (int j = 0; j < WIDTH_LINE; j++) {
			cout << drawing.screen[i][j] << " ";
		}
		cout << endl;
	} */
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
		time = true;
		this_thread::sleep_for(chrono::milliseconds(speed));
		
		move('s');
		time = false;
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
				move('s');
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



