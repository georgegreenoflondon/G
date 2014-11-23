//
//  LexicalAnalyser.h
//  GInterpreter
//
//  Created by George Green on 23/11/2014.
//  Copyright (c) 2014 George Green. All rights reserved.
//

#include <stdio.h>
#include <fstream>

#ifndef GInterpreter_LexicalAnalyser_h
#define GInterpreter_LexicalAnalyser_h

class LexicalAnalyser {
    
    /*
     * Constructor
     */
public:
    LexicalAnalyser(std::string filepath);
    
    /*
     * Data members
     */
private:
    std::string m_filepath;
    std::string m_code;
    
};


#endif
