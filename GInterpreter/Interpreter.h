//
//  Interpreter.h
//  GInterpreter
//
//  Created by George Green on 23/11/2014.
//  Copyright (c) 2014 George Green. All rights reserved.
//

#include <stdio.h>
#include "LexicalAnalyser.h"
#include "Scope.h"
#include <map>

#ifndef GInterpreter_Interpreter_h
#define GInterpreter_Interpreter_h

class Interpreter {
    
    typedef void (*g_function)(Interpreter intp, LexicalAnalyser lexer);
    
    /*
     * Consturctor
     */
public:
    Interpreter(const char *filepath);
    
    /*
     * Private methods
     */
    void setupFunctions();
    
private:
    
    
    /*
     * Data members
     */
public:
    Scope *m_globalScope;
    LexicalAnalyser m_lexer;
    std::map<std::string, g_function> m_keywords;
    
    /*
     * Functions
     */
private:

    
    
};


#endif
