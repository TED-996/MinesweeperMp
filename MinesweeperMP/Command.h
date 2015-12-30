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

		enum CommandType
		{
			TileOpen,
			TileFlag
		};

		CommandType type;
		union
		{
			TileOpenCommand tileOpenCommand;
			TileFlagCommand tileFlagCommand;
		};
	};
}
