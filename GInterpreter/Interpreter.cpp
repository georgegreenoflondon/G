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

Interpreter::Interpreter(const char *filepath) {
    // Read in the code
    std::ifstream file(filepath);
    std::string str;
    std::string code;
    while (std::getline(file, str)) {
        code.append(str);
        code.append("\n");
    }
    // Create the global scope
    m_globalScope = new Scope(code);
    // Setup the functions
    setupFunctions();
    // Start interpreting the global scope
    interpret(m_globalScope);
}

/*
 * Keyword implementations
 */

void g_print(Interpreter *intp, Scope *scope) {
    // Attempt to read a string from the file
    std::string string;
    LexicalAnalyser *lexer = scope->getLexer();
    if (lexer->readString(&string)) {
        std::cout << string;
    } else {
        // Go back one char (the first has already been read) and check for a variable
        if (lexer->back(1)) {
            if (lexer->readWord(&string)) {
                Variable * var = scope->getVariable(string);
                std::cout << string << ": " << var->toString() << '\n';
            }
        }
    }
}

void g_int(Interpreter *intp, Scope *scope) {
    // Get the next word as the variable name
    std::string varName;
    LexicalAnalyser *lexer = scope->getLexer();
    if (lexer->readIdentifier(&varName)) {
        // Look for the = symbol
        if (lexer->readSymbol('=')) {
            int i;
            if (lexer->readInt(&i)) {
                int *value = new int(i);
                scope->addVariable(varName, 0);
                scope->setVariable(varName, value);
            } else throw "Expected int.";
        } else throw "Expected: =.";
    } else throw "Expected indentifier.";
}

void g_string(Interpreter *intp, Scope *scope) {
    // Get the next word as the variable name
    std::string varName;
    LexicalAnalyser *lexer = scope->getLexer();
    if (lexer->readIdentifier(&varName)) {
        // Look for the = symbol
        if (lexer->readSymbol('=')) {
            // Attempt to read a string
            std::string string;
            if (lexer->readString(&string)) {
                std::string *value = new std::string(string);
                scope->addVariable(varName, 1);
                scope->setVariable(varName, value);
            } else throw "Expected string.";
        } else throw "Expected: =.";
    } else throw "Expected indentifier.";
}

void g_func(Interpreter *intp, Scope *scope) {
    // Get the next word as the function name
    std::string funcName;
    LexicalAnalyser *lexer = scope->getLexer();
    if (lexer->readIdentifier(&funcName)) {
        // Look for a scope following the identifier
        std::string scopeCode;
        lexer->readScope(&scopeCode);
        // Create a new lexer for the function
        Scope *newScope = new Scope(scopeCode);
        scope->addChildScope(newScope, funcName);
    } else throw "Expected indentifier.";
}

/*
 * Private methods
 */

void Interpreter::interpret(Scope *scope) {
    // Start parsing
    bool finished = false;
    while (!finished) {
        // Get the first word from the lexer
        std::string word;
        if (scope->getLexer()->readWord(&word)) {
            // Check if the word is a valid function
            if (m_keywords.count(word)) {
                g_function func = m_keywords[word];
                (*func)(this, scope);
            } else {
                // Check if the word is a valid identifier for a subscope within this scope
                Scope *childScope = scope->getChildScope(word);
                if (childScope != nullptr) {
                    interpret(childScope);
                }
            }
        } else {
            finished = true;
        }
    }
}

void Interpreter::setupFunctions() {
    m_keywords["print"] = g_print;
    m_keywords["int"] = g_int;
    m_keywords["string"] = g_string;
    m_keywords["func"] = g_func;
}
