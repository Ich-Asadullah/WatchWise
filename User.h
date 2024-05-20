#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

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
        // Update the stach by retrieving reviews from file
        updateStack(retrieveReviews(userId));
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
        string filename = "UserReviews/User_" + to_string(userId) + ".txt";
        ofstream reviewFile(filename, ios::trunc);
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
        string filename = "UserReviews/User_" + to_string(userId) + ".txt";
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

    // Function to retrieve watched movies for a user
    vector<string> getWatchedMovies(int userId) {
        vector<string> watchedMovies;
        string folderPath = "WatchHistory/";
        string filename = folderPath + "User_" + to_string(userId) + ".txt";
        ifstream watchedFile(filename);
        string movie;
        while (getline(watchedFile, movie)) {
            watchedMovies.push_back(movie);
        }
        watchedFile.close();
        return watchedMovies;
    }

    //Function to not repeat movies in watched
    bool checkUniqueMovie(vector<string> listt, string movie){
        for (string i : listt){
            if (i == movie){
                return false;
            }
        }
        return true;
    }

    // Function to update watched movies for a user
    void updateWatchedMovies(int userId, const string& movieName) {
        vector<string> watched = getWatchedMovies(userId);
        
        if (checkUniqueMovie(watched, movieName)) {
            watched.push_back(movieName);
        } else {
            return;
        }
    
        string folderPath = "WatchHistory/";
        string filename = folderPath + "User_" + to_string(userId) + ".txt";
        ofstream watchedFile(filename, ios::trunc);
    
        if (watchedFile.is_open()) {
            for (const string& movie : watched) {
                watchedFile << movie << "\n";
            }
            watchedFile.close();
        } else {
            cerr << "Error: Unable to open file " << filename << " for writing.\n";
        }
    }

    // Function to remove a movie from watched
    void removeWatched(string movieName, int userID) {
        vector<string> watched = getWatchedMovies(userID);
        // Remove the movie from the vector
        watched.erase(remove(watched.begin(), watched.end(), movieName), watched.end());
        string folderPath = "userData/";
        string filename = folderPath + "watched_" + to_string(userID) + ".txt";
        ofstream watchedFile(filename, ios::trunc);
        if (watchedFile.is_open()) {
            // Write the updated list back to the file
            for (string movie : watched) {
                watchedFile << movie << "\n";
            }
            watchedFile.close();
        } else {
            cerr << "Error: Unable to open file " << filename << " for writing.\n";
        }
    }

};

#endif
