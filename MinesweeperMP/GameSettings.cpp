#include "GameSettings.h"

namespace mMp {
	GameSettings::GameSettings(int boardSize, int mineCount, bool isMp, bool isLocal, bool isRemote,
		vector<string> names)
		: boardSize(boardSize), mineCount(mineCount), isMp(isMp), isLocal(isLocal), isRemote(isRemote),
		names(names){
	}
}