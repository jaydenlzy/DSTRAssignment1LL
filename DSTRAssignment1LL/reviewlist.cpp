#include "reviewlist.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include "SentimentCalculation.h"

using namespace std;

// Constructor for ReviewNode
ReviewNode::ReviewNode(string rev, int rate) {
    review = rev;
    rating = rate;
    positiveCount = 0;
    negativeCount = 0;
    next = nullptr;
}

// Constructor for ReviewList
ReviewList::ReviewList() {
    head = nullptr;
}

// Function to add a new review to the list
void ReviewList::addReview(string review, int rating) {
    ReviewNode* newNode = new ReviewNode(review, rating);
    if (head == nullptr) {
        head = newNode;
    }
    else {
        ReviewNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

std::unordered_set<std::string> loadWordsFromFile(const std::string& filename) {
    std::unordered_set<std::string> words;
    std::ifstream file(filename);
    std::string word;

    if (file.is_open()) {
        while (std::getline(file, word)) {
            words.insert(word);
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }

    return words;
}


// Function to display reviews (for debugging or general output)
void ReviewList::displayReviews() {
    if (head == nullptr) {
        cout << "No reviews available!" << endl;
        return;
    }
    ReviewNode* temp = head;
    while (temp != nullptr) {
        cout << "Review: " << temp->review << endl;
        cout << "Rating: " << temp->rating << endl;
        cout << "Positive Words (" << temp->positiveCount << "): ";
        temp->positiveWordList.displayWords();  // Display positive words
        cout << endl;

        cout << "Negative Words (" << temp->negativeCount << "): ";
        temp->negativeWordList.displayWords();  // Display negative words
        cout << endl;

        // Calculate and display sentiment score
        double sentimentScore = SentimentCalculation::calculateSentimentScore(temp->positiveCount, temp->negativeCount);
        cout << "Sentiment Score (1 - 5): " << sentimentScore << endl;

        temp = temp->next;
    }
}

// Function to count positive and negative words in each review
void ReviewList::countPositiveNegativeWords(const string& positiveFile, const string& negativeFile) {
    unordered_set<string> positiveWords = loadWordsFromFile(positiveFile);
    unordered_set<string> negativeWords = loadWordsFromFile(negativeFile);

    ReviewNode* temp = head;
    while (temp != nullptr) {
        stringstream ss(temp->review);
        string word;
        while (ss >> word) {
            // Remove any punctuation from the word
            word.erase(remove_if(word.begin(), word.end(), [](unsigned char c) { return ispunct(c); }), word.end());

            if (positiveWords.find(word) != positiveWords.end()) {
                temp->positiveCount++;
                temp->positiveWordList.addWord(word);  // Store the word in the linked list
            }
            else if (negativeWords.find(word) != negativeWords.end()) {
                temp->negativeCount++;
                temp->negativeWordList.addWord(word);  // Store the word in the linked list
            }
        }
        temp = temp->next;
    }
}

// Linear search through all reviews and perform sentiment analysis
void ReviewList::linearSearchAllReviews() {
    ReviewNode* temp = head;

    while (temp != nullptr) {
        // Perform sentiment analysis for each review
        cout << "Review (Linear Search): " << temp->review << endl;
        cout << "Rating: " << temp->rating << endl;
        cout << "Positive Words: " << temp->positiveCount << " [";
        temp->positiveWordList.displayWords();
        cout << "]" << endl;
        cout << "Negative Words: " << temp->negativeCount << " [";
        temp->negativeWordList.displayWords();
        cout << "]" << endl;

        // Calculate sentiment score
        double sentimentScore = SentimentCalculation::calculateSentimentScore(temp->positiveCount, temp->negativeCount);
        cout << "Sentiment Score (1 - 5): " << sentimentScore << endl;

        temp = temp->next;
    }
}
