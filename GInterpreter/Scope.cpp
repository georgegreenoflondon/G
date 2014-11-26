//
//  Scope.cpp
//  GInterpreter
//
//  Created by George Green on 23/11/2014.
//  Copyright (c) 2014 George Green. All rights reserved.
//

#include "Scope.h"
#include <string>

/*
 * Constructor
 */

Scope::Scope() {
    m_variables = new std::map<std::string, Variable*>();
}

/*
 * Public methods
 */

void Scope::setParentScope(Scope parentScope) {
    m_parentScope = &parentScope;
}

void Scope::addVariable(std::string identifier, int varType) {
    // Check that identifier does not already exist in this scope
    auto it = m_variables->find(identifier);
    if (it == m_variables->end()) { // not found
        Variable *newVar = new Variable();
        newVar->m_varType = varType;
        newVar->m_value = nullptr;
        (*m_variables)[identifier] = newVar;
    } else { // found
        throw "Cannot redefine variable.";
    }
}

void Scope::setVariable(std::string identifier, void *value) {
    // Check if the variable exists in the scope
    auto it = m_variables->find(identifier);
    if (it != m_variables->end()) { // found
        // Set the value
        auto var = it->second;
        if (var->m_value != nullptr) { // delete any existing value
            if (var->m_varType == 0) { // int
                delete (int *)var->m_value;
            }
        }
        var->m_value = value;
    } else { // not found
        throw "Variable does not exist.";
    }
}

Variable * Scope::getVariable(std::string identifier) {
    // Check if the variable exists in scope
    auto it = m_variables->find(identifier);
    if (it != m_variables->end()) { // found
        auto var = it->second;
        return var;
    } else { // not found
        throw "Variable does not exist";
    }
}
