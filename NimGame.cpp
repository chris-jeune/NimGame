// Christian Jeune, ID: 40279265
// Pawan Kumar  Gupta, ID: 40254781
// COEN 243-Nim To Win project
// Due Date: December 3, 2023
// Implementation of NimGame class

#include "NimGame.h"
#include <iostream>
#include <ctime> // Include for time function
#include <cmath>
using namespace std;

// Random number engine for distribution
default_random_engine engine(static_cast<int>(time(0)));
uniform_int_distribution<int> randomObjects(1, 2);

// Constructor for NimGame
NimGame::NimGame(string player1, string player2, int numHeaps, int numToken) {
	players = { player1, player2 };
	heaps.resize(numHeaps);
	token = numToken;
	randomHeap = uniform_int_distribution<int>(0, numHeaps - 1);
	// Check if the total number of tokens is specified
	if (numToken == -1) {
		distributeBinaryWeight(numHeaps);
	}
	else {
		distributeRandomly(numToken);
	}

}

// Function to display the current state of the heaps
void NimGame::displayHeaps() {
	cout << "\nCurrent Game State:" << endl;
	for (int i = 0; i < heaps.size(); i++) {
		cout << "Heap " << static_cast<char>('A' + i) << ": ";
		for (int j = 0; j < heaps[i]; j++) {
			cout << "O";
		}
		cout << endl;
	}
	cout << "------------------------" << endl;
}

// Function to display the winner of the game
void NimGame::displayWinner(string winner) {
	cout << "\nThere is no more token.\n" << winner << " wins!!" << endl << endl;
}

// Function to find a winning move for the current player
int NimGame::winningMove() {
	int nimSum = 0;

	for (int i = 0; i < heaps.size();i++) {
		nimSum ^= heaps[i];
	}

	if (nimSum == 0) {
		return -1; // No winning move, return -1
	}

	else {
		return (nimSum % 2 == 0) ? 2 : 1; // The current position is winning if the nimSum is not 0
	}

}

// Function to process a move made by a user
void NimGame::processUserMove(string player) {
	char heap;
	int pileIndex;
	int objectsToRemove;
	do {
		
		cout << "\nEnter the pile letter (A-" << static_cast<char>('A' + heaps.size() - 1) << "): ";
		cin >> heap;

		pileIndex = static_cast<int>(heap - 'A'); // Adjust index to match array indexing (starting from 0)

		if (pileIndex < 0 || pileIndex >= heaps.size()) {
			cout << "\nInvalid pile letter. Please try again." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}
		
		cout << "\nEnter the number of objects to remove (1 or 2): ";
		while (!(cin >> objectsToRemove) || (objectsToRemove != 1 && objectsToRemove != 2)) {
			cout << "\nInvalid number of objects. Please try again." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\nEnter the number of objects to remove (1 or 2): ";
		}

		if (heaps[pileIndex] < objectsToRemove) {
			cout << "\nInvalid move. Not enough objects in the selected heap. Please try again." << endl;
			continue;
		}
		

		heaps[pileIndex] -= objectsToRemove;
		token -= objectsToRemove;
		cout << "\n" << player << " removed " << objectsToRemove << " objects from heap " << static_cast<char>('A' + pileIndex) << endl;

		break; // Valid move, exit the loop
	} while (true);
}

// Function to process a move made by the computer
void NimGame::processComputerMove(string player) {
	int objectsToRemove = winningMove();
	int index = 0;

	if (objectsToRemove == -1) {
		do {
			index = randomHeap(engine);
			objectsToRemove = randomObjects(engine);
		} while (heaps[index] < objectsToRemove);

	}

	else {

		for (int i = 1; i < heaps.size(); i++) {
			if (heaps[i] > heaps[index]) {
				index = i;
			}
		}
	}

	heaps[index] -= objectsToRemove;
	token -= objectsToRemove;
	cout << "\n" << player << " removed " << objectsToRemove << " objects from heap " << static_cast<char>('A' + index) << endl;
}

// Function to handle a user vs. user game
void NimGame::userVsUser(int index) {
	string player = players[index];
	cout << "\nIt is now " << player << "'s turn." << endl;
	displayHeaps();
	processUserMove(player);
	if (token == 0) {
		displayWinner(player);
	}
	if (token > 0) {
		userVsUser((index + 1) % 2);
	}
}

// Function to handle a user vs. computer game
void NimGame::userVsComputer(int index) {
	string player = players[index];
	cout << "\nIt is now " << player << "'s turn." << endl;
	displayHeaps();
	if (player != "Computer") {
		processUserMove(player);
	}
	else {
		processComputerMove(player);
	}
	if (token == 0) {
		displayWinner(player);
	}
	if (token > 0) {
		userVsComputer((index + 1) % 2);
	}

}

// Function to distribute tokens randomly among the heaps
void NimGame::distributeRandomly(int numToken) {
	int index = 0;
	if (numToken >= 5) {
		for (int i = 0; i < heaps.size(); i++) {
			heaps[i] = 1;
		}
	}
	for (int i = (numToken-5); i > 0; i--) {
		index = randomHeap(engine);
		heaps[index]++;
	}
}

// Function to distribute tokens based on binary weight among the heaps
void NimGame::distributeBinaryWeight(int numHeap) {
	token = 0;
	for (int i = 0; i < heaps.size(); i++) {
		heaps[i] = static_cast<int>(pow(2, i)); // [1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096]
		token += heaps[i];
	}
	initialToken= token;
}


