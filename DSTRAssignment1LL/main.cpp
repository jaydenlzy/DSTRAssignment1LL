#include "LinkedList.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

// Function to trim leading and trailing spaces or quotes from a string
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\"");
    size_t last = str.find_last_not_of(" \t\n\r\"");
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
}

// Function to read the CSV file and store reviews
void readCSV(LinkedList& list, const std::string& filename) {
    std::ifstream file(filename);
    std::string line, feedback, ratingStr;
    int rating;

    if (file.is_open()) {
        // Skip the header line
        getline(file, line);

        while (getline(file, line)) {
            std::stringstream ss(line);

            // Extract the review text, which is quoted
            if (line.front() == '\"') {
                size_t pos = line.find_last_of('\"');
                feedback = line.substr(1, pos - 1); // Remove the quotes around the review text

                // Extract the rating after the last comma (after the last quote)
                ratingStr = line.substr(pos + 2);
            }
            else {
                // Fallback if there's no quotes (though unlikely in this file)
                std::getline(ss, feedback, ',');
                std::getline(ss, ratingStr);
            }

            // Trim the extracted rating
            ratingStr = trim(ratingStr);

            // Check if the rating is empty
            if (ratingStr.empty()) {
                std::cerr << "Empty rating found!" << std::endl;
                rating = 0; // Assign 0 if no rating is provided
            }
            else {
                // Try to convert the rating to an integer
                try {
                    rating = std::stoi(ratingStr);
                }
                catch (std::invalid_argument& e) {
                    std::cerr << "Invalid rating found in CSV file: " << ratingStr << std::endl;
                    rating = 0; // Default value if the conversion fails
                }
            }

            // Ensure the rating is within the valid range (0-5)
            if (rating < 0 || rating > 5) {
                std::cerr << "Rating out of bounds (0-5): " << rating << std::endl;
                rating = 0; // Default to 0 for out of bounds
            }

            // Add the review and rating to the linked list
            list.addReview(feedback, rating);
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
    }
}

// Function to read words from TXT files and store them into a WordLinkedList
void readWords(WordLinkedList& list, const std::string& filename) {
    std::ifstream file(filename);
    std::string word;

    if (file.is_open()) {
        while (file >> word) { // Read word by word
            list.addWord(word);
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

int main() {
    LinkedList reviewList;
    WordLinkedList positiveWordList;
    WordLinkedList negativeWordList;

    // Read hotel reviews from the CSV file
    readCSV(reviewList, "tripadvisor_hotel_reviews.csv");

    // Read positive and negative words from TXT files
    readWords(positiveWordList, "positive-words.txt");
    readWords(negativeWordList, "negative-words.txt");

    // Testing: Print reviews and ratings
    reviewList.printReviews();

    // Testing: Print positive and negative words
    std::cout << "\nPositive Words:" << std::endl;
    positiveWordList.printWords();

    std::cout << "\nNegative Words:" << std::endl;
    negativeWordList.printWords();

    return 0;
}
