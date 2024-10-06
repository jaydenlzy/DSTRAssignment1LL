#ifndef SENTIMENT_CALCULATION_H
#define SENTIMENT_CALCULATION_H

#include "hotel_reviews.h"

// Sentiment calculation node for storing analysis results
struct SentimentNode {
    std::string review;
    int rating;
    int positiveCount;
    int negativeCount;
    SentimentNode* next;
};

// Function declarations
void addSentiment(SentimentNode*& head, const std::string& review, int rating, int positiveCount, int negativeCount);
int countMatchingWords(const std::string& review, WordNode* wordHead);
void analyzeSentiments(ReviewNode* reviews, WordNode* positiveWords, WordNode* negativeWords, SentimentNode*& sentimentHead);
void displaySentimentResults(SentimentNode* head);

#endif // SENTIMENT_CALCULATION_H
