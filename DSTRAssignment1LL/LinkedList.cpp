#include "LinkedList.h"
#include <iostream>

// ReviewNode constructor
ReviewNode::ReviewNode(std::string fb, int rate) {
    feedback = fb;
    rating = rate;
    next = nullptr;
}

// LinkedList constructor
LinkedList::LinkedList() {
    headReview = nullptr;
}

// LinkedList destructor (optional, if you want to free memory when the program ends)
LinkedList::~LinkedList() {
    // Optional: If you want to delete the list nodes when the program ends
}

// Add a new review to the review linked list
void LinkedList::addReview(std::string feedback, int rating) {
    ReviewNode* newNode = new ReviewNode(feedback, rating);
    if (!headReview) {
        headReview = newNode;  // If the list is empty
    }
    else {
        ReviewNode* temp = headReview;  // Traverse to the end of the list
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Print all reviews and ratings
void LinkedList::printReviews() {
    ReviewNode* temp = headReview;
    while (temp) {
        std::cout << "Review: " << temp->feedback
            << " | Rating: " << temp->rating << std::endl;
        temp = temp->next;
    }
}
