#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <fstream>

class FileHandler {

public:
  FileHandler () {}  
  FileHandler(FileHandler &f) {
    this->fileName = f.getFileName();
    this->file.open(this->fileName);
    this->setMap();
  }
  
  FileHandler(std::string filename) {
    this->fileName = filename;
    this->file.open(filename);
  }
  
  ~FileHandler() {
    this->file.close();
  }
  
  std::string getFileName() {
    return this->fileName;
  }

  /*std::istream& operator>>(std::istream& lhs, ) {

    }*/
  char getCh() {
    char ch;
    file >>ch;
    return ch;
  }
  
  void setMap();

  unsigned int getFreq(char character);

private:
  std::string fileName;
  std::ifstream file;
  unsigned int map[128]={0};
};

#endif
