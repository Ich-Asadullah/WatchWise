#include <iostream>
#include "MoviesSystem.h"

using namespace std;

void displayMainMenu() {
    cout << "\n1- Watch a Movie\n"
         << "2- Trending\n"
         << "3- Top Rated\n"
         << "4- Filter\n"
         << "5- Recommended Movies\n"
         << "6- Profile\n"
         << "7- Exit\n";
}

void handleWatchMovie(MovieSystem* NexFlix, User* user, LinkedList* moviesList) {
    int watchChoice;
    cout << "1- Search by Movie ID\n"
         << "2- Search By Movie Title\n";
    cin >> watchChoice;

    MovieNode* watched = nullptr;
    switch (watchChoice) {
        case 1: {
            int movieIdInput;
            cout << "\nEnter Movie ID\n";
            cin >> movieIdInput;
            watched = moviesList->searchMovie(movieIdInput);
            break;
        }
        case 2: {
            string movieTitleInput;
            cout << "\nEnter Movie Title\n";
            cin >> movieTitleInput;
            watched = moviesList->search_by_name(movieTitleInput);
            break;
        }
        default:
            cout << "Invalid choice. Returning to main menu.\n";
            return;
    }

    if (watched) {
        watched->display();
        user->updateWatchedMovies(user->userId, watched->title);

        int afterWatch;
        cout << ".........Watched........."
             << "\n1- Add Reviews\n"
             << "2- Report Movie\n"
             << "3- Main Menu\n";
        cin >> afterWatch;

        switch (afterWatch) {
            case 1: {
                string reviewInput;
                cout << "\nEnter review\n";
                cin.ignore(); // Ignore the newline character left in the input buffer
                getline(cin, reviewInput);
                string review = "Movie ID: " + to_string(watched->movieId) + " Movie Title: " + watched->title + " Review: " + reviewInput;
                user->reviewStack.addReview(review, user->userId);
                cout << "Review Added.....\n";
                break;
            }
            case 2:
                moviesList->removeMovie(watched->movieId);
                user->removeWatched(watched->title, user->userId);
                cout << "Movie removed...........\nWe apologize for the inconvenience.....\n";
                break;
            default:
                break;
        }
    } else {
        cout << "Movie not found.\n";
    }
}

void handleTrending(LinkedList* moviesList) {
    cout << "\nTop 10 Trending Movies\n";
    LinkedList* trending = moviesList->sort_by_votes();
    trending->printLimited(10);
    delete trending;
}

void handleTopRated(LinkedList* moviesList) {
    cout << "\nTop Rated Movies\n";
    LinkedList* topRated = moviesList->sort_by_rating();
    topRated->printLimited(10);
    delete topRated;
}

void handleFilter(LinkedList* moviesList) {
    int filterType;
    cout << "\n1- Filter by Genre\n"
         << "2- Filter by Production\n";
    cin >> filterType;

    string filterInput;
    switch (filterType) {
        case 1:
            cout << "\nEnter preferred Genre: ";
            cin >> filterInput;
            moviesList->print_by_genre(filterInput);
            break;
        case 2:
            cout << "Enter preferred Production: ";
            cin >> filterInput;
            moviesList->print_by_production(filterInput);
            break;
        default:
            cout << "Invalid filter type.\n";
            break;
    }
}

void handleRecommendedMovies(User* user, LinkedList* moviesList, RecommendationGraph& recommend) {
    vector<string> userWatched = user->getWatchedMovies(user->userId);
    vector<TreeNode*> recommendedGraph = recommend.getRecommendation(userWatched, moviesList);

    RecommendationHeap recommendedMovies;
    for (TreeNode* treeNode : recommendedGraph) {
        recommendedMovies.insert(treeNode);
    }

    cout << "......Movies Based on your Activity......\n";
    recommendedMovies.printHeapByPriority();
}

void handleProfile(User* user) {
    cout << "Username: " << user->username;
    cout << " ID: " << user->userId;
    cout << "\nWatch History\n";
    for (const string& movieName : user->getWatchedMovies(user->userId)) {
        cout << movieName << "\n";
    }

    cout << "\nReviews\n";
    user->reviewStack.displayReviews(user->userId);
}

int main() {
    MovieSystem* NexFlix = new MovieSystem();
    RecommendationGraph recommend;

    // Login or Signup
    User* user = nullptr;
    while (!user) {
        user = NexFlix->authenticate();
    }

    LinkedList* moviesList = new LinkedList();
    NexFlix->loadData(moviesList);

    int mainChoice;
    bool running = true;

    while (running) {
        displayMainMenu();
        cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                handleWatchMovie(NexFlix, user, moviesList);
                break;
            case 2:
                handleTrending(moviesList);
                break;
            case 3:
                handleTopRated(moviesList);
                break;
            case 4:
                handleFilter(moviesList);
                break;
            case 5:
                handleRecommendedMovies(user, moviesList, recommend);
                break;
            case 6:
                handleProfile(user);
                break;
            case 7:
                running = false;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    delete moviesList;
    delete NexFlix;

    return 0;
}
