// card_list.h
// Author: Shaolun_Han
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H
#include <iostream>
#include <string>
#include "card.h"
class CardList {
public:
    CardList();
    void insertCard(const Card& c);
    void removeCard(const Card& c);
    bool containsCard(const Card& c) const;
private:
    struct TreeNode {
        Card data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(const Card& c)
            : data(c), left(nullptr), right(nullptr) {}
    };
    TreeNode* root;
    TreeNode* insert(TreeNode* node, const Card& c);
    TreeNode* remove(TreeNode* node, const Card& c);
    bool contains(TreeNode* node, const Card& c) const;
};
#endif
