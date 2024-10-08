#ifndef REVIEWLIST_H
#define REVIEWLIST_H

#include <string>
#include <iostream>

struct WordNode {
    std::string word;
    WordNode* next;

    WordNode(std::string w) : word(w), next(nullptr) {}
};

struct WordList {
    WordNode* head;

    WordList() : head(nullptr) {}

    void addWord(const std::string& word) {
        WordNode* newNode = new WordNode(word);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            WordNode* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void displayWords() const {
        WordNode* temp = head;
        while (temp != nullptr) {
            std::cout << temp->word << " ";
            temp = temp->next;
        }
    }
};

// Node structure to store review
struct ReviewNode {
    std::string review;
    int rating;
    int positiveCount;
    int negativeCount;
    ReviewNode* next;

    WordList positiveWordList;  // Store positive words as a linked list
    WordList negativeWordList;  // Store negative words as a linked list

    ReviewNode(std::string rev, int rate);
};

// Class to manage linked list of reviews
class ReviewList {
private:
    ReviewNode* head; // Pointer to the head of the list

public:
    // Constructor to initialize the list
    ReviewList();

    // Function to add a new review to the list
    void addReview(std::string review, int rating);

    // Function to display all the reviews
    void displayReviews();

    // Function to count positive and negative words in each review
    void countPositiveNegativeWords(const std::string& positiveFile, const std::string& negativeFile);

    // Function to perform linear search and sentiment analysis on all reviews
    void linearSearchAllReviews();  // Declare the linear search function
};

#endif
