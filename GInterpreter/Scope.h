//
//  Scope.h
//  GInterpreter
//
//  Created by George Green on 23/11/2014.
//  Copyright (c) 2014 George Green. All rights reserved.
//

#ifndef __GInterpreter__Scope__
#define __GInterpreter__Scope__

#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>
#include "LexicalAnalyser.h"
#include "Types.h"

class Variable {
public:
    ~Variable() {
        if (m_value != nullptr) {
            if (m_varType == G_INT_TYPE) { // int
                delete (int *)m_value;
            } else if (m_varType == G_STRING_TYPE) {// string
                delete (std::string *)m_value;
            }
        }
    }
    
    int m_varType;
    void* m_value;
    std::string toString() {
        if (m_varType == G_INT_TYPE) { // int
            int i = *(int *)m_value;
            char result[16] = "xxxxxxxxxxxxxxx";
            snprintf(result, 16, "%d", i);
            return std::string(result);
        } else if (m_varType == G_STRING_TYPE) { // string
            std::string string = *(std::string *)m_value;
            return string;
        }
        return "(NULL)";
    }
};

class Scope {
    
    /*
     * Constructor
     */
public:
    Scope(std::string code);
    
    virtual ~Scope();
    
    /*
     * Methods
     */
public:
    void setParentScope(Scope parentScope);
    void addVariable(std::string identifier, int varType);
    void setVariable(std::string identifier, void* value);
    Variable * getVariable(std::string identifier);
    void addChildScope(Scope *childScope, std::string identifier);
    Scope *getChildScope(std::string identifier);
    
    LexicalAnalyser *getLexer() { return m_lexer; }
    
    /*
     * Data members
     */
public:
    Scope *m_parentScope;
    std::map<std::string, Scope*> m_childScopes;
    std::map<std::string, Variable*> *m_variables;
    LexicalAnalyser *m_lexer;
    
};

#endif /* defined(__GInterpreter__Scope__) */
