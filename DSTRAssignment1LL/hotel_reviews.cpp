#include "hotel_reviews.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <chrono>

// Function to trim leading and trailing whitespace
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

// Function to add a review and rating to the linked list
void addReview(ReviewNode*& head, const std::string& review, int rating) {
    ReviewNode* newNode = new ReviewNode();
    newNode->review = review;
    newNode->rating = rating;
    newNode->next = nullptr;

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

// Function to add a word to the linked list (for both positive and negative words)
void addWord(WordNode*& head, const std::string& word) {
    WordNode* newNode = new WordNode();
    newNode->word = word;
    newNode->next = nullptr;

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

// Function to load reviews and ratings from the CSV file
void loadReviewsFromFile(ReviewNode*& head, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file.\n";
        return;
    }

    std::string line, review, ratingString;
    int rating;

    // Skip the header row
    std::getline(file, line);

    // Read each line from the CSV file
    while (std::getline(file, line)) {
        std::stringstream ss(line);

        // Extract the first column (review)
        if (line[0] == '"') {
            size_t endQuotePos = line.find_last_of('"');
            review = line.substr(1, endQuotePos - 1);
            ratingString = line.substr(endQuotePos + 2);
        }
        else {
            std::getline(ss, review, ',');
            std::getline(ss, ratingString, ',');
        }

        ratingString = trim(ratingString);

        try {
            rating = std::stoi(ratingString);
        }
        catch (...) {
            rating = 0;
            std::cerr << "Error: Failed to convert rating. Setting to 0.\n";
        }

        addReview(head, review, rating);
    }

    file.close();
}

// Function to load words (positive or negative) from a text file
void loadWordsFromFile(WordNode*& head, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file.\n";
        return;
    }

    std::string word;
    while (std::getline(file, word)) {
        addWord(head, word);
    }

    file.close();
}

// Function to display reviews and ratings from the linked list
void showReviewAndRating(ReviewNode* head) {
    if (head == nullptr) {
        std::cout << "No reviews available.\n";
        return;
    }

    ReviewNode* temp = head;
    while (temp != nullptr) {
        std::cout << "Review: " << temp->review << "\n";
        if (temp->rating != 0) {
            std::cout << "Rating: " << temp->rating << "/5\n";
        }
        else {
            std::cout << "Rating: N/A\n";
        }
        std::cout << "\n";
        temp = temp->next;
    }
}

// Function to display positive or negative words
void showWords(WordNode* head) {
    if (head == nullptr) {
        std::cout << "No words available.\n";
        return;
    }

    WordNode* temp = head;
    while (temp != nullptr) {
        std::cout << temp->word << "\n";
        temp = temp->next;
    }
}

// Sorting: Bubble Sort based on sentiment (dummy function)
void bubbleSortReviewsBySentiment(ReviewNode*& head) {
    std::cout << "Bubble sorting reviews by sentiment...\n";
}

// Sorting: Insertion Sort based on sentiment (dummy function)
void insertionSortReviewsBySentiment(ReviewNode*& head) {
    std::cout << "Insertion sorting reviews by sentiment...\n";
}

// Searching: Linear search for positive and negative words (dummy function)
void linearSearchSentimentAnalysis(ReviewNode* reviews, WordNode* positiveWords, WordNode* negativeWords) {
    std::cout << "Performing linear search for sentiment analysis...\n";
}

// Searching: Binary search for positive and negative words (dummy function)
void binarySearchSentimentAnalysis(ReviewNode* reviews, WordNode* positiveWords, WordNode* negativeWords) {
    std::cout << "Performing binary search for sentiment analysis...\n";
}
