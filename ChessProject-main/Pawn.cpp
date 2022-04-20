#include "Pawn.hpp"


Pawn::Pawn(int X, int Y, int C, int ID ,char N){
    x = X;
    y = Y;
    color = C;
    id = ID;
    name = N; 
}

bool Pawn::legal_move(int i,int j){
    bool ok = true;
    if ((i == x) && (j == y)){
        ok = false;
    }
    return ok;
}
