/**
 * MinHeap Implementation in C++
 * 
 * A complete binary heap data structure that maintains the min-heap property:
 * - Parent node is always smaller than its children
 * - Implemented using a dynamic array (vector)
 * - Supports insertion, deletion, and peek operations
 * 
 * Author: [Akila Maksud]
 * Date: [09.09.2025]
 */

#include<iostream>
#include<climits>
#include<sstream>
#include<vector>
using namespace std;

class MinHeap{
    private:
        vector<int> heap;        // Dynamic array to store heap elements
        int heapSize;            // Maximum capacity of the heap
        int realSize = 0;        // Current number of elements in the heap
    
    public:
        /**
         * Constructor: Initialize MinHeap with given capacity
         * @param capacity: Maximum number of elements the heap can hold
         */
        MinHeap(int capacity) : heapSize(capacity) {
            heap.resize(heapSize + 1);  // +1 because index 0 is unused (1-based indexing)
            heap[0] = 0;                // Dummy value at index 0
        }
        
        /**
         * Add an element to the heap
         * Maintains min-heap property by bubbling up the new element
         * @param element: Integer value to be added to the heap
         */
        void add(int element) {
            realSize++;
            
            // Check if heap is full
            if (realSize > heapSize) {
                cout << "Added too many Elements!" << endl;
                realSize--;
                return;
            }
            
            // Insert new element at the end
            heap[realSize] = element;
            
            // Bubble up: Compare with parent and swap if necessary
            int index = realSize;
            int parent = realSize / 2;
            
            while (index > 1 && heap[index] < heap[parent]) {
                swap(heap[index], heap[parent]);
                index = parent;
                parent = index / 2;
            }
        }
        
        /**
         * Peek at the minimum element (root) without removing it
         * @return: The minimum element in the heap, or INT_MAX if empty
         */
        int peek() const {
            if (realSize < 1) {
                cout << "Don't have any element" << endl;
                return INT_MAX;
            }
            return heap[1];  // Root element is at index 1
        }
        
        /**
         * Remove and return the minimum element from the heap
         * Maintains min-heap property by bubbling down the replacement element
         * @return: The minimum element that was removed, or INT_MAX if empty
         */
        int pop() {
            if (realSize < 1) {
                cout << "Don't have any element" << endl;
                return INT_MAX;
            }
            
            int removeElement = heap[1];    // Store the minimum element to return
            heap[1] = heap[realSize];       // Replace root with last element
            realSize--;
            
            // Bubble down: Restore heap property from root
            int index = 1;
            while (index <= realSize / 2) {  // While current node has at least one child
                int left = index * 2;        // Left child index
                int right = left + 1;        // Right child index
                
                // If only left child exists
                if (right > realSize) {
                    if (heap[index] > heap[left]) {
                        swap(heap[index], heap[left]);
                        index = left;
                    } else {
                        break;  // Heap property satisfied
                    }
                } 
                // If both children exist
                else {
                    if (heap[index] > heap[left] || heap[index] > heap[right]) {
                        // Swap with the smaller child
                        if (heap[left] < heap[right]) {
                            swap(heap[index], heap[left]);
                            index = left;
                        } else {
                            swap(heap[index], heap[right]);
                            index = right;
                        }
                    } else {
                        break;  // Heap property satisfied
                    }
                }
            }
            return removeElement;
        }
        
        /**
         * Get the current number of elements in the heap
         * @return: Number of elements currently stored in the heap
         */
        int size() const {
            return realSize;
        }
        
        /**
         * Convert heap to string representation for display
         * @return: String representation of heap elements in array format
         */
        string toString() const {
            if (realSize == 0) {
                return "No element!";
            }
            
            ostringstream oss;
            oss << '[';
            for (int i = 1; i <= realSize; ++i) {
                oss << heap[i];
                if (i < realSize) {
                    oss << ',';
                }
            }
            oss << ']';
            return oss.str();
        }
};

/**
 * Main function: Demonstrates MinHeap usage with various operations
 */
int main() {
    // Create a MinHeap with capacity of 10 elements
    MinHeap minHeap(10);
    
    // Add elements to the heap
    minHeap.add(1);
    minHeap.add(4);
    minHeap.add(3);
    minHeap.add(6);
    minHeap.add(7);
    
    // Display current heap state
    cout << "Heap after adding elements: " << minHeap.toString() << endl;
    
    // Peek at minimum element
    cout << "Minimum element (peek): " << minHeap.peek() << endl;
    
    // Remove minimum element
    minHeap.pop();
    cout << "Heap after popping minimum: " << minHeap.toString() << endl;
    
    // Add another element
    minHeap.add(1);
    cout << "Heap after adding 1: " << minHeap.toString() << endl;
    
    return 0;

}
