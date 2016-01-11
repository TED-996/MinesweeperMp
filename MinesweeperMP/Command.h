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
			Invalid,
			TileOpen,
			TileFlag,
			TurnEnd
		};

		CommandType commandType;

		union
		{
			TileOpenCommand tileOpenCommand;
			TileFlagCommand tileFlagCommand;
			TurnEndCommand turnEndCommand;
		};

		explicit Command(TileOpenCommand command);
		explicit Command(TileFlagCommand command);
		explicit Command(TurnEndCommand command);

		static Command getInvalidCommand();
	private:
		Command();
	};
}
