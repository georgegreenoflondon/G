//
//  Interpreter.h
//  GInterpreter
//
//  Created by George Green on 23/11/2014.
//  Copyright (c) 2014 George Green. All rights reserved.
//

#include <stdio.h>
#include "Scope.h"
#include <map>

#ifndef GInterpreter_Interpreter_h
#define GInterpreter_Interpreter_h

class FunctionTemplate;

class Interpreter {
    
    typedef void (*g_function)(Interpreter *intp, Scope *scope);
    
    /*
     * Consturctor
     */
public:
    Interpreter(const char *filepath);
    
    /*
     * Private methods
     */
    void interpret(Scope *scope);
    void setupTypes();
    void setupFunctions();
    void g_functionCall(Scope *currentScope, FunctionTemplate const &functionTemplate);
    
private:
    
    
    /*
     * Data members
     */
public:
    Scope *m_globalScope;
    std::map<std::string, g_function> m_keywords;
    
    /*
     * Functions
     */
private:

    
    
};


#endif
