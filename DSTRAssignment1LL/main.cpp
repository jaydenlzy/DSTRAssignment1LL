#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>  // For measuring time
#include <thread>  // For sleep
#include "reviewlist.h"
#include "sentimentcalculation.h"  // Include sentiment calculation header

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
    }
    else {
        cout << "Unable to open file!" << endl;
    }
}

// Helper function to print to both CLI and file
void printToBoth(ostream& fileStream, const string& message) {
    std::cout << message;      // Print to console
    fileStream << message;     // Print to file
}

int main() {
    // Declare and open the file for output
    std::ofstream outfile("linear_search_results.txt");

    // Check if the file was successfully opened
    if (!outfile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Start measuring total execution time
    auto totalStart = steady_clock::now();

    ReviewList reviewList;

    // Load reviews from the CSV file
    readReviewsFromCSV("tripadvisor_hotel_reviews.csv", reviewList);

    // Count positive and negative words in each review
    reviewList.countPositiveNegativeWords("positive-words.txt", "negative-words.txt");

    // Linear Search
    printToBoth(outfile, "Performing Linear Search (Sentiment Analysis for all reviews):\n");
    auto linearStart = steady_clock::now();

    // Iterate over all reviews, calculate sentiment, and evaluate accuracy
    for (int i = 0; i < reviewList.getSize(); i++) {
        string review;
        int rating;
        double sentimentScore = reviewList.calculateSentimentScore(i);  // Ensure this function is implemented in reviewlist
        reviewList.getReview(i, review, rating);  // Get the review and rating at index i

        // Print the review, rating, and sentiment score
        string sentimentResult = evaluateReview(sentimentScore, rating);
        printToBoth(outfile, "Review: " + review + "\n");
        printToBoth(outfile, "Rating: " + to_string(rating) + "\n");
        printToBoth(outfile, "Sentiment Score: " + to_string(sentimentScore) + "\n");
        printToBoth(outfile, "Evaluation: " + sentimentResult + "\n\n");
    }

    auto linearEnd = steady_clock::now();
    auto linearDuration = duration_cast<milliseconds>(linearEnd - linearStart).count();
    printToBoth(outfile, "Linear Search Time: " + to_string(linearDuration) + " milliseconds.\n");

    // End measuring total time
    auto totalEnd = steady_clock::now();
    auto totalDuration = duration_cast<milliseconds>(totalEnd - totalStart).count();

    // Print the total time taken to both CLI and the file
    printToBoth(outfile, "\nTotal time taken to run the program: " + to_string(totalDuration) + " milliseconds.\n");

    // Also print to CLI to notify the user that the results are in the file
    std::cout << "Results have been printed to linear_search_results.txt" << std::endl;

    outfile.close();  // Close the file

    return 0;
}
