#include <iostream>
#include "includes/FileHandler.hpp"
#include "includes/HuffmanTree.hpp"
int main() {
  FileHandler f("/home/kartha/Projects/HuffmanZip/data/sample.txt");
  f.setMap();
  HuffmanTree *hf = new HuffmanTree(f);
  hf->printC();
  hf->writetoFile();
}
