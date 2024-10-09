#include "reviewlist.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include "SentimentCalculation.h"

using namespace std;

// Constructor for ReviewNode
ReviewNode::ReviewNode(string rev, int rate) {
    review = rev;
    rating = rate;
    positiveCount = 0;
    negativeCount = 0;
    next = nullptr;
}

// Constructor for ReviewList
ReviewList::ReviewList() {
    head = nullptr;
}

// Function to add a new review to the list
void ReviewList::addReview(string review, int rating) {
    ReviewNode* newNode = new ReviewNode(review, rating);
    if (head == nullptr) {
        head = newNode;
    }
    else {
        ReviewNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

std::unordered_set<std::string> loadWordsFromFile(const std::string& filename) {
    std::unordered_set<std::string> words;
    std::ifstream file(filename);
    std::string word;

    if (file.is_open()) {
        while (std::getline(file, word)) {
            words.insert(word);
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }

    return words;
}


// Function to display reviews (for debugging or general output)
void ReviewList::displayReviews() {
    if (head == nullptr) {
        cout << "No reviews available!" << endl;
        return;
    }
    ReviewNode* temp = head;
    while (temp != nullptr) {
        cout << "Review: " << temp->review << endl;
        cout << "Rating: " << temp->rating << endl;
        cout << "Positive Words (" << temp->positiveCount << "): ";
        temp->positiveWordList.displayWords();  // Display positive words
        cout << endl;
        cout << "Negative Words (" << temp->negativeCount << "): ";
        temp->negativeWordList.displayWords();  // Display negative words
        cout << endl;
        // Calculate and display sentiment score
        double sentimentScore = SentimentCalculation::calculateSentimentScore(temp->positiveCount, temp->negativeCount);
        cout << "Sentiment Score (1 - 5): " << sentimentScore << endl;
        temp = temp->next;
    }
}

// Function to count positive and negative words in each review
void ReviewList::countPositiveNegativeWords(const string& positiveFile, const string& negativeFile) {
    unordered_set<string> positiveWords = loadWordsFromFile(positiveFile);
    unordered_set<string> negativeWords = loadWordsFromFile(negativeFile);

    ReviewNode* temp = head;
    while (temp != nullptr) {
        stringstream ss(temp->review);
        string word;
        while (ss >> word) {
            // Remove any punctuation from the word
            word.erase(remove_if(word.begin(), word.end(), [](unsigned char c) { return ispunct(c); }), word.end());

            if (positiveWords.find(word) != positiveWords.end()) {
                temp->positiveCount++;
                temp->positiveWordList.addWord(word);  // Store the word in the linked list
            }
            else if (negativeWords.find(word) != negativeWords.end()) {
                temp->negativeCount++;
                temp->negativeWordList.addWord(word);  // Store the word in the linked list
            }
        }
        temp = temp->next;
    }
}
std::string evaluateReview(double sentimentScore, double rating) {
    double difference = abs(rating - sentimentScore);

    if (difference > 0.5) {
        return "The review is not accurate because the rating given by the customer is higher than the calculate sentiment review.";
    }
    else if (difference <= 0.25) {
        return "The review is accurate.";
    }
    else {
        return "The review is not accurate because the rating given by the customer is lower than the calculate sentiment review.";
    }
}

void WordList::displayWords() const {
    WordNode* temp = head;
    while (temp != nullptr) {
        cout << temp->word;
        if (temp->next != nullptr) {
            cout << ", ";
        }
        temp = temp->next;
    }
}


// Linear search through all reviews and perform sentiment analysis
void ReviewList::linearSearchAllReviews(std::ofstream* outFile) {
    ReviewNode* temp = head;

    while (temp != nullptr) {
        // Perform sentiment analysis for each review
        string output = "Review: " + temp->review + "\n";
        output += "Rating: " + to_string(temp->rating) + "\n";

        output += "Positive Words (" + to_string(temp->positiveCount) + "): [";
        temp->positiveWordList.displayWords(output);
        output += "]\n";

        output += "Negative Words (" + to_string(temp->negativeCount) + "): [";
        temp->negativeWordList.displayWords(output);
        output += "]\n";

        // Calculate sentiment score
        double sentimentScore = SentimentCalculation::calculateSentimentScore(temp->positiveCount, temp->negativeCount);
        output += "Sentiment Score: " + to_string(sentimentScore) + "\n";

        // Evaluate the review based on the sentiment score
        string evaluation = evaluateReview(sentimentScore, temp->rating);
        output += "Evaluation: " + evaluation + "\n\n";

        // Print to both console and file
        cout << output;
        if (outFile != nullptr && outFile->is_open()) {
            *outFile << output;
        }

        temp = temp->next;
    }
}


// Function to calculate sentiment score for a review at a specific index
double ReviewList::calculateSentimentScore(int index) {
    ReviewNode* temp = head;
    int currentIndex = 0;

    // Traverse to the correct index
    while (temp != nullptr && currentIndex < index) {
        temp = temp->next;
        currentIndex++;
    }

    if (temp != nullptr) {
        // Use positive and negative counts to calculate sentiment score
        return SentimentCalculation::calculateSentimentScore(temp->positiveCount, temp->negativeCount);
    }
    else {
        return -1;  // Return -1 for invalid index
    }
}

void WordFrequencyList::insertionSort() {
    if (!head || !head->next) {
        return;  // List is empty or has only one node
    }


    WordFrequencyNode* sorted = nullptr;  // Start with an empty sorted list

    WordFrequencyNode* current = head;
    while (current != nullptr) {
        WordFrequencyNode* next = current->next;  // Store the next node

        // Insert the current node into the sorted list
        if (sorted == nullptr || sorted->count <= current->count) {
            current->next = sorted;
            sorted = current;
        }
        else {
            WordFrequencyNode* temp = sorted;
            while (temp->next != nullptr && temp->next->count > current->count) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;  // Move to the next node
    }

    head = sorted;  // Update the head to point to the sorted list
}



void WordFrequencyList::displayWordFrequencies(std::ofstream* outFile) {
    WordFrequencyNode* temp = head;
    while (temp != nullptr) {
        std::cout << temp->word << ": " << temp->count << std::endl;
        if (outFile) {
            *outFile << temp->word << ": " << temp->count << std::endl;
        }
        temp = temp->next;
    }
}



void WordFrequencyList::addWordFrequency(const std::string& word) {
    // Check if the word already exists in the list
    WordFrequencyNode* temp = head;
    while (temp != nullptr) {
        if (temp->word == word) {
            // If the word exists, increment its count
            temp->count++;
            return;
        }
        temp = temp->next;
    }

    // If the word doesn't exist, add a new node with count = 1
    WordFrequencyNode* newNode = new WordFrequencyNode(word, 1);
    newNode->next = head;
    head = newNode;
}


// Function to retrieve the review and rating at a given index
void ReviewList::getReview(int index, std::string& review, int& rating) {
    ReviewNode* temp = head;
    int currentIndex = 0;

    // Traverse to the correct index
    while (temp != nullptr && currentIndex < index) {
        temp = temp->next;
        currentIndex++;
    }

    if (temp != nullptr) {
        review = temp->review;
        rating = temp->rating;
    }
}

// Function to get the total number of reviews
int ReviewList::getSize() {
    int size = 0;
    ReviewNode* temp = head;
    while (temp != nullptr) {
        size++;
        temp = temp->next;
    }
    return size;
}
// Function to add all positive words from each review into the WordFrequencyList
void ReviewList::addPositiveWordsToFrequencyList(WordFrequencyList& wordFreqList) {
    ReviewNode* current = head;

    // Traverse each review
    while (current != nullptr) {
        WordNode* wordNode = current->positiveWordList.head;

        // Traverse each word in the positive word list of the current review
        while (wordNode != nullptr) {
            wordFreqList.addWordFrequency(wordNode->word);
            wordNode = wordNode->next;
        }

        current = current->next;
    }
}

void ReviewList::addNegativeWordsToFrequencyList(WordFrequencyList& wordFreqList) {
    ReviewNode* current = head;

    // Traverse each review
    while (current != nullptr) {
        WordNode* wordNode = current->negativeWordList.head;

        // Traverse each word in the negative word list of the current review
        while (wordNode != nullptr) {
            wordFreqList.addWordFrequency(wordNode->word);
            wordNode = wordNode->next;
        }

        current = current->next;
    }
}
void WordFrequencyList::selectionSort() {
    WordFrequencyNode* current = head;

    while (current != nullptr) {
        WordFrequencyNode* minNode = current;
        WordFrequencyNode* nextNode = current->next;

        // Find the node with the minimum count
        while (nextNode != nullptr) {
            if (nextNode->count < minNode->count) {
                minNode = nextNode;
            }
            nextNode = nextNode->next;
        }

        // Swap the current node with the minNode
        if (minNode != current) {
            std::swap(current->word, minNode->word);
            std::swap(current->count, minNode->count);
        }

        current = current->next;  // Move to the next node
    }
}


