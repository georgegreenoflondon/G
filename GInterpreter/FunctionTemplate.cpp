//
//  Function.cpp
//  GInterpreter
//
//  Created by George Green on 29/11/2014.
//  Copyright (c) 2014 George Green. All rights reserved.
//

#include "FunctionTemplate.h"

/*
 * Constructor
 */

FunctionTemplate::FunctionTemplate(string paramString, int returnType, string scopeCode)
: Scope(scopeCode)
, m_returnType(returnType) {
    // Parse the parameter string
    LexicalAnalyser *tempLexer = new LexicalAnalyser(paramString);
    bool finished = paramString.length() == 0;
    while (!finished) {
        std::string typeIdentifier;
        if (tempLexer->readWord(&typeIdentifier)) {
            if (g_types.count(typeIdentifier)) {
                int type = g_types[typeIdentifier];
                std::string identifier;
                if (tempLexer->readWord(&identifier)) {
                    m_params[identifier] = type;
                }
            } else throw "Expected type.";
        } else finished = true;
    }
    // Free the memory used by the temporary lexer
    delete tempLexer;
}
