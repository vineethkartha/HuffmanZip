#include <iostream>
#include "includes/FileHandler.hpp"
#include "includes/HuffmanTree.hpp"
int main() {
  //FileHandler f("/home/kartha/Projects/HuffmanZip/data/sample.txt");
  //f.setMap();
  std::string inFileName = "/home/kartha/Projects/HuffmanZip/data/sample.txt";
  HuffmanTree *hf = new HuffmanTree(inFileName, "sampleCompressed.txt");
  hf->printC();
  hf->writetoFile();
}
