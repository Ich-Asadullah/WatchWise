#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

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

    MovieNode(string title, int id, int votes, double ratings, string language, int duration, vector<string> production, vector<string> genres) {
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

    void display() {
        cout << "\nTitle: " << this->title
             << "\nID: " << this->movieId
             << "\nRatings: " << this->rating
             << "\nVotes: " << this->votes
             << "\nLanguage: " << this->language
             << "\nDuration: " << this->duration << endl;
    }
};

class LinkedList {
public:
    MovieNode* head;

    LinkedList() : head(nullptr) {}

    // Adding movies
    void addMovie(string title, int id, int votes, double ratings, string language, int duration, vector<string> production, vector<string> genres) {
        MovieNode* newNode = new MovieNode(title, id, votes, ratings, language, duration, production, genres);
        newNode->next = head;
        head = newNode;
    }

    // Remove movie
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

    // Search movies by id
    MovieNode* searchMovie(int id) {
        MovieNode* curr = head;
        while (curr != nullptr) {
            if (curr->movieId == id) {
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }

    // Display all movies
    void displayMovies() {
        MovieNode* current = head;
        while (current) {
            current->display();
            current = current->next;
        }
    }

    // Search and print movie by title
    MovieNode* search_by_name(string title) {
        MovieNode* current = head;
        while (current != nullptr) {
            if (current->title == title) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Create a copy of the list
    LinkedList* copyList() {
        LinkedList* newList = new LinkedList();
        MovieNode* current = head;
        MovieNode* tail = nullptr;

        while (current != nullptr) {
            MovieNode* newNode = new MovieNode(current->title, current->movieId, current->votes, current->rating, current->language, current->duration, current->production, current->genres);
            if (newList->head == nullptr) {
                newList->head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            current = current->next;
        }
        return newList;
    }

    // Sort movies by votes
    LinkedList* sort_by_votes() {
        LinkedList* sortedList = copyList();
        MovieNode* current = sortedList->head;
        MovieNode* sortedHead = nullptr;

        while (current != nullptr) {
            MovieNode* nextNode = current->next;
            if (sortedHead == nullptr || current->votes > sortedHead->votes) {
                current->next = sortedHead;
                sortedHead = current;
            } else {
                MovieNode* prev = sortedHead;
                while (prev->next != nullptr && prev->next->votes >= current->votes) {
                    prev = prev->next;
                }
                current->next = prev->next;
                prev->next = current;
            }
            current = nextNode;
        }
        sortedList->head = sortedHead;
        return sortedList;
    }

    // Print movies sorted by votes
    void print_sorted_by_votes() {
        int count = 1;
        LinkedList* sortedList = sort_by_votes();
        MovieNode* current = sortedList->head;
        while (current) {
            cout << count << ". " << current->movieId << "  " << current->title << "  " << current->votes << "\n";
            count++;
            current = current->next;
        }
        delete sortedList;
    }

    // Sort movies by rating
    LinkedList* sort_by_rating() {
        LinkedList* sortedList = copyList();
        MovieNode* current = sortedList->head;
        MovieNode* sortedHead = nullptr;

        while (current != nullptr) {
            MovieNode* nextNode = current->next;
            if (sortedHead == nullptr || current->rating > sortedHead->rating) {
                current->next = sortedHead;
                sortedHead = current;
            } else {
                MovieNode* prev = sortedHead;
                while (prev->next != nullptr && prev->next->rating >= current->rating) {
                    prev = prev->next;
                }
                current->next = prev->next;
                prev->next = current;
            }
            current = nextNode;
        }
        sortedList->head = sortedHead;
        return sortedList;
    }

    // Print movies sorted by rating
    void print_sorted_by_rating() {
        int count = 1;
        LinkedList* sortedList = sort_by_rating();
        MovieNode* current = sortedList->head;
        while (current) {
            if (current->votes > 100) {
                cout << count << ". " << current->movieId << "  " << current->title << "  " << current->rating << "\n";
                count++;
            }
            current = current->next;
        }
        delete sortedList;
    }

    // Print all movies of a specific genre
    void print_by_genre(string genreToSearch) {
        MovieNode* current = head;
        int count = 1;
        while (current != nullptr) {
            for (string genre : current->genres) {
                if (genre == genreToSearch) {
                    cout << count << ". " << current->movieId << "  " << current->title << "  " << current->rating << "\n";
                    count++;
                    break;
                }
            }
            current = current->next;
        }
    }

    // Print all movies of a specific production
    void print_by_production(string productionToSearch) {
        MovieNode* current = head;
        int count = 1;
        while (current != nullptr) {
            for (string production : current->production) {
                if (production == productionToSearch) {
                    cout << count << ". " << current->movieId << "  " << current->title << "  " << current->rating << "\n";
                    count++;
                    break;
                }
            }
            current = current->next;
        }
    }

    // Function to print limited top values
    void printLimited(int limit) {
        int count = 1;
        MovieNode* current = head;
        while (current != nullptr && count <= limit) {
            cout << count << ". " << current->movieId << "  " << current->title << "  " << current->rating << "\n";
            count++;
            current = current->next;
        }
    }

    ~LinkedList() {
        MovieNode* current = head;
        while (current) {
            MovieNode* next = current->next;
            delete current;
            current = next;
        }
    }
};
