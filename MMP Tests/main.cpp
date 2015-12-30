#include<iostream>
#include "Board.h"
#include <cstdlib>
#include <ctime>
using namespace std;

void print(mMp::Board board);

int main() {
	srand(time(nullptr));
	mMp::Board board(75, (int) (75 * 75 * 0.25));
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
			if (board.isMine(mMp::Board::BoardPoint(l, c))) {
				cout << '+';
				counter++;
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