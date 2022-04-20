#include "Game.hpp"

Game::Game(){
    Rook *wra = new Rook(7, 0, 0, 0, 'r');
    Knight *wnb = new Knight(7, 1, 0, 1, 'n');
    Bishop *wbc = new Bishop(7, 2, 0, 2, 'b');
    Queen *wqd = new Queen(7, 3, 0, 3, 'q');
    King *wke = new King(7, 4, 0, 4, 'k');
    Bishop *wbf = new Bishop(7, 5, 0, 5, 'b');
    Knight *wng = new Knight(7, 6, 0, 6, 'n');
    Rook *wrh = new Rook(7, 7, 0, 7, 'r');
    Pawn *wpa = new Pawn(6, 0, 0, 8, 'p');
    Pawn *wpb = new Pawn(6, 1, 0, 9, 'p');
    Pawn *wpc = new Pawn(6, 2, 0, 10, 'p');
    Pawn *wpd = new Pawn(6, 3, 0, 11, 'p');
    Pawn *wpe = new Pawn(6, 4, 0, 12, 'p');
    Pawn *wpf = new Pawn(6, 5, 0, 13, 'p');
    Pawn *wpg = new Pawn(6, 6, 0, 14, 'p');
    Pawn *wph = new Pawn(6, 7, 0, 15, 'p');
    Rook *bra = new Rook(0, 0, 1, 16, 'R');
    Knight *bnb = new Knight(0, 1, 1, 17, 'N');
    Bishop *bbc = new Bishop(0, 2, 1, 18, 'B');
    Queen *bqd = new Queen(0, 3, 1, 19, 'Q');
    King *bke = new King(0, 4, 1, 20, 'K');
    Bishop *bbf = new Bishop(0, 5, 1, 21, 'B');
    Knight *bng = new Knight(0, 6, 1, 22, 'N');
    Rook *brh = new Rook(0, 7, 1, 23, 'R');
    Pawn *bpa = new Pawn(1, 0, 1, 24, 'W');
    Pawn *bpb = new Pawn(1, 1, 1, 25, 'W');
    Pawn *bpc = new Pawn(1, 2, 1, 26, 'W');
    Pawn *bpd = new Pawn(1, 3, 1, 27, 'W');
    Pawn *bpe = new Pawn(1, 4, 1, 28, 'W');
    Pawn *bpf = new Pawn(1, 5, 1, 29, 'W');
    Pawn *bpg = new Pawn(1, 6, 1, 30, 'W');
    Pawn *bph = new Pawn(1, 7, 1, 31, 'W');
    pieces.push_back(wra);
    pieces.push_back(wnb);
    pieces.push_back(wbc);
    pieces.push_back(wqd);
    pieces.push_back(wke);
    pieces.push_back(wbf);
    pieces.push_back(wng);
    pieces.push_back(wrh);
    pieces.push_back(wpa);
    pieces.push_back(wpb);
    pieces.push_back(wpc);
    pieces.push_back(wpd);
    pieces.push_back(wpe);
    pieces.push_back(wpf);
    pieces.push_back(wpg);
    pieces.push_back(wph);
    pieces.push_back(bra);
    pieces.push_back(bnb);
    pieces.push_back(bbc);
    pieces.push_back(bqd);
    pieces.push_back(bke);
    pieces.push_back(bbf);
    pieces.push_back(bng);
    pieces.push_back(brh);
    pieces.push_back(bpa);
    pieces.push_back(bpb);
    pieces.push_back(bpc);
    pieces.push_back(bpd);
    pieces.push_back(bpe);
    pieces.push_back(bpf);
    pieces.push_back(bpg);
    pieces.push_back(bph);

    void selectChoice(Game g);
    
    Vector2f offset{28,28};

    RenderWindow window(VideoMode(504, 504), "Chess");
    Vector2i winpos = {400,150};
    window.setPosition(winpos);

    ///sound///
    sf::SoundBuffer bm,bc,bo,bs;
    bm.loadFromFile("sound/move_sound.wav");
    bc.loadFromFile("sound/check_sound.wav");
    bo.loadFromFile("sound/game_over_sound.wav");
    bs.loadFromFile("sound/game_start_sound.wav");

    sf::Sound sm,sc,so,ss;
    sm.setBuffer(bm);
    sc.setBuffer(bc);
    so.setBuffer(bo);
    ss.setBuffer(bs);
    ss.play();

    ///textures///
    Texture  t1,bg,tw,tb,ts,chover,border;

    t1.loadFromFile("images/figures.png"); 
    bg.loadFromFile("images/bg.png");
    tw.loadFromFile("images/wwin.png");
    tb.loadFromFile("images/bwin.png");
    ts.loadFromFile("images/stale.png");
    chover.loadFromFile("images/white_square.png");  
    border.loadFromFile("images/border.png"); 
    t1.setSmooth(true);

    ///sprites///
    Sprite background;
    Sprite bdd;
    Sprite wwinbg;
    Sprite bwinbg;
    Sprite sbg;
    Sprite check_overlay;
    
    background.setTexture(bg);
    bdd.setTexture(border);
    wwinbg.setTexture(tw);
    bwinbg.setTexture(tb);
    sbg.setTexture(ts);
    check_overlay.setTexture(chover);

    check_overlay.setColor(sf::Color(255, 156, 156));
    bdd.setColor(sf::Color(28, 32, 36));
    check_overlay.setPosition(-100,-100);
    bdd.setPosition(10,10);
    int highlighted_squares[64];
    
    
    int k = 0;
    for (int i =0;i <8;i++){ // put squares
        for(int j = 0;j<8;j++){
            squares[k].setTexture(chover);
            squares[k].setPosition(size*i,size*j);
            squares[k].move(offset);
            k++;
        }
    }
    colorSquares(); //color dark squares

    for(int i=0;i<32;i++){ //pieces
        f[i].setTexture(t1);
        f[i].setPosition(-100,-100);
    }
    bool isMove=false;
    float dx=0, dy=0;
    Vector2f oldPosCords;
    Vector2f newPosCords;
    int n=0;

    loadPosition();
    while (window.isOpen()){
        test = false;
        Vector2i pos = Mouse::getPosition(window) - Vector2i(offset);
        Event e;
        while (window.pollEvent(e)){
            if (e.type == Event::Closed){
                window.close();
            }
            /////drag and drop///////

            if (e.type == Event::MouseButtonPressed){ 
                if (e.key.code == Mouse::Left){ // left click //start drag
                    colorSquares();
                    for(int i=0;i<32;i++){
                        if (f[i].getGlobalBounds().contains(pos.x,pos.y)){
                            isMove=true;
                            n=i;
                            dx=pos.x - f[i].getPosition().x;
                            dy=pos.y - f[i].getPosition().y;
                            oldPosCords  =  Vector2f {pieces[i]->gety(),pieces[i]->getx()};
                        }
                    }
                }else if (e.key.code == Mouse::Right){ // right click
                    if(isMove){ //undo drag
                        isMove=false;
                        colorSquares();
                        loadPosition();
                    }

                    ////highlight/unhighlight square////
                    else{
                        int i = 0;
                        for(int j = 0;j<8;j++){
                            for(int k = 0;k<8;k++){
                                if (squares[i].getGlobalBounds().contains(pos.x + offset.x,pos.y + offset.y)){
                                    if(highlighted_squares[i] == 1){
                                        highlighted_squares[i] = 0;
                                        if((j+k)%2 == 0){
                                            squares[i].setColor(light_square_color);
                                        }else{
                                            squares[i].setColor(dark_square_color);
                                        }
                                    }else{
                                        squares[i].setColor(sf::Color(255, 200, 71));
                                        highlighted_squares[i] = 1;
                                    }
                                }
                                i++;
                            }
                        }
                    }
                }
            }

            ////drop////
            if (e.type == Event::MouseButtonReleased){
                if (e.key.code == Mouse::Left){
                    for(int i =0;i<64;i++){
                        highlighted_squares[i] = 0;
                    }
                    isMove=false;
                    colorSquares();
                    Vector2f p = f[n].getPosition() + Vector2f(size/2,size/2); // offset for placing pieces in center of square
                    newPosCords = Vector2f(int(p.y/size),int(p.x/size)); // piece position in pixels centered in square
                    bool lMove = move(oldPosCords.y,oldPosCords.x,newPosCords.x,newPosCords.y); // make the move
                    loadPosition(); // shows move result when piece is dropped
                    if(lMove){
                        ////pawn promotion////
                        if (promo){
                            std::thread promoTh(selectChoice,*this);
                            promoTh.join();
                            char c = getpchoice();
                            Promotion(newPosCords.x,newPosCords.y,c);
                            setpchoice('a');
                            promo = false;
                            loadPosition();
                        }
                        switchTurn();
                        ////king in check highlight////
                        if (turn == 0){
                            int wkx = pieces[4]->getx();
                            int wky = pieces[4]->gety();
                            if (king_in_check(wkx,wky)){
                                check_overlay.setPosition(wky*size,wkx*size);
                                check_overlay.move(offset);
                                sc.play();
                            }else{
                                sm.play();
                                check_overlay.setPosition(-100,-100);
                            }
                        }else{
                            int bkx = pieces[20]->getx();
                            int bky = pieces[20]->gety();
                            if (king_in_check(bkx,bky)){
                                check_overlay.setPosition(bky*size,bkx*size);
                                check_overlay.move(offset);
                                sc.play();
                            }else{
                                check_overlay.setPosition(-100,-100);
                                sm.play();
                            }
                        }
                        test = true;
                        bool ok1 = false;

                        ////look for moves////
                        for (int i = 0; i<8 && ok1 == false; i++){
                            for (int j = 0; j<8 && ok1 == false; j++){
                                int pid = Board[i][j];
                                if (pid < 32){
                                    if (pieces[pid]->getcolor() == turn){
                                        vector<vector<int>> t = target_Squares(i,j);
                                        if (typeid(*pieces[pid]).name() == typeid(*testp).name()){
                                            for (int k = 0; k < t.size() && ok1 == false; k++){
                                                if (In_Between_pieces(i,j,t[k][0],t[k][1]) == false){
                                                    ok1 = !pawn_mouvement(i, j, t[k][0], t[k][1], pid);
                                                }
                                            }
                                            if (ok1 == false){
                                                if (turn == 0){
                                                    if (In_Between_pieces(i,j,i-1,j) == false){
                                                        ok1 = !pawn_mouvement(i,j, i-1, j, pid);
                                                    }
                                                    if(i == 6 && ok1 == false){
                                                        if (In_Between_pieces(i,j,i-2,j) == false){
                                                            ok1 = !pawn_mouvement(i,j, i-2, j, pid);
                                                        }
                                                    }
                                                }else{
                                                    if (In_Between_pieces(i,j,i+1,j) == false){
                                                        ok1 = !pawn_mouvement(i,j, i+1, j, pid);
                                                    }
                                                    if(i == 1 && ok1 == false){
                                                        if (In_Between_pieces(i,j,i+2,j) == false){
                                                            ok1 = !pawn_mouvement(i,j, i+2, j, pid);
                                                        }
                                                    }
                                                }
                                            }
                                        }else{
                                            for (int k = 0; k < t.size() && ok1 == false; k++){
                                                ok1 = move(i,j,t[k][0],t[k][1]);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if (ok1 == false){ // 0 moves left
                            so.play();
                            game_over = true;
                        }
                    }
                }
            }

            ////drag////
            if (isMove) {
                f[n].setPosition(pos.x-dx,pos.y-dy);
                
                ////target square highlight////
                if(pieces[n]->getcolor() == turn){
                    int x = pieces[n]->getx();
                    int y = pieces[n]->gety();
                    vector<vector<int>> t = target_Squares(x,y);
                    if(typeid(*pieces[n]).name() == typeid(*testp).name()){ //pawn
                        vector<int> square;
                        if(turn == 0){ //white
                            if(Board[x-1][y] == 50){
                                square.push_back(x-1);
                                square.push_back(y);
                                t.push_back(square);
                                square.clear();
                                if(x == 6 && Board[x-2][y] == 50){
                                    square.push_back(x-2);
                                    square.push_back(y);
                                    t.push_back(square);
                                    square.clear();
                                }
                            }
                        }else{ //black
                            if(Board[x+1][y] == 50){
                                square.push_back(x+1);
                                square.push_back(y);
                                t.push_back(square);
                                square.clear();
                                if(x == 1 && Board[x+2][y] == 50){
                                    square.push_back(x+2);
                                    square.push_back(y);
                                    t.push_back(square);
                                    square.clear();
                                }
                            }
                        }
                    }
                    vector<int> pixelpos;
                    for(int i = 0;i < t.size();i++){ // highlight squares in light blue
                        pixelpos.push_back(t[i][0]*size + 30); // +30 accounts for the 26 pixel offset
                        pixelpos.push_back(t[i][1]*size + 30);
                        for(int j = 0; j < 64 ;j++){
                            if(squares[j].getGlobalBounds().contains(pixelpos[1],pixelpos[0])){
                                squares[j].setColor(sf::Color(99, 207, 255));
                            }
                        }
                        pixelpos.clear();
                    }
                }
            }
        }

        ////draw////
        if(!game_over){
            window.clear();
            window.draw(background);//white border 
            window.draw(bdd); //dark border
            for(int i =0;i<64;i++){ //squares
                window.draw(squares[i]);
            }
            window.draw(check_overlay); //check overlay
            for(int i=0;i<32;i++) { //pieces add offset
                f[i].move(offset);
            }
            
            for(int i=0;i<8;i++) { //pieces
                for(int j = 0;j<8;j++){
                    int pid = Board[i][j];
                    if(pid < 32){
                        window.draw(f[pid]);
                    }
                }
            } 
            window.draw(f[n]);// draws dragged piece over other pieces

            for(int i=0;i<32;i++) { //pieces remove offset
                f[i].move(-offset);
            }
            window.display();

        }else{ //game is over
            for(int i=0;i<32;i++) { //remove pieces (prevent movement after game is over)
                f[i].setPosition(-100,-100);
            }
            if (turn == 0){
                int wkx = pieces[4]->getx();
                int wky = pieces[4]->gety();
                if (king_in_check(wkx,wky)){ //black wins
                    window.clear();
                    window.draw(bwinbg);
                    window.display();
                }else{ //stalemate
                    window.clear();
                    window.draw(sbg);
                    window.display();
                }
            }else{
                int bkx = pieces[20]->getx();
                int bky = pieces[20]->gety();
                if (king_in_check(bkx,bky)){ // white wins
                    window.clear();
                    window.draw(wwinbg);
                    window.display();
                }else{ // stalemate
                    window.clear();
                    window.draw(sbg);
                    window.display();
                }
            }
        }
    }
}
void Game::putPiece(int ID){
    Board[pieces[ID]->getx()][pieces[ID]->gety()] = pieces[ID]->getid();
}
void Game::abstractMove(int x1, int y1, int x2, int y2){
    int pid = Board[x1][y1];
    if (pid < 32){
        Board[x1][y1] = 50;
        Board[x2][y2] = pid;
        pieces[pid]->setx(x2);
        pieces[pid]->sety(y2);
    }
}
bool Game::In_Between_pieces(int x1, int y1, int x2, int y2){
    if(x1>=0 && x1<8 && x2>=0 && x2<8 && y1>=0 && y1<8 && y2>=0 && y2<8){ // coordinates in the board
        int pid = Board[x1][y1];
        if (pid < 32){
            int c = pieces[pid]->getcolor();
            int c1 = 2;
            if (x1 == x2 && y1 == y2){ // same square
                return false;
            }
            if (Board[x2][y2] < 32){
                c1 = pieces[Board[x2][y2]]->getcolor();
            }
            if (c == c1){ // last square contains ally piece
                return true; 
            }
            if (x1 == x2){ // horizontal
                int j = (y2 - y1) / abs(y1 - y2);
                for (int i = y1 + j; abs(i - y2) > 0; i += j){
                    if (Board[x1][i] < 32){
                        return true;
                    }
                }
            }else if (y1 == y2){ // vertical
                int j = (x2 - x1) / abs(x1 - x2);
                for (int i = x1 + j; abs(i - x2) > 0; i += j){
                    if (Board[i][y1] < 32){
                        return true;
                    }
                }
            }else if (abs(x1 - x2) == abs(y1 - y2)){ //diagonal
                int k = (x2 - x1) / abs(x1 - x2);
                int l = (y2 - y1) / abs(y1 - y2);
                int j = y1 + l;
                for (int i = x1 + k; abs(i - x2) > 0; i += k){
                    if (Board[i][j] < 32){
                        return true;
                    }
                    j += l;
                }
            }
        }
    }
    return false; // default return false
}
vector<vector<int>> Game::target_Squares(int X1, int Y1){
    vector<vector<int>> squaresList;
    vector<int> square;
    int pid = Board[X1][Y1];
    if (pid < 32){
        if (typeid(*pieces[pid]).name() != typeid(*testp).name()){ // piece is not a pawn
            for (int i = 0; i < 8; i++){
                for (int j = 0; j < 8; j++){
                    if (i != X1 || j != Y1){
                        if (In_Between_pieces(X1, Y1, i, j) == 0){
                            if (pieces[pid]->legal_move(i, j)){
                                square.push_back(i);
                                square.push_back(j);
                                squaresList.push_back(square);
                                square.clear();
                            }
                        }
                    }
                }
            }
        }else{ // case of pawn
            if (pieces[pid]->getcolor() == 0){ // white pawn
                if (Y1 < 7){
                    int rid = Board[X1 - 1][Y1 + 1]; // right square
                    if (!(rid < 32 && pieces[rid]->getcolor() == pieces[pid]->getcolor())){
                        square.push_back(X1 - 1);
                        square.push_back(Y1 + 1);
                        squaresList.push_back(square);
                        square.clear();
                    }
                }
                if (Y1 > 0){ // left square
                    int lid = Board[X1 - 1][Y1 - 1];
                    if (!(lid < 32 && pieces[lid]->getcolor() == pieces[pid]->getcolor())){
                        square.push_back(X1 - 1);
                        square.push_back(Y1 - 1);
                        squaresList.push_back(square);
                        square.clear();
                    }
                }
            }else{ // black pawn
                if (Y1 < 7){ // right square
                    int rid = Board[X1 + 1][Y1 + 1];
                    if (!(rid < 32 && pieces[rid]->getcolor() == pieces[pid]->getcolor())){
                        square.push_back(X1 + 1);
                        square.push_back(Y1 + 1);
                        squaresList.push_back(square);
                        square.clear();
                    }
                }
                if (Y1 > 0){ // left square
                    int lid = Board[X1 + 1][Y1 - 1];
                    if (!(lid < 32 && pieces[lid]->getcolor() == pieces[pid]->getcolor())){
                        square.push_back(X1 + 1);
                        square.push_back(Y1 - 1);
                        squaresList.push_back(square);
                        square.clear();
                    }
                }
            }
        }
    }
    return squaresList;
}
vector<vector<int>> Game::white_Targets_Squares(){
    vector<vector<int>> wts;
    vector<vector<int>> s;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (Board[i][j] < 16){ //the piece is white
                s = target_Squares(i, j);
                for (int k = 0; k < s.size(); k++){
                    wts.push_back(s[k]);
                }
                s.clear();
            }
        }
    }
    return wts;
}
vector<vector<int>> Game::black_Targets_Squares(){
    vector<vector<int>> bts;
    vector<vector<int>> s;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (Board[i][j] > 15 && Board[i][j] != 50){ // the piece is black
                s = target_Squares(i, j);
                for (int k = 0; k < s.size(); k++){
                    bts.push_back(s[k]);
                }
                s.clear();
            }
        }
    }
    return bts;
}
bool Game::king_in_check(int X, int Y){
    vector<vector<int>> ts; // opponent target squares
    if (turn == 1){
        ts = white_Targets_Squares();
    }else{
        ts = black_Targets_Squares();
    }
    vector<int> kingPos = {X, Y};

    for (int i = 0; i < ts.size(); i++){
        if (ts[i] == kingPos){ // king square in target squares of opponent
            return true;
        }
    }
    return false;
}
void Game::Promotion(int i, int j, char choice){
    int pid = Board[i][j];
    int X = pieces[pid]->getx();
    int Y = pieces[pid]->gety();
    int C = pieces[pid]->getcolor();
    if (turn == 1){ // black pawn
        choice = toupper(choice);
    }else{          // white pawn
        choice = tolower(choice);
    }
    switch (tolower(choice)){
    case 'b':
        pieces[pid] = new Bishop(X, Y, C, pid, choice);
        putPiece(pid);
        break;
    case 'n':
        pieces[pid] = new Knight(X, Y, C, pid, choice);
        putPiece(pid);
        break;
    case 'r':
        pieces[pid] = new Rook(X, Y, C, pid, choice);
        putPiece(pid);
        break;
    case 'q':
        pieces[pid] = new Queen(X, Y, C, pid, choice);
        putPiece(pid);
        break;
    default:
        break;
    }
}
bool Game::castle(int i, int j){
    bool wrong_move = false;
    if (turn == 0){
        vector<vector<int>> bts;
        bts = black_Targets_Squares();
        int x1 = pieces[4]->getx();
        int y1 = pieces[4]->gety();
        if (Board[i][j] == 0){ //left rook
            if ((In_Between_pieces(x1, y1, x1, y1 - 3) == false) && (Board[7][1] = 50) && (pieces[4]->gethm() == false) && (pieces[0]->gethm() == false)){
                bool trouve = false;
                for (int k = 0; k < bts.size() && trouve == false; k++){
                    if (bts[k][0] == 7 && (bts[k][1] == 2 || bts[k][1] == 3 || bts[k][1] == 4)){
                        trouve = true;
                    }
                }
                if (trouve == false){
                    if (test==false){
                        abstractMove(7, 4, 7, 2);
                        abstractMove(7, 0, 7, 3);
                        pieces[4]->sethm();
                        pieces[0]->sethm();
                    }
                }else{
                    wrong_move = true;
                }
            }else{
                wrong_move = true;
            }
        }else if (Board[i][j] == 7){ // right rook
            if ((In_Between_pieces(x1, y1, x1, y1 + 2) == false) && (Board[7][6] = 50) && (pieces[4]->gethm() == false) && (pieces[7]->gethm() == false)){
                bool trouve = false;
                for (int k = 0; k < bts.size() && trouve == false; k++){
                    if (bts[k][0] == 7 && (bts[k][1] == 5 || bts[k][1] == 6 || bts[k][1] == 4)){
                        trouve = true;
                    }
                }
                if (trouve == false){
                    if (test==false){
                       abstractMove(7, 4, 7, 6);
                       abstractMove(7, 7, 7, 5);
                       pieces[4]->sethm();
                       pieces[7]->sethm();
                    }
                }else{
                    wrong_move = true;
                }
            }else{
                wrong_move = true;
            }
        }else{
            wrong_move = true;
        }
    }else{
        vector<vector<int>> wts;
        wts = white_Targets_Squares();
        int x1 = pieces[20]->getx();
        int y1 = pieces[20]->gety();
        if (Board[i][j] == 16){ // left rook
            if ((In_Between_pieces(x1, y1, x1, y1 - 3) == false) && (Board[0][1] = 50) && (pieces[20]->gethm() == false) && (pieces[16]->gethm() == false)){
                bool trouve = false;
                for (int k = 0; k < wts.size() && trouve == false; k++){
                    if (wts[k][0] == 0 && (wts[k][1] == 2 || wts[k][1] == 3 || wts[k][1] == 4)){
                        trouve = true;
                    }
                }
                if (trouve == false){
                    if (test==false){
                        abstractMove(0, 4, 0, 2);
                        abstractMove(0, 0, 0, 3);
                        pieces[20]->sethm();
                        pieces[16]->sethm();
                    }
                }else{
                    wrong_move = true;
                }
            }else{
                wrong_move = true;
            }
        }else if (Board[i][j] == 23){ //right rook
            if ((In_Between_pieces(x1, y1, x1, y1 + 2) == false) && (Board[0][6] = 50) && (pieces[20]->gethm() == false) && (pieces[23]->gethm() == false)){
                bool trouve = false;
                for (int k = 0; k < wts.size() && trouve == false; k++){
                    if (wts[k][0] == 0 && (wts[k][1] == 5 || wts[k][1] == 6 || wts[k][1] == 4)){
                        trouve = true;
                    }
                }
                if (trouve == false){
                    if (test==false){
                        abstractMove(0, 4, 0, 6);
                        abstractMove(0, 7, 0, 5);
                        pieces[20]->sethm();
                        pieces[23]->sethm();
                    }
                }else{
                    wrong_move = true;
                }
            }else{
                wrong_move = true;
            }
        }else{
            wrong_move = true;
        }
    }
    return wrong_move;
}
bool Game::pawn_mouvement(int x1, int y1, int i, int j, int id1){
    bool I_moved = false;
    bool wrong_move = false;
    int p_moved_value = p_moved;
    if (turn == 1){
        int bkx = pieces[20]->getx();
        int bky = pieces[20]->gety();
        if (pieces[id1]->getcolor() == turn){
            if (y1 == j && (x1 + 1 == i || x1 + 2 == i && x1 == 1)){ //forward mvt
                if (Board[i][j] == 50){
                    if (x1 + 2 == i && x1 == 1){ //2 square
                        setpmoved(id1);
                    }else{
                        setpmoved(100);
                    }
                    abstractMove(x1, y1, i, j);
                    if (king_in_check(bkx, bky)){
                        abstractMove(i, j, x1, y1);
                        wrong_move = true;
                        setpmoved(p_moved_value);
                    }else if (test== true){
                        abstractMove(i, j, x1, y1);
                        setpmoved(p_moved_value);
                    }else{
                        I_moved = true;
                    }
                }else{
                    wrong_move = true;
                }
            }else if (abs(j - y1) == 1 && abs(i - x1) == 1){ //eat
                if (Board[i][j] == 50){ //en passant?
                    int id2 = Board[i - 1][j];
                    if (id2 == p_moved){
                        abstractMove(x1, y1, i, j);
                        Board[i - 1][j] = 50;
                        if (king_in_check(bkx, bky)){
                            abstractMove(i, j, x1, y1);
                            Board[i - 1][j] = id2;
                            wrong_move=true;
                        }else if (test==true){
                            abstractMove(i, j, x1, y1);
                            Board[i - 1][j] = id2;
                        }else{
                            I_moved = true;
                            setpmoved(100);
                        }
                    }else{
                        wrong_move = true;
                    }
                }else if (Board[i][j] < 16){ //not en passant
                    int p = Board[i][j];
                    abstractMove(x1, y1, i, j);
                    if (king_in_check(bkx, bky)){
                        abstractMove(i, j, x1, y1);
                        Board[i][j] = p;
                        wrong_move = true;
                    }else if  (test==true){
                        abstractMove(i, j, x1, y1);
                        Board[i][j] = p;
                    }else{   
                        I_moved=true;
                        setpmoved(100);
                    }
                }
            }else{
                wrong_move = true;
            }
            if (I_moved && i == 7){
                if (test==false) {
                    promo = true;
                }
            }
        }else{
            wrong_move = true;
        }
    }else{ // white
        int wkx = pieces[4]->getx();
        int wky = pieces[4]->gety();
        if (pieces[id1]->getcolor() == turn){
            if (y1 == j && (x1 - 1 == i || x1 - 2 == i && x1 == 6)){ //forward mvt
                if (Board[i][j] == 50){
                    if (x1 - 2 == i && x1 == 6){ //2 square
                        setpmoved(id1);
                    }else{
                       setpmoved (100);
                    }
                    abstractMove(x1, y1, i, j);
                    if (king_in_check(wkx, wky)){
                        abstractMove(i, j, x1, y1);
                        wrong_move = true;
                        setpmoved(p_moved_value);
                    }else if (test==true){
                        abstractMove(i, j, x1, y1);
                        setpmoved(p_moved_value);
                    }else{
                        I_moved = true;
                    }
                }else{
                    wrong_move = true;
                }
            }else if (abs(j - y1) == 1 && x1 - i == 1){ //eat
                if (Board[i][j] == 50){ //en passat
                    int id2 = Board[i + 1][j];
                    if (id2 == p_moved){
                        abstractMove(x1, y1, i, j);
                        Board[i + 1][j] = 50;
                        if (king_in_check(wkx, wky)){
                            abstractMove(i, j, x1, y1);
                            Board[i + 1][j] = id2;
                            wrong_move = true;
                        }else if (test==true){
                            abstractMove(i, j, x1, y1);
                            Board[i + 1][j] = id2;
                            setpmoved(p_moved_value);
                        }else{
                            I_moved = true;
                            setpmoved(100);
                        }
                    }else{
                        wrong_move = true;
                    }
                }else if (Board[i][j] > 15 && Board[i][j] < 32){ //not en passant
                    int p = Board[i][j];
                    abstractMove(x1, y1, i, j);
                    if (king_in_check(wkx, wky)){
                        abstractMove(i, j, x1, y1);
                        Board[i][j] = p;
                        wrong_move = true;
                    }else if (test==true){
                        abstractMove(i, j, x1, y1);
                        Board[i][j] =p ;
                        setpmoved(p_moved_value);

                    }else{
                        pieces[id1]->sethm();
                        setpmoved(100);
                        I_moved = true;
                    }
                }
            }else{
                wrong_move = true;
            }
            if (I_moved && i == 0){
               if (test ==false){
                    promo = true;
                }
            }
        }else{
        wrong_move = true;
        }
    } 
    return wrong_move;
}
void Game::switchTurn(){
    turn = 1 - turn;
}
bool Game:: move (int x1, int y1, int i, int j){
    int id1 = Board[x1][y1];
    int wkx = pieces[4]->getx();
    int wky = pieces[4]->gety();
    int bkx = pieces[20]->getx();
    int bky = pieces[20]->gety();
    bool wrong_move = false;
    if (id1 == 50){ // initial square is empty
        wrong_move = true;
    }else if(x1 == i && y1 == j){ // same square selected
        wrong_move = true;
    }else{
        if (typeid(*pieces[id1]).name() == typeid(*testp).name()){ // pawn selected
            if (In_Between_pieces(x1,y1,i,j) == false){
                wrong_move = pawn_mouvement(x1, y1, i, j, id1);
            }else{
                wrong_move == true;
            }
        }else if (typeid(*pieces[id1]).name() == typeid(*testk).name() && (abs(y1 - j) == 3 || abs(y1 - j) == 4)){ //caslte
            wrong_move = castle(i, j);
        }else{
            vector<int> square_f = {i,j};
            if (pieces[id1]->getcolor() == turn){ // selected ally piece
                vector<vector<int>> c = target_Squares(x1, y1);
                vector<vector<int>>::iterator it1;
                it1 = find(c.begin(), c.end(), square_f);
                if (it1 != c.end()){ // final square found in target squares
                    int p = Board[i][j];
                    abstractMove(x1, y1, i, j);
                    if (turn == 1){ // black piece
                        if (id1 == 20){ // in case king moved
                            bkx = i;
                            bky = j;
                        }
                        if (king_in_check(bkx, bky)){ // revert the change if the king is in check after the mvt
                            abstractMove(i, j, x1, y1);
                            Board[i][j] = p;
                            wrong_move = true;
                        }else if (test==true){ // revert the change if it was a test
                            abstractMove(i,j,x1,y1);
                            Board[i][j]=p;
                        }else{
                            pieces[id1]->sethm();
                            setpmoved(100);
                        }
                    }else{ // chite piece
                        if (id1 == 4){ // in case king moved
                            wkx = i;
                            wky = j;
                        }
                        if (king_in_check(wkx, wky)){ // revert the change if the king is in check after the mvt
                            abstractMove(i, j, x1, y1);
                            Board[i][j] = p;
                            wrong_move = true;
                        }else if (test==true ){ // revert the change if it was a test
                            abstractMove(i, j, x1, y1);
                            Board[i][j]=p;
                        }else{
                            pieces[id1]->sethm();
                            setpmoved(100);
                        }
                    }
                }else{
                    wrong_move = true;
                }
            }else{
                wrong_move = true;
            }
        }
    }
    return (!wrong_move);
}
void Game::loadTexture(int id){
    char name = pieces[id]->getname();
    switch (name){
        case 'r':
            f[id].setTextureRect(IntRect(size*0,size*1,size,size));
            break;
        case 'n':
            f[id].setTextureRect(IntRect(size*1,size*1,size,size));
            break;
        case 'b':
            f[id].setTextureRect(IntRect(size*2,size*1,size,size));
            break;
        case 'q':
            f[id].setTextureRect(IntRect(size*3,size*1,size,size));
            break;
        case 'k':
            f[id].setTextureRect(IntRect(size*4,size*1,size,size));
            break;
        case 'p':
            f[id].setTextureRect(IntRect(size*5,size*1,size,size));
            break;
        case 'R':
            f[id].setTextureRect(IntRect(size*0,size*0,size,size));
            break;
        case 'N':
            f[id].setTextureRect(IntRect(size*1,size*0,size,size));
            break;
        case 'B':
            f[id].setTextureRect(IntRect(size*2,size*0,size,size));
            break;
        case 'Q':
            f[id].setTextureRect(IntRect(size*3,size*0,size,size));
            break;
        case 'K':
            f[id].setTextureRect(IntRect(size*4,size*0,size,size));
            break;
        case 'W':
            f[id].setTextureRect(IntRect(size*5,size*0,size,size));
            break;
        default:
            break;
    }
}
void Game::loadPosition(){ // loads texture and pieces positions from board
    int ids[32] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            int pid = Board[i][j];
            if (pid < 32){
                loadTexture(pid);
                int x = pieces[pid]->getx();
                int y = pieces[pid]->gety();
                f[pid].setPosition(size*y,size*x);
                ids[pid] = -1;
            }
        }
    }
    for (int i = 0; i <32;i++){
        if(ids[i]>0){
            f[i].setPosition(-400,-400); // remove taken pieces from the board
        }
    }
}
void Game::colorSquares(){ // sets board squares to normal color
    int k = 0;
    for(int i = 0;i <8;i++){
        for(int j = 0;j<8;j++){
            if((i+j)%2 == 0){
                squares[k].setColor(light_square_color);
            }
            if((i+j)%2 == 1){
                squares[k].setColor(dark_square_color);
            }
            k++;
        }
    }
}
void selectChoice(Game g){ // promotion choice select thread
    int size = 56;
    RenderWindow promowin(VideoMode(224, 56), "Promotion");
    Vector2i winpos = {400,150};
    promowin.setPosition(winpos);
    Texture tc,bg;
    tc.loadFromFile("images/figures.png");
    bg.loadFromFile("images/bg.png");
    bg.setRepeated(true);
    Sprite background,hover[4];
    background.setTexture(bg);
    Sprite choices[4];
    for(int i = 0; i < 4; i++){
        choices[i].setTexture(tc);
        choices[i].setTextureRect(IntRect(size*i,size*(1-g.getTurn()),size,size));
        choices[i].setPosition(size*i,0);
    }
    for(int i =0;i<4;i++){
        hover[i].setTexture(bg);
        hover[i].setPosition(size*i,0);
    }
    while (promowin.isOpen()){
        Vector2i mpos = Mouse::getPosition(promowin);
        Event e;
        while (promowin.pollEvent(e)){
            if (e.type == Event::Closed){
                continue;
            }
            if (e.type == Event::MouseButtonPressed){ // choice select
                if (e.key.code == Mouse::Left){
                    for(int i=0;i<4;i++){
                        if (choices[i].getGlobalBounds().contains(mpos.x,mpos.y)){
                            switch (i){
                                case 0:
                                    g.setpchoice('r');
                                    break;
                                case 1:
                                    g.setpchoice('n');
                                    break;
                                case 2:
                                    g.setpchoice('b');
                                    break;
                                case 3:
                                    g.setpchoice('q');

                                    break;
                                default:
                                    break;
                            }
                            promowin.close();
                        }
                    }
                }
            }
            for(int i=0;i<4;i++){ //mouse hover effect
                if (choices[i].getGlobalBounds().contains(mpos.x,mpos.y)){
                    hover[i].setColor(sf::Color(36, 186, 255));
                }else{
                    hover[i].setColor(sf::Color(255,255,255));
                }
            }
        }
        promowin.clear();
        promowin.draw(background);
        for(int i = 0;i<4;i++){
            promowin.draw(hover[i]);
            promowin.draw(choices[i]); 
        }
        promowin.display();
    }
}