#include "Board.h"
#include <algorithm>
#include <cstdlib>

namespace mMp {
	Board::BoardPoint::BoardPoint(int line, int column)
		: line(line), column(column) {
	}

	int dvL[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	int dvC[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	Board::BoardPoint Board::BoardPoint::getNeighbor(Direction direction) {
		return BoardPoint(line + dvL[direction], column + dvC[direction]);
	}

	Board::Board(int size, int mineCount)
		: size(size), mineCount(mineCount) {
		generate();
	}

	bool Board::isMine(BoardPoint point) {
		if (point.line < 0 || point.line >= maxSize || point.column < 0 || point.column >= maxSize) {
			return false;
		}
		return mines[point.line][point.column];
	}

	int Board::getNeighbors(BoardPoint point) {
		int count = 0;
		for (int i = 0; i < 8; i++) {
			if (isMine(point.getNeighbor((Direction) i))) {
				count++;
			}
		}
		return count;
	}

	void Board::generate() {
		bool probExists[maxSize * maxSize] = {};
		int mineProb[maxSize][maxSize];

		const int cornerPadding = 3;

		//First, generate a matrix of _unique_ "probability factors" up to size^2.
		//Along the corners are guaranteed safe cells to decrease the luck factor.
		for (int l = 0; l < size; l++) {
			int currentPadding = max(max(cornerPadding - l, cornerPadding - (size - l - 1)), 0);
			for (int c = 0; c < currentPadding; c++) {
				mineProb[l][c] = 0;
				mineProb[l][size - c] = 0;
			}
			for (int c = currentPadding; c < size - currentPadding; c++) {
				int probability;
				do {
					probability = rand() % (size * size);
				} while (probExists[probability]);

				probExists[probability] = true;
				mineProb[l][c] = probability;
			}
		}
		//Find the top [mineCount] probability factors. Those will be the mines.
		int probCounter = 0;
		int maxSafe;
		for (maxSafe = size * size - 1; maxSafe >= 0 && probCounter < mineCount; maxSafe--) {
			if (probExists[maxSafe]) {
				probCounter++;
			}
		}
		//Set the mines. Also, initialize the "revealed" matrix to 0.
		for (int l = 0; l < size; l++) {
			for (int c = 0; c < size; c++) {
				mines[l][c] = (mineProb[l][c] > maxSafe);
				revealed[l][c] = false;
			}
		}
	}
}
