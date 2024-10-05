#include "LinkedList.hpp"
#include <iostream>

// ReviewNode constructor
ReviewNode::ReviewNode(const std::string& fb, int rate) {
    feedback = fb;
    rating = rate;
    next = nullptr;
}

// LinkedList constructor
LinkedList::LinkedList() {
    headReview = nullptr;
    tailReview = nullptr;  // Tail pointer initialization
    nodeCount = 0;         // Initialize the node count
}

// LinkedList destructor
LinkedList::~LinkedList() {
    ReviewNode* current = headReview;
    while (current) {
        ReviewNode* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

// Add a new review to the review linked list
void LinkedList::addReview(const std::string& feedback, int rating) {
    ReviewNode* newNode = new ReviewNode(feedback, rating);
    if (!headReview) {
        headReview = tailReview = newNode;  // If the list is empty, set both head and tail
    }
    else {
        tailReview->next = newNode;  // Append new node at the end
        tailReview = newNode;        // Move the tail pointer to the new last node
    }
    nodeCount++;  // Increment the node count
}

// Print all reviews and ratings
void LinkedList::printReviews() const {
    ReviewNode* temp = headReview;
    while (temp) {
        std::cout << "Review: " << temp->feedback
            << " | Rating: " << temp->rating << std::endl;
        temp = temp->next;
    }
}

// Return the number of reviews in the list
int LinkedList::getCount() const {
    return nodeCount;
}

// WordNode constructor
WordNode::WordNode(const std::string& w) {
    word = w;
    next = nullptr;
}

// WordLinkedList constructor
WordLinkedList::WordLinkedList() {
    headWord = nullptr;
    tailWord = nullptr;  // Tail pointer initialization
    wordCount = 0;       // Initialize the word count
}

// WordLinkedList destructor
WordLinkedList::~WordLinkedList() {
    WordNode* current = headWord;
    while (current) {
        WordNode* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

// Add a new word to the word linked list
void WordLinkedList::addWord(const std::string& word) {
    WordNode* newNode = new WordNode(word);
    if (!headWord) {
        headWord = tailWord = newNode;  // If the list is empty, set both head and tail
    }
    else {
        tailWord->next = newNode;  // Append new node at the end
        tailWord = newNode;        // Move the tail pointer to the new last node
    }
    wordCount++;  // Increment the word count
}

// Print all words in the linked list
void WordLinkedList::printWords() const {
    WordNode* temp = headWord;
    while (temp) {
        std::cout << "Word: " << temp->word << std::endl;
        temp = temp->next;
    }
}

// Return the number of words in the list
int WordLinkedList::getCount() const {
    return wordCount;
}
