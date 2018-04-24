#include "includes/FileHandler.hpp"
#include <iostream>

void FileHandler::setMap() {
  char c;
  while(file.get(c)) {
    this->map[c]++;
  }
}

unsigned int FileHandler::getFreq(char character) {
  return this->map[character]; 
}
