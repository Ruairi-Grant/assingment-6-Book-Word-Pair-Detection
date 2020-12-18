#pragma once
#include <string>

class node : public std::string {
  public:
  node();
  int count; // number of occurrences
  int linked_list_size;
  // "before" points to the subtree of words that come
  // before this word in alphabetical order
  node *before;
  // "after" points to the subtree of words that come
  // after this word in alphabetical order, duh.
  node *after;
  //"next_word" points to the list of words that come imidiatly after each occurace of the word
  node *next_word_root;
};
