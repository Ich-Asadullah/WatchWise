#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>

#include "MoviesData.h"
#include "UserLogin.h"
#include "MoviesTree.h"
#include "Recommendation.h"
#include "User.h"

using namespace std;

class MovieSystem {
public:

    // Function to Log In to the System
    User* logIn(){
        string username, password;
        cout<<"Enter Username: ";
        cin>>username;
        cout<<"Enter Password: ";
        cin>>password;

        int loggedin = (userExists(username, password));

        if (loggedin != -1){
            return new User(loggedin, username);
        }
        else{
            return nullptr;
        }
    }//LogIn ends here

    //Function to Sign Up to the System
    User* SignUP(){
        string username, password;
        cout<<"Enter Username: ";
        cin>>username;

        if(!(checkUnique(username))){
            cout<<"Username already taken....";
            return SignUP();
        }
        else{
            cout<<"Enter Password: ";
            cin>>password;
            int id = getLastID();

            if(createUser(username,password, id+1)){
                cout<<"User created with ID: "<<id+1<<endl;
                return new User(id+1, username);
            }
            else{
                return nullptr;
            }
        }
    } //SignUp ends here

    User* authenticate(){
        int choice;
        cout<<"Enter 1 to Login\n"
            <<"Enter 2 to SignUP: ";
        
        cin>>choice;

        if (choice == 1){
            User* user = this->logIn();
            if(user){
                cout<<"WELCOME "<<user->username<<endl;
                return user;
            }
            else{
                cout<<"Incorrect Username or Password....."<<endl;
                return nullptr;
            }
        }

        else if(choice == 2){
            User* user = this->SignUP();

            if(user){
                cout<<"WELCOME "<<user->username<<endl;
                return user;
            }
            else{
                cout<<"We are having Technical Issues.... Try Again..."<<endl;
                return nullptr;
            }
        }
    }

    //Function to Split String(Genre and Production strings to vectors) helper for loading dataset
    vector<string> splitString(const string& input) {
        vector<string> tokens;
        stringstream ss(input);
        string token;
        char d = '-';

        while (getline(ss, token, d)) {
            tokens.push_back(token);
        }

        return tokens;
    }

    // Function to load all the Data from CSV
    LinkedList* loadData(LinkedList*& movieList){
    ifstream fin("movies_metadata.csv");
    string line, word;
    vector<string> lineData;
    int lines = 0;
    while (getline(fin, line)) {
        stringstream s(line);
        while (getline(s, word, ',')) {
            lineData.push_back(word);
        }
        // Ensure that the line contains the expected number of fields
        if (lineData.size() == 8) {
            // Type casting id, vote_count, and runtime from string to int, and vote_average from string to float
            stringstream idStream(lineData[1]);
            stringstream voteCountStream(lineData[2]);
            stringstream voteAverageStream(lineData[3]);
            stringstream runtimeStream(lineData[5]);
            int id, voteCount, runtime;
            double voteAverage;
            idStream >> id;
            voteCountStream >> voteCount;
            voteAverageStream >> voteAverage;
            runtimeStream >> runtime;

            vector<string> production = splitString(lineData[6]);
            vector<string> genres = splitString(lineData[7]);

            // Adding data to linked list
            movieList->addMovie(lineData[0], id, voteCount, voteAverage, lineData[4], runtime, production, genres );
        } else {
            // Handle invalid data format
            cerr << "Invalid data format in line " << lines + 1 << ": " << line << endl;
        }
        lineData.clear();
        lines++;
    }
    fin.close();
    return movieList;
}

};

#endif