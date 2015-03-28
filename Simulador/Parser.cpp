/* 
 * File:   Parser.cpp
 * Author: knoppix
 * 
 * Created on March 28, 2015, 1:39 PM
 */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <errno.h>


#include "Parser.h"

std::string getLine(std::string path, std::string keyword, int* result){
    std::string line;
    std::ifstream in(path.c_str());
    if(in.is_open()){
          while( getline(in,line)){
              if (line.find(keyword+":") == 0 ) {
                  *result=0;
                  return line;
              } 
          }
          errno=EINVAL;
          *result=PARAM_NOT_FOUND;
          return "";
    }
    errno=ENOENT;
    *result=FILE_NOT_FOUND;
    return "";
}

Parser::Parser(const char* path){
    this->path = path;
}

int Parser::getBoolParam(std::string keyword){
    int result=0;
    std::string line = getLine(this->path,keyword,&result);
    if(result<0) return result;
    if(line.find("true")!=std::string::npos) { return BOOL_TRUE;}
    if(line.find("false")!=std::string::npos) { return BOOL_FALSE;}
    errno=EINVAL;
    return PARAM_NOT_FOUND;
}

int Parser::getIntParam(std::string keyword){
    int result=0;
    std::string line = getLine(this->path,keyword,&result);
    if(result < 0) return result;
    return atoi(line.substr(line.find(":")+1).c_str());
}

Parser::~Parser() {
}

