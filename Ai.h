#ifndef AI_H
#define AI_H

#include "setting.h"
#include "Drawing.h"

class Ai {
public:
	Ai(Drawing& drawing);
	~Ai();
	bool moveAi(int input);
	void rotateAi(int input);

	bool checkCrashAi();
	bool checkCrashAi(vector<int> temp);
	void getNewControlAi();
	void timeUpdateAi();
	void autoMoveAi();
	bool isGameOverAi();
	void updateScreenAi(int type);
	void updateTempScreenAi(vector<int> temp, int type);
	bool pauseAi;

//	RECT getNowLocAi();
	bool updateComputerUI;

	void getOptimizedLocationAi();
	void updateTempScreenAi();
	double totalHeight(BLOCKMAP reverseScreen);
	double completeLine(BLOCKMAP reverseScreen);
	double countHole(BLOCKMAP reverseScreen);
	double countBump(BLOCKMAP reverseScreen);
	BLOCKMAP aiTempScreen;
	bool time;
protected:
	thread logicThread;
	thread aiTimeThread;
	Drawing &drawing;
	vector<int> startAi;
	vector<int> nowAi;
	DWORD speedAi;
	DWORD prevTimeAi;
	vector<int> aiMove;
	mutex mt;
	
};

#endif
