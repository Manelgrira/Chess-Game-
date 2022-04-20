#include "King.hpp"

King::King(int X, int Y, int C, int ID , char N){
    x = X;
    y = Y;
    color = C;
    id = ID;
    name = N;
}

bool King::legal_move(int i,int j){
    bool ok = true;
    if (abs(i - x) > 1 || abs(j - y) > 1){              
        ok = false;
    }
    return ok;   
}