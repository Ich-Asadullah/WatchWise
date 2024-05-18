#ifndef MOVIESTREE_H
#define MOVIESTREE_H

#include <iostream>
#include <vector>

using namespace std;

class TreeNode {
public:
    MovieNode* movie;
    int resemblance;
    TreeNode* left;
    TreeNode* right;

    TreeNode(MovieNode* movie, int resemblance){
        this->movie = movie;
        this->resemblance = resemblance;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class RecommendationHeap {
private:
    vector<TreeNode*> heap;

    void heapifyUp(int index) {
        int parent = (index - 1) / 2;
        while (index > 0 && heap[index]->resemblance > heap[parent]->resemblance) {
            swap(heap[index], heap[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;

        if (leftChild < heap.size() && heap[leftChild]->resemblance > heap[largest]->resemblance) {
            largest = leftChild;
        }
        if (rightChild < heap.size() && heap[rightChild]->resemblance > heap[largest]->resemblance) {
            largest = rightChild;
        }

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    void insert(TreeNode* node) {
        heap.push_back(node); //Adds element at end
        heapifyUp(heap.size() - 1);
    }

    TreeNode* extractMax() {
        if (heap.empty()) {
            return nullptr;
        }

        TreeNode* maxNode = heap[0];
        heap[0] = heap.back(); //replace index 0 with last element
        heap.pop_back(); //removes last item
        heapifyDown(0); //maintains heapify property

        return maxNode;
    }

    void printHeapByPriority() {
        TreeNode* temp = extractMax();
        temp->movie->display();
        insert(temp);
    }
};

#endif