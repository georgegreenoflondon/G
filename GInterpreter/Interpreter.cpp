//
//  Interpreter.cpp
//  GInterpreter
//
//  Created by George Green on 23/11/2014.
//  Copyright (c) 2014 George Green. All rights reserved.
//

#include "Interpreter.h"
#include <string>
#include <iostream>

/*
 * Constructor
 */

Interpreter::Interpreter(const char *filepath)
: m_lexer(filepath) {
    // Setup the functions
    setupFunctions();
    // Start parsing
    bool finished = false;
    while (!finished) {
        // Get the first word from the lexer
        std::string word;
        if (m_lexer.readWord(word)) {
            // Check if the word is a valid function
            if (m_keywords.count(word)) {
                g_function func = m_keywords[word];
                (*func)(*this, m_lexer);
            }
        } else {
            finished = true;
        }
    }
    
}

/*
 * Keyword implementations
 */

void g_print(Interpreter intp, LexicalAnalyser lexer) {
    // Check that the next character is a "\""
    char ch;
    if (lexer.readNext(ch)) {
        if (ch == '"') {
            // Read the string to be printed
            std::string str;
            lexer.readUntil('"', str);
            // Print the result string
            std::cout << str << '\n';
        } else throw "Expected: \"";
    }
}

/*
 * Private methods
 */

void Interpreter::setupFunctions() {
    m_keywords["print"] = g_print;
}

