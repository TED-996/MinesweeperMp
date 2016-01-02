﻿#pragma once

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

			explicit GameOverEvent(bool won);
		};
		struct TurnStartEvent
		{
			int player;
		};

		enum class UiEventType
		{
			TileReveal,
			TileFlag,
			MineExplode,
			GameOver
		};

		UiEventType eventType;

		union
		{
			TileRevealEvent tileRevealEvent;
			TileFlagEvent tileFlagEvent;
			MineExplodeEvent mineExplodeEvent;
			GameOverEvent gameOverEvent;
		};

		explicit UiEvent(TileRevealEvent event);
		explicit UiEvent(TileFlagEvent event);
		explicit UiEvent(MineExplodeEvent event);
		explicit UiEvent(GameOverEvent event);
	};
}
