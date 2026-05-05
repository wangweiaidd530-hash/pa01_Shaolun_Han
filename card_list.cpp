// card_list.cpp
// Author: Shaolun Han
// Implementation of the classes defined in card_list.h
#include "card_list.h";
void CardList::insertCard(const Card& c) {
    insert(root, c);
}
CardList::TreeNode* insert(TreeNode* node, const Card& c) {
    if (node == nullptr) {
        node = new TreeNode(c);
	return node;
    }
    if (c == node->data) {
        return node;
    }
    if (c < node->data) {
        node->left = insert(node->left, c);
    }
    if (c > node->data) {
        node->right = insert(node->right, c);
    }
    return node;
}
void CardList::removeCard(const Card& c) {}
CardList::TreeNode* remove(TreeNode* node, const Card& c) {
    
}
bool CardList::containsCard(const Card& c) const {
    return contains(root, c);
}
CardList::bool contains(TreeNode* node, const Card& c) const {
    if (node == nullptr) {
        return false;
    }
    if (node->data == c) {
        return true;
    }
    if (c < node->data) {
        return contains(node->left, c);
    }
    else {
        return contains(node->right, c);
    }
}

