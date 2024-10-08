#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>  // For measuring time
#include <thread>  // For sleep
#include "reviewlist.h"

using namespace std;
using namespace std::chrono;  // For easier access to chrono types

// Function to read reviews from the CSV file and store them in the linked list
void readReviewsFromCSV(string filename, ReviewList& reviewList) {
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        // Skip the header line
        getline(file, line);

        // Read each line from the file
        while (getline(file, line)) {
            // Find the last comma in the line
            size_t lastComma = line.find_last_of(',');

            if (lastComma != string::npos) {
                string review = line.substr(0, lastComma);  // Everything before the last comma is the review
                string ratingStr = line.substr(lastComma + 1);  // Everything after the last comma is the rating
                int rating = stoi(ratingStr);  // Convert the rating to an integer

                // Add the review to the linked list
                reviewList.addReview(review, rating);
            }
        }
        file.close();
    } else {
        cout << "Unable to open file!" << endl;
    }
}

// Helper function to print to both CLI and file
void printToBoth(ostream& fileStream, const string& message) {
    std::cout << message;
    fileStream << message;
}

int main() {
    // Open the files for writing results
    std::ofstream binaryOutFile("binary_search_results.txt");
    std::ofstream linearOutFile("linear_search_results.txt");
    if (!binaryOutFile || !linearOutFile) {
        std::cerr << "Error opening one of the files for writing" << std::endl;
        return 1;
    }

    // Start measuring total execution time
    auto totalStart = steady_clock::now();

    ReviewList reviewList;

    // Load reviews from the CSV file
    readReviewsFromCSV("tripadvisor_hotel_reviews.csv", reviewList);

    // Count positive and negative words in each review
    reviewList.countPositiveNegativeWords("positive-words.txt", "negative-words.txt");

    // Binary Search
    printToBoth(binaryOutFile, "Performing Binary Search (Sentiment Analysis for all reviews):\n");
    auto binaryStart = steady_clock::now();
    reviewList.binarySearchAllReviews();  // Modified to process all reviews for sentiment
    auto binaryEnd = steady_clock::now();
    auto binaryDuration = duration_cast<milliseconds>(binaryEnd - binaryStart).count();
    printToBoth(binaryOutFile, "Binary Search Time: " + to_string(binaryDuration) + " milliseconds.\n\n");

    // Pause for 10 seconds
    printToBoth(binaryOutFile, "Pausing for 10 seconds before linear search...\n");
    this_thread::sleep_for(chrono::seconds(10));
    printToBoth(binaryOutFile, "Pause completed.\n\n");

    // Linear Search
    printToBoth(linearOutFile, "Performing Linear Search (Sentiment Analysis for all reviews):\n");
    auto linearStart = steady_clock::now();
    reviewList.linearSearchAllReviews();  // Modified to process all reviews for sentiment
    auto linearEnd = steady_clock::now();
    auto linearDuration = duration_cast<milliseconds>(linearEnd - linearStart).count();
    printToBoth(linearOutFile, "Linear Search Time: " + to_string(linearDuration) + " milliseconds.\n");

    // End measuring total time
    auto totalEnd = steady_clock::now();
    auto totalDuration = duration_cast<milliseconds>(totalEnd - totalStart).count();

    // Print the total time taken to both CLI and the file
    printToBoth(binaryOutFile, "\nTotal time taken to run the program: " + to_string(totalDuration) + " milliseconds.\n");
    printToBoth(linearOutFile, "\nTotal time taken to run the program: " + to_string(totalDuration) + " milliseconds.\n");

    binaryOutFile.close();  // Close the binary search file
    linearOutFile.close();  // Close the linear search file
    return 0;
}
