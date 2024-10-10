#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include "reviewlist.h"
#include "sentimentcalculation.h"  

using namespace std;
using namespace std::chrono;

// Function to read reviews from the CSV file and store in linked list
void readReviewsFromCSV(string filename, ReviewList& reviewList) {
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        // Skip the header line
        getline(file, line);

        // Read each line from the file
        while (getline(file, line)) {
            size_t lastComma = line.find_last_of(',');
            if (lastComma != string::npos) {
                string review = line.substr(0, lastComma);
                string ratingStr = line.substr(lastComma + 1);
                int rating = stoi(ratingStr);
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
    std::cout << message;
    fileStream << message;
}

int main() {
    std::ofstream reportOutFile("report.txt");
    if (!reportOutFile) {
        std::cerr << "Error opening the report file for writing" << std::endl;
        return 1;
    }

    std::ofstream linearOutFile("linear_search_results.txt");
    if (!linearOutFile) {
        std::cerr << "Error opening the linear search results file" << std::endl;
        return 1;
    }

    cout << "Reading files needed..." << endl;

    ReviewList reviewList;

    readReviewsFromCSV("tripadvisor_hotel_reviews.csv", reviewList);

    // Linear Search
    printToBoth(linearOutFile, "Performing Linear Search (Sentiment Analysis for all reviews):\n");
    auto linearStart = steady_clock::now();

    reviewList.countPositiveNegativeWords("positive-words.txt", "negative-words.txt");
    reviewList.linearSearchAllReviews(&linearOutFile);

    auto linearEnd = steady_clock::now();
    auto linearDuration = duration_cast<milliseconds>(linearEnd - linearStart).count();
    printToBoth(linearOutFile, "Linear Search Time: " + to_string(linearDuration) + " milliseconds.\n");
    printToBoth(reportOutFile, "Linear Search Time: " + to_string(linearDuration) + " milliseconds.\n");

    // Count reviews matching/not matching sentiment
    int matchingReviews = 0;
    int nonMatchingReviews = 0;
    ReviewNode* current = reviewList.head;
    while (current != nullptr) {
        double sentimentScore = SentimentCalculation::calculateSentimentScore(current->positiveCount, current->negativeCount);
        double difference = abs(current->rating - sentimentScore);
        if (difference <= 0.25) {
            matchingReviews++;
        }
        else {
            nonMatchingReviews++;
        }
        current = current->next;
    }

    printToBoth(reportOutFile, "Amount of user reviews matching sentiment review: " + to_string(matchingReviews) + "\n");
    printToBoth(reportOutFile, "Amount of user reviews not matching sentiment review: " + to_string(nonMatchingReviews) + "\n\n");

    linearOutFile.close();

    std::cout << "\nPress Enter to run the insertion sort on word frequencies...";
    std::cin.get();

    // Create WordFrequencyList for positive and negative words
    WordFrequencyList positiveWordFreqList;
    WordFrequencyList negativeWordFreqList;

    reviewList.addPositiveWordsToFrequencyList(positiveWordFreqList);
    reviewList.addNegativeWordsToFrequencyList(negativeWordFreqList);

    // ---- Insertion Sort ----
    std::cout << "Sorting positive and negative words using insertion sort...\n";
    auto sortStart = steady_clock::now();

    positiveWordFreqList.insertionSort();
    negativeWordFreqList.insertionSort();

    // Now calculate and display total positive and negative word counts
    current = reviewList.head;  // Reset current to head
    int totalPositiveWords = 0;
    int totalNegativeWords = 0;

    while (current != nullptr) {
        totalPositiveWords += current->positiveCount;
        totalNegativeWords += current->negativeCount;
        current = current->next;
    }
    int totalReviews = reviewList.getSize();

    // Add these statistics to the report file
    printToBoth(reportOutFile, "Total number of reviews: " + to_string(totalReviews) + "\n");
    printToBoth(reportOutFile, "Total number of positive words used in reviews: " + to_string(totalPositiveWords) + "\n");
    printToBoth(reportOutFile, "Total number of negative words used in reviews: " + to_string(totalNegativeWords) + "\n\n");

    // Output the sorted positive and negative word frequencies into one file
    std::ofstream sortedOutFile("insertion_sorted_word_frequencies.txt");
    if (sortedOutFile.is_open()) {
        printToBoth(sortedOutFile, "Total number of reviews: " + to_string(totalReviews) + "\n");
        printToBoth(sortedOutFile, "Total number of positive words used in reviews: " + to_string(totalPositiveWords) + "\n");
        printToBoth(sortedOutFile, "Total number of negative words used in reviews: " + to_string(totalNegativeWords) + "\n");

        sortedOutFile << "Positive Word Frequencies:\n";
        positiveWordFreqList.displayWordFrequencies(&sortedOutFile);

        sortedOutFile << "\n----------------------------------------\n\n";

        sortedOutFile << "Negative Word Frequencies:\n";
        negativeWordFreqList.displayWordFrequencies(&sortedOutFile);

        positiveWordFreqList.displayTop5Frequencies(sortedOutFile, "positive");
        negativeWordFreqList.displayTop5Frequencies(sortedOutFile, "negative");

        sortedOutFile.close();
    }
    else {
        std::cerr << "Error opening the file for writing sorted word frequencies." << std::endl;
    }

    auto sortEnd = steady_clock::now();
    auto totalInsertionSortDuration = duration_cast<milliseconds>(sortEnd - sortStart).count();

    // Append sorting times to report.txt
    printToBoth(reportOutFile, "Total insertion sort time: " + to_string(totalInsertionSortDuration) + " milliseconds.\n");

    reportOutFile << "Insertion Sort - Top 5 Words (Positive & Negative):\n";
    positiveWordFreqList.displayTop5Frequencies(reportOutFile, "positive");
    negativeWordFreqList.displayTop5Frequencies(reportOutFile, "negative");

    std::cout << "\nPress Enter to run the selection sort on word frequencies...";
    std::cin.get();  // Wait for user to press Enter

    // ---- Selection Sort ----
    std::cout << "Sorting positive and negative words using selection sort...\n";
    auto selectionSortStart = std::chrono::high_resolution_clock::now();

    positiveWordFreqList.selectionSort();
    negativeWordFreqList.selectionSort();

    // Reset current to head
    current = reviewList.head;

    // Output the sorted positive and negative word frequencies into one file
    std::ofstream selectionFile("selection_sorted_word_frequencies.txt");
    if (selectionFile.is_open()) {
        printToBoth(selectionFile, "Total number of reviews: " + to_string(totalReviews) + "\n");
        printToBoth(selectionFile, "Total number of positive words used in reviews: " + to_string(totalPositiveWords) + "\n");
        printToBoth(selectionFile, "Total number of negative words used in reviews: " + to_string(totalNegativeWords) + "\n");

        selectionFile << "Positive Word Frequencies:\n";
        positiveWordFreqList.displayWordFrequencies(&selectionFile);

        selectionFile << "\n----------------------------------------\n\n";

        selectionFile << "Negative Word Frequencies:\n";
        negativeWordFreqList.displayWordFrequencies(&selectionFile);

        positiveWordFreqList.displayTop5Frequencies(selectionFile, "positive");
        negativeWordFreqList.displayTop5Frequencies(selectionFile, "negative");

        selectionFile.close();
    }
    else {
        std::cerr << "Error opening the file for writing selection word frequencies." << std::endl;
    }

    auto selectionSortEnd = std::chrono::high_resolution_clock::now();
    auto selectionSortDuration = std::chrono::duration_cast<milliseconds>(selectionSortEnd - selectionSortStart).count();

    // Append selection sort results to report.txt
    printToBoth(reportOutFile, "Total selection sort time: " + to_string(selectionSortDuration) + " milliseconds.\n");

    positiveWordFreqList.displayTop5Frequencies(reportOutFile, "positive");
    negativeWordFreqList.displayTop5Frequencies(reportOutFile, "negative");


    reportOutFile.close();  // Close the report file

    return 0;
}
