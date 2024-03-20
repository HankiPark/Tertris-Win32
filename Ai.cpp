#include "Ai.h"

Ai::Ai(Drawing& drawing) :
	drawing(drawing) 
{
	for (int w = 0; w < WIDTH_LINE + 1; w++) {
		aiReverseScreen.push_back(vector<int>());

		for (int h = 0; h < HEIGHT_LINE; h++) {
			aiReverseScreen[w].push_back(0);
		}

	}

	start = { 0, WIDTH_LINE / 2 - 2, rand() % 7 + 1, 0 };
	//cout << start[0] << start[1] << start[2] << start[3] << endl;
	now = start;
	speed = 30;
	prevTime = timeGetTime();
	pauseAi = false;
	getOptimizedLocationAi();
	//t1.detach();
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
			getNewControlAi();
			getOptimizedLocationAi();
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
				
			//	if (loc[h][w] == 0) {
			//		continue;
			//	}
				drawing.aiScreen[h + height][w + width] -= loc[h][w];

			}
		}
	}

	else if (type == DRAW) {
		for (int h = 0; h < 4; h++) {
			for (int w = 0; w < 4; w++) {
				
			//	if (loc[h][w] == 0) {
			//		continue;
			//	}
				drawing.aiScreen[h + height][w + width] += loc[h][w];

			}
		}
	}
	else if (type == LINECLEAR) {
		cout << "-----------"<< endl;
		for (auto a : aiReverseScreen) {
			for (auto b : a) {
				cout << b << " ";
			}
			cout << endl;
		}
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
	cout << aiMove.size();
	autoMoveAi();


	if (currentTime - prevTime < speed) {
		return;
	}
	if (moveAi('s')) {
		prevTime = currentTime;

	}

}

void Ai::autoMoveAi() {
	if (aiMove.size() == 0) {
		return;
	}
	else {
		int m = aiMove[0];
		if (m == LEFT) {
			moveAi('a');
		}
		else if (m == RIGHT) {
			moveAi('d');
		}
		else if (m == DOWN) {
			moveAi('s');
		}
		else if (m == ROTATE) {
			moveAi('r');
		}
		aiMove.erase(aiMove.begin(), aiMove.begin() + 1);
	}
}


bool Ai::checkCrashAi() {



	int height = now[0];
	int width = now[1];
	int figure = now[2];
	int rotate = now[3];

	BLOCKMAP loc = drawing.block->getBlock(figure)[rotate];

	for (int w = 0; w < 4; w++) {
		for (int h = 0; h < 4; h++) {
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

bool Ai::checkCrashAi(vector<int> temp) {

	int height = temp[0];
	int width = temp[1];
	int figure = temp[2];
	int rotate = temp[3];

	BLOCKMAP loc = drawing.block->getBlock(figure)[rotate];

	BLOCKMAP rotateLoc(4, vector<int> (4, 0));
	for (int w = 0; w < 4; w++) {
		for (int h = 0; h < 4; h++) {
			rotateLoc[h][w] = loc[w][3 - h];
		}
	}

	for (int w = 0; w < 4; w++) {
		for (int h = 0; h < 4; h++) {
			if (rotateLoc[h][w] == 0) {
				continue;
			}
			if (h + height < 0 || h + height >= WIDTH_LINE + 1 || w + width < 0 || w + width >= HEIGHT_LINE) {
				return true;
			}
			if (aiReverseScreen[h + height][w + width] != 0) {
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


void Ai::updateReverseScreenAi() {

	for (int w = 0; w < HEIGHT_LINE; w++) {
		for (int h = 0; h < WIDTH_LINE + 1; h++) {
			aiReverseScreen[h][w] = drawing.aiScreen[w][WIDTH_LINE - h];
		}
	}

}

void Ai::getOptimizedLocationAi() {

	updateReverseScreenAi();



	vector<int> len;
	double maxScore = -999.0;
	vector<int> t(now);
	for (vector<int> screen : aiReverseScreen) {
		bool chk = true;
		for (int i = 0; i < screen.size() - 1; i++) {
			if (screen[i] != 0) {
				len.push_back(HEIGHT_LINE - i - 1);
				chk = false;
				break;
			}
		}
		if (chk == true) {
			len.push_back(0);
		}
	}

	for (int rt = 0; rt < 1; rt++) {
		cout << " ---" << endl;
		for (int wd = 0; wd < WIDTH_LINE + 1; wd++) {
			vector<int> temp(t);
			int t = temp[0];
			temp[0] = temp[1];
			temp[1] = t;
			vector<int> movement;
			double tempScore = 0.0;
			int figure = temp[2];
			int rotate = rt;
			temp[3] = rt;
			for (int i = 0; i < rt; i++) {
				movement.push_back(ROTATE);
			}
			movement.push_back(LEFT);
			for (int i = 0; i < WIDTH_LINE / 2 - 2; i++) {
				temp[0]--;
				if (checkCrashAi(temp)) {
					//temp[0]++;
				//	movement.pop_back();
					break;
				}
				else {
					movement.push_back(LEFT);
				}
			}
	/*		while (!checkCrashAi(temp)) {
				temp[0]--;
				movement.push_back(LEFT);
			}
			temp[0]++;5
			movement.push_back(RIGHT);
			*/
			for (int i = 0; i < wd; i++) {
				temp[0]++;
				if (checkCrashAi(temp)) {
					temp[0]--;
					
					break;
				}
				else {
					movement.push_back(RIGHT);
				}
			}

			int height = temp[0];

			for (int i = 0; i < HEIGHT_LINE; i++) {
				temp[1]++;
				if (checkCrashAi(temp)) {
				//	cout << "height : " << i << endl;

					temp[1]--;
					break;
				}
				else {
					
				}
			}
			//cout << temp[0] << " " << temp[1] << endl;

			if (checkCrashAi(temp)) {
				continue;
			}

			int width = temp[1];

			BLOCKMAP loc = drawing.block->getBlock(figure)[rotate];
			BLOCKMAP rotateLoc(4, vector<int>(4, 0));
			for (int w = 0; w < 4; w++) {
				for (int h = 0; h < 4; h++) {
					rotateLoc[h][w] = loc[w][3 - h];
				}
			}

			for (int w = 0; w < 4; w++) {
				for (int h = 0; h < 4; h++) {
					if (rotateLoc[h][w] == 0) {
						continue;
					}
					aiReverseScreen[h + height][w + width] += rotateLoc[h][w];
				}
			}
			/*for (int h = 0; h < 4; h++) {
				for (int w = 0; w < 4; w++) {
					if (loc[w][h] == 0) {
						continue;
					}
					aiReverseScreen[h + height][w + width] += loc[w][h];
				}
			}
			*/
			cout << "rt : " << rt << " wd : " << wd << endl;;
			tempScore -= 0.510066 * totalHeight(aiReverseScreen);
			cout << tempScore <<  " ";
			tempScore += 0.760666 * completeLine(aiReverseScreen);
			cout << tempScore << " ";
			tempScore -= 0.35663 * countHole(aiReverseScreen);
			cout << tempScore << " ";
			tempScore -= 0.184483 * countBump(aiReverseScreen);
			cout << tempScore << endl;
			cout << "-----------" << endl;
			for (auto a : aiReverseScreen) {
				for (auto b : a) {
					cout << b << " ";
				}
				cout << endl;
			}
			

			for (int w = 0; w < 4; w++) {
				for (int h = 0; h < 4; h++) {
					if (rotateLoc[h][w] == 0) {
						continue;
					}
					aiReverseScreen[h + height][w + width] -= rotateLoc[h][w];
				}
			}

			if (maxScore <= tempScore) {
				maxScore = tempScore;
				aiMove.clear();
				aiMove.assign(movement.begin(), movement.end());
			}
		}
		//cout << " ---" << endl;
	}
	cout << "maxScore : " << maxScore << endl;
	for (auto a : aiMove) {
		cout << a;
	}
	cout << endl;
	


}

double Ai::totalHeight(BLOCKMAP reverseScreen) {
	double count = 0.0;
	for (vector<int> screen : reverseScreen) {
		for (int i = 0; i < screen.size() - 1; i++) {
			if (screen[i] != 0) {
				count += HEIGHT_LINE - i;
				break;
			}
		}
	}

	return count;
}

double Ai::completeLine(BLOCKMAP reverseScreen) {
	double count = 0.0;
	for (int i = 0; i < HEIGHT_LINE; i++) {
		int clear = 0;
		for (int j = 0; j < WIDTH_LINE; j++) {
			if (reverseScreen[j][i] == 0) {
				clear = 1;
				break;
			}
		}
		if (clear == 0) {
			count++;
		}
	}

	return count;
}

double Ai::countHole(BLOCKMAP reverseScreen) {
	double count = 0.0;
	for (vector<int> screen : reverseScreen) {
		for (int i = 0; i < screen.size(); i++) {
			if (screen[i] != 0) {
				for (int j = i + 1; j < screen.size() - 1; j++) {
					if (screen[i] == 0) {
						count++;
					}
				}
			}
		}
	}

	return count;
}

double Ai::countBump(BLOCKMAP reverseScreen) {
	double count = 0.0;
	double prev = 0.0;
	for (int i = 0; i < reverseScreen.size(); i++) {
		for (int j = 0; j < reverseScreen[i].size(); j++) {
			if (reverseScreen[i][j] != 0) {
				if (i == 0) {
					prev = (double)j;
				}
				else {
					count += abs(prev - (double)j);
					prev = (double)j;
				}
			}
		}
	}

	return count;
}



