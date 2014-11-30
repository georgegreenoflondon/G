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
#include "Function.h"

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

void g_baseVar(Interpreter *intp, Scope *scope, int varType) {
    // Read the next word as the var name
    std::string varName;
    LexicalAnalyser *lexer = scope->getLexer();
    if (lexer->readIdentifier(&varName)) {
        // Look for the = symbol
        if (lexer->readSymbol('=')) {
            switch (varType) {
                case G_INT_TYPE: {
                    // Attempt to read an int
                    int i;
                    if (lexer->readInt(&i)) {
                        int *value = new int(i);
                        scope->addVariable(varName, 0);
                        scope->setVariable(varName, value);
                    } else throw "Expected int.";
                } break;
                    
                case G_STRING_TYPE: {
                    // Attempt to read a string
                    std::string string;
                    if (lexer->readString(&string)) {
                        std::string *value = new std::string(string);
                        scope->addVariable(varName, 1);
                        scope->setVariable(varName, value);
                    } else throw "Expected string.";
                } break;
                    
                default:
                    break;
            }
        } else throw "Expected =.";
    } else throw "Expected identifier.";
}

void g_func(Interpreter *intp, Scope *scope) {
    // Get the next word as the function name
    std::string funcName;
    LexicalAnalyser *lexer = scope->getLexer();
    if (lexer->readIdentifier(&funcName)) {
        // Go back 1 as the call to readIdentifier will have read the '('
        lexer->back(1);
        // Look for a parameter list following the identifier
        if (lexer->readSymbol('(')) {
            std::string paramString;
            lexer->readUntil(')', &paramString);
            // Look for a return type
            int returnType = G_VOID_TYPE;
            if (lexer->readSymbol('>')) {
                std::string returnTypeIdentifier;
                if (lexer->readWord(&returnTypeIdentifier)) {
                    if (g_types.count(returnTypeIdentifier)) returnType = g_types[returnTypeIdentifier];
                }
            }
            // Look for a scope following the identifier
            std::string scopeCode;
            lexer->readScope(&scopeCode);
            // Create a new function scope for the function
            Function *newFunc = new Function(paramString, returnType, scopeCode);
            scope->addChildScope(newFunc, funcName);
        } else throw "Expected parameter list.";
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
                // Check if the word is a basic type identifier
                if (g_types.count(word)) {
                    int varType = g_types[word];
                    g_baseVar(this, scope, varType);
                } else {
                    // Check if the word is a valid identifier for a subscope within this scope
                    Scope *childScope = scope->getChildScope(word);
                    if (childScope != nullptr) {
                        interpret(childScope);
                    }
                }
            }
        } else {
            finished = true;
        }
    }
}

void Interpreter::setupFunctions() {
    m_keywords["print"] = g_print;
    m_keywords["func"] = g_func;
}
