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

    cout << "waiting 5s before proceeding...\n";
    // Wait for 5 seconds before proceeding
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Create WordFrequencyList for positive and negative words
    WordFrequencyList positiveWordFreqList;
    WordFrequencyList negativeWordFreqList;

    // Add all positive and negative words to the respective frequency lists
    reviewList.addPositiveWordsToFrequencyList(positiveWordFreqList);
    reviewList.addNegativeWordsToFrequencyList(negativeWordFreqList);

    // Sort and time both positive and negative word sorting together
    std::cout << "Sorting positive and negative words using insertion sort...\n";
    auto sortStart = steady_clock::now();  // Start the timer before sorting

    positiveWordFreqList.insertionSort();  // Perform the sorting for positive words
    negativeWordFreqList.insertionSort();  // Perform the sorting for negative words

    auto sortEnd = steady_clock::now();  // Stop the timer after sorting
    auto totalInsertionSortDuration = duration_cast<milliseconds>(sortEnd - sortStart).count();  // Calculate the total sorting duration
    std::cout << "Total insertion sort sorting time: " << totalInsertionSortDuration << " milliseconds.\n";

    // Now calculate and display total positive and negative word counts
    ReviewNode* current = reviewList.head;
    int totalPositiveWords = 0;
    int totalNegativeWords = 0;

    while (current != nullptr) {
        totalPositiveWords += current->positiveCount;  // Sum up positive words
        totalNegativeWords += current->negativeCount;  // Sum up negative words
        current = current->next;
    }
    int totalReviews = reviewList.getSize();
    std::cout << "Total number of reviews: " << totalReviews << std::endl;

    std::cout << "Total number of positive words used in reviews: " << totalPositiveWords << std::endl;
    std::cout << "Total number of negative words used in reviews: " << totalNegativeWords << std::endl;

    // Output the sorted positive and negative word frequencies into one file
    std::ofstream sortedOutFile("insertion_sorted_word_frequencies.txt");
    if (sortedOutFile.is_open()) {
        // Output positive word frequencies
        sortedOutFile << "Positive Word Frequencies:\n";
        positiveWordFreqList.displayWordFrequencies(&sortedOutFile);

        // Separate positive and negative sections
        sortedOutFile << "\n----------------------------------------\n\n";

        // Output negative word frequencies
        sortedOutFile << "Negative Word Frequencies:\n";
        negativeWordFreqList.displayWordFrequencies(&sortedOutFile);

        // Append sorting times
        sortedOutFile << "\n----------------------------------------\n\n";
        sortedOutFile << "Total sorting time (positive and negative words): " << totalInsertionSortDuration << " milliseconds\n";

        // Function to display top 5 most and least frequent words
        auto displayTop5Words = [](WordFrequencyList& wordList, std::ostream& os, const std::string& type) {
            WordFrequencyNode* current = wordList.head;
            int count = 0;

            // Display top 5 most frequent words
            os << "Top 5 most frequent " << type << " words:\n";
            std::cout << "Top 5 most frequent " << type << " words:\n";
            while (current != nullptr && count < 5) {
                os << current->word << " (" << current->count << "), ";
                std::cout << current->word << " (" << current->count << "), ";
                current = current->next;
                count++;
            }
            os << "\n\n";
            std::cout << "\n\n";

            // Reset to head and find the top 5 least frequent words by sorting them manually
            WordFrequencyNode* temp = wordList.head;
            int totalCount = 0;

            // Traverse to find the total number of nodes
            while (temp != nullptr) {
                totalCount++;
                temp = temp->next;
            }

            // Traverse again to get the least frequent words
            temp = wordList.head;
            count = 0;
            os << "Top 5 least frequent " << type << " words:\n";
            std::cout << "Top 5 least frequent " << type << " words:\n";
            while (temp != nullptr && count < totalCount - 5) {
                temp = temp->next;
                count++;
            }
            // Print the last 5 nodes
            count = 0;
            while (temp != nullptr && count < 5) {
                os << temp->word << " (" << temp->count << "), ";
                std::cout << temp->word << " (" << temp->count << "), ";
                temp = temp->next;
                count++;
            }
            os << "\n\n";
            std::cout << "\n\n";
            };

        // Display max and min used words for positive and negative reviews
        if (positiveWordFreqList.head != nullptr) {
            displayTop5Words(positiveWordFreqList, sortedOutFile, "positive");
        }
        else {
            sortedOutFile << "\nNo positive words found in the reviews.\n";
            std::cout << "\nNo positive words found in the reviews.\n";
        }

        if (negativeWordFreqList.head != nullptr) {
            displayTop5Words(negativeWordFreqList, sortedOutFile, "negative");
        }
        else {
            sortedOutFile << "No negative words found in the reviews.\n";
            std::cout << "No negative words found in the reviews.\n";
        }

        sortedOutFile.close();
    }
    else {
        std::cerr << "Error opening the file for writing sorted word frequencies." << std::endl;
    }


// After displaying selection sort results
    std::cout << "\nPress Enter to run the selection sort on word frequencies...";
    std::cin.get();  // Wait for user to press Enter

    // Start timing the selection sort
    auto selectionSortStart = std::chrono::high_resolution_clock::now();

    // Summing up positive and negative words
    while (current != nullptr) {
        totalPositiveWords += current->positiveCount;  // Sum up positive words
        totalNegativeWords += current->negativeCount;  // Sum up negative words
        current = current->next;
    }
    std::cout << "Total number of reviews: " << totalReviews << std::endl;

    std::cout << "Total number of positive words used in reviews: " << totalPositiveWords << std::endl;
    std::cout << "Total number of negative words used in reviews: " << totalNegativeWords << std::endl;

    // Output the sorted positive and negative word frequencies into one file
    std::ofstream selectionFile("selection_sorted_word_frequencies.txt");
    if (selectionFile.is_open()) {
        // Output positive word frequencies
        std::cout << "Frequency of positive words used in overall reviews, listed in ascending order based on frequency:" << std::endl;
        std::cout << std::endl << std::endl;
        selectionFile << "Positive Word Frequencies:\n";
        positiveWordFreqList.selectionSort();  // Perform selection sort on positive word frequencies
        positiveWordFreqList.displayWordFrequencies(&selectionFile);

        // Separate positive and negative sections
        selectionFile << "\n----------------------------------------\n\n";
        std::cout << std::endl << std::endl;
        // Output negative word frequencies
        std::cout << "Frequency of negative words used in overall reviews, listed in ascending order based on frequency:" << std::endl;
        std::cout << std::endl << std::endl;
        selectionFile << "Negative Word Frequencies:\n";
        negativeWordFreqList.selectionSort();  // Perform selection sort on negative word frequencies
        negativeWordFreqList.displayWordFrequencies(&selectionFile);

        // Stop timing the selection sort process
        auto selectionSortEnd = std::chrono::high_resolution_clock::now();
        auto selectionSortDuration = std::chrono::duration_cast<std::chrono::milliseconds>(selectionSortEnd - selectionSortStart).count();

        // Append sorting times
        selectionFile << "\n----------------------------------------\n\n";
        selectionFile << "Total sorting time (positive and negative words): " << selectionSortDuration << " milliseconds\n";

        // Function to display top 5 most and least frequent words
        auto displayTop5Words = [](WordFrequencyList& wordList, std::ostream& os, const std::string& type) {
            WordFrequencyNode* current = wordList.head;
            int count = 0;

            // Display top 5 most frequent words
            os << "Top 5 most frequent " << type << " words:\n";
            std::cout << "Top 5 most frequent " << type << " words:\n";
            while (current != nullptr && count < 5) {
                os << current->word << " (" << current->count << "), ";
                std::cout << current->word << " (" << current->count << "), ";
                current = current->next;
                count++;
            }
            os << "\n\n";
            std::cout << "\n\n";

            // Reset to head and find the top 5 least frequent words by sorting them manually
            WordFrequencyNode* temp = wordList.head;
            int totalCount = 0;

            // Traverse to find the total number of nodes
            while (temp != nullptr) {
                totalCount++;
                temp = temp->next;
            }

            // Traverse again to get the least frequent words
            temp = wordList.head;
            count = 0;
            os << "Top 5 least frequent " << type << " words:\n";
            std::cout << "Top 5 least frequent " << type << " words:\n";
            while (temp != nullptr && count < totalCount - 5) {
                temp = temp->next;
                count++;
            }
            // Print the last 5 nodes
            count = 0;
            while (temp != nullptr && count < 5) {
                os << temp->word << " (" << temp->count << "), ";
                std::cout << temp->word << " (" << temp->count << "), ";
                temp = temp->next;
                count++;
            }
            os << "\n\n";
            std::cout << "\n\n";
            };

        // Display max and min used words for positive and negative reviews
        if (positiveWordFreqList.head != nullptr) {
            displayTop5Words(positiveWordFreqList, selectionFile, "positive");
        }
        else {
            selectionFile << "\nNo positive words found in the reviews.\n";
            std::cout << "\nNo positive words found in the reviews.\n";
        }

        if (negativeWordFreqList.head != nullptr) {
            displayTop5Words(negativeWordFreqList, selectionFile, "negative");
        }
        else {
            selectionFile << "No negative words found in the reviews.\n";
            std::cout << "No negative words found in the reviews.\n";
        }

        // Close the file after writing
        selectionFile.close();
    }
    else {
        std::cerr << "Error opening the file for writing selection word frequencies." << std::endl;
    }
    // Stop timing the selection sort process
    auto selectionSortEnd = std::chrono::high_resolution_clock::now();
    auto selectionSortDuration = std::chrono::duration_cast<std::chrono::milliseconds>(selectionSortEnd - selectionSortStart).count();

    // Display total selection sort time to console as well
    std::cout << "Total selection sorting time (positive and negative words): " << selectionSortDuration << " milliseconds\n";

    return 0;

}
