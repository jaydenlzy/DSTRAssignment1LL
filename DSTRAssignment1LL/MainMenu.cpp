#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>  // For trimming whitespace

// Linked list node for storing reviews and ratings
struct ReviewNode {
    std::string review;  // Review text
    int rating;          // Rating
    ReviewNode* next;    // Pointer to the next node
};

// Linked list node for storing words (positive and negative)
struct WordNode {
    std::string word;    // Word (positive or negative)
    WordNode* next;      // Pointer to the next node
};

// Function to trim leading and trailing whitespace
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

// Function to add a review and rating to the linked list
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

// Function to add a word to the linked list (for both positive and negative words)
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

// Function to load reviews and ratings from the CSV file
void loadReviewsFromFile(ReviewNode*& head, const std::string& filename) {
    std::ifstream file(filename);  // Open the CSV file
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file.\n";
        return;
    }

    std::string line, review, ratingString;
    int rating;

    // Skip the header row
    std::getline(file, line);

    // Read each line from the CSV file
    while (std::getline(file, line)) {
        std::stringstream ss(line);

        // Extract the first column (review)
        if (line[0] == '"') {
            // If the review is enclosed in quotes, handle it correctly
            size_t endQuotePos = line.find_last_of('"');
            review = line.substr(1, endQuotePos - 1);  // Get the text between the quotes
            ratingString = line.substr(endQuotePos + 2);  // Rating comes after the last quote and a comma
        }
        else {
            // If the review isn't enclosed in quotes, treat normally
            std::getline(ss, review, ',');
            std::getline(ss, ratingString, ',');
        }

        // Trim any extra whitespace or special characters
        ratingString = trim(ratingString);

        // Convert the rating from string to integer
        try {
            rating = std::stoi(ratingString);  // Convert to integer
        }
        catch (...) {
            rating = 0;  // If conversion fails, default to 0
            std::cerr << "Error: Failed to convert rating. Setting to 0.\n";
        }

        // Add the review and rating to the linked list
        addReview(head, review, rating);
    }

    file.close();  // Close the file after reading
}

// Function to load words (positive or negative) from a text file
void loadWordsFromFile(WordNode*& head, const std::string& filename) {
    std::ifstream file(filename);  // Open the text file
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file.\n";
        return;
    }

    std::string word;
    while (std::getline(file, word)) {
        // Add each word to the linked list
        addWord(head, word);
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
        // Display review and rating in the desired format
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

// Function to display positive or negative words
void showWords(WordNode* head) {
    if (head == nullptr) {
        std::cout << "No words available.\n";
        return;
    }

    WordNode* temp = head;
    while (temp != nullptr) {
        std::cout << temp->word << "\n";
        temp = temp->next;
    }
}

// Function to display the menu
void displayMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Show Reviews and Ratings\n";
    std::cout << "2. Show Positive Words\n";
    std::cout << "3. Show Negative Words\n";
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
            // Display positive words
            std::cout << "Positive Words:\n";
            showWords(positiveWordsHead);
            break;
        case 3:
            // Display negative words
            std::cout << "Negative Words:\n";
            showWords(negativeWordsHead);
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
