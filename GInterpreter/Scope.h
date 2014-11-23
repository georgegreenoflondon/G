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

class Variable {
public:
    ~Variable() {
        if (m_value != nullptr) {
            if (m_varType == 0) { // int
                delete (int *)m_value;
            }
        }
    }
    
    int m_varType;
    void* m_value;
    const char * toString() {
        if (m_varType == 0) { // int
            int i = *(int *)m_value;
            char * result;
            sprintf(result, "%i", i);
            return result;
        }
        return "(NULL)";
    }
};

class Scope {
    
    /*
     * Constructor
     */
public:
    Scope();
    ~Scope();
    
    /*
     * Methods
     */
public:
    void setParentScope(Scope parentScope);
    void addVariable(std::string identifier, int varType);
    void setVariable(std::string identifier, void* value);
    Variable * getVariable(std::string identifier);
    
    /*
     * Data members
     */
private:
    Scope *m_parentScope;
    std::map<std::string, Scope> m_childScopes;
    std::map<std::string, Variable*> *m_variables;
    
};

#endif /* defined(__GInterpreter__Scope__) */
