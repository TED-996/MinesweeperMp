#include<iostream>
#include "Board.h"
#include <cstdlib>
#include <ctime>
using namespace std;

void print(mMp::Board board);

int main() {
	srand((unsigned int) time(nullptr));
	int size = 25;
	mMp::Board board(size, (int) (size * size * 0.24));

	board.reveal(mMp::Board::BoardPoint(0, 0));
	board.reveal(mMp::Board::BoardPoint(0, size - 1));
	board.reveal(mMp::Board::BoardPoint(size - 1, 0));
	board.reveal(mMp::Board::BoardPoint(size - 1, size - 1));

	print(board);
	return 0;
}

void print(mMp::Board board) {
	int counter = 0;
	for (int c = 0; c < board.size + 2; c++) {
		cout << '|';
	}
	cout << '\n';
	for (int l = 0; l < board.size; l++) {
		cout << '|';
		for (int c = 0; c < board.size; c++) {
			mMp::Board::BoardPoint point(l, c);
			if (board.isMine(point)) {
				cout << '+';
				counter++;
			}
			else if (board.isRevealed(point)) {
				cout << board.getNeighbors(point);
			}
			else {
				cout << ' ';
			}
		}
		cout << '|' << '\n';
	}
	for (int c = 0; c < board.size + 2; c++) {
		cout << '|';
	}
	cout << '\n';
	cout << counter << " mines in total." << '\n';
}