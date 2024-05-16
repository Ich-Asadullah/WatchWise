#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <stack>

#include "MoviesData.h"

using namespace std;

class UserReviewStack {
public:
    stack<string> reviews;

    // Retrieve data from file and update the user stack
    void updateStack(vector<string> reviews){
        stack<string> reviewStack;
        for (string review : reviews) {
            reviewStack.push(review);
        }
        this->reviews = reviewStack;
    }
    
    //Function to add reviews for a movie
    void addReview(string review, int userId) {
        reviews.push(review);
        saveReviewToFile(review, userId);
    }

    // Function to display all reviews made by a user
    void displayReviews(int userId) {
        vector<string> reviews_list = retrieveReviews(userId);
        updateStack(reviews_list); //Updating stack of reviews from file
        
        stack<string> tempStack = reviews;
        while (!tempStack.empty()) {
            cout << tempStack.top() << endl;
            tempStack.pop();
        }
    }

    // Function to write reviews to reviews file
    void saveReviewToFile(string review, int userId) {
        string filename = "userReviews/User_" + to_string(userId) + ".txt";
        ofstream reviewFile(filename, ios::app);
        if (reviewFile.is_open()) {
            reviewFile << review << "\n";
            reviewFile.close();
        } else {
            cerr << "Error: Unable to open file " << filename << " for writing.\n";
        }
    }

    // Function to get reviews from reviews file
    vector<string> retrieveReviews(int userId) {
        vector<string> allReviews;
        string filename = "userReviews/User_" + to_string(userId) + ".txt";
        ifstream reviewFile(filename);
        if (reviewFile.is_open()) {
            string review;
            while (getline(reviewFile, review)) {
                allReviews.push_back(review);
            }
            reviewFile.close();
        } else {
            cerr << "Error: Unable to open file " << filename << " for reading.\n";
        }
        return allReviews;
    }
};

class User {
public:
    int userId;
    string username;
    LinkedList watchHistory;
    UserReviewStack reviewStack;

    User(int id, string n){
        this->userId = id;
        this->username = n;
    }
};

#endif