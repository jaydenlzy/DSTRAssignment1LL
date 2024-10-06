#ifndef HOTEL_REVIEWS_H
#define HOTEL_REVIEWS_H

#include <string>

// Linked list node for storing reviews and ratings
struct ReviewNode {
    std::string review;  // Review text
    int rating;          // Rating
    ReviewNode* next;    // Pointer to the next node

    // Constructor to initialize the member variables
    ReviewNode() : review(""), rating(0), next(nullptr) {}
};

// Linked list node for storing words (positive and negative)
struct WordNode {
    std::string word;    // Word (positive or negative)
    WordNode* next;      // Pointer to the next node

    // Constructor to initialize the member variables
    WordNode() : word(""), next(nullptr) {}
};

// Function declarations
std::string trim(const std::string& str);
void addReview(ReviewNode*& head, const std::string& review, int rating);
void addWord(WordNode*& head, const std::string& word);
void loadReviewsFromFile(ReviewNode*& head, const std::string& filename);
void loadWordsFromFile(WordNode*& head, const std::string& filename);
void showReviewAndRating(ReviewNode* head);
void showWords(WordNode* head);

// Sorting algorithms
void bubbleSortReviewsBySentiment(ReviewNode*& head);
void insertionSortReviewsBySentiment(ReviewNode*& head);

// Searching algorithms
void linearSearchSentimentAnalysis(ReviewNode* reviews, WordNode* positiveWords, WordNode* negativeWords);
void binarySearchSentimentAnalysis(ReviewNode* reviews, WordNode* positiveWords, WordNode* negativeWords);

#endif // HOTEL_REVIEWS_H
