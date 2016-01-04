#include "Command.h"

namespace mMp
{
	Command::TileOpenCommand::TileOpenCommand(int line, int column, int player)
		: line(line), column(column), player(player) {
	}

	Command::TileFlagCommand::TileFlagCommand(int line, int column, int player)
		: line(line), column(column), player(player) {
	}

	Command::TurnEndCommand::TurnEndCommand(int player)
		: player(player) {
	}

	Command::Command(TileOpenCommand command) {
		tileOpenCommand = command;
		commandType = CommandType::TileOpen;
	}

	Command::Command(TileFlagCommand command) {
		tileFlagCommand = command;
		commandType = CommandType::TileFlag;
	}

	Command::Command(TurnEndCommand command) {
		turnEndCommand = command;
		commandType = CommandType::TurnEnd;
	}
}
