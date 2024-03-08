#ifndef BLOCKS_H
#define BLOCKS_H

#include "setting.h"

class Blocks {
public:
	Blocks();
	~Blocks();
	vector<BLOCKMAP> getBlock(int ran);
protected:
	vector<BLOCKMAP> OBlock;
	vector<BLOCKMAP> IBlock;
	vector<BLOCKMAP> SBlock;
	vector<BLOCKMAP> ZBlock;
	vector<BLOCKMAP> LBlock;
	vector<BLOCKMAP> JBlock;
	vector<BLOCKMAP> TBlock;

};

#endif
