#pragma once

namespace mMp {
	class UiEvent
	{
	public:
		struct TileRevealEvent
		{
			int line;
			int column;
			int neighbors;

			TileRevealEvent(int line, int column, int neighbors);
		};
		struct TileFlagEvent
		{
			int line;
			int column;
			bool flagged;
			int player;

			TileFlagEvent(int line, int column, bool flagged, int player = 0);
		};
		struct MineExplodeEvent
		{
			int line;
			int column;

			MineExplodeEvent(int line, int column);
		};
		struct GameOverEvent
		{
			bool won;
			int player;

			GameOverEvent(bool won, int player);
		};
		struct PlayerDeadEvent
		{
			int player;

			explicit PlayerDeadEvent(int player);
		};
		struct TurnStartEvent
		{
			int player;

			explicit TurnStartEvent(int player);
		};
		struct RevealAcceptedEvent
		{
			RevealAcceptedEvent();
		};

		enum class UiEventType
		{
			Invalid,
			TileReveal,
			TileFlag,
			MineExplode,
			GameOver,
			PlayerDead,
			TurnStart,
			RevealAccepted
		};

		UiEventType eventType;

		union
		{
			TileRevealEvent tileRevealEvent;
			TileFlagEvent tileFlagEvent;
			MineExplodeEvent mineExplodeEvent;
			GameOverEvent gameOverEvent;
			PlayerDeadEvent playerDeadEvent;
			TurnStartEvent turnStartEvent;
			RevealAcceptedEvent revealAcceptedEvent;
		};

		explicit UiEvent(TileRevealEvent event);
		explicit UiEvent(TileFlagEvent event);
		explicit UiEvent(MineExplodeEvent event);
		explicit UiEvent(GameOverEvent event);
		explicit UiEvent(PlayerDeadEvent event);
		explicit UiEvent(TurnStartEvent event);
		explicit UiEvent(RevealAcceptedEvent event);

		static UiEvent getInvalidEvent();
	private:
		UiEvent();
	};
}
