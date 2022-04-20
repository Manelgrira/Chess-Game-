#ifndef PIECE_H
#define PIECE_H

#include <cmath>

using namespace std;

class Piece{
    protected:
        int color;
        int id;
        int x;
        int y;
        char name;
        bool hm = false;
    public:
        Piece();
        void setx(int X);
        void sety(int Y);
        int getx();
        int gety();
        int getid();
        int getcolor();
        char getname();
        bool gethm();
        void sethm();
        virtual bool legal_move(int ,int );
};

#endif