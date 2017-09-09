#include "includes/FileHandler.hpp"
#include <iostream>

void FileHandler::setMap() {
  char c;
  while(this->file>>c) {
    this->map[c]++;
  }
}

unsigned int FileHandler::getFreq(char character) {
  return this->map[character]; 
}
