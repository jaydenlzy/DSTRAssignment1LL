#include "sentimentcalculation.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// Function to add a sentiment result to the linked list
void addSentiment(SentimentNode*& head, const std::string& review, int rating, int positiveCount, int negativeCount) {
    SentimentNode* newNode = new SentimentNode();
    newNode->review = review;
    newNode->rating = rating;
    newNode->positiveCount = positiveCount;
    newNode->negativeCount = negativeCount;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    }
    else {
        SentimentNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to count matching words in a review
int countMatchingWords(const std::string& review, WordNode* wordHead) {
    int count = 0;
    std::stringstream ss(review);
    std::string word;

    std::string lowerReview = review;
    std::transform(lowerReview.begin(), lowerReview.end(), lowerReview.begin(), ::tolower);

    while (ss >> word) {
        std::string lowerWord = word;
        std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);

        WordNode* temp = wordHead;
        while (temp != nullptr) {
            if (lowerWord == temp->word) {
                count++;
                break;
            }
            temp = temp->next;
        }
    }
    return count;
}

// Function to analyze all reviews and count positive and negative words
void analyzeSentiments(ReviewNode* reviews, WordNode* positiveWords, WordNode* negativeWords, SentimentNode*& sentimentHead) {
    ReviewNode* temp = reviews;
    while (temp != nullptr) {
        int positiveCount = countMatchingWords(temp->review, positiveWords);
        int negativeCount = countMatchingWords(temp->review, negativeWords);
        addSentiment(sentimentHead, temp->review, temp->rating, positiveCount, negativeCount);
        temp = temp->next;
    }
}

// Function to display the results of sentiment analysis
void displaySentimentResults(SentimentNode* head) {
    SentimentNode* temp = head;
    while (temp != nullptr) {
        std::cout << "Review: " << temp->review << "\n";
        std::cout << "Positive Words: " << temp->positiveCount << "\n";
        std::cout << "Negative Words: " << temp->negativeCount << "\n";
        std::cout << "Rating: " << temp->rating << "\n\n";
        temp = temp->next;
    }
}
