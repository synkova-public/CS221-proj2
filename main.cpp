#include <iostream>

#include "string_bst.hpp"
#include "max_heap.hpp"
#include "text_item.hpp"
#include "util.hpp"

using namespace std;

//--- PART 1A: Implementation and testing of heap insert
void heap_insert_tests(max_heap &hp) {
	text_item temp;
	std::string word = "item";
	int random_num;
	long int seed = long(time(0));    // seed for random number generator
	srand(seed);
	
	//--- Testing insert functionality
	std::cout << "*** TESTING INSERT ***" << std::endl;
	//--- This adds 5 items to the heap with random numbers
	//    and prints out the top, but it does not fully 
	//    test the correctness of the insert function.
	for (int i = 0 ; i < 5; i++) {
		random_num = rand() % 100;
		string text = word;
		text += std::to_string(i+1);
		std::cout << "adding " << text << ",  with number " << random_num << " to heap" << std::endl;
		hp.insert(text_item{text, random_num});	
		temp = hp.top();
		std::cout << "Top of heap is: " << temp << std::endl;		
	}
	
	//--- Specific insert functionality that should be tested:
	
    max_heap testHeap(10);
    
	// insert without any swap_ups needed
    testHeap.insert(text_item{word, 100});
    std::cout << "Top of the heap is: " << testHeap.top() << std::endl;
    
    testHeap.delete_max();
    
    
	// insert with a swap_up / multiple swap_ups
    testHeap.insert(text_item{word, 10});
    testHeap.insert(text_item{word, 5});
    testHeap.insert(text_item{word, 25});
    std::cout << "Top of the heap is: " << testHeap.top() << std::endl;
    
    testHeap.insert(text_item{word, 7});
    testHeap.insert(text_item{word, 30});
    testHeap.insert(text_item{word, 21});
    std::cout << "Top of the heap is: " << testHeap.top() << std::endl;
    
}

//--- PART 1B: Implementation and testing of heap delete
void heap_delete_tests(max_heap &hp) {
	text_item temp;
	
	//--- Testing deleteMax functionality
	std::cout << "*** TESTING DELETEMAX ***" << std::endl;
	//--- This does not fully test delete_max functionality.
	if (hp.size() > 1) {
		temp = hp.delete_max();
		std::cout << "Item returned from heap delete: "<< temp << std::endl;
		temp = hp.top();
		std::cout << "Top of heap is now: " << temp << std::endl;	
	}
	
	//--- Specific insert functionality that should be tested:
	
    max_heap testHeap(10);
    std::string word = "item";
	// remove_max works when swap_down with left child
   
    testHeap.insert(text_item{word, 25});
    testHeap.insert(text_item{word, 10});
    testHeap.insert(text_item{word, 5});
    
    testHeap.delete_max();
    std::cout << "Top of the heap now is: " << testHeap.top() << std::endl;
    
    testHeap.delete_max();
    testHeap.delete_max();
    
		
	// remove_max workd when swap_down with right child
    testHeap.insert(text_item{word, 25});
    testHeap.insert(text_item{word, 10});
    testHeap.insert(text_item{word, 15});
    
    testHeap.delete_max();
    std::cout << "Top of the heap now is: " << testHeap.top() << std::endl;
		
	// remove_max on an empty heap (should throw exception similar to top())
    while (!testHeap.empty())
        testHeap.delete_max();
    
    // testHeap.delete_max();  // <--- commented out so the exception is not thrown and other tests can be done
		
}

//--- PART 2: Implementation and testing of BST word_frequency
void tree_tester(string_bst const &tree) {
	std::cout << std::endl << "BEGINNING TESTS FOR PART 2" << std::endl;
	
	//--- Testing word_frequency functionality
	//--- This does not fully test word_frequency functionality.
	if (tree.size() > 1) {
		string to_find = "difficult";
		int num_times = tree.word_frequency(to_find);
		std::cout << "Found: "<< to_find << 
			" in the input file " << num_times 
			<< " time(s)." << std::endl;
	}
	
	//--- Specific word_frequency functionality that should be tested:
	
	// can search through both left and right subtrees if not found at current node
    string_bst testTree;
    testTree.insert("court");
    testTree.insert("fox");
    testTree.insert("andrew");
    testTree.insert("neil");
    testTree.insert("evenfall");
    testTree.insert("court");
    testTree.insert("andrew");
    testTree.insert("court");
    testTree.insert("court");
    
    std::cout << "Expected frequency of 'court': 4" << std::endl;
    std::cout << "Found frequency of 'court': " << testTree.word_frequency("court") << std::endl;
 
		
	// returns 0 if word is not found
    std::cout << "Expected freqiency of 'apple': 0" << std::endl;
    std::cout << "Found frequency of 'apple': " << testTree.word_frequency("apple") << std::endl;
			
}

//--- PART 3: Implementation and testing of word frequency analysis
void overall_most_freq(max_heap hp) {
	std::cout << "*** Top 5 most frequent words: ***" << std::endl;
	
	//--- Add your code to print out the 5 most frequent words below:
    
    // make sure it does not go beyond 5
    int count = 0;
    
    while (hp.size() > 1 && count < 5) {
        text_item cmf = hp.top();  // stores the current most frequent item
		std::cout << "Most frequent text item: " << cmf << std::endl;
        count++;
        
        // allows for the print of all 5 words
        hp.delete_max();
	}

}

void at_least_length(max_heap hp, size_t num_letters) {
	cout << "*** Top 5 most frequent words with at least " 
		<< num_letters << " letters ***" << std::endl;
		
    // make sure it does not go beyond 5
    int count = 0;
    while (hp.size() > 1 && count < 5){
        text_item cmf = hp.top();  // stores the current most frequent item
        
        // Check the length of the word
        if (cmf.word.size() >= num_letters) {
            std::cout << "Most frequent text item with at least " << num_letters << " letters: " << cmf << std::endl;
            count++;
        }
        
        // allows for the print of all 5 words
        hp.delete_max();
    }
}

void starts_with(max_heap hp, char starts_with_letter) {
	cout << "*** Top 5 most frequent words that begin with " 
		<< starts_with_letter << " ***" << std::endl;
		
    // make sure it does not go beyond 5
    int count = 0;
    while (hp.size() > 1 && count < 5){
        text_item cmf = hp.top();  // stores the current most frequent item
        
        // Check the first letter of the word
        if (cmf.word[0] == starts_with_letter) {
            std::cout << "Most frequent text item that starts with "<< starts_with_letter << ": " << cmf << std::endl;
            count++;
        }
        
        // allows for the print of all 5 words
        hp.delete_max();
    }
}

void heap_tester() {
	text_item temp;
	int heap_size = 10; //feel free to create heaps of other sizes when testing
	//cout << "How many items should be added to heap? ";
	//cin >> heap_size;
	max_heap hp(heap_size);
	std::cout << "Created heap of size " << heap_size << std::endl;
		
	//--- Testing heap size and top
	std::cout << "Current number of items in heap is: " << hp.size() << std::endl;
	try {
		temp = hp.top(); //should throw and exception without items in heap
		std::cout << "Top of heap is: " << temp << std::endl;	
	} catch (std::logic_error e) {
		std::cout << e.what() << std::endl;
	}
	// PART 1A:
	std::cout << std::endl << "BEGINNING TESTS FOR PART 1A" << std::endl;
	heap_insert_tests(hp);
	// PART 1B:
	std::cout << std::endl << "BEGINNING TESTS FOR PART 1B" << std::endl;
	heap_delete_tests(hp);
}

void text_analysis_tester(string_bst &tree) {
	std::cout << std::endl << "BEGINNING TESTS FOR PART 3" << std::endl;
	overall_most_freq(copy_to_heap(tree));
	std::cout << std::endl;
	at_least_length(copy_to_heap(tree), 10); // change the 8 to test other string-lengths
	std::cout << std::endl;
	starts_with(copy_to_heap(tree), 'f'); // change the 'c' to test words that starts_with_letter
											// with different characters
}

int main(int argc, char* argv[]) {
	
	//--- Part 1: max_heap implementation
	heap_tester(); 
	
	//--- Part 2: string_bst implementation
	string_bst tree;
	load_bst("sample2.txt", tree); // create a bst from an input file.
	tree_tester(tree);			//sample2.txt contains a much bigger file
	
	//--- Part 3: word frequency analysis of text files
	text_analysis_tester(tree);

}
