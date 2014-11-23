//
//  LexicalAnalyser.cpp
//  GInterpreter
//
//  Created by George Green on 23/11/2014.
//  Copyright (c) 2014 George Green. All rights reserved.
//

#include "LexicalAnalyser.h"
#include <vector>
#include <ctype.h>

/*
 * Constants
 */

/*
 * Constructor
 */

LexicalAnalyser::LexicalAnalyser(std::string filepath)
:m_filepath(filepath)
,m_position(0) {
    // Read the file
    std::ifstream file(m_filepath);
    std::string str;
    m_length = 0;
    while (std::getline(file, str)) {
        m_code.append(str);
        m_code.append("\n");
        m_length += str.length() + 1;
    }
}

/*
 * Methods
 */

bool LexicalAnalyser::readNext(char &result) {
    if (m_position < m_length - 1) {
        result = m_code.at(m_position);
        m_position++;
        return true;
    }
    return false;
}

bool LexicalAnalyser::readUntil(char end, std::string &result) {
    std::string returnString;
    char ch;
    while (readNext(ch)) {
        if (ch != end) {
            // Append the characted to the result
            returnString += ch;
        } else {
            // We have found the relevant chunk
            result = returnString;
            return true;
        }
    }
    throw std::runtime_error("Expected: " + std::string(&end));
    return false;
}

bool LexicalAnalyser::readWord(std::string &word) {
    std::string returnWord;
    char ch;
    while (readNext(ch)) {
        if (!isspace(ch)) {
            // Append the character to the result
            returnWord += ch;
        } else {
            if (returnWord.length() != 0) {
                // We have found the relevant chunk
                word = returnWord;
                return true;
            } else {
                return false;
            }
        }
    }
    if (returnWord.length() != 0) {
        word = returnWord;
        return true;
    } else {
        return false;
    }
}

