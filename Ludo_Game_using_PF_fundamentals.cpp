//SYED SHAYAAN HASNAIN AHMAD
//20I-0647
//SECTION Z
//FINAL PROJECT LUDO GAME

#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include<string>
using namespace std;

//FUNCTION PROTOTYPES

enum color { green = 1, blue = 2, red = 3, purple = 4 }; //ASSIGNING COLOURS 
void gotoRowCol(int rpos, int cpos);                     //GO TO CERTAIN ROW AND COLUMN
void PrintHollowBox(int sr, int sc, int rdim, int cdim, char s, int c);  //USED FOR GRID PRINTING
void PrintGrid(int Rows, int cols, int d, int rdim, int cdim, char s, int dv,char P1[15],char P2[15],char P3[15],char P4[15]); //GRID PRINTING 
void PrintBox(int sr, int sc, int rdim, int cdim, char s, int c);   //TO DISPLAY LUDO BOARD BOX
void colour(int k);   //USED FOR DIFFERENT COLOURS
void changeturn(int Nop, color& turn);   //USED FOR CHANGING TURNS
bool Ishome(int**& BB, int sx, int sy, int dx, int dy, int dv, int turn);  //USED IN ISWIN FUNCTION
void Iskill(int**& B, char**& C, color& turn, int sx, int sy, int dx, int dy);  //CHECK IF ANY PEICE IS KILLED OR NOT

void getRowColbyLeftClick(int& rpos, int& cpos)    //RETURNS ROW AND COLUMN INDEX OF WHATEVER IS SELECTED ON THE BOARD  //MOUSE CLICK FUNCTION USED HERE FOR MOVING PEICE
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void PrintGrid(int Rows, int cols, int d, int rdim, int cdim, char s, int dv,char P1[15],char P2[15],char P3[15],char P4[15],int Nop)
{
	rdim = Rows / d;
	cdim = cols / d;
	for (int r = 0; r < d; r++)
	{
		for (int c = 0; c < d; c++)
		{
			int sr = r * rdim, sc = c * cdim;

			if ((c < 6 && r < 6) || (c < 6 && c > 0 && r == 7) || (c == 1 && r == 6) || (c == 2 && r == 8))
				PrintBox(sr, sc, rdim, cdim, s, 10);//GREEN BOX
			if (c > 8 && r < 6 || (c == 7 && r > 0 && r < 6) || (c == 6 && r == 2) || (c == 8 && r == 1))
				PrintBox(sr, sc, rdim, cdim, s, 9);//BLUE BOX
			if (c < 6 && r > 8 || (c == 7 && r >= 6 && r < 14) || (c == 6 && r == 13) || (c == 8 && r == 12))
				PrintBox(sr, sc, rdim, cdim, s, 5);//PURPLE BOX
			if (c > 8 && (r > 8) || (c >= 9 && c < 14 && r == 7) || (c == 12 && r == 6) || (c == 13 && r == 8))
				PrintBox(sr, sc, rdim, cdim, s, 4);//RED BOX
			if ((c >= 6 && c < 9) || (r >= 6 && r < 9))
				PrintHollowBox(sr, sc, rdim, cdim, s, 15);//WHITE BOX
			if ((c >= 6 && c < 9) && (r >= 6 && r < 9))
				PrintBox(sr, sc, rdim, cdim, s, 0);//BLACK BOX
		}
	}
	int i = 0;
	char j = 'p';
	PrintHollowBox(35, 35, 5, 5, -37, 15);  //USED FOR PRINTING HOLLOW BOX
	gotoRowCol(37, 37);
	cout << dv;
	gotoRowCol(2, 80);
	if (Nop == 2 || Nop == 3 || Nop == 4)
	{
		cout << "Player 1  is: ";
		while (j != '.')
		{
			cout << P1[i];
			j = P1[i];
			i++;
		}
	}
	if (Nop == 2 || Nop == 3 || Nop == 4)
	{
		gotoRowCol(4, 80);
		cout << "Player 2  is: ";
		i = 0;
		j = 'p';
		while (j != '.')
		{
			cout << P2[i];
			j = P2[i];
			i++;
		}
	}
	if (Nop == 3 || Nop == 4)
	{
		gotoRowCol(6, 80);
		cout << "Player 3  is: ";
		i = 0;
		j = 'p';
		while (j != '.')
		{
			cout << P3[i];
			j = P3[i];
			i++;
		}
	}
	if (Nop == 4)
	{
		gotoRowCol(8, 80);
		cout << "Player 4  is: ";
		i = 0;
		j = 'p';
		while (j != '.')
		{
			cout << P4[i];
			j = P4[i];
			i++;
		}
	}
	
}
void PrintBox(int sr, int sc, int rdim, int cdim, char s, int c)
{
	colour(c);
	for (int r = 0; r < rdim; r++)
	{
		for (int c = 0; c < cdim; c++)
		{
			if (r == 0 || r == rdim - 1)
			{
				gotoRowCol(sr + r, sc + c);
				cout << s;
			}
			else if (c == 0 || c == cdim - 1)
			{
				gotoRowCol(sr + r, sc + c);
				cout << s;
			}
			else
			{
				gotoRowCol(sr + r, sc + c);
				cout << s;
			}
		}
	}
}
void PrintHollowBox(int sr, int sc, int rdim, int cdim, char s, int c)
{
	colour(c);
	for (int r = 0; r < rdim; r++)
	{
		for (int c = 0; c < cdim; c++)
		{
			if (r == 0 || r == rdim - 1)
			{
				gotoRowCol(sr + r, sc + c);
				cout << s;
			}
			else if (c == 0 || c == cdim - 1)
			{
				gotoRowCol(sr + r, sc + c);
				cout << s;
			}
		}
	}
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void colour(int k)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
}
void PrintNumberInBox(int sr, int sc, int rdim, int cdim, int s)
{
	gotoRowCol(sr + rdim / 2, sc + cdim / 2);
	if (s > 0 && s < 1000)
		cout << s;
}
void BoxNumbertosrsc(int n, int d, int& sr, int& sc, int rdim, int cdim)
{
	sr = ((n - 1) / d) * rdim;
	sc = ((n - 1) % d) * cdim;

}
void Displaymarkedlocations(int sri, int sci, int rdim, int cdim, int**& BB)
{
	int i = 1;
	for (int ri = 0; ri < 15; ri++)
	{
		for (int ci = 0; ci < 15; ci++)
		{
			BoxNumbertosrsc(i++, 15, sri, sci, rdim, cdim);
			PrintNumberInBox(sri, sci, rdim, cdim, BB[ri][ci]);
		}
	}
}
void backendboard(int**& BB)
{
	int a = 0, b = 18, d = 32, e = 51, f = 12, g = 45, h = 12, i = 31
		, t = 200, s = 406, p = 100, q = 306;
	for (int r = 0; r < 15; r++)
	{
		for (int c = 0; c < 15; c++)
		{
			if (r == 6)
			{
				if (c > 8)
					BB[r][c] = b += 1;
				else if (c > 0 && c < 6)
					BB[r][c] = a += 1;
			}
			else if (r == 7)
			{
				if (c > 8 && c < 14)
					BB[r][c] = q -= 1;
				else if (c > 0 && c < 6)
					BB[r][c] = p += 1;
			}
			else if (r == 8)
			{
				if (c < 6)
					BB[r][c] = e -= 1;
				else if (c > 8)
					BB[r][c] = d -= 1;
			}
			else if (c == 6)
			{
				if (r < 6)
					BB[r][c] = f -= 1;
				else if (r > 8)
					BB[r][c] = g -= 1;
			}
			else if (c == 7)
			{
				if (r > 0 && r < 6)
					BB[r][c] = t += 1;
				else if (r > 8 && r < 14)
					BB[r][c] = s -= 1;
			}
			else if (c == 8)
			{
				if (r < 6)
					BB[r][c] = h += 1;
				else if (r > 8)
					BB[r][c] = i += 1;
			}
			BB[0][7] = 12;
			BB[7][14] = 25;
			BB[14][7] = 38;
			BB[7][0] = 51;
			BB[6][0] = 52;
		}
	}
}
void DrawP(int r, int c, char a, int k)
{
	colour(k);
	r = r * 5;
	c = c * 5;
	gotoRowCol(r + 2, c + 2);
	cout << a;
	gotoRowCol(r + 2, c + 1);
	cout << a;
	gotoRowCol(r + 1, c + 2);
	cout << a;
	gotoRowCol(r + 1, c + 1);
	cout << a;
	gotoRowCol(r + 3, c + 3);
	cout << a;
}
void Init(int Nop, char**& C, color turn)
{
	for (int ri = 0; ri < 15; ri++)
	{
		for (int ci = 0; ci < 15; ci++)
		{
			if (Nop == 4)
			{
				if ((ri == 1 || ri == 3) && (ci == 1 || ci == 3))
				{  //DARKGREEN GOTI
					DrawP(ri, ci, -37, 2);
					C[ri][ci] = '*';
				}
				else if ((ri == 1 || ri == 3) && (ci == 10 || ci == 12))
				{
					//DARK BLUE GOTI
					DrawP(ri, ci, -37, 1);
					C[ri][ci] = '$';
				}
				else if ((ri == 10 || ri == 13) && (ci == 1 || ci == 3))
				{
					//LIGHT RED GOTI
					DrawP(ri, ci, -37, 12);
					C[ri][ci] = '@';
				}
				else if ((ri == 10 || ri == 13) && (ci == 10 || ci == 13))
				{
					//YELLOW GOTI
					DrawP(ri, ci, -37, 6);
					C[ri][ci] = '#';
				}
			}
			else if (Nop == 3)
			{
				if ((ri == 1 || ri == 3) && (ci == 1 || ci == 3))
				{ //DARK GREEN 
					DrawP(ri, ci, -37, 2);
					C[ri][ci] = '*';
				}
				else if ((ri == 1 || ri == 3) && (ci == 10 || ci == 12))
				{
					//DARK BLUE 
					DrawP(ri, ci, -37, 1);
					C[ri][ci] = '$';
				}
				else if ((ri == 10 || ri == 13) && (ci == 1 || ci == 3))
				{
					//YELLOW 
					DrawP(ri, ci, -37, 12);
					C[ri][ci] = '@';
				}
			}
			else if (Nop == 2)
			{
				if ((ri == 1 || ri == 3) && (ci == 1 || ci == 3))
				{ //DARK GREEN 
					DrawP(ri, ci, -37, 2);
					C[ri][ci] = '*';
				}
				else if ((ri == 10 || ri == 13) && (ci == 10 || ci == 13))
				{
					//LIGHT RED 
					DrawP(ri, ci, -37, 12);
					C[ri][ci] = '#';
				}
			}
		}
	}
	colour(0);
}
void Selection(int& r, int& c)
{
	int q, w;
	bool ch = false;
	do
	{
		gotoRowCol(80, 0);
		cout << "\nPlease select the piece";
		getRowColbyLeftClick(q, w);
		r = q;
		c = w;

		for (int ri = 0; ri < 75; ri += 5)
		{
			for (int ci = 0; ci < 75; ci += 5)
			{
				if ((r >= ri && r <= ri + 5) && (c >= ci && c <= ci + 5))
				{
					ch = true;
					r = ri / 5;
					c = ci / 5;
				}
			}
		}
		if (!ch)
			cout << "\nInvalid Coordinate Select Agian!!!";
	} while (ch == false);
}
void Destination(int& r, int& c)
{
	int er, ec;
	bool ch = false;
	do
	{
		gotoRowCol(84, 0);
		cout << "\nPlease Select Destination";
		getRowColbyLeftClick(er, ec);
		r = er;
		c = ec;

		for (int ri = 0; ri < 75; ri += 5)
		{
			for (int ci = 0; ci < 75; ci += 5)
			{
				if ((r >= ri && r <= ri + 5) && (c >= ci && c <= ci + 5))
				{
					ch = true;
					r = ri / 5;
					c = ci / 5;
				}
			}
		}
		if (!ch)
			cout << "\nInvalid Coordinate Select Agian!!!";
	} while (ch == false);
}
void displayplayermsg(color &turn)
{
	if (turn == green)
	{
		PrintBox(30, 85, 10, 10, -37, 10);  //GREEN 
	}
	else if (turn == blue)
	{
		PrintBox(30, 85, 10, 10, -37, 9);  //BLUE
	}
	else if (turn == red)
	{
		PrintBox(30, 85, 10, 10, -37, 4);  //RED
	}
	else if (turn == purple)
	{
		PrintBox(30, 85, 10, 10, -37, 5);  //PURPLE
	}
}
void Move(int& sx, int& sy, int& dx, int& dy, int**& B, color turn, char**& C)
{
	if (turn == green)
	{
		DrawP(dx, dy, -37, 2);
		C[dx][dy] = '*';
		if ((sx < 6 && sy < 6) || (sx == 6 && sy == 1) || (sx == 8 && sy == 2))
			DrawP(sx, sy, -37, 10);
		else
			DrawP(sx, sy, -37, 0);
		C[sx][sy] = ' ';
	}
	else if (turn == blue)
	{
		DrawP(dx, dy, -37, 1);
		C[dx][dy] = '$';
		if ((sx < 6 && sy > 8) || (sx == 1 && sy == 8) || (sx == 2 && sy == 6))
			DrawP(sx, sy, -37, 9);
		else
			DrawP(sx, sy, -37, 0);
		C[sx][sy] = ' ';
	}
	else if (turn == purple)
	{
		DrawP(dx, dy, -37, 12);
		C[dx][dy] = '@';
		if ((sx > 8 && sy < 6) || (sx == 13 && sy == 7) || (sx == 12 && sy == 9))
			DrawP(sx, sy, -37, 5);
		else
			DrawP(sx, sy, -37, 0);
		C[sx][sy] = ' ';
	}
	else if (turn == red)
	{
		DrawP(dx, dy, -37, 6);
		C[dx][dy] = '#';
		if ((sx > 8 && sy > 8) || (sx == 6 && sy == 12) || (sx == 8 && sy == 13))
			DrawP(sx, sy, -37, 4);
		else
			DrawP(sx, sy, -37, 0);
		C[sx][sy] = ' ';
	}
}
void clstext()
{
	colour(0);
	gotoRowCol(75, 0);
	for (int r = 0; r < 11; r++)
	{
		for (int c = 0; c < 75; c++)
		{
			cout << " ";
		}
		cout << endl;
	}
}
int DiceRoll(int dv)
{
	srand(time(0));
	int sri, sci;
	do {
		getRowColbyLeftClick(sri, sci);
		if (sri > 44 && sri < 52 && sci > 79 && sci < 86)
		{
			do
			{
				gotoRowCol(77, 0);
				cout << "Enter dice value: ";
				cin >> dv;
			} while (dv > 90);
			gotoRowCol(78, 0);
			cout << "You got a: " << dv;
			return dv;
		}
		else if (sri >= 33 && sri <= 37 && sci >= 33 && sci <= 37)
		{
			for (int i = 0; i < 25; i++)
			{
				dv = rand() % 6 + 1;
				gotoRowCol(37, 37);
				cout << dv;
				Sleep(100);
			}
			gotoRowCol(78, 0);
			cout << "You got a: " << dv;
			return dv;
		}
		else
			continue;

	} while (true);
}
bool IsValidSelection(int dv, int sx, int sy, int**& B, color& turn, char**& C, int Nop)
{
	if (dv == 6)
	{
		if (turn == green && (sx == 1 || sx == 3) && (sy == 1 || sy == 3))
			return true;
		else if (turn == blue && (sx == 1 || sx == 3) && (sy == 10 || sy == 12))
			return true;
		else if (turn == red && (sx == 10 || sx == 13) && (sy == 10 || sy == 13))
			return true;
		else if (turn == purple && (sx == 10 || sx == 13) && (sy == 1 || sy == 3))
			return true;

	}
	else if ((turn == green && (sx == 1 || sx == 3) && (sy == 1 || sy == 3)) ||
		(turn == blue && (sx == 1 || sx == 3) && (sy == 10 || sy == 12)) ||
		(turn == red && (sx == 10 || sx == 13) && (sy == 10 || sy == 13)) ||
		(turn == purple && (sx == 10 || sx == 13) && (sy == 1 || sy == 3)))
	{
		gotoRowCol(82, 0);
		cout << "You need a 6 to open Goti";
		changeturn(Nop, turn);
		Sleep(2000);
		return false;
	}
	else if (turn == green && C[sx][sy] == '*')
		return true;
	else if (turn == blue && C[sx][sy] == '$')
		return true;
	else if (turn == purple && C[sx][sy] == '@')
		return true;
	else if (turn == red && C[sx][sy] == '#')
		return true;
	else if (sx > 14 || sy > 14 || sx < 0 || sy < 0)
	{
		cout << "\nINVALID SELECTION. IT IS OUT OF RANGE!!!\n ";
		return false;
	}
	else
	{
		cout << "\nINVALID SELECTION!!!\n ";
		return false;
	}
}
bool IsValidDestination(int dv, int sx, int sy, int dx, int dy, int**& B, color& turn, char**& C, int*& homecount, int h_k_b, int h_k_g, int h_k_p, int h_k_r)
{
	int a;
	a = B[sx][sy] + dv;
	if (a > 52)
	{
		a = a - 52;
	}
	if ((dv == 6) && ((turn == green && dx == 6 && dy == 1) || (turn == blue && dx == 1 && dy == 8)
		|| (turn == red && dx == 8 && dy == 13) || (turn == purple && dx == 13 && dy == 6)))
		return true;
	else if (Ishome(B, sx, sy, dx, dy, dv, turn) == true)
	{
		homecount[turn]++;
		return true;
	}
	else if (B[dx][dy] == a)
	{
		if (C[dx][dy] != ' ' && turn == green && C[dx][dy] != '*')//something left
		{
			Iskill(B, C, turn, sx, sy, dx, dy);
			C[sx][sy] = ' ';
			h_k_g = true;
			return true;
		}
		else if (C[dx][dy] != ' ' && turn == blue && C[dx][dy] != '$')//something left
		{
			Iskill(B, C, turn, sx, sy, dx, dy);
			C[sx][sy] = ' ';
			h_k_b = true;
			return true;
		}
		else if (C[dx][dy] != ' ' && turn == purple && C[dx][dy] != '@')//something left
		{
			Iskill(B, C, turn, sx, sy, dx, dy);
			C[sx][sy] = ' ';
			h_k_p = true;
			return true;
		}
		else if (C[dx][dy] != ' ' && turn == red && C[dx][dy] != '#')//something left
		{
			Iskill(B, C, turn, sx, sy, dx, dy);
			C[sx][sy] = ' ';
			h_k_r = true;
			return true;
		}
		return false;
	}
	else
	{
		gotoRowCol(82, 0);
		cout << "Invalid move";
		return false;
	}
}
void changeturn(int Nop, color& turn)
{
	if (Nop == 4)
	{
		if (turn == green)
			turn = blue;
		else if (turn == blue)
			turn = red;
		else if (turn == red)
			turn = purple;
		else if (turn == purple)
			turn = green;
	}
	else if (Nop == 3)
	{
		if (turn == green)
			turn = blue;
		else if (turn == blue)
			turn = purple;
		else if (turn == purple)
			turn = green;
	}
	else
	{
		if (turn == green)
			turn = red;
		else if (turn == red)
			turn = green;
	}
}
void Iskill(int**& B, char**& C, color& turn, int sx, int sy, int dx, int dy)
{
	if (C[dx][dy] == '*')
	{
		if (C[1][1] == ' ')
		{
			C[1][1] = '*';
			DrawP(1, 1, -37, 2);
			return;
		}
		else if (C[1][3] == ' ')
		{
			C[1][3] = '*';
			DrawP(1, 3, -37, 2);
			return;
		}
		else if (C[3][1] == ' ')
		{
			C[3][1] = '*';
			DrawP(3, 1, -37, 2);
			return;
		}
		else if (C[3][3] == ' ')
		{
			C[3][3] = '*';
			DrawP(3, 3, -37, 2);
			return;
		}
	}
	if (C[dx][dy] == '$')
	{
		if (C[1][10] == ' ')
		{
			C[1][10] = '$';
			DrawP(1, 10, -37, 1);
			return;
		}
		else if (C[1][12] == ' ')
		{
			C[1][12] = '$';
			DrawP(1, 12, -37, 1);
			return;
		}
		else if (C[3][10] == ' ')
		{
			C[3][10] = '$';
			DrawP(3, 10, -37, 1);
			return;
		}
		else if (C[3][12] == ' ')
		{
			C[3][12] = '$';
			DrawP(3, 12, -37, 1);
			return;
		}
	}
	if (C[dx][dy] == '@')
	{
		if (C[10][1] == ' ')
		{
			C[10][1] = '@';
			DrawP(10, 1, -37, 6);
			return;
		}
		else if (C[10][3] == ' ')
		{
			C[10][3] = '@';
			DrawP(10, 3, -37, 6);
			return;
		}
		else if (C[13][1] == ' ')
		{
			C[13][1] = '@';
			DrawP(13, 1, -37, 6);
			return;
		}
		else if (C[13][3] == ' ')
		{
			C[13][3] = '@';
			DrawP(13, 3, -37, 6);
			return;
		}
	}
	if (C[dx][dy] == '#')
	{
		if (C[10][10] == ' ')
		{
			C[10][10] = '#';
			DrawP(10, 10, -37, 12);
			return;
		}
		else if (C[10][13] == ' ')
		{
			C[10][13] = '#';
			DrawP(10, 13, -37, 12);
			return;
		}
		else if (C[13][10] == ' ')
		{
			C[13][10] = '#';
			DrawP(13, 10, -37, 12);
			return;
		}
		else if (C[13][13] == ' ')
		{
			C[13][13] = '#';
			DrawP(13, 13, -37, 12);
			return;
		}
	}
}
bool Ishome(int**& BB, int sx, int sy, int dx, int dy, int dv, int turn)
{
	int ishomeG, ishomeB, ishomeR, ishomeP;
	ishomeG = BB[sx][sy] + dv + 49;
	ishomeB = BB[sx][sy] + dv + 188;
	ishomeR = BB[sx][sy] + dv + 275;
	ishomeP = BB[sx][sy] + dv + 362;
	if ((turn == green && BB[dx][dy] == ishomeG)
		|| (turn == blue && BB[dx][dy] == ishomeB)
		|| (turn == red && BB[dx][dy] == ishomeR)
		|| (turn == purple && BB[dx][dy] == ishomeP))
		return true;
	else
		return false;
}
bool IsWin(int*& homecount, int& Nop, int h_k_g, int h_k_b, int h_k_p, int h_k_r)
{
	for (int i = 1; i < Nop + 1; i++)
	{
		if (i == 1 && homecount[i] == 4 && h_k_g == true)
			return true;
		else if (i == 2 && homecount[i] == 4 && h_k_b == true)
			return true;
		else if (i == 3 && homecount[i] == 4 && h_k_p == true)
			return true;
		else if (i == 4 && homecount[i] == 4 && h_k_r == true)
			return true;
	}
	return false;
}
void Playernames(char P1[15], char P2[15], char P3[15], char P4[15],int Nop)
{
	int i = 0;
	char j;
	if (Nop == 4)
	{
		cout << "\n\nEnter name and then full stop(.) for name";
		cout << "\n\n\n\n\nEnter player 1 name: ";
		do
		{
			cin >> P1[i];
			j = P1[i];
			i++;
		} while (j != '.');
		cout << "\n\n\n\n\nEnter player 2 name: ";
		i = 0;
		do
		{
			cin >> P2[i];
			j = P2[i];
			i++;
		} while (j != '.');
		i = 0;
		cout << "\n\n\n\n\nEnter player 3 name: ";
		i = 0;
		do
		{
			cin >> P3[i];
			j = P3[i];
			i++;
		} while (j != '.');
		i = 0;
		cout << "\n\n\n\n\nEnter player 4 name: ";
		i = 0;
		do
		{
			cin >> P4[i];
			j = P4[i];
			i++;
		} while (j != '.');
		i = 0;
	}
	else if (Nop == 3)
	{
		cout << "\n\n\n\n\nEnter player 1 name: ";
		do
		{
			cin >> P1[i];
			j = P1[i];
			i++;
		} while (j != '.');
		cout << "\n\n\n\n\nEnter player 2 name: ";
		i = 0;
		do
		{
			cin >> P2[i];
			j = P2[i];
			i++;
		} while (j != '.');
		i = 0;
		cout << "\n\n\n\n\nEnter player 3 name: ";
		i = 0;
		do
		{
			cin >> P3[i];
			j = P3[i];
			i++;
		} while (j != '.');
	}
	else if (Nop == 2)
	{
		cout << "\n\n\n\n\nEnter player 1 name: ";
		do
		{
			cin >> P1[i];
			j = P1[i];
			i++;
		} while (j != '.');
		cout << "\n\n\n\n\nEnter player 2 name: ";
		i = 0;
		do
		{
			cin >> P2[i];
			j = P2[i];
			i++;
		} while (j != '.');
		i = 0;
	}
}
void pehlibari(int d,color &turn,int Nop)
{
	PrintHollowBox(35, 35, 5, 5, -37, 15);
	gotoRowCol(37, 37);
	cout << d;
	int m1, m2, m3, m4, f;
	if (Nop == 4)
	{
		
		for (int i = 1;i <= 4;i++)
		{
			gotoRowCol(i+2, 0);
			cout << "\nPlayer " << i << "'s turn, please roll the dice ";
			f = DiceRoll(d);
			if( i == 1)
				m1 = f;
			else if (i == 2)
				m2 = f;
			else if (i == 3)
				m3 = f;
			else if (i == 4)
				m4 = f;
		}
		if (m1 >= m4 && m1 >= m3 && m1 >= m2)
			turn = green;
		else if (m2 >= m4 && m2 >= m3 && m2 >= m1)
			turn = blue;
		else if (m3 >= m4 && m3 >= m1 && m3 >= m2)
			turn = purple;
		else if (m4 >= m1 && m4 >= m3 && m4 >= m2)
			turn = red;
	}
	if (Nop == 3)
	{

		for (int i = 1;i <= 3;i++)
		{
			gotoRowCol(i + 2, 0);
			cout << "\nPlayer " << i << "'s turn, please roll the dice ";
			f = DiceRoll(d);
			if (i == 1)
				m1 = f;
			else if (i == 2)
				m2 = f;
			else if (i == 3)
				m3 = f;
		}
		if (m1 >= m3 && m1 >= m2)
			turn = green;
		else if (m2 >= m3 && m2 >= m1)
			turn = blue;
		else if (m3 >= m1 && m3 >= m2)
			turn = purple;
	}
	if (Nop == 2)
	{

		for (int i = 1;i <= 2;i++)
		{
			gotoRowCol(i + 2, 0);
			cout << "\nPlayer " << i << "'s turn, please roll the dice ";
			f = DiceRoll(d);
			if (i == 1)
				m1 = f;
			else if (i == 2)
				m2 = f;
		}
		if (m1 >= m2)
			turn = green;
		else
			turn = red;
	}

}
int main()
{
	cout<<"***THE LUDO GAME***"<<endl;
	cout<<"YOU SHALL USE MOUSECLICK TO ROLL DICE AND TO SELECT AND MOVE PIECES"<<endl;
	char A1[15], B1[15], C1[15], D1[15];  //ARRAY USED FOR STORING NAMES OF PLAYERS  
	bool h_k_g = false, h_k_b = false, h_k_p = false, h_k_r = false;    //BOOL VARIABLE USED TO CHECK WHETHER KILLED GOTI OR NOT
	int sx, sy, dx, dy, count = 0;    //COLUMN AND ROW INDEX SELECTION AND DESTINATION
	int Nop, dv = 0, d = 0;
	color turn;
	gotoRowCol(40, 40);
	colour(5);
	cout << "Please Enter the number of players 2/3/4 playing the game: ";
	cin >> Nop;    //ENTERING NUMBER OF PLAYERS
	system("cls");
	pehlibari(dv, turn, Nop);   //FUNCTION CALLED TO DECIDE WHICH PLAYER GETS THE FIRST TURN
	system("cls");   //FUNCTION USED FOR CLEARING SCREEN
	int** BB = new int* [15];     //BACKENDBOARD
	for (int i = 0;i < 15;i++)
	{
		BB[i] = new int[15];
	}
	char** C = new char* [15];   //CHARACTER 2-D ARRAY USED
	for (int i = 0;i < 15;i++)
	{
		C[i] = new char[15];
	}
	int* homecount = new int[Nop];
	Playernames(A1, B1, C1, D1, Nop);  //USED FOR INPUTING NAMES OF PLAYERS
	system("cls");
	PrintGrid(75, 75, 15, 5, 5, -37, dv, A1, B1, C1, D1,Nop);    //GRIDPRINTING (BOARD)
	Init(Nop, C, turn);  //FUNCTION USED TO ENTER POSITION OF PEICES
	turn = green;
	do
	{
		do
		{
			clstext(); //CLEAR TEXT
			displayplayermsg(turn); //THIS USES COLOURED BOX TO SHOW THE TURN
			backendboard(BB);
			//Displaymarkedlocations(7,0,5,5,BB);
			dv = DiceRoll(d);    //FUNCTION FOR DICE ROLL  //YOU MAY CHANGE THIS FOR YOUR LIKING
			//dv = 6;
			colour(9);
			Selection(sx, sy);      //RETURNS COLUMN+ROW INDEX OF THE PIECE FOR SELECTION 
		} while (IsValidSelection(dv, sx, sy, BB, turn, C, Nop) == false);    //EXAMPLE: if turn=green and piece of blue is selected it will return false.
		do
		{
			Destination(dx, dy);   //RETURNS COLUMN+ROW INDEX OF THE PIECE FOR DESTINATION
		} while (IsValidDestination(dv, sx, sy, dx, dy, BB, turn, C, homecount, h_k_b, h_k_g, h_k_p, h_k_r) == false); //EXAMPLE: if turn=green and piece of blue is selected it will return false.
		Move(sx, sy, dx, dy, BB, turn, C);//to move the pieces 
		count++;
		if (count == 3)
		{
			changeturn(Nop, turn); //FUNCTION USED FOR CHANGING TURN 
			count = 0;
		}
		if (dv != 6)
		{
			changeturn(Nop, turn); //FUNCTION USED FOR CHANGING TURN
			count = 0;
		}
	} while (!IsWin(homecount, Nop, h_k_g, h_k_b, h_k_p, h_k_r)); //CHECK TO SEE IF PLAYER HAS WON OR NOT
	return 0;
}