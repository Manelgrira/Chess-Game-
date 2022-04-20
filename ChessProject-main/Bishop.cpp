#include "Bishop.hpp"

Bishop::Bishop(int X, int Y, int C, int ID, char N){
    x = X;
    y = Y;
    color = C;
    id = ID;
    name = N ;
}
bool Bishop::legal_move(int i,int j){
    bool ok = true;
    if (abs(i - x) != abs(j - y)){
        ok = false;
    }
    return ok;
}