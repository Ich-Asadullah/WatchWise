# WatchWise
"Watch Wise" revolutionizes your movie-watching experience by seamlessly integrating user authentication, watch history tracking, movie recommendations, and user reviews into one cohesive system.
Watch Wise Movie System
Introduction
Watch Wise Movie System is a console-based application that simulates a movie streaming platform. It provides users with functionalities to watch movies, view trending and top-rated movies, filter movies based on genre or production, get movie recommendations based on their watch history, and manage their profile.

Features
User Authentication: Allows users to login or signup.
Watch a Movie: Users can search for movies by ID or title, watch them, add reviews, or report movies.
Trending Movies: Displays the top 10 trending movies.
Top Rated Movies: Displays the top-rated movies.
Filter Movies: Filters movies based on genre or production company.
Recommended Movies: Recommends movies based on the user's watch history.
User Profile: Displays the user's profile, watch history, and reviews.
Code Overview
Main Components
MovieSystem Class: Handles user authentication and loading movie data.
User Class: Manages user information, watch history, and reviews.
LinkedList Class: Stores and manages the list of movies.
RecommendationGraph Class: Generates movie recommendations.
RecommendationHeap Class: Prioritizes and stores recommended movies.
Main Program Flow
User Authentication: The user is prompted to login or signup.
Load Movie Data: The system loads movie data into a linked list.
Main Menu: Presents options to the user for different actions:
Watch a Movie
View Trending Movies
View Top Rated Movies
Filter Movies
View Recommended Movies
View User Profile
Detailed Functionality
Watch a Movie:

Search by Movie ID or Title.
If the movie is found, the user can watch it, add a review, or report the movie.
Trending Movies:

Displays the top 10 trending movies sorted by rating.
Top Rated Movies:

Displays the top-rated movies sorted by votes.
Filter Movies:

Filter movies by genre or production company.
Recommended Movies:

Generates recommendations based on the user's watch history and displays them.
User Profile:

Displays the user's username, ID, watch history, and reviews.
How to Run
Compile the Code:
bash
Copy code
g++ -o WatchWise main.cpp MoviesSystem.cpp User.cpp
Run the Program:
./WatchWise
File Structure
main.cpp: Contains the main function and program flow.
MoviesSystem.h/cpp: Contains the MovieSystem class and its methods.
User.h/cpp: Contains the User class and its methods.
LinkedList.h/cpp: Contains the LinkedList class and its methods.
RecommendationGraph.h/cpp: Contains the RecommendationGraph class and its methods.
RecommendationHeap.h/cpp: Contains the RecommendationHeap class and its methods.
Dependencies
Standard C++ libraries.
Custom headers and source files for MovieSystem, User, LinkedList, RecommendationGraph, and RecommendationHeap.
Future Improvements
Implement a database to store user and movie data persistently.
Enhance the recommendation algorithm for better accuracy.
Add a user-friendly graphical interface.
Implement error handling and input validation for robustness.
Conclusion
Watch Wise Movie System is a basic yet functional movie streaming platform that demonstrates various features such as user authentication, movie search, reviews, filtering, and recommendations. It serves as a foundation for building more complex and user-friendly applications in the future.
