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

class Function : Scope {
    
    /*
     * Condtructor
     */
    Function(string code, int returnType, map<string, int> params);
    
    /*
     * Data members
     */
    map<string, int> m_params;
    
};

#endif /* defined(__GInterpreter__Function__) */
