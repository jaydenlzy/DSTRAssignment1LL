#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>

// Define the Review Node (for hotel reviews)
struct ReviewNode {
    std::string feedback;   // Hotel feedback text
    int rating;             // Rating for the hotel
    ReviewNode* next;       // Pointer to the next review

    // Constructor to initialize a ReviewNode
    ReviewNode(std::string fb, int rate);
};

// Class to manage linked lists for reviews
class LinkedList {
public:
    ReviewNode* headReview;    // Head of the reviews linked list

    LinkedList();  // Constructor
    ~LinkedList(); // Destructor (optional)

    // Function prototypes
    void addReview(std::string feedback, int rating);
    void printReviews();       // Print all reviews and ratings
};

#endif
