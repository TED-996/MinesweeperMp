#pragma once

namespace mMp {
	class Command
	{
	public:
		struct TileOpenCommand
		{
			int line;
			int column;

			TileOpenCommand(int line, int column);
		};
		struct TileFlagCommand
		{
			int line;
			int column;

			TileFlagCommand(int line, int column);
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
