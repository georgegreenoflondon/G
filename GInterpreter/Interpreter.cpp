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
    // Create the global scope
    m_globalScope = new Scope();
    m_lexer.m_scope = m_globalScope;
    // Setup the functions
    setupFunctions();
    // Start parsing
    bool finished = false;
    while (!finished) {
        // Get the first word from the lexer
        std::string *word = new std::string();
        if (m_lexer.readWord(word)) {
            // Check if the word is a valid function
            if (m_keywords.count(*word)) {
                g_function func = m_keywords[*word];
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
    // Attempt to read a string from the file
    std::string string;
    if (lexer.readString(&string)) {
        std::cout << string;
    } else {
        // Go back one char (the first has already been read) and check for a variable
        if (lexer.back(1)) {
            if (lexer.readWord(&string)) {
                Variable * var = lexer.m_scope->getVariable(string);
                std::cout << string << ": " << var->toString() << '\n';
            }
        }
    }
}

void g_int(Interpreter intp, LexicalAnalyser lexer) {
    // Get the next word as the variable name
    std::string varName;
    if (lexer.readIdentifier(&varName)) {
        // Look for the = symbol
        if (lexer.readSymbol('=')) {
            int i;
            if (lexer.readInt(&i)) {
                int *value = new int(i);
                lexer.m_scope->addVariable(varName, 0);
                lexer.m_scope->setVariable(varName, value);
            } else throw "Expected int.";
        } else throw "Expected: =.";
    }
}

/*
 * Private methods
 */

void Interpreter::setupFunctions() {
    m_keywords["print"] = g_print;
    m_keywords["int"] = g_int;
}

