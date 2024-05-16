#ifndef MOVIESDATA_H
#define MOVIESDATA_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Movies Data Class
class MovieNode {
public:
    int movieId;
    string title;
    int votes;
    double rating;
    string language;
    vector<string> production;
    vector<string> genres;      
    int duration;
    MovieNode* next;

    MovieNode(int id, string title, double ratings, int votes, string language, int duration,  vector<string> production,  vector<string> genres){
        this->movieId = id;
        this->rating = ratings;
        this->title = title;
        this->votes = votes;
        this->language = language;
        this->duration = duration;
        this->production = production;
        this->genres = genres;
        this->next = nullptr;
    }

    void display(){
        cout<<"\nTitle: "<< this->title
        <<"\nID: "<< this->movieId
        <<"\nRatings: "<< this->rating
        <<"\nVotes: "<<this->votes
        <<"\nLanguage: "<<this->language
        <<"\nDuration"<<this->duration;
    }
};

// Data Structure used to save Movies data
class LinkedList {
public:
    MovieNode* head;

    LinkedList() : head(nullptr) {}

    void addMovie(int id, string title, double ratings, int votes, string language, int duration,  vector<string> production,  vector<string> genres) {
        MovieNode* newNode = new MovieNode(id, title, ratings, votes, language, duration, production, genres);
        newNode->next = head;
        head = newNode;
    }

    void removeMovie(int movieId) {
        MovieNode* current = head;
        MovieNode* previous = nullptr;

        while (current) {
            if (current->movieId == movieId) {
                if (previous) {
                    previous->next = current->next;
                } else {
                    head = current->next;
                }
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }
    }

    MovieNode* searchMovie(int id){
        MovieNode* curr = head;
        while (curr != nullptr){
            if(curr->movieId == id){
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }

    void displayMovies() {
        MovieNode* current = head;
        while (current) {
            current->display();
            current = current->next;
        }
    }
};

#endif