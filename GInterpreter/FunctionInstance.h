//
//  FunctionInstance.h
//  GInterpreter
//
//  Created by George Green on 30/11/2014.
//  Copyright (c) 2014 George Green. All rights reserved.
//

#ifndef __GInterpreter__FunctionInstance__
#define __GInterpreter__FunctionInstance__

#include "FunctionTemplate.h"

using namespace std;

class FunctionInstance : public FunctionTemplate {
    
    /*
     * Constructor
     */
public:
    FunctionInstance(FunctionTemplate const &functionTemplate, string parameterString);
    
};

#endif /* defined(__GInterpreter__FunctionInstance__) */
