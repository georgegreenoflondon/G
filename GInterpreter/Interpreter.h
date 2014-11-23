//
//  Interpreter.h
//  GInterpreter
//
//  Created by George Green on 23/11/2014.
//  Copyright (c) 2014 George Green. All rights reserved.
//

#include "LexicalAnalyser.h"

#ifndef GInterpreter_Interpreter_h
#define GInterpreter_Interpreter_h

class Interpreter {
    
    /*
     * Consturctor
     */
public:
    Interpreter(const char *filepath);
    
    
    /*
     * Data members
     */
private:
    LexicalAnalyser m_lexer;
    
    
};


#endif
