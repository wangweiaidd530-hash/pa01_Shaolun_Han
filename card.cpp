// card.cpp
// Author: Shaolun Han
// AI Usage: static, which is better since we don't want the user to access it elsewhere.
// Implementation of the classes defined in card.h
#include <iostream>
#include "card.h"
Card::Card() {
    suit = 'c';
    value = '2';
}

Card::Card(char su, std::string val) {
    suit = su;
    value = val;
}

static int cardVal(const char s, std::string v) {
    int num = 0;
    if (s == 'c') num += 100;
    if (s == 'd') num += 200;
    if (s == 's') num += 300;
    if (s == 'h') num += 400;
    if (v == "a") num += 1;
    if (v == "2") num += 2;
    if (v == "3") num += 3;
    if (v == "4") num += 4;
    if (v == "5") num += 5;
    if (v == "6") num += 6;
    if (v == "7") num += 7;
    if (v == "8") num += 8;
    if (v == "9") num += 9;
    if (v == "10") num += 10;
    if (v == "j") num += 11;
    if (v == "q") num += 12;
    if (v == "k") num += 13;
    return num;
}

bool Card::operator<(const Card& that) const {
    int thisVal = cardVal(this->suit, this->value);
    int thatVal = cardVal(that.suit, that.value);
    return thisVal < thatVal;
}

bool Card::operator==(const Card& that) const {
    return cardVal(this->suit, this->value) == cardVal(that.suit, that.value);
}

bool Card::operator>(const Card& that) const {
    return that < *this;
}

std::ostream& operator<<(std::ostream& first, const Card& card) {
    first << card.suit << " " << card.value;
    return first;
}

char Card::getSuit() const {
    return suit;
}

std::string Card::getValue() const {
    return value;
}
