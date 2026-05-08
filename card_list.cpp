// card_list.cpp
// Author: Shaolun Han
// Actually, this is very similar to the BST ones, I just copy most of it, find useful functions and copied, delete useless helpers. That's the case.
// Implementation of the classes defined in card_list.h
#include "card_list.h"
CardList::CardList() {
    root = nullptr;
}

CardList::~CardList() {
    clear(root);
}

void CardList::clear(Node* node) {
    if (node == nullptr) {return;}
    clear(node->left);
    clear(node->right);
    delete node;
}

CardList::Node* CardList::getNodeFor(const Card& c, Node* n) const {
    if (n == nullptr) {
        return nullptr;
    }
    if (n->data == c) {
        return n;
    }
    if (n->data < c) {
        return getNodeFor(c, n->right);
    }
    else {
        return getNodeFor(c, n->left);
    }
}

bool CardList::containsCard(const Card& c) const {
    if (getNodeFor(c, root) == nullptr) {return false;}
    else {return true;}
}

CardList::Node* CardList::getMin(Node* n) const {
    if (n == nullptr) {
        return nullptr;
    }
    while (n->left != nullptr) {
        n = n->left;
    }
    return n;
}

CardList::Node* CardList::getMax(Node* n) const {
    if (n == nullptr) {
        return nullptr;
    }
    while (n->right != nullptr) {
        n = n->right;
    }
    return n;
}

bool CardList::insertCard(const Card& c) {
    if (root == nullptr) {
        root = new Node(c);
        return true;
    }
    return insert(c, root);
}

bool CardList::insert(const Card& c, Node* n) {
    if (c == n->data) {
        return false;
    }
    if (c < n->data) {
        if (n->left == nullptr) {
            n->left = new Node(c);
            n->left->parent = n;
            return true;
        }
       	else {
            return insert(c, n->left);
        }
    } 
    else {
        if (n->right == nullptr) {
            n->right = new Node(c);
            n->right->parent = n;
            return true;
        }
       	else {
            return insert(c, n->right);
        }
    }
}

void CardList::printInOrder() const {
    printInOrder(root);
}

void CardList::printInOrder(Node* n) const {
    if (n == nullptr) {
        return;
    }
    printInOrder(n->left);
    std::cout << n->data << std::endl;
    printInOrder(n->right);
}

CardList::Node* CardList::getSuccessorNode(Node* n) const {
    if (n == nullptr) {
        return nullptr;
    }
    if (n->right != nullptr) {
        return getMin(n->right);
    }
    Node* parent = n->parent;
    while (parent != nullptr && n == parent->right) {
        n = parent;
        parent = parent->parent;
    }
    return parent;
}

CardList::Node* CardList::getPredecessorNode(Node* n) const {
    if (n == nullptr) {
        return nullptr;
    }
    if (n->left != nullptr) {
        return getMax(n->left);
    }
    Node* parent = n->parent;
    while (parent != nullptr && n == parent->left) {
        n = parent;
        parent = parent->parent;
    }
    return parent;
}
bool CardList::removeCard(const Card& c) {
    Node* node = getNodeFor(c, root);
    if (node == nullptr) return false;
    if (!node->left && !node->right) {
        if (node->parent == nullptr) {
            root = nullptr;
        }
       	else if (node->parent->left == node) {
            node->parent->left = nullptr;
        }
       	else {
            node->parent->right = nullptr;
        }
        delete node;
    }
    else if (!node->left || !node->right) {
        Node* child = (node->left) ? node->left : node->right;

        if (node->parent == nullptr) {
            root = child;
        }
       	else if (node->parent->left == node) {
            node->parent->left = child;
        }
       	else {
            node->parent->right = child;
        }
        child->parent = node->parent;
        delete node;
    }
    else {
        Node* succNode = node->right;
        while (succNode->left) {
            succNode = succNode->left;
        }
        node->data = succNode->data;
        Node* succChild = succNode->right;

        if (succNode->parent->left == succNode) {
            succNode->parent->left = succChild;
        }
       	else {
            succNode->parent->right = succChild;
        }
        if (succChild) {
            succChild->parent = succNode->parent;
        }
        delete succNode;
    }
    return true;
}

CardList::Iterator::Iterator(Node* p) : curr(p) {}
Card& CardList::Iterator::operator*() const {
    return curr->data;
}
CardList::Iterator& CardList::Iterator::operator++() {
    if (curr) {
        if (curr->right) {
            curr = curr->right;
            while (curr->left) curr = curr->left;
        }
       	else {
            Node* p = curr->parent;
            while (p && curr == p->right) {
                curr = p;
                p = p->parent;
            }
            curr = p;
        }
    }
    return *this;
}
CardList::Iterator& CardList::Iterator::operator--() {
    if (curr) {
        if (curr->left) {
            curr = curr->left;
            while (curr->right) curr = curr->right;
        } 
	else {
            Node* p = curr->parent;
            while (p && curr == p->left) {
                curr = p;
                p = p->parent;
            }
            curr = p;
        }
    }
    return *this;
}

bool CardList::Iterator::operator==(const Iterator& other) const {
    return curr == other.curr;
}

bool CardList::Iterator::operator!=(const Iterator& other) const {
    return curr != other.curr;
}

CardList::Iterator CardList::begin() const {
    return Iterator(getMin(root));
}

CardList::Iterator CardList::end() const {
    return Iterator(nullptr);
}

CardList::Iterator CardList::rbegin() const {
    return Iterator(getMax(root));
}

CardList::Iterator CardList::rend() const {
    return Iterator(nullptr);
}
void playGame(CardList& alice, CardList& bob) {
    bool cardFound = true;
    while (cardFound) {
        cardFound = false; 
        for (auto itA = alice.begin(); itA != alice.end(); ++itA) {
            Card currentCard = *itA;
            if (bob.containsCard(currentCard)) {
                std::cout << "Alice picked matching card " << currentCard << std::endl;
                
                alice.removeCard(currentCard);
                bob.removeCard(currentCard);
                
                cardFound = true; 
                break; 
            }
        }
        if (!cardFound) break;
        bool bobFound = false;
        for (auto itB = bob.rbegin(); itB != bob.rend(); --itB) {
            Card currentCard = *itB;
            if (alice.containsCard(currentCard)) {
                std::cout << "Bob picked matching card " << currentCard << std::endl;
                alice.removeCard(currentCard);
                bob.removeCard(currentCard);
                bobFound = true; 
                break; 
            }
        }
        if (!bobFound) {
            cardFound = false; 
        } else {
            cardFound = true; 
        }
    }
    std::cout << std::endl;
    std::cout << "Alice's cards:" << std::endl;
    alice.printInOrder();
    std::cout << std::endl;
    std::cout << "Bob's cards:" << std::endl;
    bob.printInOrder();
}
