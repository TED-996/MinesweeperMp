#pragma once

namespace mMp {
	class Command
	{
	public:
		struct TileOpenCommand
		{
			int line;
			int column;
			int player;

			TileOpenCommand(int line, int column, int player = 0);
		};
		struct TileFlagCommand
		{
			int line;
			int column;
			int player;

			TileFlagCommand(int line, int column, int player = 0);
		};
		struct TurnEndCommand
		{
			int player;

			explicit TurnEndCommand(int player);
		};

		enum class CommandType
		{
			TileOpen,
			TileFlag
		};

		CommandType commandType;

		union
		{
			TileOpenCommand tileOpenCommand;
			TileFlagCommand tileFlagCommand;
		};

		explicit Command(TileOpenCommand command);
		explicit Command(TileFlagCommand command);
	};
}
