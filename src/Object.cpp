#include "headers/Object.h"

Object::Object(int color){
    this->color = color;
    type = NONE;
}

map<int,int> Object::positionValues(int id, vector<Object*> board){
    map<int,int> temp;
    return temp;
}

void Object::removeUnkilledPositions(map<int,int>* values){}
