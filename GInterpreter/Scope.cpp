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
    
}

/*
 * Public methods
 */

void Scope::setParentScope(Scope parentScope) {
    m_parentScope = &parentScope;
}

void Scope::addVariable(std::string identifier, int varType) {
    // Check that identifier does not already exist in this scope
    auto it = m_variables.find(identifier);
    if (it == m_variables.end()) { // not found
        Variable newVar;
        newVar.m_varType = varType;
        newVar.m_value = nullptr;
        m_variables[identifier] = newVar;
    } else { // found
        throw "Cannot redefine variable.";
    }
}

void Scope::setVariable(std::string identifier, void *value) {
    // Check if the variable exists in the scope
    auto it = m_variables.find(identifier);
    if (it != m_variables.end()) { // found
        // Set the value
        auto var = it->second;
        var.m_value = value;
    } else { // not found
        throw "Variable does not exist.";
    }
}

void *Scope::getVariable(std::string identifier, int &varType) {
    // Check if the variable exists in scope
    auto it = m_variables.find(identifier);
    if (it != m_variables.end()) { // found
        auto var = it->second;
        varType = var.m_varType;
        return var.m_value;
    } else { // not found
        throw "Variable does not exist";
    }
}
