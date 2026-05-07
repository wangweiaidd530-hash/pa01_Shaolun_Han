// card.h
// Author: Shaolun Han
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>
struct Card {
    char suit;
    std::string value;
    Card();
    Card(char s, std::string v);
    char getSuit() const;
    std::string getValue() const;
    bool operator<(const Card& that) const;
    bool operator==(const Card& that) const;
    bool operator>(const Card& that) const;
};
std::ostream& operator<<(std::ostream& first, const Card& card);
#endif
