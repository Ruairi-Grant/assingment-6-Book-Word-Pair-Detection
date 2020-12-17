#include <iostream>
#include <string>
#include <fstream>
#include "node.hpp"

using namespace std;

// forward declarations
void search_tree(node *tree, string word);
bool process_word(string new_word, node*& tree);

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
  while (readInFile.eof() == false){ 
    string t_word;
    readInFile >> t_word; 
    if (cin.fail() == false) {
			wordcount++;
      if (process_word(t_word, root)) { //puts word in binary tree if distinct, add to word counter if not
      	distinct_word_count++;
      }
    }
  }

	cout << "The file \"" << fileName << "\" contains " << wordcount << " words of which " << distinct_word_count << " are distinct." << endl;
	

  while (cin.eof() == false){ //^D not pressed
    string t_word;
    cout << "Please enter the word you wish to check:" << endl;
    cin >> t_word;
  
    //********add exeption for the case of the word not being in the file
    if (!cin.eof())
    search_tree(root, t_word);  
    
  }
  cout << "Goodbye" << endl;
  return 0; 
}

// returns true if the word is new, false otherwise
bool process_word(string new_word, node*& tree) {
	bool response;
	if (tree == nullptr) {
		tree = new node();
    tree->assign(new_word);
		response = true; // it is a new word
    // add instance of that word to end of linked list of the previous word unless perv word is a nullptr
	} else {
		if (new_word == *tree) {
			tree->count++;
			response = false; // it is not a new word
      //find the instance of that word in the linked list, then incerment its counter by one.
		} else {
			if (new_word < *tree) {
				response = process_word(new_word, tree->before);
			} else {
				response = process_word(new_word, tree->after);
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
      if (tree->count > 2) {
      cout << "The word \"" << *tree <<"\" was found " << tree->count << " times." << endl;}
      else if (tree->count == 2) {
         cout << "The word \"" << *tree <<"\" was found twice." << endl;
      }
      else if (tree->count == 1)  {
        cout << "The word \"" << *tree <<"\" was found once." << endl;
        }
      
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