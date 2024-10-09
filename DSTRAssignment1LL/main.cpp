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
    // Open the file for writing results
    std::ofstream linearOutFile("linear_search_results.txt");
    if (!linearOutFile) {
        std::cerr << "Error opening the file for writing" << std::endl;
        return 1;
    }


    ReviewList reviewList;

    // Load reviews from the CSV file
    readReviewsFromCSV("tripadvisor_hotel_reviews.csv", reviewList);

    // Count positive and negative words in each review
    reviewList.countPositiveNegativeWords("positive-words.txt", "negative-words.txt");

    // Linear Search
    printToBoth(linearOutFile, "Performing Linear Search (Sentiment Analysis for all reviews):\n");
    auto linearStart = steady_clock::now();

    reviewList.linearSearchAllReviews(&linearOutFile);  // Pass the output file stream

    auto linearEnd = steady_clock::now();
    auto linearDuration = duration_cast<milliseconds>(linearEnd - linearStart).count();
    printToBoth(linearOutFile, "Linear Search Time: " + to_string(linearDuration) + " milliseconds.\n");


    linearOutFile.close();  // Close the linear search file

    // Wait for 5 seconds before proceeding
    std::this_thread::sleep_for(std::chrono::seconds(5));

        // Create a WordFrequencyList to store and sort word frequencies
    WordFrequencyList wordFreqList;
    // Add all positive words to the frequency list
    reviewList.addPositiveWordsToFrequencyList(wordFreqList);
    // Populate word frequencies from all reviews (after counting words)
    // Assuming we use wordFreqList.addWordFrequency(...) in the loop where words are counted
    
    std::cout << "Sorting using insertion sort...\n";
    int totalReviews = reviewList.getSize();
    std::cout << "Total number of reviews: " << totalReviews << std::endl;

    // Now calculate and display total positive and negative word counts
    ReviewNode* current = reviewList.head;  // Assuming 'head' is the start of your linked list
    int totalPositiveWords = 0;
    int totalNegativeWords = 0;

    while (current != nullptr) {
        totalPositiveWords += current->positiveCount;  // Sum up positive words
        totalNegativeWords += current->negativeCount;  // Sum up negative words
        current = current->next;
    }

    std::cout << "Total number of positive words used in reviews: " << totalPositiveWords << std::endl;
    std::cout << "Total number of negative words used in reviews: " << totalNegativeWords << std::endl;
    wordFreqList.insertionSort();  // Sort the word frequencies
    // Display the word with the highest frequency
    WordFrequencyNode* mostFrequentWord = wordFreqList.head;
    // Output the sorted word frequencies to both console and a new file
    std::ofstream sortedOutFile("sorted_word_frequencies.txt");
    wordFreqList.displayWordFrequencies(&sortedOutFile);

    sortedOutFile.close();


    return 0;
}
