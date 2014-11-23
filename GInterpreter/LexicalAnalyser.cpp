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
    bool startedWord = false;
    while (readNext(ch)) {
        if (!isspace(ch)) {
            // Append the character
            returnWord += ch;
            startedWord = true;
        } else {
            // If the word has started, return the word, else wait for the word to start
            if (startedWord) {
                word = returnWord;
                return true;
            }
        }
    }
    return false;
}

bool LexicalAnalyser::readString(std::string &string) {
    std::string returnString;
    char ch;
    bool intoString = false;
    while (readNext(ch)) {
        if (!intoString) {
            if (isspace(ch)) continue; // ignore whitespace before the first "
            else if (ch == '"') { // start the string at the first "
                intoString = true;
                continue;
            } else throw "String not found";
        } else {
            if (ch != '\\') { // not an escape character
                if (ch == '"') { // end "
                    string = returnString;
                    return true;
                } else { // just another character to append
                    returnString += ch;
                }
            } else {
                // Read the next character
                if (readNext(ch)) {
                    if (ch == 'n') { // return character
                        returnString += '\n';
                    }
                } else throw "Reached end of file before end of string.";
            }
        }
    }
    throw "Reached end of file before end of string.";
    return false;
}

bool LexicalAnalyser::readScope(std::string &scope) {
    std::string returnString;
    char ch;
    bool startedScope = false;
    int openCount = 0;
    while (readNext(ch)) {
        if (!startedScope) {
            if (isspace(ch)) continue;
            else if (ch == '{') {
                openCount++;
                startedScope = true;
            } else throw "Extected: {";
        } else {
            if (ch == '{') openCount++;
            if (ch == '}') openCount--;
            if (openCount != 0) {
                // Append the character
                returnString += ch;
            } else {
                return true;
            }
        }
    }
    return false;
}

