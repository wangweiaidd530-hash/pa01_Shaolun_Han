// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;
int main(int argc, char** argv){
  set<Card> aliceCards, bobCards;
  
  if(argc < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argv[1]);
  ifstream cardFile2 (argv[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file" << endl;
    return 1;
  }

  while (getline (cardFile1, line) && (line.length() >= 3)){
      char suit = line[0];
      string value = line.substr(2);
      aliceCards.insert(Card(suit, value));
  }
  cardFile1.close();

  while (getline (cardFile2, line) && (line.length() >= 3)){
      char suit = line[0];
      string value = line.substr(2);
      bobCards.insert(Card(suit, value));
  }
  cardFile2.close();
  
  bool matchFound = true;
  while (matchFound) {
      matchFound = false;

      
      for (auto it = aliceCards.begin(); it != aliceCards.end(); ++it) {
          if (bobCards.find(*it) != bobCards.end()) {
              cout << "Alice picked matching card " << (*it).getSuit() << " " << (*it).getValue() << endl;
              Card matchedCard = *it;
              aliceCards.erase(matchedCard);
              bobCards.erase(matchedCard);
              matchFound = true;
              break; 
          }
      }

      if (!matchFound) break; 
      matchFound = false;

      
      for (auto it = bobCards.rbegin(); it != bobCards.rend(); ++it) {
          if (aliceCards.find(*it) != aliceCards.end()) {
              cout << "Bob picked matching card " << (*it).getSuit() << " " << (*it).getValue() << endl;
              Card matchedCard = *it;
              aliceCards.erase(matchedCard);
              bobCards.erase(matchedCard);
              matchFound = true;
              break; 
          }
      }
  }

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
