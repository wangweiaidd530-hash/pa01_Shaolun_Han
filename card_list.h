// card_list.h
// Author: Shaolun_Han
// All class declarations related to defining a BST that represents a player's hand
// Cited Prof. Mirza's BST Head Style Structure
#ifndef CARD_LIST_H
#define CARD_LIST_H
#include <iostream>
#include <string>
#include "card.h"
class CardList {
private:
    struct Node {
        Card data;
        Node* left;
        Node* right;
        Node* parent;
        Node(const Card& c)
            : data(c), left(nullptr), right(nullptr), parent(nullptr) {}
    };
public:
    CardList();
    ~CardList();
    bool insertCard(const Card& c);
    bool removeCard(const Card& c);
    bool containsCard(const Card& c) const;
    void printInOrder() const;
    class Iterator {
    public:
        Iterator(Node* p = nullptr);
        Card& operator*() const;
        Iterator& operator++();
        Iterator& operator--();
	bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    private:
        Node* curr;
    };
    Iterator begin() const;
    Iterator end() const;
    Iterator rbegin() const;
    Iterator rend() const;
private:
    Node* root;
    Node* getNodeFor(const Card& c, Node* n) const;
    void clear(Node* n);
    bool insert(const Card& c, Node* n);
    Node* insert(const Card& c, Node* n, Node* parent);
    void printInOrder(Node* n) const;
    Node* getSuccessorNode(Node* n) const;
    Node* getPredecessorNode(Node* n) const;
    Node* getMin(Node* n) const;
    Node* getMax(Node* n) const;
};
void playGame(CardList& alice, CardList& bob);
#endif
