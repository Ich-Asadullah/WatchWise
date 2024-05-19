# WatchWise

"WatchWise" revolutionizes your movie-watching experience by seamlessly integrating user authentication, watch history tracking, movie recommendations, and user reviews into one cohesive system.

## WatchWise Movie System

### Introduction

WatchWise Movie System is a console-based application that simulates a movie streaming platform. It provides users with functionalities to watch movies, view trending and top-rated movies, filter movies based on genre or production, get movie recommendations based on their watch history, and manage their profile.

### Features

1. **User Authentication**: Allows users to login or signup.
2. **Watch a Movie**: Users can search for movies by ID or title, watch them, add reviews, or report movies.
3. **Trending Movies**: Displays the top 10 trending movies.
4. **Top Rated Movies**: Displays the top-rated movies.
5. **Filter Movies**: Filters movies based on genre or production company.
6. **Recommended Movies**: Recommends movies based on the user's watch history.
7. **User Profile**: Displays the user's profile, watch history, and reviews.

### Code Overview

#### Main Components

1. **MovieSystem Class**: Handles user authentication and loading movie data.
2. **User Class**: Manages user information, watch history, and reviews.
3. **LinkedList Class**: Stores and manages the list of movies.
4. **RecommendationGraph Class**: Generates movie recommendations.
5. **RecommendationHeap Class**: Prioritizes and stores recommended movies.

#### Main Program Flow

1. **User Authentication**: The user is prompted to login or signup.
2. **Load Movie Data**: The system loads movie data into a linked list.
3. **Main Menu**: Presents options to the user for different actions:
    - Watch a Movie
    - View Trending Movies
    - View Top Rated Movies
    - Filter Movies
    - View Recommended Movies
    - View User Profile

#### Detailed Functionality

1. **Watch a Movie**:
    - Search by Movie ID or Title.
    - If the movie is found, the user can watch it, add a review, or report the movie.

2. **Trending Movies**:
    - Displays the top 10 trending movies sorted by rating.

3. **Top Rated Movies**:
    - Displays the top-rated movies sorted by votes.

4. **Filter Movies**:
    - Filter movies by genre or production company.

5. **Recommended Movies**:
    - Generates recommendations based on the user's watch history and displays them.

6. **User Profile**:
    - Displays the user's username, ID, watch history, and reviews.

### How to Run

1. **Compile the Code**:
    ```bash
    g++ main.cpp -o WatchWise
    ```
2. **Run the Program**:
    ```bash
    ./WatchWise
    ```

### File Structure

- **main.cpp**: Contains the main function and program flow.
- **MoviesSystem.h/cpp**: Contains the MovieSystem class and its methods.
- **User.h/cpp**: Contains the User class and its methods.
- **LinkedList.h/cpp**: Contains the LinkedList class and its methods.
- **RecommendationGraph.h/cpp**: Contains the RecommendationGraph class and its methods.
- **RecommendationHeap.h/cpp**: Contains the RecommendationHeap class and its methods.

### Dependencies

- Standard C++ libraries.
- Custom headers and source files for MovieSystem, User, LinkedList, RecommendationGraph, and RecommendationHeap.

### Future Improvements

- Implement a database to store user and movie data persistently.
- Enhance the recommendation algorithm for better accuracy.
- Add a user-friendly graphical interface.
- Implement error handling and input validation for robustness.

### Conclusion

WatchWise Movie System is a basic yet functional movie streaming platform that demonstrates various features such as user authentication, movie search, reviews, filtering, and recommendations. It serves as a foundation for building more complex and user-friendly applications in the future.
