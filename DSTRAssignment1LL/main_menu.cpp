#include "hotel_reviews.h"
#include <iostream>

void displayMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Show Reviews and Ratings\n";
    std::cout << "2. Analyze Sentiment of Reviews using binary search (Positive and Negative Word Count)\n";
    std::cout << "4. Exit\n";
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
            // Perform sentiment analysis (positive and negative word count for each review)
            option2DisplaySentiment(reviewHead, positiveWordsHead, negativeWordsHead);
            break;
        case 4:
            // Exit the program
            std::cout << "Exiting the program.\n";
            return 0;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
