#include <iostream>
#include <windows.h>
#include <ctime>
#include "Prototypes.h"
#include "Constants.h"

//Для цветного текста
#include <conio.h>
#include <stdio.h>

#define random(a,b) a+rand()%b+1-a;
using namespace std;

struct Domino {
	int Start;
	int Finish;
	string pole1;
	string pole2;
	string pole3;
};
Domino* creatBox(int domino) {
	Domino* box = new Domino[domino];
	for (int i = 0, k = 0, v = 0; i < domino; i++) {
		box[i].pole1 = "[";
		box[i].Start = k;
		box[i].pole2 = "|";
		box[i].Finish = v++;
		box[i].pole3 = "]";
		if (v == 7) {
			k++;
			v = k;
		}
	}
	return box;
}
void showPl(Domino* pl, int* ppli) {
	int const size = *ppli;
	cout << "Nomber = ";
	for (int i = 0; i < size; i++) {
		cout << i + 1 << "\t  ";
	}
	cout << endl << "\t";
	for (int i = 0; i < size; i++) {
		cout << pl[i].pole1;
		cout << pl[i].Start;
		cout << pl[i].pole2;
		cout << pl[i].Finish;
		cout << pl[i].pole3 << "\t";
	}
}
void initPole(Domino pole[15][15]) {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			pole[i][j].pole1 = "";
			pole[i][j].Start = 0;
			pole[i][j].pole2 = "";
			pole[i][j].Finish = 0;
			pole[i][j].pole3 = "";
		}
	}
}
void showPole(Domino pole[15][15]) {
	cout << "   X   "<<"\t";
	for (int i = 0; i < 15; i++) {
		if (i < 10) cout << i << "\t ";
		else cout << i << "\t";
	}
	cout << endl;
	cout << "Y\n " << "\n";
	for (int k = 0;;) {
		for (int i = 0; i < 15; i++) {
			cout << k << "\t";
			for (int j = 0; j < 15; j++) {
				if (j < 10) {
					cout << pole[i][j].pole1<<pole[i][j].Start << pole[i][j].pole2 << pole[i][j].Finish << pole[i][j].pole3 << "\t";

				}
				else cout << pole[i][j].pole1 << pole[i][j].Start << pole[i][j].pole2 << pole[i][j].Finish << pole[i][j].pole3 << "\t";
			}
			cout<< k++ << endl;
		}
		if (k = 10)break;
	}
}
void blendBox(Domino* box,int size) {
	int index = 0;
	for (int i = 0; i < size; i++)
	{
		index = random(i, size - 1);
		swap(box[i], box[index]);		
	}
}
void takeBox(Domino*& box,int* pboxi, Domino*& pl,int* ppli,int n) {
		int sizepl = *ppli + n;
		int sizebox = *pboxi - n;
		Domino* bufpl = new Domino[sizepl];
		Domino* bufbox = new Domino[sizebox];
		for (int i = 0; i < *ppli; i++) {
			bufpl[i].pole1 = pl[i].pole1;
			bufpl[i].Start = pl[i].Start;
			bufpl[i].pole2 = pl[i].pole2;
			bufpl[i].Finish = pl[i].Finish;
			bufpl[i].pole3 = pl[i].pole3;
		}
		for (int i = 0, j = *ppli; i < n; j++, i++) {
			bufpl[j].pole1 = box[i].pole1;
			bufpl[j].Start = box[i].Start;
			bufpl[j].pole2 = box[i].pole2;
			bufpl[j].Finish = box[i].Finish;
			bufpl[j].pole3 = box[i].pole3;
		}
		delete[]pl;
		pl = bufpl;
		for (int i = 0, a = n; a < *pboxi; a++, i++) {
			bufbox[i].pole1 = box[a].pole1;
			bufbox[i].Start = box[a].Start;
			bufbox[i].pole2 = box[a].pole2;
			bufbox[i].Finish = box[a].Finish;
			bufbox[i].pole3= box[a].pole3;
		}
		delete[]box;
		box = bufbox;
		*pboxi = sizebox;
		*ppli = sizepl;
	
}
void delDomino(Domino* &pl,int *ppli, int n) {
	int size = *ppli-1;
	Domino* buf = new Domino[size];
	for (int i = 0; i < n; i++) {
		buf[i] = pl[i];
	}
	for (int i = n,j=n+1; j < *ppli ;j++, i++) {
		buf[i] = pl[j];
	}
	
	delete[]pl;
	pl = buf;
	*ppli = size;

}
void hod(Domino pole[15][15], Domino*& pl,int* ppli, int n, int x, int y) {
	pole[y][x].pole1 = pl[n].pole1;
	pole[y][x].Start = pl[n].Start;
	pole[y][x].pole2 = pl[n].pole2;
	pole[y][x].Finish = pl[n].Finish;
	pole[y][x].pole3 = pl[n].pole3;
	delDomino(pl,ppli, n);
}
int proverkaHoda(Domino pole[15][15],int x,int y) {
	if (pole[y][x].pole1 == "") return 1;
	else return 0;
}
int proverkaHoda2(Domino pole[15][15], Domino*& pl,int n,int x, int y) {
	bool flag = false;
	if (pole[y + 1][x + 1].pole1 != "" || pole[y - 1][x + 1].pole1 != "" || pole[y + 1][x - 1].pole1 != "" || pole[y - 1][x - 1].pole1 != "") {
		if (pole[y][x + 1].Start == pl[n].Start || pole[y][x + 1].Start == pl[n].Finish || pole[y][x + 1].Finish == pl[n].Start || pole[y][x + 1].Finish == pl[n].Finish)flag = true;
		else if (pole[y][x - 1].Finish == pl[n].Start || pole[y][x - 1].Finish == pl[n].Finish || pole[y][x - 1].Start == pl[n].Start || pole[y][x - 1].Start == pl[n].Finish)flag = true;
		else if (pole[y+1][x].Start == pl[n].Start || pole[y+1][x].Start == pl[n].Finish || pole[y + 1][x].Finish == pl[n].Start || pole[y + 1][x].Finish == pl[n].Finish)flag = true;
		else if (pole[y-1][x].Start == pl[n].Start || pole[y-1][x].Start == pl[n].Finish || pole[y - 1][x].Finish == pl[n].Start || pole[y - 1][x].Finish == pl[n].Finish) flag=true;
		else if(flag==false)return 0;
	}
	if (pole[y][x - 1].pole1 != "") 
	{
		if (pole[y][x - 2].pole1 != "" && pole[y - 1][x - 1].pole1 == "" && pole[y + 1][x - 1].pole1 == "")
		{
			if (pole[y][x - 1].Finish == pl[n].Start || pole[y][x - 1].Finish == pl[n].Finish)
			{
				if (pole[y][x - 1].Finish == pl[n].Finish)
				{
					Domino* buf = new Domino[1];
					int i = 0;
					buf[i].Start = pl[n].Finish;
					buf[i].Finish = pl[n].Start;
					pl[n].Start = buf[i].Start;
					pl[n].Finish = buf[i].Finish;
				}
				return 2;
			}
		}
		else if (pole[y - 1][x - 1].pole1 != "")
		{
			if (pole[y][x - 1].Start == pole[y - 1][x - 1].Finish)
			{
				if (pole[y][x - 1].Finish == pl[n].Start || pole[y][x - 1].Finish == pl[n].Finish)
				{
					if (pole[y][x - 1].Finish == pl[n].Finish)
					{
						Domino* buf = new Domino[1];
						int i = 0;
						buf[i].Start = pl[n].Finish;
						buf[i].Finish = pl[n].Start;
						pl[n].Start = buf[i].Start;
						pl[n].Finish = buf[i].Finish;
					}
					return 2;
				}
			}
			else if (pole[y][x - 1].Start == pl[n].Start || pole[y][x - 1].Start == pl[n].Finish)
			{
				if (pole[y][x - 1].Start == pl[n].Start)
				{
					Domino* buf = new Domino[1];
					int i = 0;
					buf[i].Start = pl[n].Finish;
					buf[i].Finish = pl[n].Start;
					pl[n].Start = buf[i].Start;
					pl[n].Finish = buf[i].Finish;
				}
				return 2;
			}
		}
		else if (pole[y + 1][x - 1].pole1 != "" && pole[y - 1][x - 1].pole1 == "" && pole[y][x - 2].pole1 != "")return 0;
		else if (pole[y + 1][x - 1].pole1 != "" && pole[y - 1][x - 1].pole1 == "")
		{
			if (pole[y][x - 1].Start == pole[y + 1][x - 1].Finish)
			{
				if (pole[y][x - 1].Finish == pl[n].Start || pole[y][x - 1].Finish == pl[n].Finish)
				{
					if (pole[y][x - 1].Finish == pl[n].Finish)
					{
						Domino* buf = new Domino[1];
						int i = 0;
						buf[i].Start = pl[n].Finish;
						buf[i].Finish = pl[n].Start;
						pl[n].Start = buf[i].Start;
						pl[n].Finish = buf[i].Finish;
					}
					return 2;
				}
			}
			else if (pole[y][x - 1].Start == pl[n].Start || pole[y][x - 1].Start == pl[n].Finish)
			{
				if (pole[y][x - 1].Start == pl[n].Start)
				{
					Domino* buf = new Domino[1];
					int i = 0;
					buf[i].Start = pl[n].Finish;
					buf[i].Finish = pl[n].Start;
					pl[n].Start = buf[i].Start;
					pl[n].Finish = buf[i].Finish;
				}
				return 2;
			}
		}
		else if (pole[y][x - 1].pole1 != "" && pole[y][x - 2].pole1 != "" && pole[y - 1][x - 1].pole1 != "")return 0;
		else if (pole[y][x - 1].pole1 != "" && pole[y][x - 2].pole1 != "" && pole[y - 1][x + 1].pole1 != "")return 0;
		else if (pole[y][x - 1].Finish == pl[n].Start || pole[y][x - 1].Finish == pl[n].Finish) 
		{
				if (pole[y][x - 1].Finish == pl[n].Finish) 
				{
					Domino* buf = new Domino[1];
					int i = 0;
					buf[i].Start = pl[n].Finish;
					buf[i].Finish = pl[n].Start;
					pl[n].Start = buf[i].Start;
					pl[n].Finish = buf[i].Finish;
				}
		return 2;
			
		}
	}
	if (pole[y][x + 1].pole1 != "") 
	{
		if (pole[y][x + 2].pole1 != "" && pole[y+1][x +1].pole1 == "" && pole[y-1][x +1].pole1 == "")
		{
			if (pole[y][x + 1].Start == pl[n].Start || pole[y][x + 1].Start == pl[n].Finish) 
			{
				if (pole[y][x + 1].Start == pl[n].Start) 
				{
					Domino* buf = new Domino[1];
					int i = 0;
					buf[i].Start = pl[n].Finish;
					buf[i].Finish = pl[n].Start;
					pl[n].Start = buf[i].Start;
					pl[n].Finish = buf[i].Finish;
				}
			return 2;
			}
		}
		else if (pole[y - 1][x + 1].pole1 != "" && pole[y + 1][x + 1].pole1 == "" && pole[y][x + 2].pole1 == "")
		{
				if (pole[y - 1][x + 1].Finish == pole[y][x + 1].Start) 
				{
					if (pole[y][x + 1].Start == pl[n].Start || pole[y][x + 1].Start == pl[n].Finish) 
					{
						if (pole[y][x + 1].Finish == pl[n].Finish) 
						{
							Domino* buf = new Domino[1];
							int i = 0;
							buf[i].Start = pl[n].Finish;
							buf[i].Finish = pl[n].Start;
							pl[n].Start = buf[i].Start;
							pl[n].Finish = buf[i].Finish;
						}
						return 2;
					}
				}
				else if (pole[y][x + 1].Start == pl[n].Start || pole[y][x + 1].Start == pl[n].Finish) 
				{
						if (pole[y][x + 1].Start == pl[n].Start) 
						{
							Domino* buf = new Domino[1];
							int i = 0;
							buf[i].Start = pl[n].Finish;
							buf[i].Finish = pl[n].Start;
							pl[n].Start = buf[i].Start;
							pl[n].Finish = buf[i].Finish;
						}
						return 2;
				}
		}
		else if(pole[y+1][x+1].pole1 != "" && pole[y - 1][x + 1].pole1 == "" && pole[y][x + 1].pole1 != "" && pole[y][x+2].pole1 == "")
		{
				if (pole[y][x + 1].Start == pl[n].Start || pole[y][x + 1].Start == pl[n].Finish) 
				{
					if (pole[y][x + 1].Start == pl[n].Start) 
					{
						Domino* buf = new Domino[1];
						int i = 0;
						buf[i].Start = pl[n].Finish;
						buf[i].Finish = pl[n].Start;
						pl[n].Start = buf[i].Start;
						pl[n].Finish = buf[i].Finish;
					}
				return 2;
				}
		}
		else if (pole[y][x + 1].pole1 != "" && pole[y+1][x+1].pole1 == "" && pole[y-1][x + 1].pole1 == "")
		{
			if(pole[y][x + 1].Start == pl[n].Start || pole[y][x + 1].Start == pl[n].Finish)
			{
				if (pole[y][x + 1].Start == pl[n].Start)
				{
				Domino* buf = new Domino[1];
				int i = 0;
				buf[i].Start = pl[n].Finish;
				buf[i].Finish = pl[n].Start;
				pl[n].Start = buf[i].Start;
				pl[n].Finish = buf[i].Finish;
				}
			return 2;
			}
		}
	}
	if (pole[y - 1][x].pole1 != "") 
	{
		if (pole[y - 1][x].pole1 != "" && pole[y - 2][x].pole1 == "" && pole[y][x - 1].pole1 == "" && pole[y][x + 1].pole1 == "") {
			if (pole[y - 1][x].Finish == pl[n].Start || pole[y - 1][x].Finish == pl[n].Finish || pole[y - 1][x].Start == pl[n].Start || pole[y - 1][x].Start == pl[n].Finish)
			{
				if (pole[y - 1][x].Finish == pl[n].Finish)
				{
					Domino* buf = new Domino[1];
					int i = 0;
					buf[i].Start = pl[n].Finish;
					buf[i].Finish = pl[n].Start;
					pl[n].Start = buf[i].Start;
					pl[n].Finish = buf[i].Finish;
				}
				return 2;
			}
		}
		if (pole[y - 2][x].pole1 != "" && pole[y - 1][x+1].pole1 == "")
		{
			if (pole[y - 2][x].pole1 !="" && pole[y - 1][x-1].pole1 =="" && pole[y - 1][x + 1].pole1 == "") {
				if (pole[y - 2][x].Finish == pole[y - 1][x].Start)
				{
					if (pole[y - 1][x].Finish == pl[n].Start || pole[y - 1][x].Finish == pl[n].Finish)
					{
						if (pole[y - 1][x].Finish == pl[n].Finish)
						{
							Domino* buf = new Domino[1];
							int i = 0;
							buf[i].Start = pl[n].Finish;
							buf[i].Finish = pl[n].Start;
							pl[n].Start = buf[i].Start;
							pl[n].Finish = buf[i].Finish;
						}
						return 2;
					}
				}
				else if (pole[y - 1][x].Start == pl[n].Start || pole[y - 1][x].Start == pl[n].Finish)
				{
					if (pole[y - 1][x].Start == pl[n].Start)
					{
						Domino* buf = new Domino[1];
						int i = 0;
						buf[i].Start = pl[n].Finish;
						buf[i].Finish = pl[n].Start;
						pl[n].Start = buf[i].Start;
						pl[n].Finish = buf[i].Finish;
					}
					return 2;
				}
			}
			else if (pole[y - 1][x].Start == pl[n].Start || pole[y - 1][x].Start == pl[n].Finish)
			{
				if (pole[y - 1][x].Start == pl[n].Start)
				{
					Domino* buf = new Domino[1];
					int i = 0;
					buf[i].Start = pl[n].Finish;
					buf[i].Finish = pl[n].Start;
					pl[n].Start = buf[i].Start;
					pl[n].Finish = buf[i].Finish;
				}
				return 2;
			}
		}
		else if (pole[y - 1][x - 1].pole1 != "" && pole[y - 1][x + 1].pole1 == "" && pole[y - 2][x].pole1 == "")
		{
			if (pole[y - 1][x].Finish == pl[n].Start || pole[y - 1][x].Finish == pl[n].Finish)
			{
				if (pole[y - 1][x].Finish == pl[n].Finish)
				{
					Domino* buf = new Domino[1];
					int i = 0;
					buf[i].Start = pl[n].Finish;
					buf[i].Finish = pl[n].Start;
					pl[n].Start = buf[i].Start;
					pl[n].Finish = buf[i].Finish;
				}
				return 2;
			}
		}
		else if (pole[y - 1][x - 1].pole1 == "" && pole[y - 1][x + 1].pole1 != "" && pole[y - 2][x].pole1 == "")
		{
			if (pole[y - 1][x].Start == pl[n].Start || pole[y - 1][x].Start == pl[n].Finish)
			{
				if (pole[y - 1][x].Start == pl[n].Start)
				{
					Domino* buf = new Domino[1];
					int i = 0;
					buf[i].Start = pl[n].Finish;
					buf[i].Finish = pl[n].Start;
					pl[n].Start = buf[i].Start;
					pl[n].Finish = buf[i].Finish;
				}
				return 2;
			}
		}
		else if (pole[y - 1][x].pole1 != "" && pole[y - 1][x - 1].pole1 != "" && pole[y - 1][x + 1].pole1 != "") return 0;
		else if (pole[y - 1][x].pole1 != "" && pole[y - 1][x - 1].pole1 != "" && pole[y - 2][x].pole1 == ""){
			if (pole[y - 1][x].Finish == pl[n].Start || pole[y - 1][x].Finish == pl[n].Finish || pole[y - 1][x].Start == pl[n].Start || pole[y - 1][x].Start == pl[n].Finish)
			{
				if (pole[y - 1][x].Finish == pl[n].Finish)
				{
					Domino* buf = new Domino[1];
					int i = 0;
					buf[i].Start = pl[n].Finish;
					buf[i].Finish = pl[n].Start;
					pl[n].Start = buf[i].Start;
					pl[n].Finish = buf[i].Finish;
				}
				return 2;
			}
		}
	}
	if (pole[y + 1][x].pole1 != "") 
	{
		if (pole[y + 2][x].pole1 != "" && pole[y + 1][x + 1].pole1 == "" && pole[y + 1][x-1].pole1 == "")
		{
			if (pole[y + 2][x].Start == pole[y + 1][x].Finish && pole[y + 1][x + 1].pole1 == "" && pole[y + 1][x - 1].pole1 == "")
			{
				if (pole[y + 1][x].Start == pl[n].Start || pole[y + 1][x].Start == pl[n].Finish)
				{
					if (pole[y + 1][x].Start == pl[n].Start)
					{
						Domino* buf = new Domino[1];
						int i = 0;
						buf[i].Start = pl[n].Finish;
						buf[i].Finish = pl[n].Start;
						pl[n].Start = buf[i].Start;
						pl[n].Finish = buf[i].Finish;
					}
					return 2;
				}
			}
			else if (pole[y + 1][x].Finish == pl[n].Start || pole[y + 1][x].Finish == pl[n].Finish)
			{
				if (pole[y + 1][x].Finish == pl[n].Finish)
				{
					Domino* buf = new Domino[1];
					int i = 0;
					buf[i].Start = pl[n].Finish;
					buf[i].Finish = pl[n].Start;
					pl[n].Start = buf[i].Start;
					pl[n].Finish = buf[i].Finish;
				}
				return 2;
			}
		}
		else if (pole[y + 1][x - 1].pole1 != "" && pole[y + 1][x + 1].pole1 == "" && pole[y + 2][x].pole1 == "")
		{
			if (pole[y + 1][x].Finish == pl[n].Start || pole[y + 1][x].Finish == pl[n].Finish)
			{
				if (pole[y + 1][x].Finish == pl[n].Finish)
				{
					Domino* buf = new Domino[1];
					int i = 0;
					buf[i].Start = pl[n].Finish;
					buf[i].Finish = pl[n].Start;
					pl[n].Start = buf[i].Start;
					pl[n].Finish = buf[i].Finish;
				}
				return 2;
			}
		}
		else if (pole[y + 1][x].pole1 != "" && pole[y + 1][x - 1].pole1 != "" && pole[y+2][x].pole1 != "") return 0;
		else if (pole[y + 1][x].pole1 != "" && pole[y + 1][x - 1].pole1 != "" && pole[y + 1][x + 1].pole1 != "") return 0;
		else if (pole[y + 1][x - 1].pole1 == "" && pole[y + 1][x + 1].pole1 != "" && pole[y + 2][x].pole1 != "")return 0;
		{
			if (pole[y + 1][x].Start == pl[n].Start || pole[y + 1][x].Start == pl[n].Finish) 
			{
				if (pole[y + 1][x].Start == pl[n].Start) 
				{
					Domino* buf = new Domino[1];
					int i = 0;
					buf[i].Start = pl[n].Finish;
					buf[i].Finish = pl[n].Start;
					pl[n].Start = buf[i].Start;
					pl[n].Finish = buf[i].Finish;
				}
				return 2;
			}
		}
	}

	return 0;
}
int whoIsFirst(Domino* &pl1,int*ppli1,Domino* &pl2,int*ppli2) {
	int mini1 = pl1[0].Start;
	int mini2 = pl2[0].Start;
	for (int i = 0; i < *ppli1; i++) {
		if (pl1[i].Start == pl1[i].Finish) {
			if (pl1[i].Start < mini1)mini1 = pl1[i].Start;
		}
	}
	for (int i = 0; i < *ppli2; i++) {
		if (pl2[i].Start == pl2[i].Finish) {
			if (pl2[i].Start < mini2)mini2 = pl2[i].Start;
		}
	}
	if (mini1 < mini2)return 1;
	else return 2;
}
int coutPl1(Domino pole[15][15], Domino*& pl1, int* ppli1, Domino*& box, int* pboxi, bool flag,int& i2) {
	int x, y, n;
	int p = 0;
	int u = 0;
	for (; p == 0;) {
		system("cls");
		showPole(pole);
		cout << endl << endl << endl << endl;
		cout << "Player1 : " << endl;
		showPl(pl1, ppli1);
		cout << endl << endl << endl << endl;
		cout << "Bazar, input 100" << endl << endl;
		cout << "Input Number Domino Pl1= ";
		cin >> n;
		if (n <= 0 || n > *ppli1 && n != 100) {
			cout << "Wrong number!!\n Please repet!\nTo continue press enter any number!";
			cin >> n;
			continue;
		}
		else if (n == 100) {
			if (u == 3) {
				cout << "You skip a trun. Sorry...\nTo continue press enter any number!";
				cin >> n;
				break;
			}
			u++;
			if (*pboxi == 0) {
				cout << "Domino are over. =( \nTo continue press enter any number!";
				cin >> n;
				break;
			}
			else {
				takeBox(box, pboxi, pl1, ppli1, 1);
				continue;
			}
		}
		cout << "Input cor.X Pl1= ";
		cin >> x;
		if (x < 0 || x >= 15) {
			cout << "Wrong number!!\n Please repet!\nTo continue press enter any number!";
			cin >> x;
			continue;
		}
		else {
			cout << "Input cor.Y Pl1= ";
			cin >> y;
		}
		if (y < 0 || y >= 15) {
			cout << "Wrong number!!\n Please repet!\nTo continue press enter any number!";
			cin >> y;
			continue;
		}
		if (x > 0 && x < 15 && y>0 && y < 15);
		int i = proverkaHoda(pole, x, y);
		if (i == 1) i = proverkaHoda2(pole, pl1, n - 1, x, y);
		if (i2 != 0 && i==0) {
				p = 0;
				cout << "No move possibe\nPlease repet!\nTo continue press enter any number!";
				cin >> n;
				continue;
			
		}
		if (i == 2 || i2 == 0) {
			hod(pole, pl1, ppli1, n - 1, x, y);
			p = 1;
			
		}
	}
	if (*ppli1 == 0)return 1;
	else return 2;
}
int coutPl2(Domino pole[15][15], Domino*& pl2, int* ppli2, Domino*& box, int* pboxi, bool flag) 
{
	int x2, y2, n2;
	int p = 0;
	int u = 0;
	for (; p == 0;) {
		system("cls");
		showPole(pole);
		cout << endl << endl << endl << endl;
		cout << "Player2 : " << endl;
		showPl(pl2, ppli2);
		cout << endl << endl << endl << endl;
		cout << "Bazar, imput 100" << endl << endl;
		cout << "Imput Nomber Domino Pl2= ";
		cin >> n2;
		if (n2 <= 0 || n2 > *ppli2 && n2 != 100) {
			cout << "Wrong number!!\n Please repet!\nTo continue press enter any number!";
			cin >> n2;
			continue;
		}
		else if (n2 == 100)
		{
			if (u == 3) {
				cout << "You skip a trun. Sorry...\nTo continue press enter any number!";
				cin >> n2;
				break;
			}
			u++;
			if (*pboxi == 0) {
				cout << "Domino are over. =( \nTo continue press enter any number!";
				cin >> n2;
				continue;
			}
			else {
				takeBox(box, pboxi, pl2, ppli2, 1);
				continue;
			}
		}
		cout << "Input cor.X Pl2= ";
		cin >> x2;
		if (x2 < 0 || x2 >= 15) {
			cout << "Wrong number!!\n Please repet!\nTo continue press enter any number!";
			cin >> x2;
			continue;
		}
		else {
			cout << "Input cor.Y Pl2= ";
			cin >> y2;
		}
		if (y2 < 0 || y2 >= 15) {
			cout << "Wrong number!!\n Please repet!\nTo continue press enter any number!";
			cin >> y2;
			continue;
		}
		else if (x2 > 0 && x2 < 15 && y2>0 && y2 < 15);
		int i = proverkaHoda(pole, x2, y2);
		if (i == 1) i = proverkaHoda2(pole, pl2, n2 - 1, x2, y2);
		if (i == 0) {
			p = 0;
			cout << "No move possibe\nPlease repet!\nTo continue press enter any number!";
			cin >> n2;
			continue;
		}
		if (i == 2) {
			hod(pole, pl2, ppli2, n2 - 1, x2, y2);
			p = 1;
			
		}
	}
	if (*ppli2 == 0)return 0;
	else return 2;
}

int main()
{
	srand(time(NULL));
	sizeWindow(WIDTH, HIGHT, TOP, LEFT);
	menu(xb, yb);
	int domino = 28;
	Domino* box = creatBox(domino);
	int boxi = 28;
	int* pboxi = &boxi;
	blendBox(box,28);
	Domino pole[15][15];
	Domino* pl1 = new Domino[7];
	int pli1 = 0;
	int* ppli1 = &pli1;
	Domino* pl2 = new Domino[7];
	int pli2 = 0;
	int* ppli2 = &pli2;
	takeBox(box,pboxi, pl1,ppli1,7);
	takeBox(box,pboxi, pl2,ppli2,7);
	//-0 - выиграл игрок №1
	//-1 - выиграл игрок №2
	//-2 - идет игра
	//-3 - Ничья
	initPole(pole);
	int status = 2;
	bool flag=true;
	int i = 0;
	int w = whoIsFirst(pl1, ppli1, pl2, ppli2);
	if (w == 2)swap(pl1, pl2);
	int qw = 2;
	for (; status == 2;) {
		if(flag==true)
		{
			status = coutPl1(pole,pl1,ppli1,box,pboxi,flag,i);
			flag = false;
			if (status == 0)	break;
		}
		else 
		{
			status = coutPl2(pole, pl2, ppli2, box, pboxi, flag);
			flag = true;
			if (status == 1) break;
		}
		i++;
		if (i == 50) {
			status == 3;
			break;
		}
	}
	if (status == 0) {
		system("cls");
		gotoxy(64, 13);
		cout << "Player number 1 WINNER!!!";
		gotoxy(64, 15);
		cout << "Enter any number to exit";
		cin >> qw;
	}
	else if (status == 1) {
		system("cls");
		gotoxy(64, 13);
		cout << "Player number 2 WINNER!!!";
		gotoxy(64, 15);
		cout << "Enter any number to exit";
		cin >> qw;
	}
	else {
		system("cls");
		gotoxy(73, 13);
		cout << "DRAW!!!";
		gotoxy(64, 14);
		cout << "Enter any number to exit";
		cin >> qw;
	}
}

	
