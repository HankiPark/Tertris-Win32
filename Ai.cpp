#include "Ai.h"

Ai::Ai(Drawing& drawing) :
	drawing(drawing) 
{
	for (int h = 0; h < HEIGHT_LINE; h++) {
		aiTempScreen.push_back(vector<int>());

		for (int w = 0; w < WIDTH_LINE; w++) {
			aiTempScreen[h].push_back(0);
		}
	}
	
	
	startAi = { 0, WIDTH_LINE / 2 - 2, rand() % 7 + 1, 0 };
	//cout << startAi[0] << startAi[1] << startAi[2] << startAi[3] << endl;
	nowAi = startAi;
	speedAi = 500;
	//prevTimeAi = timeGetTime();
	pauseAi = false;
	time = false;
	updateComputerUI = true;
	logicThread = thread(&Ai::getOptimizedLocationAi, this);
	logicThread.detach();

	aiTimeThread = thread(& Ai::timeUpdateAi, this);
	aiTimeThread.detach();
	//thread t1 (getOptimizedLocationAi);
	//t1.detach();
	//getOptimizedLocationAi();
	updateScreenAi(DRAW);
}

bool Ai::moveAi(int input) {
	if (input == 'a') {
		updateScreenAi(CLEAN);
		nowAi[1]--;
		if (checkCrashAi()) {
			nowAi[1]++;
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
		nowAi[1]++;
		if (checkCrashAi()) {
			nowAi[1]--;
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
		//nowAi[1]++;
	//	cout << "up" << endl;
	}
	if (input == 's') {
		updateScreenAi(CLEAN);
		nowAi[0]++;
		if (checkCrashAi()) {

			nowAi[0]--;
			updateScreenAi(DRAW);
			
			updateScreenAi(LINECLEAR);
			getNewControlAi();
			updateComputerUI = true;
			logicThread = thread(&Ai::getOptimizedLocationAi, this);
			logicThread.detach();
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
void Ai::rotateAi(int input) {
	if (input == 'r') {
		updateScreenAi(CLEAN);
		int prev = nowAi[3];
		nowAi[3]++;
		if (nowAi[3] > 3) {
			nowAi[3] = 0;
		}
		if (checkCrashAi()) {
			nowAi[3] = prev;
		}
		updateScreenAi(DRAW);
	}
}

void Ai::updateScreenAi(int type) {

	//cout << &screen[0][0] << endl;
	int height = nowAi[0];
	int width = nowAi[1];
	int figure = nowAi[2];
	int rotate = nowAi[3];

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
				drawing.aiScore++;
				cout << "erase" << endl;
				drawing.aiScreen.erase(drawing.aiScreen.begin() + h + height);
				drawing.aiScreen.insert(drawing.aiScreen.begin(), vector<int>(WIDTH_LINE, 0));
				
				//drawing.score++;
			}
		}
		updateTempScreenAi(); 
	}
	/*	for (int i = 0; i < HEIGHT_LINE; i++) {
			for (int j = 0; j < WIDTH_LINE; j++) {
				cout << drawing.screen[i][j] << " ";
			}
			cout << endl;
		} */
}

void Ai::updateTempScreenAi(vector<int> temp, int type) {

	//cout << &screen[0][0] << endl;
	int height = temp[0];
	int width = temp[1];
	int figure = temp[2];
	int rotate = temp[3];

	BLOCKMAP loc = drawing.block->getBlock(figure)[rotate];
	if (type == CLEAN) {
		for (int h = 0; h < 4; h++) {
			for (int w = 0; w < 4; w++) {
				if (loc[h][w] == 0) {
					continue;
				}
				aiTempScreen[h + height][w + width] -= loc[h][w];
			}
		}
	}
	else if (type == DRAW) {
		for (int h = 0; h < 4; h++) {
			for (int w = 0; w < 4; w++) {
				if (loc[h][w] == 0) {
					continue;
				}
				aiTempScreen[h + height][w + width] += loc[h][w];
			}
		}
	}
}




void Ai::timeUpdateAi() {
	while (drawing.pause == false) {
		time = true;
		this_thread::sleep_for(chrono::milliseconds(speedAi));
		autoMoveAi();
		moveAi('s');
		time = false;
	}
//	DWORD currentTime = timeGetTime();
//	cout << aiMove.size();
//	autoMoveAi();

	//cout <<currentTime << " "<<  speedAi << endl;
//	if (currentTime - prevTimeAi < speedAi) {
//		return;
//	}
//	if (moveAi('s')) {
//		prevTimeAi = currentTime;

//	}

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
			rotateAi('r');
		}
		aiMove.erase(aiMove.begin(), aiMove.begin() + 1);
	}
}


bool Ai::checkCrashAi() {



	int height = nowAi[0];
	int width = nowAi[1];
	int figure = nowAi[2];
	int rotate = nowAi[3];

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

	for (int w = 0; w < 4; w++) {
		for (int h = 0; h < 4; h++) {
			if (loc[h][w] == 0) {
				continue;
			}
			if (h + height >= HEIGHT_LINE || w + width < 0 || w + width >= WIDTH_LINE) {
				return true;
			}
			if (aiTempScreen[h + height][w + width] != 0) {
				return true;
			}
			
		}
	}

	return false;
}

void Ai::getNewControlAi() {

	nowAi = { startAi[0], startAi[1], drawing.aiNextBlock - 1, 0 };
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


void Ai::updateTempScreenAi() {
	for (int h = 0; h < HEIGHT_LINE; h++) {
		for (int w = 0; w < WIDTH_LINE; w++) {
			aiTempScreen[h][w] = drawing.aiScreen[h][w];
		}
	}
}

void Ai::getOptimizedLocationAi() {
	
	this_thread::sleep_for(chrono::seconds(3));
	double maxScore = -999.0;
	vector<int> tempMove;
	vector<int> t(startAi);
	t[2] = nowAi[2];
	for (int rt = 3; rt >= 0; rt--) {
		for (int wd = 0; wd < WIDTH_LINE; wd++) {
			
			vector<int> temp(t);
			vector<int> movement;

			double tempScore = 0.0;
			int height = temp[0];
			int width = temp[1];
			int figure = temp[2];
			int rotate = rt;
			temp[3] = rt;

			for (int i = 0; i < rt; i++) {
				movement.push_back(ROTATE);
			}

			updateTempScreenAi(temp, DRAW);
			while (1) {
				updateTempScreenAi(temp, CLEAN);
				temp[1]--;
				if (checkCrashAi(temp)) {
					temp[1]++;
					updateTempScreenAi(temp, DRAW);
					break;
				}
				else {
					movement.push_back(LEFT);
				}
				updateTempScreenAi(temp, DRAW);
			}

			for (int i = 0; i < wd; i++) {
				updateTempScreenAi(temp, CLEAN);
				temp[1]++;
				if (checkCrashAi(temp)) {
					temp[1]--;
					updateTempScreenAi(temp, DRAW);
					break;
				}
				else {
					if (movement.size() > 0 && movement.back() == LEFT) {
						movement.pop_back();
					}
					else {
						movement.push_back(RIGHT);
					}
					
				}
				updateTempScreenAi(temp, DRAW);
			}



			for (int i = 0; i < HEIGHT_LINE; i++) {
				updateTempScreenAi(temp, CLEAN);
				temp[0]++;
				if (checkCrashAi(temp)) {
					temp[0]--;
					updateTempScreenAi(temp, DRAW);
					break;
				}
				updateTempScreenAi(temp, DRAW);
			}
			//cout << temp[0] << " " << temp[1] << endl;
			
			//cout << "rt : " << rt << " wd : " << wd << endl;;
			tempScore -= 0.510066 * totalHeight(aiTempScreen);
			//cout << tempScore <<  " ";
			tempScore += 0.760666 * completeLine(aiTempScreen);
			//cout << tempScore << " ";
			tempScore -= 0.45663 * countHole(aiTempScreen);
			//cout << tempScore << " ";
			tempScore -= 0.184483 * countBump(aiTempScreen);
		//	cout << tempScore << endl;
			//cout << "-----------" << endl;
			//cout << "fu" << endl;
		/*	for (auto a : aiTempScreen) {
				for (auto b : a) {
					cout << b << " ";
				}
				cout << endl;
			}
			cout << endl;
			*/
			if (maxScore <= tempScore) {
				maxScore = tempScore;
				tempMove.clear();
				tempMove.assign(movement.begin(), movement.end());
			}
			updateTempScreenAi(temp, CLEAN);
		}
		//cout << " ---" << endl;
	}
	aiMove.clear();
	aiMove.assign(tempMove.begin(), tempMove.end());
	cout << endl<<"maxScore : " << maxScore << endl;
	for (auto a : aiMove) {
		cout << a;
	}
	cout << endl;
	


}

double Ai::totalHeight(BLOCKMAP aiTempScreen) {
	double count = 0.0;
	vector<int> visited(WIDTH_LINE, 0);
	//cout << "height : ";
	for (int h = 0; h < HEIGHT_LINE; h++) {
		for (int w = 0; w < WIDTH_LINE; w++) {
			if (visited[w] == 1) {
				continue;
			}
			if (aiTempScreen[h][w] != 0) {
				//cout << HEIGHT_LINE - h << " ";
				count += HEIGHT_LINE - h;
				visited[w] = 1;
			}
		}
	}
	//cout << endl;
	return count;
}

double Ai::completeLine(BLOCKMAP aiTempScreen) {
	double count = 0.0;
	for (int h = 0; h < HEIGHT_LINE; h++) {
		int clear = 0;
		for (int w = 0; w < WIDTH_LINE; w++) {
			if (aiTempScreen[h][w] == 0) {
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

double Ai::countHole(BLOCKMAP aiTempScreen) {
	double count = 0.0;
	vector<int> visited(WIDTH_LINE, 0);
	for (int h = 0; h < HEIGHT_LINE; h++) {
		for (int w = 0; w < WIDTH_LINE; w++) {
			if (visited[w] == 0 && aiTempScreen[h][w] != 0) {
				visited[w] = 1;
			}
			else if (visited[w] == 1 && aiTempScreen[h][w] == 0) {
				count++;
			}
		}
	}
	return count;
}

double Ai::countBump(BLOCKMAP aiTempScreen) {
	double count = 0.0;
	int prev = 0;
	vector<int> visited(WIDTH_LINE, 0);
	for (int h = 0; h < HEIGHT_LINE; h++) {
		for (int w = 0; w < WIDTH_LINE; w++) {
			if (visited[w] != 0) {
				continue;
			}
			if (aiTempScreen[h][w] != 0) {
				visited[w] = HEIGHT_LINE - h + 1;
			}
		}
	}
	prev = visited[0];
	for (int i = 1; i < WIDTH_LINE; i++) {
		count += abs(prev - visited[i]);
		prev = visited[i];
	}
	return count;
}


/*
RECT Ai::getNowLocAi() {
	RECT rec = { AIPOS(nowAi[1] - 4), POS(nowAi[0] - 4), AIPOS(nowAi[1] + 4), POS(nowAi[0] + 4) };
	return rec;
}
*/
