#ifndef OBJECT_H
#define OBJECT_H

#include <map>
#include <vector>
#include "defines.h"

class Object{
    public:
        Object(int color);
        virtual ~Object(){}
        int color;
        int type;

        virtual map<int,int> positionValues(int id, 
                vector<Object*> board);
        virtual void removeUnkilledPositions(map<int,int>* values);
};

#endif
