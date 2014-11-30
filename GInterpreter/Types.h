//
//  Types.h
//  GInterpreter
//
//  Created by George Green on 29/11/2014.
//  Copyright (c) 2014 George Green. All rights reserved.
//

#ifndef GInterpreter_Types_h
#define GInterpreter_Types_h

#include <map>

#define G_VOID_TYPE -1
#define G_INT_TYPE 0
#define G_STRING_TYPE 1

struct A {
    static std::map<std::string, int> create_map()
    {
        std::map<std::string, int> m;
        m["void"] = G_VOID_TYPE;
        m["int"] = G_INT_TYPE;
        m["string"] = G_STRING_TYPE;
        return m;
    }
    static const std::map<std::string, int> myMap;
    
};

static std::map<std::string,int> g_types = A::create_map();

#endif
