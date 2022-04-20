#include "Queen.hpp"

Queen::Queen(int X, int Y, int C, int ID,char N){
    x = X;
    y = Y;
    color = C;
    id = ID;
    name = N;
}
bool Queen::legal_move(int i,int j){
    bool ok = true;
    if ((i != x) && (j != y)){ 
        if (abs(i - x) != abs(j - y)){
            ok = false;
        }
    }   
    return ok;
    
}