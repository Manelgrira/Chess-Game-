#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.hpp"

class Bishop: public Piece {

    public:
        Bishop(int , int , int , int, char );
        bool legal_move(int i,int j);     
};

#endif