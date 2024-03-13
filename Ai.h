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
	void getNewControlAi();
	void timeUpdateAi();
	bool isGameOverAi();
	void updateScreenAi(int type);
	bool pauseAi;

	void getOptimizedLocationAi();
	void updateBumpyAi();

protected:
	Drawing &drawing;
	vector<int> start;
	vector<int> now;
	DWORD speed;
	DWORD prevTime;
};

#endif
