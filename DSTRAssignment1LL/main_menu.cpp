#include "hotel_reviews.h"
#include "sentimentcalculation.h"
#include <iostream>

void displayMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Show Reviews and Ratings\n";
    std::cout << "2. Linear Search Sentiment Analysis\n";  // Added option for linear search
    std::cout << "3. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    // Initialize the linked list heads
    ReviewNode* reviewHead = nullptr;
    WordNode* positiveWordsHead = nullptr;
    WordNode* negativeWordsHead = nullptr;

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
            // Perform linear search sentiment analysis
            linearSearchSentimentAnalysis(reviewHead, positiveWordsHead, negativeWordsHead);
            break;
        case 3:
            // Exit the program
            std::cout << "Exiting the program.\n";
            return 0;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
