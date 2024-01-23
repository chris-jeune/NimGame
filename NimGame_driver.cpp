// Christian Jeune, ID: 40279265
// Pawan Kumar Gupta, ID: 40254781
// COEN 243-Nim To Win project
// Due Date: December 3, 2023
// main file to initiate the Nim Game

#include "NimGame.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// Function to print the rules of the Nim Game
void printGameRules() {
	cout << "Welcome to the Nim Game!\n";
	cout << "Rules:\n";
	cout << "1. This game includes two players.\n";
	cout << "2. Each player can pick up from one pile.\n";
	cout << "3. Each player can only take one or two tokens.\n";
	cout << "4. The winner is the player who makes the last move.\n";
	cout << "5. Enjoy the game!\n\n";
}

// Function to prompt the user to choose an option (User vs. User, PC vs. User, or Exit)
void chooseOption() {
	int choice;
	cout << "Choose an option:\n";
	cout << "1. User vs. User\n";
	cout << "2. PC vs. User\n";
	cout << "3. Exit\n\n";

	// Get input for the user's choice
	cout << "Enter your choice: ";

	while (!(cin >> choice)) {
		cout << "\nInvalid choice. Please try again.\n\n";
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Enter your choice: ";
	}


	switch (choice) {
	case 1: {
		string player1, player2;
		int numTokens;

		// Get input for User vs. User game
		cout << "\nEnter Player 1's name: ";
		cin >> player1;

		cout << "\nEnter Player 2's name: ";
		cin >> player2;

		cout << "\nEnter the total number of tokens(greater than or equal to 5): ";
		while (!(cin >> numTokens) || numTokens < 5) {
			cout << "\nInvalid choice. Please try again.\n";
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\nEnter the total number of tokens(greater than or equal to 5): ";
		}

		// Initialize NimGame object for User vs. User
		NimGame nimGame(player1, player2, 5, numTokens);

		cout << "\nGame Start" << endl;

		// Start User vs. User game
		nimGame.userVsUser(0);
		break;
	}
	case 2: {
		string playerName;
		int numHeaps;

		// Get input for PC vs. User game
		cout << "\nEnter your name: ";
		cin >> playerName;

		cout << "\nEnter the number of heaps: ";

		while (!(cin >> numHeaps) || numHeaps < 1) {
			cout << "\nInvalid choice. Please try again.\n";
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\nEnter the number of heaps: ";
		}

		// Initialize NimGame object for PC vs. User
		NimGame nimGame("Computer", playerName, numHeaps);

		cout << "\nGame Start" << endl;

		// Start PC vs. User game
		nimGame.userVsComputer(0);
		break;
	}
	case 3:
		cout << "\nGoodbye!\n";
		return;
	default:
		cout << "\nInvalid choice. Please try again.\n\n";
		break;
	}

	// Recursively prompt the user for another option
	chooseOption();
}

// Main function to initiate the Nim Game
int main() {
	// Display the rules of the game
	printGameRules();

	// Prompt the user to choose an option and start the game
	chooseOption();

	return 0;
}
