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
	bool pauseAi;

	void getOptimizedLocationAi();
	void updateReverseScreenAi();
	double totalHeight(BLOCKMAP reverseScreen);
	double completeLine(BLOCKMAP reverseScreen);
	double countHole(BLOCKMAP reverseScreen);
	double countBump(BLOCKMAP reverseScreen);
	BLOCKMAP aiReverseScreen;

protected:
	Drawing &drawing;
	vector<int> start;
	vector<int> now;
	DWORD speed;
	DWORD prevTime;
	vector<int> aiMove;
};

#endif
