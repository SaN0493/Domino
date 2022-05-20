//Присвоение тексту нужного цвета
void setColour(int text);

//Размещение в координатах
void gotoxy(int x, int y);

//Размещение в координатах c цветом
void gotoxy(int x, int y, int color);

//Menu
void rules();
//void newGame();
int menu(int x, int y);
void blackMenu();
void sizeWindow(int width, int hight, int top, int left);

struct Domino;
Domino* creatBox(int domino);
void showPl(Domino* pl, int* ppli);
void initPole(Domino pole[15][15]);
void showPole(Domino pole[15][15]);
void blendBox(Domino* box, int size);
void takeBox(Domino*& box, int* pboxi, Domino*& pl, int* ppli, int n = 1);
void delDomino(Domino* &pl, int* ppli, int n);
void hod(Domino pole[15][15], Domino*& pl, int* ppli, int n, int x, int y);
int proverkaHoda(Domino pole[15][15], int x, int y);
int proverkaHoda2(Domino pole[15][15], Domino*& pl, int n, int x, int y);
int whoIsFirst(Domino*& pl1, int* ppli1, Domino*& pl2, int* ppli2);
int coutPl1(Domino pole[15][15], Domino*& pl1, int* ppli1, Domino*& box, int* pboxi, bool flag,int& i2);
int coutPl2(Domino pole[15][15], Domino*& pl2, int* ppli2, Domino*& box, int* pboxi, bool flag);