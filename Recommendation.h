#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class RecommendationGraph {
public:
    double checkGenre(MovieNode* m1, MovieNode* m2) {
        double res = 0;
        for (const string& i : m1->genres) {
            for (const string& j : m2->genres) {
                if (i == j) {
                    res+=1;
                }
            }
        }
        return res;
    }

    double checkProduction(MovieNode* m1, MovieNode* m2) {
        double res = 0;
        for (const string& i : m1->production) {
            for (const string& j : m2->production) {
                if (i == j) {
                    res += 1;
                }
            }
        }
        return res;
    }

    vector<TreeNode*> getRecommendation(const vector<string>& movies, LinkedList* listt) {
        unordered_set<TreeNode*> recommendations;
        if (movies.empty()) {
            return vector<TreeNode*>(recommendations.begin(), recommendations.end());
        }

        for (string name : movies) {
            MovieNode* movie = listt->search_by_name(name);
            if (movie == nullptr) continue;

            MovieNode* curr = listt->head;
            while (curr != nullptr) {
                if (curr->movieId != movie->movieId){
                    double weight = 0;
                    weight += checkGenre(movie, curr);
                    weight += checkProduction(movie, curr);

                    if (weight > 1 && curr->rating > 5) {
                        if (movie->language == curr->language) {
                            weight++;
                        }
                        weight += (curr->rating - 5);
                    }

                    if (weight > 6.5){
                        TreeNode* newTree = new TreeNode(curr, weight);
                        recommendations.insert(newTree);
                    }
                }
                
                curr = curr->next;
            }
        }
        return vector<TreeNode*>(recommendations.begin(), recommendations.end());
    }
};

#endif // RECOMMENDATION_H
