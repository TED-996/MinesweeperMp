#include "GameSettings.h"

namespace mMp {
	GameSettings::GameSettings(int boardSize, int mineCount, bool isMp, vector<string> names)
		: boardSize(boardSize), mineCount(mineCount), isMp(isMp), names(names) {
	}
}
