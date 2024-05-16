#ifndef USERLOGIN_H
#define USERLOGIN_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// Function to check if a user exists in the system and return the user ID
int userExists(string username, string password) {
    ifstream userFile("users.txt");
    string line;
    while (getline(userFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);  // Find the second comma after the username
        if (pos1 == string::npos || pos2 == string::npos) {
            continue;  // Skip lines that don't have the correct format
        }
        string storedUsername = line.substr(0, pos1);
        string storedPassword = line.substr(pos1 + 1, pos2 - pos1 - 1);  // Extract password between commas
        string userIdStr = line.substr(pos2 + 1);  // Extract user ID after the second comma
        if (storedUsername == username && storedPassword == password) {
            userFile.close();
            return stoi(userIdStr);  // Convert user ID string to integer and return
        }
    }
    userFile.close();
    return -1;  // Return -1 if user not found
}

// Function to update watched movies for a user
void updateWatchedMovies(int userId, string movieName) {
    string folderPath = "userData/";
    string filename = folderPath + "watched_" + to_string(userId) + ".txt";
    ofstream watchedFile(filename, ios::app);
    if (watchedFile.is_open()) {
        watchedFile << movieName << "\n";
        watchedFile.close();
    } else {
        cerr << "Error: Unable to open file " << filename << " for writing.\n";
    }
}

// Function to retrieve watched movies for a user
vector<string> getWatchedMovies(int userId) {
    vector<string> watchedMovies;
    string folderPath = "userData/";
    string filename = folderPath + "watched_" + to_string(userId) + ".txt";
    ifstream watchedFile(filename);
    string movie;
    while (getline(watchedFile, movie)) {
        watchedMovies.push_back(movie);
    }
    watchedFile.close();
    return watchedMovies;
}

// Function to check the Uniqueness of new Username
bool checkUnique(string usernameCheck){
    ifstream userFile("users.txt");
    string line;
    while (getline(userFile, line)) {
        size_t pos1 = line.find(',');
        string storedUsername = line.substr(0, pos1);
        if (usernameCheck == storedUsername){
            return false;
        }
    }
    return true;
}

// Function to create a new user
bool createUser(string username, string password, int userId) {
    ofstream userFile("users.txt", ios::app);
    if (userFile.is_open()) {
        if(checkUnique(username)){
            userFile << username << "," << password << "," << userId << "\n";
            userFile.close();
            return true;
        }
        else{
            return false;
        }  
    } else {
        cerr << "Error: Unable to create or open users file.\n";
    }
}

// Function to get last UserID
int getLastID(){
    string userIdStr = "0";
    ifstream userFile("users.txt");
    string line;
    while (getline(userFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);  // Find the second comma after the username
        if (pos1 == string::npos || pos2 == string::npos) {
            continue;  // Skip lines that don't have the correct format
        }
        string storedUsername = line.substr(0, pos1);
        string storedPassword = line.substr(pos1 + 1, pos2 - pos1 - 1);  // Extract password between commas
        userIdStr = line.substr(pos2 + 1);  // Extract user ID after the second comma
    }

    return stoi(userIdStr);
}

#endif
