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

struct Variable {
    int m_varType;
    void* m_value;
};

class Scope {
    
    /*
     * Constructor
     */
public:
    Scope();
    
    /*
     * Methods
     */
public:
    void setParentScope(Scope parentScope);
    void addVariable(std::string identifier, int varType);
    void setVariable(std::string identifier, void* value);
    void *getVariable(std::string identifier, int &varType);
    
    /*
     * Data members
     */
private:
    Scope *m_parentScope;
    std::map<std::string, Scope> m_childScopes;
    std::map<std::string, Variable> m_variables;
    
};

#endif /* defined(__GInterpreter__Scope__) */
