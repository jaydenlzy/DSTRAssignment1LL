#include "hotel_reviews.h"
#include "sentimentcalculation.h"
#include <iostream>

void displayMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Show Reviews and Ratings\n";
    std::cout << "2. Linear Search Sentiment Analysis\n";
    std::cout << "3. Binary Search Sentiment Analysis\n";
    std::cout << "4. Bubble Sort Reviews by Sentiment\n";
    std::cout << "5. Insertion Sort Reviews by Sentiment\n";
    std::cout << "6. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    // Initialize the linked list heads
    ReviewNode* reviewHead = nullptr;
    WordNode* positiveWordsHead = nullptr;
    WordNode* negativeWordsHead = nullptr;
    SentimentNode* sentimentHead = nullptr;

    // Load reviews and ratings from the CSV file
    std::string reviewFilename = "tripadvisor_hotel_reviews.csv";
    loadReviewsFromFile(reviewHead, reviewFilename);

    // Load positive and negative words from text files
    std::string positiveFilename = "positive-words.txt";
    std::string negativeFilename = "negative-words.txt";
    loadWordsFromFile(positiveWordsHead, positiveFilename);
    loadWordsFromFile(negativeWordsHead, negativeFilename);

    int choice;

    // Menu loop
    while (true) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            // Display reviews and ratings
            showReviewAndRating(reviewHead);
            break;
        case 2:
            // Perform linear search and display sentiment analysis
            linearSearchSentimentAnalysis(reviewHead, positiveWordsHead, negativeWordsHead);
            break;
        case 3:
            // Perform binary search and display sentiment analysis
            binarySearchSentimentAnalysis(reviewHead, positiveWordsHead, negativeWordsHead);
            break;
        case 4:
            // Bubble sort the reviews by sentiment
            bubbleSortReviewsBySentiment(reviewHead);
            break;
        case 5:
            // Insertion sort the reviews by sentiment
            insertionSortReviewsBySentiment(reviewHead);
            break;
        case 6:
            // Exit the program
            std::cout << "Exiting the program.\n";
            return 0;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
