#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include "Object.h"
#include "defines.h"

class Piece: public Object{
    protected:
        void markPosition(int diagId, int diagonal, map<int,int>* values, 
                vector<Object*> board);

        virtual void selectTarget(int diagId, int diagonal, map<int,int>* values,
                vector<Object*> board);

        void incrementDiagonal(int diagId, int id, int diagonal,
                map<int,int>* values, vector<Object*> board);

        void decrementDiagonal(int diagId, int id, int diagonal,
                map<int,int>* values, vector<Object*> board);


        int canKill; //variable to check if this Piece will kill other piece

    public:
        Piece(int color);
        virtual ~Piece(){}
        virtual map<int,int> positionValues(int id, vector<Object*> board);
        void removeUnkilledPositions(map<int,int>* values);

};

#endif
