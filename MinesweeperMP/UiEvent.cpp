#include "UiEvent.h"

namespace mMp
{
	UiEvent::TileRevealEvent::TileRevealEvent(int line, int column, int neighbors)
		: line(line), column(column), neighbors(neighbors) {
	}

	UiEvent::MineExplodeEvent::MineExplodeEvent(int line, int column)
		: line(line), column(column) {
	}

	UiEvent::GameOverEvent::GameOverEvent(bool won)
		: won(won) {
	}
}
