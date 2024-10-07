#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono> // For measuring time
#include "reviewlist.h"

using namespace std;
using namespace std::chrono; // For easier access to chrono types


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
                string review = line.substr(0, lastComma); // Everything before the last comma is the review
                string ratingStr = line.substr(lastComma + 1); // Everything after the last comma is the rating
                int rating = stoi(ratingStr); // Convert the rating to an integer

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
void printToBoth(ostream& fileStream, const string& message) {
    std::cout << message;
    fileStream << message;
}


int main() {
    std::ofstream outFile("binary_search.txt"); // Open file for writing

    if (!outFile) {
        std::cerr << "Error opening file for writing" << std::endl;
        return 1;
    }

    // Start measuring time
    auto start = steady_clock::now();

    ReviewList reviewList;

    // Load reviews from the CSV file
    readReviewsFromCSV("tripadvisor_hotel_reviews.csv", reviewList);

    // Count positive and negative words in each review
    reviewList.countPositiveNegativeWords("positive-words.txt", "negative-words.txt");

    // Display all reviews (Assuming this function prints to cout)
    reviewList.displayReviews();  // It will print to both the console and the file

    // Perform binary search for a specific review
    string searchReview = "sample review text"; // Modify this to input the desired review
    reviewList.binarySearchReview(searchReview);

    // End measuring time
    auto end = steady_clock::now();

    // Calculate the duration and convert to milliseconds
    auto duration = duration_cast<milliseconds>(end - start).count();

    // Print the time taken to both CLI and the file
    printToBoth(outFile, "Time taken to run the program: " + to_string(duration) + " milliseconds.\n");

    outFile.close(); // Close the file
    return 0;
}
