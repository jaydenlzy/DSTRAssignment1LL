#ifndef REVIEWLIST_HPP
#define REVIEWLIST_HPP

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

    bool contains(const std::string& word) const;

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

struct WordFrequencyNode {
    std::string word;
    int count;
    WordFrequencyNode* next;
    WordFrequencyNode(std::string w, int c) : word(w), count(c), next(nullptr) {}
};

class WordFrequencyList {
private:
    
public:
    WordFrequencyList() : head(nullptr) {}
    WordFrequencyNode* head;
    void addWordFrequency(const std::string& word);
    void displayWordFrequencies(std::ofstream* outFile = nullptr);
    void insertionSort(); 
    void selectionSort(); 
    void displayTop5Frequencies(std::ofstream& outFile, const std::string& type);
};



// Class to manage linked list of reviews
class ReviewList {
private:

public:
    // Constructor to initialize the list
    ReviewList();
    ReviewNode* head; // Pointer to the head of the list
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
    void addPositiveWordsToFrequencyList(WordFrequencyList& wordFreqList);
    void addNegativeWordsToFrequencyList(WordFrequencyList& wordFreqList);
};

#endif