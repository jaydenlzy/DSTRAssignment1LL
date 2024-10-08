#ifndef REVIEWLIST_H
#define REVIEWLIST_H

#include <string>
#include <iostream>
std::string evaluateReview(double sentimentScore, double rating);

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
    void displayWords() const;
    void displayWords(std::string& output) const {
        WordNode* temp = head;
        while (temp != nullptr) {
            output += temp->word; // Append the word
            if (temp->next != nullptr) {
                output += ", ";  // Add a comma and space if there's a next word
            }
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
    void linearSearchAllReviews(std::ofstream* outFile = nullptr);  // Declare the linear search function
    double calculateSentimentScore(int index);  // Declaration of the sentiment calculation function
    void getReview(int index, std::string& review, int& rating);  // Declaration for retrieving a review and rating
    int getSize();  // Declaration for getting the total number of reviews

};

#endif