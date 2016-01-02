#include "Command.h"

namespace mMp
{
	Command::TileOpenCommand::TileOpenCommand(int line, int column)
		: line(line), column(column) {
	}

	Command::TileFlagCommand::TileFlagCommand(int line, int column)
		: line(line), column(column) {
	}

	Command::Command(TileOpenCommand command) {
		tileOpenCommand = command;
		commandType = CommandType::TileOpen;
	}

	Command::Command(TileFlagCommand command) {
		tileFlagCommand = command;
		commandType = CommandType::TileFlag;
	}
}
