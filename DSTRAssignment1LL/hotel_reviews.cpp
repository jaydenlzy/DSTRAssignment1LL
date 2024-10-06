#include "hotel_reviews.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <chrono>

// Helper function to split a string into words manually and store them in a linked list
WordNode* splitReviewIntoWords(const std::string& review) {
    WordNode* wordListHead = nullptr;
    std::istringstream iss(review);
    std::string word;

    while (iss >> word) {
        addWord(wordListHead, word);  // Add each word to the linked list
    }

    return wordListHead;  // Return the head of the word linked list
}

// Function to get the size of the linked list
int getListSize(WordNode* head) {
    int size = 0;
    WordNode* current = head;
    while (current != nullptr) {
        size++;
        current = current->next;
    }
    return size;
}

// Function to get the node at a specific index in the linked list
WordNode* getNodeAtIndex(WordNode* head, int index) {
    WordNode* current = head;
    int count = 0;
    while (current != nullptr) {
        if (count == index) {
            return current;
        }
        count++;
        current = current->next;
    }
    return nullptr;  // Index out of bounds
}

// Binary search on linked list
bool binarySearchWord(WordNode* head, const std::string& word, int listSize) {
    int left = 0;
    int right = listSize - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        WordNode* midNode = getNodeAtIndex(head, mid);

        if (midNode->word == word) {
            return true;
        }
        if (midNode->word < word) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return false;
}

// Function to display positive and negative word counts in reviews
void option2DisplaySentiment(ReviewNode* reviewHead, WordNode* positiveWordsHead, WordNode* negativeWordsHead) {
    int positiveListSize = getListSize(positiveWordsHead);
    int negativeListSize = getListSize(negativeWordsHead);

    ReviewNode* currentReview = reviewHead;
    while (currentReview != nullptr) {
        std::string reviewText = currentReview->review;
        WordNode* reviewWordsHead = splitReviewIntoWords(reviewText);  // Split review into words (linked list)

        int positiveCount = 0;
        int negativeCount = 0;

        // Count positive and negative words in the review
        WordNode* currentWord = reviewWordsHead;
        while (currentWord != nullptr) {
            if (binarySearchWord(positiveWordsHead, currentWord->word, positiveListSize)) {
                positiveCount++;
            }
            if (binarySearchWord(negativeWordsHead, currentWord->word, negativeListSize)) {
                negativeCount++;
            }
            currentWord = currentWord->next;
            std::getline(ss, ratingString, ',');
        }
        // Display the review and the counts
        std::cout << "\nReview: " << reviewText << "\n";
        std::cout << "Positive words: " << positiveCount << "\n";
        std::cout << "Negative words: " << negativeCount << "\n";

        // Move to the next review
        currentReview = currentReview->next;
        ratingString = trim(ratingString);
        // Free the memory for the reviewWordsHead linked list
        while (reviewWordsHead != nullptr) {
            WordNode* temp = reviewWordsHead;
            reviewWordsHead = reviewWordsHead->next;
            delete temp;
        }
    }
}
        }
// Load reviews from CSV file
void loadReviewsFromFile(ReviewNode*& head, const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        // Find the position of the last comma (before the rating)
        size_t commaPos = line.find_last_of(',');

        if (commaPos != std::string::npos) {
            // Extract the review text (from start to just before the last comma)
            std::string review = line.substr(0, commaPos);

            // Extract the rating (after the last comma)
            int rating = std::stoi(line.substr(commaPos + 1));

            // Add the review and rating to the linked list
            addReview(head, review, rating);
        }
    }
    file.close();  // Close the file after reading
}

// Load words from a text file into a linked list
    std::ifstream file(filename);

    while (file >> word) {
    while (std::getline(file, word)) {
        // Add each word to the linked list

    file.close();  // Close the file after reading
}

// Add a review to the linked list
void addReview(ReviewNode*& head, const std::string& review, int rating) {
    ReviewNode* newNode = new ReviewNode{ review, rating, nullptr };
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
// Add a word to the linked list
void addWord(WordNode*& head, const std::string& word) {
    WordNode* newNode = new WordNode{ word, nullptr };
    if (head == nullptr) {
        head = newNode;
    }
    else {
        WordNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        else {
        temp->next = newNode;
        std::cout << "\n";  // Add a blank line after each review and rating
        temp = temp->next;
    }
}

// Show reviews and ratings
void showReviewAndRating(ReviewNode* head) {
    ReviewNode* current = head;
    while (current != nullptr) {
        std::cout << "Review: " << current->review << "\n";
        std::cout << "Rating: " << current->rating << "\n";
        current = current->next;
    }
}

// Show all words in the linked list
void showWords(WordNode* head) {
    WordNode* current = head;
    while (current != nullptr) {
        std::cout << current->word << "\n";
void binarySearchSentimentAnalysis(ReviewNode* reviews, WordNode* positiveWords, WordNode* negativeWords) {
    std::cout << "Performing binary search for sentiment analysis...\n";
}
