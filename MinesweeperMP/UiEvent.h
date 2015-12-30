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

		enum UiEventType
		{
			TileReveal,
			MineExplode,
			GameOver
		};

		UiEventType eventType;

		union
		{
			TileRevealEvent tileRevealEvent;
			MineExplodeEvent mineExplodeEvent;
			GameOverEvent gameOverEvent;
		};
	};
}
