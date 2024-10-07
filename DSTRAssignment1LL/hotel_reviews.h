#ifndef HOTEL_REVIEWS_H
#define HOTEL_REVIEWS_H

#include <string>

// Linked list node for storing reviews and ratings
struct ReviewNode {
    std::string review;  // Review text
    int rating;          // Rating
    ReviewNode* next = nullptr;
};

// Linked list node for storing words (positive and negative)
struct WordNode {
    std::string word;
    WordNode* next = nullptr;
};

// Linked list node for storing results of the linear search sentiment analysis
struct LinearSentimentNode {
    std::string review;
    int rating;
    int positiveCount;
    int negativeCount;
    LinearSentimentNode* next = nullptr;
};

// Function declarations

// Helper functions
void addReview(ReviewNode*& head, const std::string& review, int rating);
void addWord(WordNode*& head, const std::string& word);
void addLinearSentiment(LinearSentimentNode*& head, const std::string& review, int rating, int positiveCount, int negativeCount);

// File loading functions
void loadReviewsFromFile(ReviewNode*& head, const std::string& filename);
void loadWordsFromFile(WordNode*& head, const std::string& filename);

// Display functions
void showReviewAndRating(ReviewNode* head);
void displayLinearSentimentResults(LinearSentimentNode* head);

// Sentiment analysis functions
void linearSearchSentimentAnalysis(ReviewNode* reviews, WordNode* positiveWords, WordNode* negativeWords, LinearSentimentNode*& sentimentHead);

#endif // HOTEL_REVIEWS_H
