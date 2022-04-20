#include "Piece.hpp"

Piece::Piece(){
    int x,y,color,id ,name;
}

void Piece::setx(int X){
    x = X;
}
void Piece::sety(int Y){
    y = Y;
}
int Piece::getx(){
    return x;
}
int Piece::gety(){
    return y;
}
int Piece::getid(){
    return id;
}
int Piece::getcolor(){
    return color;
}
char Piece::getname(){
    return name;
}
bool Piece::legal_move(int X,int Y){
    return false;
}
bool Piece::gethm(){
    return hm;
}
void Piece::sethm(){
    hm = true;
}