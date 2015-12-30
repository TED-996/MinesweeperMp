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
		};
	public:
		static const int maxSize = 100;

		int size;
		int mineCount;
	private:
		bool mines[maxSize][maxSize];
		bool revealed[maxSize][maxSize];

	public:
		Board(int size, int mineCount);

		bool isMine(BoardPoint point);
		int getNeighbors(BoardPoint point);

		//vector<BoardPoint> reveal(BoardPoint root);
	private:
		void generate();
	};
}
