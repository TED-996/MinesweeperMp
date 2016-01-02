#include "UiEvent.h"

namespace mMp
{
	UiEvent::TileRevealEvent::TileRevealEvent(int line, int column, int neighbors)
		: line(line), column(column), neighbors(neighbors) {
	}

	UiEvent::TileFlagEvent::TileFlagEvent(int line, int column, bool flagged, int player)
		: line(line), column(column), flagged(flagged), player(player) {
	}

	UiEvent::MineExplodeEvent::MineExplodeEvent(int line, int column)
		: line(line), column(column) {
	}

	UiEvent::GameOverEvent::GameOverEvent(bool won)
		: won(won) {
	}

	UiEvent::UiEvent(TileRevealEvent event) {
		tileRevealEvent = event;
		eventType = UiEventType::TileReveal;
	}

	UiEvent::UiEvent(TileFlagEvent event) {
		tileFlagEvent = event;
		eventType = UiEventType::TileFlag;
	}

	UiEvent::UiEvent(MineExplodeEvent event) {
		mineExplodeEvent = event;
		eventType = UiEventType::MineExplode;
	}

	UiEvent::UiEvent(GameOverEvent event) {
		gameOverEvent = event;
		eventType = UiEventType::GameOver;
	}
}
