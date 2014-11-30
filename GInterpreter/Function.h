//
//  Function.h
//  GInterpreter
//
//  Created by George Green on 29/11/2014.
//  Copyright (c) 2014 George Green. All rights reserved.
//

#ifndef __GInterpreter__Function__
#define __GInterpreter__Function__

#include "Scope.h"
#include <map>

using namespace std;

class Function : public Scope {
    
    /*
     * Constructor
     */
public:
    Function(string paramString, int returnType, string scopeCode);
    
    /*
     * Data members
     */
    int m_returnType;
    map<string, int> m_params;
    
};

#endif /* defined(__GInterpreter__Function__) */
