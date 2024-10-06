#ifndef HOTEL_REVIEWS_H
#define HOTEL_REVIEWS_H

#include <string>

// Linked list node for storing reviews and ratings
struct ReviewNode {
    std::string review;  // Review text
    int rating;          // Rating
    ReviewNode* next;    // Pointer to the next node
};

// Linked list node for storing words (positive and negative)
struct WordNode {
    std::string word;    // Word (positive or negative)
    WordNode* next;      // Pointer to the next node
};

// Function declarations
std::string trim(const std::string& str);
void addReview(ReviewNode*& head, const std::string& review, int rating);
void addWord(WordNode*& head, const std::string& word);
void loadReviewsFromFile(ReviewNode*& head, const std::string& filename);
void loadWordsFromFile(WordNode*& head, const std::string& filename);
void showReviewAndRating(ReviewNode* head);
void showWords(WordNode* head);
void displayMenu();

#endif // HOTEL_REVIEWS_H
