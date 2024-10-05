#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <string>

// Define the Review Node (for hotel reviews)
struct ReviewNode {
    std::string feedback;   // Hotel feedback text
    int rating;             // Rating for the hotel
    ReviewNode* next;       // Pointer to the next review

    // Constructor to initialize a ReviewNode
    ReviewNode(const std::string& fb, int rate);
};

// Class to manage linked lists for reviews
class LinkedList {
public:
    ReviewNode* headReview;    // Head of the reviews linked list
    ReviewNode* tailReview;    // Tail pointer for optimized insertion
    int nodeCount;             // Keeps track of the number of nodes

    LinkedList();  // Constructor
    ~LinkedList(); // Destructor

    // Function prototypes
    void addReview(const std::string& feedback, int rating);
    void printReviews() const;       // Print all reviews and ratings
    int getCount() const;            // Return number of reviews
};

// Define the Word Node (for storing positive/negative words)
struct WordNode {
    std::string word;     // Word (positive or negative)
    WordNode* next;       // Pointer to the next word

    // Constructor to initialize a WordNode
    WordNode(const std::string& w);
};

// Class to manage linked lists for words
class WordLinkedList {
public:
    WordNode* headWord;    // Head of the words linked list
    WordNode* tailWord;    // Tail pointer for optimized insertion
    int wordCount;         // Keeps track of the number of words

    WordLinkedList();  // Constructor
    ~WordLinkedList(); // Destructor

    // Function prototypes
    void addWord(const std::string& word);
    void printWords() const;       // Print all words in the list
    int getCount() const;          // Return number of words
};

#endif
