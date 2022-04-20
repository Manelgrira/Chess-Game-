#ifndef KING_H
#define KING_H

#include "Piece.hpp"

class King: public Piece {
    public:
        King(int , int , int , int, char );
        bool legal_move(int i,int j);
};

#endif