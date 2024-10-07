#include "hotel_reviews.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

// Helper function to split a string into words and store them in a linked list
WordNode* splitReviewIntoWords(const std::string& review) {
    WordNode* wordListHead = nullptr;
    std::istringstream iss(review);
    std::string word;

    while (iss >> word) {
        addWord(wordListHead, word);  // Add each word to the linked list
    }

    return wordListHead;  // Return the head of the word linked list
}

// Function to add a review to the linked list
void addReview(ReviewNode*& head, const std::string& review, int rating) {
    ReviewNode* newNode = new ReviewNode();  // Create a new node
    newNode->review = review;                // Assign review text
    newNode->rating = rating;                // Assign rating
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;  // Set the new node as the head if the list is empty
    }
    else {
        ReviewNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;  // Traverse to the end of the list
        }
        temp->next = newNode;  // Append the new node at the end of the list
    }
}

// Function to add a word to the linked list
void addWord(WordNode*& head, const std::string& word) {
    WordNode* newNode = new WordNode();  // Create a new node
    newNode->word = word;                // Assign word
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;  // Set the new node as the head if the list is empty
    }
    else {
        WordNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;  // Traverse to the end of the list
        }
        temp->next = newNode;  // Append the new node at the end of the list
    }
}

// Function to add a sentiment result to the linear search sentiment linked list
void addLinearSentiment(LinearSentimentNode*& head, const std::string& review, int rating, int positiveCount, int negativeCount) {
    LinearSentimentNode* newNode = new LinearSentimentNode();
    newNode->review = review;
    newNode->rating = rating;
    newNode->positiveCount = positiveCount;
    newNode->negativeCount = negativeCount;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;  // Set the new node as the head if the list is empty
    }
    else {
        LinearSentimentNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;  // Traverse to the end of the list
        }
        temp->next = newNode;  // Append the new node at the end of the list
    }
}

// Function to load reviews from CSV file
void loadReviewsFromFile(ReviewNode*& head, const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    // Skip the header row
    if (std::getline(file, line)) {
        // Read the header line but don't process it
    }

    while (std::getline(file, line)) {
        size_t commaPos = line.find_last_of(',');

        if (commaPos != std::string::npos) {
            std::string review = line.substr(0, commaPos);
            std::string ratingString = line.substr(commaPos + 1);

            int rating = 0;
            try {
                rating = std::stoi(ratingString);
            }
            catch (const std::invalid_argument&) {
                std::cerr << "Invalid rating encountered: " << ratingString << ". Defaulting to 0.\n";
                rating = 0;
            }

            addReview(head, review, rating);
        }
    }
    file.close();  // Close the file after reading
}

// Function to load words (positive or negative) from a text file into a linked list
void loadWordsFromFile(WordNode*& head, const std::string& filename) {
    std::ifstream file(filename);
    std::string word;

    while (std::getline(file, word)) {
        addWord(head, word);  // Add each word to the linked list
    }

    file.close();  // Close the file after reading
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
        std::cout << "\n";  // Add a blank line after each review and rating
        temp = temp->next;
    }
}

// Function to display sentiment analysis results
void displayLinearSentimentResults(LinearSentimentNode* head) {
    if (head == nullptr) {
        std::cout << "No sentiment results available.\n";
        return;
    }

    LinearSentimentNode* temp = head;
    while (temp != nullptr) {
        std::cout << "Review: " << temp->review << "\n";
        std::cout << "Positive Words: " << temp->positiveCount << "\n";
        std::cout << "Negative Words: " << temp->negativeCount << "\n";
        std::cout << "Rating: " << temp->rating << "\n\n";
        temp = temp->next;
    }
}

// Linear search function to count matching words in a review
int linearSearchForWord(WordNode* wordList, const std::string& word) {
    WordNode* current = wordList;
    while (current != nullptr) {
        if (current->word == word) {
            return 1;  // Word found
        }
        current = current->next;
    }
    return 0;  // Word not found
}

// Linear search for sentiment analysis
void linearSearchSentimentAnalysis(ReviewNode* reviews, WordNode* positiveWords, WordNode* negativeWords, LinearSentimentNode*& sentimentHead) {
    ReviewNode* currentReview = reviews;

    while (currentReview != nullptr) {
        std::string reviewText = currentReview->review;
        WordNode* reviewWordsHead = splitReviewIntoWords(reviewText);  // Split review into words

        int positiveCount = 0;
        int negativeCount = 0;

        WordNode* currentWord = reviewWordsHead;
        while (currentWord != nullptr) {
            if (linearSearchForWord(positiveWords, currentWord->word)) {
                positiveCount++;
            }
            if (linearSearchForWord(negativeWords, currentWord->word)) {
                negativeCount++;
            }
            currentWord = currentWord->next;
        }

        // Add the sentiment analysis result to the new linked list
        addLinearSentiment(sentimentHead, reviewText, currentReview->rating, positiveCount, negativeCount);

        // Move to the next review
        currentReview = currentReview->next;

        // Free memory allocated for the review words linked list
        while (reviewWordsHead != nullptr) {
            WordNode* temp = reviewWordsHead;

