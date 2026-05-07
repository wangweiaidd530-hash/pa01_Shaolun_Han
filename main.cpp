// This file should implement the game using a custom implementation of a BST (based on your earlier BST implementation)
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"
//Do not include set in this file
using namespace std;
int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream cardFile1(argv[1]);
    ifstream cardFile2(argv[2]);
    string line;

    if (cardFile1.fail() || cardFile2.fail()) {
        cout << "Could not open file" << endl;
        return 1;
    }

    CardBST aliceCards;
    CardBST bobCards;

    while (getline(cardFile1, line) && (line.length() >= 3)) {
        char suit = line[0];
        string value = line.substr(2);
        aliceCards.insert(Card(suit, value));
    }
    cardFile1.close();

    while (getline(cardFile2, line) && (line.length() >= 3)) {
        char suit = line[0];
        string value = line.substr(2);
        bobCards.insert(Card(suit, value));
    }
    cardFile2.close();

    playGame(aliceCards, bobCards);

    cout << endl << "Alice's cards:" << endl;
    for (auto it = aliceCards.begin(); it != aliceCards.end(); ++it) {
        cout << (*it).getSuit() << " " << (*it).getValue() << endl;
    }

    cout << endl << "Bob's cards:" << endl;
    for (auto it = bobCards.begin(); it != bobCards.end(); ++it) {
        cout << (*it).getSuit() << " " << (*it).getValue() << endl;
    }

    return 0;
}
