#include <iostream>

#include "MoviesSystem.h"
#include "User.h"

using namespace std;

int main(){

    MovieSystem* NexFlix = new MovieSystem();
    RecommendationGraph recommend;

    // Login or Signup
    User* user = nullptr;
    while(!user){
        user = NexFlix->authenticate();
    }

    //Loading the data for Dataset
    LinkedList* moviesList;
    NexFlix->loadData(moviesList);

    //Initialization of all variables that will be used
    LinkedList* topRated;
    LinkedList* trending;
    MovieNode* watched;
    vector<string> userWatched;
    vector<TreeNode*> recommendedGraph;
    RecommendationHeap recommendedMovies;
    int mainChoice, watchChoice, movieIdInput, filterType;
    string review, reviewInput, movieTitleInput, filterInput;

    //Main Menu
    cout<<"1- Watch a Movie\n"
        <<"2- Trending\n"
        <<"3- Top Rated\n"
        <<"4- Filter\n"
        <<"5- Recommended Movies\n"
        <<"6- Profile\n";
    
    cin>>mainChoice;

    switch (mainChoice)
    {
    // Case To watch a Movie
    case 1:
        cout<<"1- Search by Movie ID\n"
            <<"2- Search By Movie Title\n";
        cin>>watchChoice;

        switch (watchChoice)
        {
        case 1:
            cout<<"Enter Movie ID\n";
            cin>>movieIdInput;
            watched = moviesList->searchMovie(movieIdInput);
            // Check if movie is watched
            if (watched){
                int afterWatch;
                cout<<".........Watched........."
                    <<"1- Add Reviews\n"
                    <<"2- Report Movie\n"
                    <<"3- Main Menu\n";
                cin>>afterWatch;

                // Switch to Check Reviews Report or Main menu
                switch (afterWatch)
                {
                //Adding review
                case 1:
                    cout<<"Enter review\n";
                    cin>>reviewInput;
                    review = "Movie ID: " + to_string(watched->movieId) + "Movie Title: " + watched->title + "\nReview: " + reviewInput;
                    user->reviewStack.addReview(review, user->userId);
                    cout<<"Review Added.....";
                    break;
                // Reporting and removing a movie
                case 2:
                    moviesList->removeMovie(watched->movieId);
                    user->removeWatched(watched->title, user->userId);
                    cout<<"Movie removed...........\nWe apologize for inconvinience.....";
                // Main Menu
                default:
                    break;
                }
                }
            // No Movie Found
            else{
                cout<<"Movie not fount with ID : "<<movieIdInput;
                break;
            }
            break;
        
        case 2:
            cout<<"Enter Movie Title\n";
            cin>>movieTitleInput;
            watched = moviesList->search_by_name(movieTitleInput);
            // Check if movie is watched
            if (watched){
                int afterWatch;
                cout<<".........Watched........."
                    <<"1- Add Reviews\n"
                    <<"2- Report Movie\n"
                    <<"3- Main Menu\n";
                cin>>afterWatch;

                // Switch to Check Reviews Report or Main menu
                switch (afterWatch)
                {
                    //Adding review
                    case 1:
                        reviewInput;
                        cout<<"Enter review\n";
                        cin>>reviewInput;
                        review = "Movie ID: " + to_string(watched->movieId) + "Movie Title: " + watched->title + "\nReview: " + reviewInput;
                        user->reviewStack.addReview(review, user->userId);
                        cout<<"Review Added.....";
                        break;
                    // Reporting and removing a movie
                    case 2:
                        moviesList->removeMovie(watched->movieId);
                        cout<<"Movie removed...........\nWe apologize for inconvinience.....";
                    // Main Menu
                    default:
                        break;
                    }
                }
            // No Movie Found
            else{
                cout<<"Movie not fount with Title : "<<movieTitleInput;
                break;
            }
            break;
        
        default:
            break;
        }
        break;
    
    case 2:
        cout<<"\nTop 10 Trending Movies\n";
        trending = moviesList->sort_by_rating();
        trending->printLimited(10);
        break;

    case 3:
        cout<<"\nTop Rated Movies\n";
        topRated = moviesList->sort_by_votes();
        topRated->printLimited(10);
        break;
    
    case 4:
        filterType;
        cout<<"1- Filter by Genre\n"
            <<"2- Filter by Production\n";

        cin>>filterType;

        switch (filterType)
        {
            filterInput;
            case 1:
                cout<<"Enter prefered Genre: ";
                cin>>filterInput;
                moviesList->print_by_genre(filterInput);
                break;
            
            case 2:
                cout<<"Enter prefered Production: ";
                cin>>filterInput;
                moviesList->print_by_production(filterInput);
                break;
            
            default:
                break;
        }

    case 5:
        userWatched = user->getWatchedMovies(user->userId);
        recommendedGraph = recommend.getRecommendation(userWatched, moviesList);

        for (TreeNode* treeNode : recommendedGraph){
            recommendedMovies.insert(treeNode);
        }

        cout<<"......Movies Based on your Activity......";
        recommendedMovies.printHeapByPriority();
    
    case 6:
        cout<<"Username: "<<user->username;
        cout<<"ID: "<<user->userId;
        cout<<"\nWatch History\n";
        for (string movieName : user->getWatchedMovies(user->userId)){
            cout<<movieName<<"\n";
        } 

        cout<<"\nReviews\n";
        user->reviewStack.displayReviews(user->userId);

    default:
        break;
    }
}