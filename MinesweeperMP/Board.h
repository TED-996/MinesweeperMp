#pragma once
#include <vector>
#include "Defines.h"

namespace mMp {
	using namespace std;
	class Board
	{
	public:
		struct BoardPoint
		{
			int line;
			int column;
			
			BoardPoint(int line, int column);

			BoardPoint getNeighbor(Direction direction);
			BoardPoint clampMax(int max);

			friend bool operator==(const BoardPoint& lhs, const BoardPoint& rhs) {
				return lhs.line == rhs.line && lhs.column == rhs.column;
			}

			friend bool operator!=(const BoardPoint& lhs, const BoardPoint& rhs) {
				return !(lhs == rhs);
			}
		};
	public:
		static const int maxSize = 100;

		int size;
		int mineCount;
	private:
		bool mines[maxSize][maxSize];
		bool revealed[maxSize][maxSize];
		bool flagged[maxSize][maxSize];
		int neighbors[maxSize][maxSize];

		int revealCount;
		int flagCount;

	public:
		Board(int size, int mineCount);

		bool isMine(BoardPoint point);
		bool isRevealed(BoardPoint point);
		bool isFlagged(BoardPoint point);
		bool isValid(BoardPoint point);
		int getNeighbors(BoardPoint point);

		bool isCompleted(bool byFlags = false);

		vector<BoardPoint> reveal(BoardPoint root);
		void toggleFlag(BoardPoint point);
	private:
		void generate();
	};
}
