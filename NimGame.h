// Christian Jeune, ID: 40279265
// Pawan Kumar Gupta, ID: 40254781
// COEN 243-Nim To Win project
// Due Date: December 3, 2023
// Definition of NimGame class

#pragma once
#ifndef NIMGAME_H_
#define NIMGAME_H_

#include <string>
#include <vector>
#include <array>
#include <random> // Include for random number generation
using namespace std;

class NimGame {
private:
    array<string, 2> players; // Array to store player names
    int initialToken; // Initial number of tokens
    int token; // Total number of tokens
    vector<int> heaps; // Vector to represent the piles of tokens
    uniform_int_distribution<int> randomHeap; // Uniform distribution for random heap selection

public:
    // Constructor to initialize the NimGame object
    NimGame(string player1, string player2, int heaps, int numToken = -1);

    // Function to display the current state of the heaps
    void displayHeaps();

    // Function to display the winner of the game
    void displayWinner(string winner);

    // Function to find a winning move for the current player
    int winningMove();

    // Function to process a move made by a user
    void processUserMove(string player);

    // Function to process a move made by the computer
    void processComputerMove(string player);

    // Function to handle a user vs. user game
    void userVsUser(int index);

    // Function to handle a user vs. computer game
    void userVsComputer(int index);

    // Function to distribute tokens randomly among the heaps
    void distributeRandomly(int numToken);

    // Function to distribute tokens based on binary weight among the heaps
    void distributeBinaryWeight(int numHeap);
	
};

#endif
