#ifndef PAWN_H
#define PAWN_H

#include "Piece.hpp"

class Pawn: public Piece {
    public:
        Pawn(int , int , int , int ,char );
        bool legal_move(int i,int j);
};

#endif