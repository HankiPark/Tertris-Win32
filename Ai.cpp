#include "Ai.h"

Ai::Ai(Drawing& drawing) :
	drawing(drawing) 
{
	start = { 0, WIDTH_LINE / 2 - 2, rand() % 7 + 1, 0 };
	//cout << start[0] << start[1] << start[2] << start[3] << endl;
	now = start;
	speed = 100;
	prevTime = timeGetTime();
	pauseAi = false;
	updateScreenAi(DRAW);
}

bool Ai::moveAi(int input) {
	if (input == 'a') {
		updateScreenAi(CLEAN);
		now[1]--;
		if (checkCrashAi()) {
			now[1]++;
			updateScreenAi(DRAW);
			return false;
		}
		else {
			updateScreenAi(DRAW);
			return true;
		}


	}
	if (input == 'd') {
		updateScreenAi(CLEAN);
		now[1]++;
		if (checkCrashAi()) {
			now[1]--;
			updateScreenAi(DRAW);
			return false;
		}
		else {
			updateScreenAi(DRAW);
			return true;
		}
		//cout << "right" << endl;
	}
	if (input == 'w') {
		//now[1]++;
	//	cout << "up" << endl;
	}
	if (input == 's') {
		updateScreenAi(CLEAN);
		now[0]++;
		if (checkCrashAi()) {
			now[0]--;
			updateScreenAi(DRAW);
			updateScreenAi(LINECLEAR);
			updateBumpyAi();
			getNewControlAi();
			isGameOverAi();
			updateScreenAi(DRAW);
			return false;
		}
		else {
			updateScreenAi(DRAW);
			return true;
		}
	}
	return false;
}


void Ai::updateScreenAi(int type) {

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
				drawing.aiScreen[h + height][w + width] -= loc[h][w];
			}
		}
	}

	else if (type == DRAW) {
		for (int h = 0; h < 4; h++) {
			for (int w = 0; w < 4; w++) {
				if (loc[h][w] == 0) {
					continue;
				}
				drawing.aiScreen[h + height][w + width] += loc[h][w];
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
				if (drawing.aiScreen[h + height][i] == 0) {
					check_zero = 1;
					break;
				}
			}
			if (check_zero == 0) {
				//	cout << "erase" << endl;
				drawing.aiScreen.erase(drawing.aiScreen.begin() + h + height);
				drawing.aiScreen.insert(drawing.aiScreen.begin(), vector<int>(WIDTH_LINE, 0));
				//drawing.score++;
			}
			else {
				//	cout << "no" << endl;
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

void Ai::timeUpdateAi() {
	DWORD currentTime = timeGetTime();
	if (currentTime - prevTime < speed) {
		return;
	}
	if (moveAi('s')) {
		prevTime = currentTime;

	}

}


bool Ai::checkCrashAi() {



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
			if (drawing.aiScreen[h + height][w + width] != 0) {
				return true;
			}
		}
	}
	return false;
}


void Ai::getNewControlAi() {

	now = { start[0], start[1], drawing.aiNextBlock - 1, 0 };
	drawing.aiNextBlock = rand() % 7 + 1;
	drawing.drawAiNextBlock();
}



bool Ai::isGameOverAi() {
	if (checkCrashAi()) {
		pauseAi = true;
		drawing.isGameOver();
		return true;
	}
	return false;
}




void Ai::getOptimizedLocationAi() {
	vector<int> temp(now);


	while (checkCrashAi()) {
		temp[1]--;
	}
	while (checkCrashAi()) {
		temp[0]++;
	}

}

void Ai::updateBumpyAi() {

	int height = now[0];
	int width = now[1];
	int figure = now[2];
	int rotate = now[3];

	BLOCKMAP loc = drawing.block->getBlock(figure)[rotate];

	drawing.aiBumpy[]



}