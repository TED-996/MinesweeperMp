#include "MpGameManager.h"

namespace mMp
{
	MpGameManager::MpGameManager(GameSettings gameSettings, Action1P<UiEvent> postUiEventAction)
		: postUiEventAction(postUiEventAction), board(gameSettings.boardSize, gameSettings.mineCount),
		gameSettings(gameSettings) {
		currentPlayer = 0;
		revealsThisTurn = 0;
		playerDead.resize(gameSettings.names.size(), false);
		scores.resize(gameSettings.names.size(), 0);
	}

	void MpGameManager::postCommand(Command command) {
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

	void MpGameManager::handleTurnEnd(int player) {
		if (player != currentPlayer) {
			return;
		}
		do {
			currentPlayer = (currentPlayer + 1) % gameSettings.names.size();
		} while (playerDead[currentPlayer] && currentPlayer != player);
		revealsThisTurn = 0;

		postUiEventAction(UiEvent(UiEvent::TurnStartEvent(currentPlayer)));
	}

	void MpGameManager::handleReveal(Board::BoardPoint rootPoint, int player) {
		if (player != currentPlayer) {
			return;
		}

		if (board.isFlagged(rootPoint)) {
			return;
		}
		if (revealsThisTurn >= 3) {
			return;
		}
		if (board.isRevealed(rootPoint) && !handleRevealAround(rootPoint)) {
			return;
		}
		if (board.isMine(rootPoint)) {
			KillCurrentPlayer();
			return;
		}

		postUiEventAction(UiEvent(UiEvent::RevealAcceptedEvent()));
		revealsThisTurn++;
		revealPoint(rootPoint);
	}

	void MpGameManager::revealPoint(Board::BoardPoint rootPoint) {
		vector<Board::BoardPoint> revealedPoints = board.reveal(rootPoint);
		for (auto point : revealedPoints) {
			if (board.isFlagged(point)) {
				board.toggleFlag(point);
				postUiEventAction(UiEvent(UiEvent::TileFlagEvent(point.line, point.column, false)));
			}
			postUiEventAction(
				UiEvent(UiEvent::TileRevealEvent(point.line, point.column, board.getNeighbors(point))));
		}
		
	}

	bool MpGameManager::handleRevealAround(Board::BoardPoint rootPoint) {
		int flagsAround = 0;
		int minesAround = 0;
		bool found = false;

		for (int i = 0; i < 8; i++) {
			auto neighbor = rootPoint.getNeighbor((Direction)i);
			if (board.isFlagged(neighbor)) {
				flagsAround++;
			}
			if (board.isMine(neighbor)) {
				minesAround++;
			}
		}
		if (flagsAround != minesAround) {
			return false;
		}

		for (int i = 0; i < 8; i++) {
			auto neighbor = rootPoint.getNeighbor((Direction)i);
			if (board.isValid(neighbor) && !board.isRevealed(neighbor) && !board.isFlagged(neighbor)) {
				revealPoint(neighbor);
				found = true;
			}
		}

		return found;
	}

	int MpGameManager::getWinner() {
		int maxPos = 0;
		for (int i = 1; i < (int) scores.size(); i++) {
			if (scores[i] > scores[maxPos]) {
				maxPos = i;
			}
		}
		return maxPos;
	}

	void MpGameManager::handleFlag(Board::BoardPoint point, int player) {
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
			return;
		}
		board.toggleFlag(point);
		postUiEventAction(
			UiEvent(UiEvent::TileFlagEvent(point.line, point.column, board.isFlagged(point), currentPlayer)));

		if (board.isCompleted(true)) {
			postUiEventAction(UiEvent(UiEvent::GameOverEvent(true, getWinner())));
		}
	}

	void MpGameManager::KillCurrentPlayer() {
		playerDead[currentPlayer] = true;
		postUiEventAction(UiEvent(UiEvent::PlayerDeadEvent(currentPlayer)));
		handleTurnEnd(currentPlayer);

		//If no other players found, and this one is dead...
		if (playerDead[currentPlayer]) {
			postUiEventAction(UiEvent(UiEvent::GameOverEvent(false, currentPlayer)));
		}
	}
}
