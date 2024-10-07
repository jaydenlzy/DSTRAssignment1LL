#include "reviewlist.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_set>

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

        temp = temp->next;
    }
}


// Function to load words from a file into an unordered_set for fast lookup
unordered_set<string> loadWordsFromFile(const string& filename) {
    unordered_set<string> words;
    ifstream file(filename);
    string word;

    if (file.is_open()) {
        while (getline(file, word)) {
            words.insert(word);
        }
        file.close();
    }
    else {
        cout << "Unable to open file: " << filename << endl;
    }
    return words;
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


// Binary search to find and display a review
void ReviewList::binarySearchReview(const string& review) {
    ReviewNode* start = head;
    ReviewNode* end = nullptr;

    while (start != end) {
        ReviewNode* mid = start;
        ReviewNode* temp = start;
        int len = 0;

        // Find the length of the remaining list and the middle element
        while (temp != end) {
            len++;
            temp = temp->next;
        }

        for (int i = 0; i < len / 2; ++i) {
            mid = mid->next;
        }

        if (mid->review == review) {
            cout << "Review found: " << mid->review << endl;
            cout << "Rating: " << mid->rating << endl;
            cout << "Positive Words: " << mid->positiveCount << " [";
            mid->positiveWordList.displayWords();  // Display positive words
            cout << "]" << endl;
            cout << "Negative Words: " << mid->negativeCount << " [";
            mid->negativeWordList.displayWords();  // Display negative words
            cout << "]" << endl;
            return;
        }
        else if (mid->review < review) {
            start = mid->next;
        }
        else {
            end = mid;
        }
    }
}

