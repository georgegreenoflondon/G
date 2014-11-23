//
//  LexicalAnalyser.cpp
//  GInterpreter
//
//  Created by George Green on 23/11/2014.
//  Copyright (c) 2014 George Green. All rights reserved.
//

#include "LexicalAnalyser.h"

LexicalAnalyser::LexicalAnalyser(std::string filepath)
:m_filepath(filepath) {
    // Read the file
    std::ifstream file(m_filepath);
    std::string str;
    while (std::getline(file, str)) {
        m_code.append(str);
        m_code.append("\n");
    }
    printf("Read code: %s", m_code.c_str());
}