/*--- max_heap.cpp -----------------------------------------------
  This file implements hax_heap.hpp member functions.
-------------------------------------------------------------------------*/

#include "max_heap.hpp"
#include <stdexcept>

max_heap::max_heap(int n){
	data = new text_item[n];
	numItems = 0;
	max_capacity = n;
}

max_heap::~max_heap()
{ 
	delete [] data;
}

bool max_heap::empty() const {
	return (numItems == 0);
}
bool max_heap::full() const {
	return (numItems == max_capacity);
}

int max_heap::size() const {
	return numItems;
}	

text_item& max_heap::top() {
	if (empty()) {
		throw std::logic_error("Heap is empty, can't access top!");
	}
	return data[0];
}


//--- You must comple the following functions: 


text_item max_heap::delete_max() {
	if (empty()) {
		throw std::logic_error("Cannot delete, heap is empty!");
	} else {
		// Part 1b
		
        // swap the last and the first items
        text_item returnVal = data[0];
        data[0] = data[numItems - 1];
        numItems--;
        max_heap::swap_down(0);
		
		return returnVal;
	}
}

void max_heap::swap_down(int i) {
	// Part 1b
    
    // Get the right, left, save the index value
    int max = i;
    int left = i * 2 + 1;
    int right = left + 1;
    
    // Check the left child
    if (left < numItems && data[left].freq > data[max].freq)
        max = left;
    // Check the right child
    if (right < numItems && data[right].freq > data[max].freq)
        max = right;
    
    // If max has changed
    if (max != i) {
        text_item temp = data[i];
        data[i] = data[max];
        data[max] = temp;
        max_heap::swap_down(max);
    }
}

void max_heap::insert(const text_item & item) {
	if (full()) {
		throw std::logic_error("Cannot insert, heap array is full!");
	} else {
		// Part 1a
		data[numItems++] = item;         // Adds the item at the end of the array
        max_heap::swap_up(numItems-1);   // Maintains the correct structure of the heap
	}
}

void max_heap::swap_up(int i) {
	// Part 1a
    
    // Check if the node is at the top
    if (i == 0) return;
    
    // Get the parent
    int parent_node = (i - 1) / 2;
    
    // Check if necessary to do the swap
    if (data[i].freq > data[parent_node].freq) {
        text_item temp = data[i];
        data[i] = data[parent_node];
        data[parent_node] = temp;
        
        max_heap::swap_up(parent_node);
    }
}
