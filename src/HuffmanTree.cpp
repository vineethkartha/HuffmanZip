#include "includes/HuffmanTree.hpp"
#include "FileHandler.hpp"
#include <boost/archive/text_oarchive.hpp>
#include <iostream>
#include <fstream>

// Try to refactor this class such that the class takes
// input from an interface class and gives out put to an interface class 

// should this be made explicit ?
// Is this constructor doing too much work ?
HuffmanTree::HuffmanTree(std::string inFileName, std::string compressedFileName) {
  this->inFile = new FileHandler(inFileName);
  this->compressedFile = new FileHandler(compressedFileName);
  
  inFile->setMap();
  for(unsigned char i = 0;i < 127;i++) {
    if(inFile->getFreq(i)) {
      HuffmanTreeNode *node = new HuffmanTreeNode(i, inFile->getFreq(i));
      tree.push(node);
    }
  }
  while(tree.size() != 1) {
    auto left = tree.top();
    tree.pop();
    auto right = tree.top();
    tree.pop();

    HuffmanTreeNode *temp = new HuffmanTreeNode('=', *left + *right);
    temp->addLeftNode(left);
    temp->addRightNode(right);
    tree.push(temp);
  }
}
 

void HuffmanTree::printC() {
  this->codeRetreiver(tree.top(),"");
  for(auto &code :this->lookUpTable) {
    std::cout<<code.first<<":"<<code.second<<"\n";
  }
  //boost::archive::text_oarchive oa{std::cout};
  //oa << this->lookUpTable;
}

void HuffmanTree::writetoFile() {
  std::ofstream fil;
  std::ifstream inFile;
  inFile.open("/home/kartha/Projects/HuffmanZip/data/sample.txt");
  //fil.open("encrypt.txt");
  char c;
  std::string str="";
  while(inFile>>c) {
    std::string code = this->lookUpTable[c];
    str = str + code;
  }
  auto len = str.length();
  len = len/8;
  char bitstream[len]={0};
  int i=0;
  for(char &ch :str) {
    bitstream[i/8] = bitstream[i/8] << 1;
    if(ch == '1'){
      bitstream[i/8] = bitstream[i/8] | 1;
    }
    ++i;
  }
  std::cout<<"The code is\n"<<str<<"\n";
  std::cout<<"The bitstream is\n"<<bitstream<<"\n";

}
void HuffmanTree::codeRetreiver(HuffmanTreeNode *node,std::string str) {
  if(node == nullptr)
    return;
  if(node->getData() !='=') {
    this->lookUpTable[node->getData()] = str;
    //std::cout<<node->getData()<<":"<<str<<"\n";
  }
  codeRetreiver(node->getLeftNode(),str+"0");
  codeRetreiver(node->getRightNode(),str+"1");
}
