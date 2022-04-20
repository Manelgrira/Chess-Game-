#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cctype>
#include <iostream>
#include <vector>
#include "Knight.hpp"
#include "Pawn.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"
#include "Rook.hpp"
#include <iomanip>
#include <typeinfo>
#include <string>
#include <algorithm>
#include <thread>
#include <fstream>

using namespace sf;

class Game
{

private:
    King *testk = new King(100, 100, 100, 100, 'k');
    Pawn *testp = new Pawn(100, 100, 100, 100, 'p');
    int size = 56;
    Sprite squares[64];///squares///
    Sprite f[32];///pieces///
    int turn=0;
    int Board[8][8] = {
        16,17,18,19,20,21,22,23,
        24,25,26,27,28,29,30,31,
        50,50,50,50,50,50,50,50,
        50,50,50,50,50,50,50,50,
        50,50,50,50,50,50,50,50,
        50,50,50,50,50,50,50,50,
        8 ,9 ,10,11,12,13,14,15,
        0 ,1 ,2 , 3, 4, 5, 6, 7,
    };
    bool promo = false;
    vector<Piece *> pieces;
    int p_moved=100;
    bool test;
    bool game_over = false;
    ///square color///
    Color dark_square_color = Color(3, 152, 158); 
    Color light_square_color = Color(255, 255, 255);
public:
    Game();
    void loadTexture(int);
    void loadPosition();
    int getTurn(){return turn;}
    vector<vector<int>> target_Squares(int, int);
    vector<vector<int>> white_Targets_Squares();
    vector<vector<int>> black_Targets_Squares();
    void putPiece(int);
    void abstractMove(int, int, int, int);
    void Promotion(int , int ,char );
    bool castle(int , int );
    bool king_in_check(int, int);
    bool In_Between_pieces(int, int, int, int);
    bool pawn_mouvement(int, int, int, int, int);
    bool move (int,int,int,int);
    void setpmoved(int x){
        p_moved = x;
    }
    void switchTurn();  
    void colorSquares();
    void setpchoice(char c){
        fstream ofs;
        ofs.open("c.txt", ios::out | ios::trunc);
        ofs<<c;
        ofs.close();
    }
    char getpchoice(){
        ifstream ifs;
        char c;
        ifs.open("c.txt");
        ifs>>c;
        ifs.close();
        return c;
    }
};

#endif
