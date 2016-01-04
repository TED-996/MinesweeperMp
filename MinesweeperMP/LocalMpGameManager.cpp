#include "LocalMpGameManager.h"

namespace mMp
{
	LocalMpGameManager::LocalMpGameManager(GameSettings gameSettings, Action1P<UiEvent> postUiEventAction)
		: postUiEventAction(postUiEventAction), board(gameSettings.boardSize, gameSettings.mineCount),
		gameSettings(gameSettings) {
		currentPlayer = 0;
		reveals = 0;
		playerDead.resize(gameSettings.names.size(), false);
		scores.resize(gameSettings.names.size(), 0);
	}

	void LocalMpGameManager::postCommand(Command command) {
		if (command.commandType == Command::CommandType::TurnEnd) {
			handleTurnEnd(command.turnEndCommand.player);
		}
		if (command.commandType == Command::CommandType::TileOpen) {
			auto tileOpenCommand = command.tileOpenCommand;
			handleReveal(Board::BoardPoint(tileOpenCommand.line, tileOpenCommand.column), tileOpenCommand.player);
		}
		if (command.commandType == Command::CommandType::TileFlag) {
			auto tileFlagCommand = command.tileFlagCommand;
			handleFlag(Board::BoardPoint(tileFlagCommand.line, tileFlagCommand.column), tileFlagCommand.player);
		}
	}

	void LocalMpGameManager::handleTurnEnd(int player) {
		if (player != currentPlayer) {
			return;
		}
		do {
			currentPlayer = (currentPlayer + 1) % gameSettings.names.size();
		} while (playerDead[currentPlayer] && currentPlayer != player);
		reveals = 0;

		postUiEventAction(UiEvent(UiEvent::TurnStartEvent(currentPlayer)));
	}

	void LocalMpGameManager::handleReveal(Board::BoardPoint rootPoint, int player) {
		if (player != currentPlayer) {
			return;
		}

		if (board.isFlagged(rootPoint)) {
			return;
		}
		if (reveals >= 3) {
			return;
		}
		if (board.isMine(rootPoint)) {
			KillCurrentPlayer();
			return;
		}

		reveals++;
		revealPoint(rootPoint);
	}

	void LocalMpGameManager::revealPoint(Board::BoardPoint rootPoint) {
		vector<Board::BoardPoint> revealedPoints = board.reveal(rootPoint);
		for (auto point : revealedPoints) {
			if (board.isFlagged(point)) {
				board.toggleFlag(point);
				postUiEventAction(UiEvent(UiEvent::TileFlagEvent(point.line, point.column, false)));
			}
			postUiEventAction(
				UiEvent(UiEvent::TileRevealEvent(point.line, point.column, board.getNeighbors(point))));
		}
		if (board.isCompleted()) {
			postUiEventAction(UiEvent(UiEvent::GameOverEvent(true, getWinner())));
		}
	}

	int LocalMpGameManager::getWinner() {
		int maxPos = 0;
		for (int i = 1; i < scores.size(); i++) {
			if (scores[i] > scores[maxPos]) {
				maxPos = i;
			}
		}
		return maxPos;
	}

	void LocalMpGameManager::handleFlag(Board::BoardPoint point, int player) {
		if (player != currentPlayer) {
			return;
		}

		if (board.isRevealed(point)) {
			return;
		}
		if (board.isFlagged(point)) {
			//Cannot unflag in multiplayer, since all flags are checked.
			return;
		}
		if (!board.isMine(point)) {
			KillCurrentPlayer();
		}
		else {
			board.toggleFlag(point);
			postUiEventAction(UiEvent(UiEvent::TileFlagEvent(point.line, point.column, board.isFlagged(point))));
		}
	}

	void LocalMpGameManager::KillCurrentPlayer() {
		playerDead[currentPlayer] = true;
		postUiEventAction(UiEvent(UiEvent::PlayerDeadEvent(currentPlayer)));
		handleTurnEnd(currentPlayer);

		//If no other players found, and this one is dead...
		if (playerDead[currentPlayer]) {
			postUiEventAction(UiEvent(UiEvent::GameOverEvent(false, currentPlayer)));
		}
	}
}
