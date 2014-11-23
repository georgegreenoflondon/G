//
//  LexicalAnalyser.h
//  GInterpreter
//
//  Created by George Green on 23/11/2014.
//  Copyright (c) 2014 George Green. All rights reserved.
//

#include <stdio.h>
#include <fstream>
#include "Scope.h"

#ifndef GInterpreter_LexicalAnalyser_h
#define GInterpreter_LexicalAnalyser_h

class LexicalAnalyser {
    
    /*
     * Constructor
     */
public:
    LexicalAnalyser(std::string filepath);
    
    /*
     * Methods
     */
public:
    // Read a single character from the code source
    bool readNext(char &result);
    // Read a chunk from the code source until the specified character is found
    bool readUntil(char end, std::string &result);
    // Read a chunk from the code source until whitespace is found
    bool readWord(std::string &word);
    // Looks for a " and then reads until the matching "
    bool readString(std::string &string);
    // Looks for an opening { and then reads until the matching }
    bool readScope(std::string &scope);
    // Reads any numerical characters
    bool readInt(int &result);
    // Reads any alpha characters that can be used in an identifier upto the next whitespace
    bool readIdentifier(std::string &identifier);
    // Looks for the next non-whitespace character and checks if it is the supplied symbol.
    bool readSymbol(char symbol);
    // Move the position pointer back
    bool back(int count);
    
    /*
     * Data members
     */
public:
    std::string m_filepath;
    std::string m_code;
    unsigned int m_position;
    unsigned int m_length;
    Scope *m_scope;
    
};


#endif
