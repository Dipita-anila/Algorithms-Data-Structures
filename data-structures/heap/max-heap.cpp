/**
 * MaxHeap Implementation in C++
 * 
 * A complete binary heap data structure that maintains the max-heap property:
 * - Parent node is always greater than its children
 * - Root contains the maximum element
 * - Implemented using a dynamic array (vector) with 1-based indexing
 * - Supports insertion, deletion, and peek operations in O(log n) time
 * 
 * Time Complexities:
 * - Insert: O(log n)
 * - Delete (pop): O(log n)
 * - Peek: O(1)
 * - Build heap: O(n)
 * 
 * Space Complexity: O(n)
 * 
 * Author: [Akila Maksud]
 * Date: [09.09.25]
 */

#include<iostream>
#include<climits>
#include<sstream>
#include<vector>
using namespace std;

class MaxHeap {
    private:
        vector<int> heap;        // Dynamic array to store heap elements
        int heapSize;            // Maximum capacity of the heap
        int realSize = 0;        // Current number of elements in the heap
    
    public:
        /**
         * Constructor: Initialize MaxHeap with given capacity
         * Uses 1-based indexing for easier parent-child calculations
         * Parent of node i: i/2
         * Left child of node i: 2*i
         * Right child of node i: 2*i + 1
         * 
         * @param capacity: Maximum number of elements the heap can hold
         */
        MaxHeap(int capacity) : heapSize(capacity) {
            heap.resize(heapSize + 1);  // +1 because index 0 is unused
            heap[0] = 0;                // Dummy value at index 0
        }
        
        /**
         * Insert an element into the heap
         * Step 1: Add element at the end (maintain complete binary tree)
         * Step 2: Bubble up to maintain max-heap property
         * 
         * @param element: Integer value to be added to the heap
         */
        void add(int element) {
            realSize++;
            
            // Check if heap exceeds capacity
            if (realSize > heapSize) {
                cout << "Added too many Elements!" << endl;
                realSize--;  // Revert the increment
                return;
            }
            
            // Step 1: Insert new element at the next available position
            heap[realSize] = element;
            
            // Step 2: Bubble up (heapify up) to maintain max-heap property
            int index = realSize;           // Start from the newly inserted element
            int parent = realSize / 2;      // Parent index
            
            // Continue until we reach root or heap property is satisfied
            while (index > 1 && heap[index] > heap[parent]) {
                swap(heap[index], heap[parent]);  // Swap with parent
                index = parent;                   // Move up to parent position
                parent = index / 2;               // Update parent index
            }
        }
        
        /**
         * Peek at the maximum element (root) without removing it
         * The root of a max-heap always contains the maximum element
         * 
         * @return: The maximum element in the heap, or INT_MAX if empty
         */
        int peek() const {
            if (realSize < 1) {
                cout << "Don't have any element" << endl;
                return INT_MAX;  // Return sentinel value for empty heap
            }
            return heap[1];  // Root element is always at index 1
        }
        
        /**
         * Remove and return the maximum element from the heap
         * Step 1: Store the root (maximum element)
         * Step 2: Replace root with last element
         * Step 3: Bubble down to restore heap property
         * 
         * @return: The maximum element that was removed, or INT_MIN if empty
         */
        int pop() {
            if (realSize < 1) {
                cout << "Don't have any element" << endl;
                return INT_MIN;  // Return sentinel value for empty heap
            }
            
            // Step 1: Store the maximum element to return later
            int removeElement = heap[1];
            
            // Step 2: Replace root with the last element
            heap[1] = heap[realSize];
            realSize--;  // Reduce heap size
            
            // Step 3: Bubble down (heapify down) to restore max-heap property
            int index = 1;  // Start from root
            
            // Continue until we reach a leaf node or heap property is satisfied
            while (index <= realSize / 2) {  // While current node has at least one child
                int left = index * 2;        // Left child index
                int right = left + 1;        // Right child index
                
                // Case 1: Only left child exists (right child is out of bounds)
                if (right > realSize) {
                    if (heap[index] < heap[left]) {
                        swap(heap[index], heap[left]);
                        index = left;  // Move down to left child
                    } else {
                        break;  // Heap property satisfied
                    }
                } 
                // Case 2: Both children exist
                else {
                    // Check if current node violates heap property with either child
                    if (heap[index] < heap[left] || heap[index] < heap[right]) {
                        // Swap with the larger child to maintain max-heap property
                        if (heap[left] > heap[right]) {
                            swap(heap[index], heap[left]);
                            index = left;   // Move down to left child
                        } else {
                            swap(heap[index], heap[right]);
                            index = right;  // Move down to right child
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
         * Convert heap to string representation for visualization
         * Shows elements in level-order (array representation)
         * Note: This is NOT sorted order - it's the internal heap structure
         * 
         * @return: String representation of heap elements in array format
         */
        string toString() const {
            if (realSize == 0) {
                return "No element!";
            }
            
            ostringstream oss;
            oss << '[';
            
            // Print elements from index 1 to realSize (1-based indexing)
            for (int i = 1; i <= realSize; ++i) {
                oss << heap[i];
                if (i < realSize) {
                    oss << ',';  // Add comma separator except for last element
                }
            }
            oss << ']';
            return oss.str();
        }
};

/**
 * Main function: Demonstrates MaxHeap usage and operations
 * Shows how elements are organized in heap structure (not sorted order)
 */
int main() {
    // Create a MaxHeap with capacity of 10 elements
    MaxHeap maxHeap(10);
    
    cout << "=== MaxHeap Demonstration ===" << endl;
    
    // Step 1: Add elements to the heap
    cout << "\n1. Adding elements: 1, 4, 3, 6, 7" << endl;
    maxHeap.add(1);
    maxHeap.add(4);
    maxHeap.add(3);
    maxHeap.add(6);
    maxHeap.add(7);
    

    // Display current heap state (level-ord
