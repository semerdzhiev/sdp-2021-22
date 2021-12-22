#include "LinearProbingHashSet.h"

void LinearProbingHashSet::rehash() {
	vector<int> oldData = data;
	volume *= 2;
	remainingFree = volume;
	data.resize(volume);
	takenPositions.resize(volume);
	for (int i = 0; i < volume; ++i) {
		takenPositions[i] = false;
	}
	for (int i = 0; i < oldData.size(); ++i) {
		add(oldData[i]);
	}
}

LinearProbingHashSet::LinearProbingHashSet(int volume) : volume(volume), remainingFree(volume) {
	data.resize(volume);
	takenPositions.resize(volume);
	for (int i = 0; i < volume; ++i) {
		takenPositions[i] = false;
	}
}

void LinearProbingHashSet::add(int number) {
	if (remainingFree == 0) {
		rehash();
	}

	int freeIndex = number % volume;
	for (; takenPositions[freeIndex]; freeIndex = (freeIndex + 1) % volume);
	data[freeIndex] = number;
	takenPositions[freeIndex] = true;
	remainingFree -= 1;
}

bool LinearProbingHashSet::has(int number) {
	for (int numberIndex = number % volume; takenPositions[numberIndex]; ++numberIndex) {
		if (data[numberIndex] == number) {
			return true;
		}
	}
	return false;
}

void LinearProbingHashSet::print() {
	for (int i = 0; i < volume; ++i) {
		if (takenPositions[i]) {
			cout << data[i];
		} else {
			cout << "x";
		}
		cout << " ";
	}
	cout << endl;
}
