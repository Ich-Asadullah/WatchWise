#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "MoviesData.h"

using namespace std;

class RecommendationGraph {
public:

    //Function to check Genre Resemblance
    double checkGenre(MovieNode* m1, MovieNode* m2){
        double res = 0;
        for (string i : m1->genres){
            for (string j : m2->genres){
                if (i==j){
                    res++;
                }
            }
        }
        return res;
    }

    //function to check Production house resemblance
    double checkProduction(MovieNode* m1, MovieNode* m2){
        double res = 0;
        for (string i : m1->production){
            for (string j : m2->production){
                if (i==j){
                    res = res+2;
                }
            }
        }
        return res;
    }

    //Function to get recommendations based on Specific logic
    vector<MovieNode*> getRecommendation(vector<int> movies, LinkedList* listt) {
        unordered_set<MovieNode*> recommendations;
        for (int id : movies)
            {   
                MovieNode* movie = listt->searchMovie(id);
                if (movie == nullptr) continue; // If we cannot find the movie then leave it.
                double weight = 0;
                MovieNode* curr = listt->head;
                while (curr != nullptr){
                    weight += checkGenre(movie, curr);
                    weight += checkProduction(movie, curr);
                    
                    //if Genre or Production matches then we check further
                    if(weight>1 && curr->rating > 5){
                        if(movie->language == curr->language){
                            weight++;
                        }
                        weight += (curr->rating) - 5;
                    }

                    if(weight>4){
                        recommendations.insert(curr);
                    }
            }}
        return vector<MovieNode*>(recommendations.begin(), recommendations.end());
    }

};

#endif