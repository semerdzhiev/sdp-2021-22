#include <iostream>
#include "queue.hpp"

struct KnightPosition {
	int row, col, moves;

	KnightPosition() : row(0), col(0), moves(0) {}
	KnightPosition(int row, int col, int moves) : row(row), col(col), moves(moves) {}
};

int knightMovement(char startRank, int startFile, int targetRank, int targetFile) {
    int startRow = startFile - 1;
    int startCol = startRank - 'a';
    int targetRow = targetFile - 1;
    int targetCol = targetRank - 'a';
    bool visited[8][8] = { {false} };

    Queue<KnightPosition> bfsQueue;
    bfsQueue.enqueue(KnightPosition(startRow, startCol, 0));
    while (!bfsQueue.empty()) {
        KnightPosition currentPosition = bfsQueue.front();
        bfsQueue.dequeue();
        if (visited[currentPosition.row][currentPosition.col]) {
            continue;
        }
        if (currentPosition.row == targetRow && currentPosition.col == targetCol) {
            return currentPosition.moves;
        }
        visited[currentPosition.row][currentPosition.col] = true;


        int multipliers[] = { -1, 1 };
        int multipliersCount = 2;
        for (int multiplierIndex1 = 0; multiplierIndex1 < multipliersCount; ++multiplierIndex1) {
            for (int multiplierIndex2 = 0; multiplierIndex2 < multipliersCount; ++multiplierIndex2) {
                KnightPosition nextPosition(currentPosition.row + multipliers[multiplierIndex1] * 1,
                    currentPosition.col + multipliers[multiplierIndex2] * 2,
                    currentPosition.moves + 1);
                if (nextPosition.row >= 0 && nextPosition.row < 8 && nextPosition.col >= 0 && nextPosition.col < 8) {
                    bfsQueue.enqueue(nextPosition);
                }

                nextPosition = KnightPosition(currentPosition.row + multipliers[multiplierIndex1] * 2,
                    currentPosition.col + multipliers[multiplierIndex1] * 1,
                    currentPosition.moves + 1);
                if (nextPosition.row >= 0 && nextPosition.row < 8 && nextPosition.col >= 0 && nextPosition.col < 8) {
                    bfsQueue.enqueue(nextPosition);
                }
            }
        }
    }
    return -1;
}