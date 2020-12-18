#include <iostream>
#include <string>
#include <fstream>
#include "node.hpp"

using namespace std;

// forward declarations
void search_tree(node *tree, string word);
bool process_word_tree(string new_word, node*& tree,node* &prev_word);
void process_next_word_tree(string new_word, node*& head, node* &first_word);
void print_tree(node *tree, node *word);

int main() {
  node* root = nullptr; // start with an empty tree
  string fileName;

  int wordcount = 0; 
  int distinct_word_count = 0; 
  ifstream readInFile;
  readInFile.exceptions(std::iostream::failbit);

  do {
    cout << "Please enter the name of the book file:" << endl;
    cin >> fileName;

    try {
      readInFile.open(fileName);
    }
    catch(...){
      cout <<"An error occurred attempting to open the file \"" << fileName << "\"." << endl;
    }
  } while (!readInFile.is_open());


  //reads a file in word by word, 
  node *previous_word = nullptr;
  node *list_start = nullptr;
  while (readInFile.eof() == false){ 
    string t_word;
    readInFile >> t_word; 
    if (previous_word != nullptr){
      //cout << *previous_word << "  ";
      list_start = previous_word->next_word_root;
      process_next_word_tree(t_word, previous_word->next_word_root, previous_word);
    }
    if (cin.fail() == false) {
			wordcount++;
      if (process_word_tree(t_word, root, previous_word)) { //puts word in binary tree if distinct, add to word counter if not
      	distinct_word_count++;
        
      }
     
    }
  }

	cout << "The file \"" << fileName << "\" contains " << wordcount << " words of which " << distinct_word_count << " are distinct." << endl;
	

  while (cin.eof() == false){ //^D not pressed
    string t_word;
    cout << "Please enter the word you wish to check:" << endl;
    cin >> t_word;
  
   
    if (!cin.eof())
    search_tree(root, t_word);  
    
  }
  cout << "Goodbye" << endl;
  return 0; 
}

// returns true if the word is new, false otherwise
bool process_word_tree(string new_word, node*& tree,  node* &prev_word) {
	bool response;
  // make the bianery tree
	if (tree == nullptr) {
		tree = new node();
    tree->assign(new_word);
    prev_word = tree;
		response = true; // it is a new word
	} else {
		if (new_word == *tree) {
			tree->count++;
      prev_word = tree;
			response = false; // it is not a new word
		} else {
			if (new_word < *tree) {
				response = process_word_tree(new_word, tree->before, prev_word);
			} else {
				response = process_word_tree(new_word, tree->after, prev_word);
			}
		}
	}
  
	return response;
}


// prints the word and its counter to the console
void search_tree(node *tree, string word) {
  if (tree != nullptr) {
    if (*tree == word) {
      string countOutput;
      if (tree->linked_list_size == 0){
        cout << "Word pairs starting with \"" << *tree << "\" were not found." <<endl; 
      }
      if (tree->linked_list_size == 1){
        cout << "Word pairs starting with \"" << *tree << "\" were found once." <<endl; 
      }
      if (tree->linked_list_size == 2){
        cout << "Word pairs starting with \"" << *tree << "\" were found twice." <<endl; 
      }
      if (tree->linked_list_size > 2){
        cout << "Word pairs starting with \"" << *tree << "\" were found " << tree->linked_list_size << " times." <<endl; 
      }
      //cout words in the binary tree from left to right where the root is tree->next_word_root
      print_tree(tree->next_word_root, tree);
      
    }
    if (*tree > word){
      search_tree(tree->before, word );
    }
    if (*tree < word){
      search_tree(tree->after, word );
    }
  } 
  if (tree == nullptr)  cout << "The word \"" << word <<"\" was not found." << endl;

  
}



// returns true if the word is new, false otherwise
void process_next_word_tree(string new_word, node*& tree,  node* &first_word) {
	//bool response;
  // make the bianery tree
	if (tree == nullptr) {
		tree = new node();
    tree->assign(new_word);
    first_word->linked_list_size ++;
    
    
		
	} else {
		if (new_word == *tree) {
			tree->count++;
      first_word->linked_list_size ++;
      
			
		} else {
			if (new_word < *tree) {
				process_next_word_tree(new_word, tree->before, first_word);
			} else {
				process_next_word_tree(new_word, tree->after, first_word);
			}
		}
	}
  
	
}

void print_tree(node *tree, node *word) {
  if (tree != nullptr) {
    print_tree(tree->before, word);
    if (tree->count == 1){
      cout << "\"" << *word << " " << *tree <<"\" was found once."  << endl;
    }
    if (tree->count == 2){
      cout << "\"" << *word << " " << *tree <<"\" was found twice." << endl;
    }
    if (tree->count > 2){
      cout << "\"" << *word << " " << *tree <<"\" was found " << tree->count << " times." << endl;
    }
    print_tree(tree->after, word);
  }
}
