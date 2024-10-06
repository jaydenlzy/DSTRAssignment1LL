#ifndef HOTEL_REVIEWS_H
#define HOTEL_REVIEWS_H

#include <string>

// Linked list node for storing reviews and ratings
struct ReviewNode {
    std::string review;  // Review text
    int rating;          // Rating associated with the review
    ReviewNode* next = nullptr;    // Pointer to the next node, initialized to nullptr
};

// Linked list node for storing words (positive and negative)
struct WordNode {
    std::string word;    // Word (positive or negative)
    WordNode* next = nullptr;      // Pointer to the next node, initialized to nullptr
};

// Linked list node for storing words found during sentiment analysis
struct FoundWordNode {
    std::string word;    // Word found in the review
    FoundWordNode* next = nullptr; // Pointer to the next node, initialized to nullptr
};

// Function declarations

// Helper functions
void addReview(ReviewNode*& head, const std::string& review, int rating);
void addWord(WordNode*& head, const std::string& word);
void addFoundWord(FoundWordNode*& head, const std::string& word);

// File loading functions
void loadReviewsFromFile(ReviewNode*& head, const std::string& filename);
void loadWordsFromFile(WordNode*& head, const std::string& filename);

// Display functions
void showReviewAndRating(ReviewNode* head);
void displayFoundWords(FoundWordNode* head);

// Sentiment analysis functions
void option2DisplaySentiment(ReviewNode* reviewHead, WordNode* positiveWordsHead, WordNode* negativeWordsHead);

// Utility functions for word processing
WordNode* splitReviewIntoWords(const std::string& review);
int getListSize(WordNode* head);
WordNode* getNodeAtIndex(WordNode* head, int index);
bool binarySearchWord(WordNode* head, const std::string& word, int listSize);

#endif // HOTEL_REVIEWS_H
