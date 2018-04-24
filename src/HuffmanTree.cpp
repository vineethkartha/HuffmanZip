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
    //std::cout<<code.first<<":"<<code.second<<"\n";
  }
  //boost::archive::text_oarchive oa{std::cout};
  //oa << this->lookUpTable;
}

void HuffmanTree::writetoFile() {
  std::ofstream fil;
  std::ifstream inFile;
  inFile.open("/home/kartha/Projects/HuffmanZip/data/sample.txt");
  fil.open("encrypt.txt");
  char c;
  std::string str="";
  fil<<sorted.size()<<"\n";
  for(auto &code :this->sorted) {
    fil<<code.first<<":"<<(int)code.second<<"\n";
  }

  while(inFile.get(c)) {
    // xxx NEED TO REDO
    std::string code;
    boost::to_string(this->lookUpTable[c],code);
    str = str + code;
  }
  fil<<str.length()<<"\n";
  auto len = str.length();
  len = len/8 +1;
  char bitstream[len]={0};
  int i=0;
  for(char &ch :str) {
    bitstream[i/8] = bitstream[i/8] << 1;
    if(ch == '1'){
      bitstream[i/8] = bitstream[i/8] | 1;
    }
    ++i;
  }
  bitstream[i/8] = bitstream[i/8]<<((len*8)-str.length() -1);
  std::cout<<"The code is\n"<<str<<"\n";
  //std::cout<<"The bitstream is\n"<<bitstream<<"\n";
  fil<<bitstream;
  fil.close();
  decode(str);
}
void HuffmanTree::codeRetreiver(HuffmanTreeNode *node,std::string str) {
  if(node == nullptr)
    return;
  if(node->getData() !='=') {
    boost::dynamic_bitset<> b3(str);
    this->lookUpTable[node->getData()] = b3;
    //std::cout<<node->getData()<<":"<<str<<"\n";
  }
  codeRetreiver(node->getLeftNode(),str+"0");
  codeRetreiver(node->getRightNode(),str+"1");
}

void HuffmanTree::canonHuffman() {
  for (auto iterator = lookUpTable.begin(); iterator != lookUpTable.end(); ++iterator) {
    char c = (*iterator).first;
    sorted.push_back(std::make_pair<int,char&>(static_cast<int>((iterator->second).size()),c));
  }
  std::sort(sorted.begin(),sorted.end());
  for(auto &code :this->sorted) {
    //std::cout<<code.first<<":"<<code.second<<"\n";
  }
  // recreate the lookUpTable
  (this->lookUpTable).clear();
  std::pair<int,char> temp(sorted[0]);
  std::string code;
  for(int i = 0 ;i < temp.first;++i)
    code += "0";
  boost::dynamic_bitset<> b3(code);
  this->lookUpTable[temp.second] = b3;
  for(auto it = sorted.begin() + 1 ; it!= sorted.end(); ++it) {
    boost::dynamic_bitset<> bTemp(code);
    auto t = bTemp.to_ulong();
    t+=1;
    t = t<<(it->first- (it-1)->first);
    boost::dynamic_bitset<> bTemp1{it->first,t};
    boost::to_string(bTemp1,code);
    this->lookUpTable[it->second] = bTemp1;
  }

   for(auto &code :this->lookUpTable) {
     // std::cout<<code.first<<":"<<code.second<<"\n";
  }
}

void HuffmanTree::decode(std::string str) {
  // create a decode table with code as the key and symbol as value
  std::map<std::string,char> decodeTable;
  for(auto &code :this->lookUpTable) {
    std::string tempC;
    boost::to_string(code.second,tempC);
    decodeTable[tempC] = code.first;
  }
  std::string outStr="";
  std::string bits="";
  for(int i = 0; i< str.length() ;++i) {
    bits+=str[i];
    if(decodeTable.find(bits) != decodeTable.end()) {
      outStr += decodeTable[bits];
      bits ="";
    }
  }
  std::cout<<"\nDecoded text is\n"<<outStr;
}
