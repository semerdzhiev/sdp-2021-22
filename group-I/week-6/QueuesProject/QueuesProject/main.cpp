#include <iostream>
#include "queue.hpp"

int knightMovement(char startRank, int startFile, int targetRank, int targetFile);

int main() {
	cout << "Knight minumum movement from d4 to f3: " << knightMovement('d', 4, 'g', 4);

	return 0;
}