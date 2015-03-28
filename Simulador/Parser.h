/* 
 * File:   Parser.h
 * Author: knoppix
 *
 * Created on March 28, 2015, 1:39 PM
 */

#ifndef PARSER_H
#define	PARSER_H

#include <string>

#define FILE_NOT_FOUND -1
#define PARAM_NOT_FOUND -2

#define BOOL_TRUE 1
#define BOOL_FALSE 0

class Parser {
public:
    Parser(const char* path);
    int getBoolParam(std::string path);
    int getIntParam(std::string path);
    virtual ~Parser();
    
private:
    std::string path;
};

#endif	/* PARSER_H */

