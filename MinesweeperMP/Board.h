﻿#pragma once
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
		};
	public:
		static const int maxSize = 100;

		int size;
		int mineCount;
	private:
		bool mines[maxSize][maxSize];
		bool revealed[maxSize][maxSize];
		bool flagged[maxSize][maxSize];

		int revealCount;

	public:
		Board(int size, int mineCount);

		bool isMine(BoardPoint point);
		bool isRevealed(BoardPoint point);
		bool isFlagged(BoardPoint point);
		int getNeighbors(BoardPoint point);

		bool isCompleted();

		vector<BoardPoint> reveal(BoardPoint root);
		void toggleFlag(BoardPoint point);
	private:
		bool isValid(BoardPoint point);
		void generate();
	};
}
