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

	UiEvent::GameOverEvent::GameOverEvent(bool won, int player)
		: won(won), player(player) {
	}

	UiEvent::PlayerDeadEvent::PlayerDeadEvent(int player)
		: player(player) {
	}

	UiEvent::TurnStartEvent::TurnStartEvent(int player)
		: player(player) {
	}

	UiEvent::RevealAcceptedEvent::RevealAcceptedEvent() {
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

	UiEvent::UiEvent(PlayerDeadEvent event) {
		playerDeadEvent = event;
		eventType = UiEventType::PlayerDead;
	}

	UiEvent::UiEvent(TurnStartEvent event) {
		turnStartEvent = event;
		eventType = UiEventType::TurnStart;
	}

	UiEvent::UiEvent(RevealAcceptedEvent event) {
		revealAcceptedEvent = event;
		eventType = UiEventType::RevealAccepted;
	}
}
