//
//  FunctionInstance.cpp
//  GInterpreter
//
//  Created by George Green on 30/11/2014.
//  Copyright (c) 2014 George Green. All rights reserved.
//

#include "FunctionInstance.h"

FunctionInstance::FunctionInstance(FunctionTemplate const &functionTemplate, string parameterString)
: FunctionTemplate(functionTemplate) {
    // Parse the parameter string and create in scope variables for each one
    LexicalAnalyser *tempLexer = new LexicalAnalyser(parameterString);
    // Loop over the expected params and attempt to read them from the param string
    for (string identifier : m_paramIdentifiers) {
        int varType = m_paramTypes[identifier];
        void *value;
        tempLexer->readBasicLiteral(varType, &value);
        addVariable(identifier, varType);
        setVariable(identifier, value);
    }
    // Free the temp lexer
    delete tempLexer;
}