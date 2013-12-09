#ifndef KINGPIECE_H
#define KINGPIECE_H

#include "Piece.h"

class KingPiece: public Piece{
    protected:
        void selectTarget(int diagId, int diagonal, map<int,int>* values,
                vector<Object*> board);
    public:
        KingPiece(int color);
        ~KingPiece(){}
        map<int,int> positionValues(int id, vector<Object*> board);
};

#endif
