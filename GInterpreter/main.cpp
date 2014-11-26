//
//  main.cpp
//  GInterpreter
//
//  Created by George Green on 23/11/2014.
//  Copyright (c) 2014 George Green. All rights reserved.
//

#include "Interpreter.h"

int main(int argc, const char * argv[]) {
    // Get the first parameter
    const char *file = argv[1];
    printf("Reading from %s\n", file);
    // Create an interpreter
    Interpreter *interpreter = new Interpreter(file);
    delete interpreter;
    // Return
    return 0;
}
