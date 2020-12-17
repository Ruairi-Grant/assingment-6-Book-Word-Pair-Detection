#pragma once
#include <string>

class node : public std::string {
  public:
  node();
  int count; // number of occurrences
  // "before" points to the subtree of words that come
  // before this word in alphabetical order
  node *before;
  // "after" points to the subtree of words that come
  // after this word in alphabetical order, duh.
  node *after;
};