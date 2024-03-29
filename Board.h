#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<time.h>
using namespace std;
#include"Pieces.h"
#include"Green.h"
#include"Red.h"
#include"Purple.h"
#pragma once
#include"Blue.h"
#include"Dice.h"
#include"Stops.h"
class Board
{
protected:
	int turn;
	Pieces* B[15][15];
	int BB[15][15];
	int dicevalue;
	Position S, E;
	int homecount[5];
public:
	int Nop;
	Board()
	{
		dicevalue = 0;
		for (int i = 0; i < 5; i++)
			homecount[i] = 0;
	}
	void getRowColbyLeftClick(int& rpos, int& cpos)
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
	bool IsWin()
	{
		for (int i = 1; i < Nop+1; i++)
		{
			if (homecount[i] == 4)
				return true;
		}
		return false;
	}
	void DiceRoll()
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
					cin >> dicevalue;
				} while (dicevalue > 90);
				gotoRowCol(78, 0);
				cout << "You got a: " << dicevalue;
				return;
			}
			else if (sri >= 33 && sri <= 37 && sci >= 33 && sci <= 37)
			{
				for (int i = 0; i < 25; i++)
				{
					dicevalue = rand() % 6 + 1;
					gotoRowCol(37, 37);
					cout << dicevalue;
					Sleep(100);
				}
				gotoRowCol(78, 0);
				cout << "You got a: " << dicevalue;
				return;
			}
			else
				continue;

		} while (true);
	}
	void PrintBoard()
	{
		//Cheat
		PrintHollowBox(45, 80, 7, 7, -37, 15);
		gotoRowCol(48, 81);
		cout << "Cheat";
		PrintGrid(75, 75, 15, 5, 5, -37);
		PrintHollowBox(35, 35, 5, 5, -37, 15);
		gotoRowCol(37, 37);
		cout << dicevalue;
		//Display dice
		for (int r = 0; r < 15; r++)
		{
			for (int c = 0; c < 15; c++)
			{
				if (B[r][c] == nullptr)
					continue;
				if ((B[r][c]->getcolor() == green) || (B[r][c]->getcolor() == blue) || 
					(B[r][c]->getcolor() == red) || (B[r][c]->getcolor() == purple))
				{
					colour(12);
					//gotoRowCol(((r + 4 * r) +2), ((c + 4 * c)+2));
					B[r][c]->DrawP(r, c, 5, 5, B[r][c]->getcolor(), -37);
				}
			}
		}
	}
	void PrintGrid(int Rows, int cols, int d, int rdim, int cdim, char s)
	{
		rdim = Rows / d;
		cdim = cols / d;
		for (int r = 0; r < d; r++)
		{
			for (int c = 0; c < d; c++)
			{
				int sr = r * rdim, sc = c * cdim;
				
				if ((c < 6 && r < 6 )|| (c < 6 && c > 0 && r == 7) || (c == 1 && r == 6) || (c == 2 && r == 8))
					PrintBox(sr, sc, rdim, cdim, s, 10);//Green 
				if (c > 8 && r < 6 || (c == 7 && r > 0 && r < 6) || (c == 6 && r == 2) || (c == 8 && r == 1))
					PrintBox(sr, sc, rdim, cdim, s, 9);//Blue
				if (c < 6 && r > 8||(c == 7 && r >= 6 && r < 14) || (c == 6 && r == 13) || (c == 8 && r == 12))
					PrintBox(sr, sc, rdim, cdim, s, 5);//purple
				if (c > 8 && (r > 8) || (c >=9 && c < 14  && r == 7) || (c == 12 && r == 6) || (c == 13 && r == 8))
					PrintBox(sr, sc, rdim, cdim, s, 4);//red
				if ((c >= 6 && c < 9) || (r >= 6 && r < 9))
					PrintHollowBox(sr, sc, rdim, cdim, s, 15);//white
				if ((c >= 6 && c < 9) && (r >= 6 && r < 9))
					PrintBox(sr, sc, rdim, cdim, s, 0);//black
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
	void Init()
	{
		for (int ri = 0; ri < 15; ri++)
		{
			for (int ci = 0; ci < 15; ci++)
			{
				if (Nop == 4)
				{
					
					if ((ri == 1 || ri == 3) && (ci == 1 || ci == 3))
						B[ri][ci] = new Green(green, Position(ri, ci), this);
					else if ((ri == 1 || ri == 3) && (ci == 10 || ci == 12))
						B[ri][ci] = new Blue(blue, Position(ri, ci), this);
					else if ((ri == 10 || ri == 13) && (ci == 10 || ci == 13))
						B[ri][ci] = new Red(red, Position(ri, ci), this);
					else if ((ri == 10 || ri == 13) && (ci == 1 || ci == 3))
						B[ri][ci] = new Purple(purple, Position(ri, ci), this);
					else
						B[ri][ci] = nullptr;

				}
				else if (Nop == 3)
				{
					if ((ri == 1 || ri == 3) && (ci == 1 || ci == 3))
						B[ri][ci] = new Green(green, Position(ri, ci), this);
					else if ((ri == 1 || ri == 3) && (ci == 10 || ci == 12))
						B[ri][ci] = new Blue(blue, Position(ri, ci), this);
					else if ((ri == 10 || ri == 13) && (ci == 10 || ci == 13))
						B[ri][ci] = new Red(red, Position(ri, ci), this);
					else
						B[ri][ci] = nullptr;
				}
				else if (Nop == 2)
				{
					if ((ri == 1 || ri == 3) && (ci == 1 || ci == 3))
						B[ri][ci] = new Green(green, Position(ri, ci), this);
					else if ((ri == 10 || ri == 13) && (ci == 10 || ci == 13))
						B[ri][ci] = new Red(red, Position(ri, ci), this);
					else
						B[ri][ci] = nullptr;
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
	void changeturn()
	{
		if (Nop == 2)
		{
			if (turn == green)
				turn = red;
			else
				turn = green;
		}
		else if (Nop == 3)
		{
			turn++;
			if (turn > 3)
				turn = 1;
		}
		if (Nop == 4)
		{
			turn++;
			if (turn > 4)
				turn = 1;
		}
		
	}
	bool IsValidSelection()
	{
		if (B[S.x][S.y] == nullptr)
			return false;
		if (dicevalue == 6)
		{
			if (turn == green && (S.x == 1 || S.x == 3) && (S.y == 1 || S.y == 3))
			{
				B[S.x][S.y]->IsOpen = true;
				return true;
			}
			else if (turn == blue && (S.x == 1 || S.x == 3) && (S.y == 10 || S.y == 12))
			{
				B[S.x][S.y]->IsOpen = true;
				return true;
			}
			else if (turn == red && (S.x == 10 || S.x == 13) && (S.y == 10 || S.y == 13))
			{
				B[S.x][S.y]->IsOpen = true;
				return true;
			}
			else if (turn == purple && (S.x == 10 || S.x == 13) && (S.y == 1 || S.y == 3))
			{
				B[S.x][S.y]->IsOpen = true;
				return true;
			}
		}
		else if ((B[S.x][S.y] != nullptr && (B[S.x][S.y]->getcolor() == green && turn == 1) && B[S.x][S.y]->IsOpen == true) 
			||(B[S.x][S.y] != nullptr && (B[S.x][S.y]->getcolor() == blue && turn == 2) && B[S.x][S.y]->IsOpen == true)
			||(B[S.x][S.y] != nullptr && (B[S.x][S.y]->getcolor() == red && turn == 3) && B[S.x][S.y]->IsOpen == true)
			||(B[S.x][S.y] != nullptr && (B[S.x][S.y]->getcolor() == purple && turn == 4) && B[S.x][S.y]->IsOpen == true))
		{
			return true;
		}
		else if (B[S.x][S.y]->IsOpen == false)
		{
			gotoRowCol(82, 0);
			cout << "You need a 6 to open Goti";
			changeturn();
			Sleep(2000);
			return false;
		}
		else if (S.x > 14 || S.y > 14 || S.x < 0 || S.y < 0)
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
	void Selection(Position& a)
	{	
		int q, w;
		bool ch = false;
		do
		{
			gotoRowCol(80, 0);
			cout << "\nPlease select the piece";
			getRowColbyLeftClick(q, w);
			a.x = q;
			a.y = w;

			for (int ri = 0; ri < 75; ri += 5)
			{
				for (int ci = 0; ci < 75; ci += 5)
				{
					if ((a.x >= ri && a.x <= ri + 5) && (a.y >= ci && a.y <= ci + 5))
					{
						ch = true;
						a.x = ri / 5;
						a.y = ci / 5;
					}
				}
			}
			if (!ch)
				cout << "\nInvalid Coordinate Select Agian!!!";
		} while (ch == false);
	}
	void Destination(Position& a)
	{
		int er, ec;
		bool ch = false;
		do
		{
			gotoRowCol(84, 0);
			cout << "\nPlease Select Destination";
			getRowColbyLeftClick(er, ec);
			a.x = er;
			a.y = ec;

			for (int ri = 0; ri < 75; ri += 5)
			{
				for (int ci = 0; ci < 75; ci += 5)
				{
					if ((a.x >= ri && a.x <= ri + 5) && (a.y >= ci && a.y <= ci + 5))
					{
						ch = true;
						a.x = ri / 5;
						a.y = ci / 5;
					}
				}
			}
			if (!ch)
				cout << "\nInvalid Coordinate Select Agian!!!";
		} while (ch == false);
	}
	void Iskill()
	{
		if (B[E.x][E.y]->getcolor() == green)
		{
			if (B[1][1] == nullptr)
			{
				B[1][1] = new Green(green, Position(1, 1), this);
				B[1][1]->DrawP(1, 1, 5, 5, B[1][1]->getcolor(), -37);
				return;
			}
			else if (B[1][3] == nullptr)
			{
				B[1][3] = new Green(green, Position(1, 3), this);
				B[1][3]->DrawP(1, 3, 5, 5, B[1][3]->getcolor(), -37);
				return;
			}
			else if (B[3][1] == nullptr)
			{
				B[3][1] = new Green(green, Position(3, 1), this);
				B[3][1]->DrawP(3, 1, 5, 5, B[3][1]->getcolor(), -37);
				return;
			}
			else if (B[3][3] == nullptr)
			{
				B[3][3] = new Green(green, Position(3, 3), this);
				B[3][3]->DrawP(3, 3, 5, 5, B[3][3]->getcolor(), -37);
				return;
			}
		}
		if (B[E.x][E.y]->getcolor() == blue)
		{
			if (B[1][10] == nullptr)
			{
				B[1][10] = new Blue(blue, Position(1, 10), this);
				B[1][10]->DrawP(1, 10, 5, 5, B[1][10]->getcolor(), -37);
				return;
			}
			else if (B[1][12] == nullptr)
			{
				B[1][12] = new Blue(blue, Position(1, 12), this);
				B[1][12]->DrawP(1, 12, 5, 5, B[1][12]->getcolor(), -37);
				return;
			}
			else if (B[3][10] == nullptr)
			{
				B[3][10] = new Blue(blue, Position(3, 10), this);
				B[3][10]->DrawP(3, 10, 5, 5, B[3][10]->getcolor(), -37);
				return;
			}
			else if (B[3][12] == nullptr)
			{
				B[3][12] = new Blue(blue, Position(3, 12), this);
				B[3][12]->DrawP(3, 12, 5, 5, B[3][12]->getcolor(), -37);
				return;
			}
		}
		if (B[E.x][E.y]->getcolor() == purple)
		{
			if (B[10][1] == nullptr)
			{
				B[10][1] = new Purple(purple, Position(10, 1), this);
				B[10][1]->DrawP(10, 1, 5, 5, B[10][1]->getcolor(), -37);
				return;
			}
			else if (B[10][3] == nullptr)
			{
				B[10][3] = new Purple(purple, Position(10, 3), this);
				B[10][3]->DrawP(10, 3, 5, 5, B[10][3]->getcolor(), -37);
				return;
			}
			else if (B[13][1] == nullptr)
			{
				B[13][1] = new Purple(purple, Position(13, 1), this);
				B[13][1]->DrawP(13, 1, 5, 5, B[13][1]->getcolor(), -37);
				return;
			}
			else if (B[13][3] == nullptr)
			{
				B[13][3] = new Purple(purple, Position(13, 3), this);
				B[13][3]->DrawP(13, 3, 5, 5, B[13][3]->getcolor(), -37);
				return;
			}
		}
		if (B[E.x][E.y]->getcolor() == red)
		{
			if (B[10][10] == nullptr)
			{
				B[10][10] = new Red(red, Position(10, 10), this);
				B[10][10]->DrawP(10, 10, 5, 5, B[10][10]->getcolor(), -37);
				return;
			}
			else if (B[10][13] == nullptr)
			{
				B[10][13] = new Red(red, Position(10, 13), this);
				B[10][13]->DrawP(10, 13, 5, 5, B[10][13]->getcolor(), -37);
				return;
			}
			else if (B[13][10] == nullptr)
			{
				B[13][10] = new Red(red, Position(13, 10), this);
				B[13][10]->DrawP(13, 10, 5, 5, B[13][10]->getcolor(), -37);
				return;
			}
			else if (B[13][13] == nullptr)
			{
				B[13][13] = new Red(red, Position(13, 13), this);
				B[13][13]->DrawP(13, 13, 5, 5, B[13][13]->getcolor(), -37);
				return;
			}
		}
	}
	bool Ishome()
	{
		if (B[S.x][S.y]->CanGo == false)
			return false;
		int ishomeG, ishomeB , ishomeR, ishomeP;
		ishomeG = BB[S.x][S.y] + dicevalue + 49;
		ishomeB = BB[S.x][S.y] + dicevalue + 188;
		ishomeR = BB[S.x][S.y] + dicevalue + 275;
		ishomeP = BB[S.x][S.y] + dicevalue + 362;
		if ((turn == green && BB[E.x][E.y] == ishomeG)
			|| (turn == blue && BB[E.x][E.y] == ishomeB)
			|| (turn == red && BB[E.x][E.y] == ishomeR)
			|| (turn == purple && BB[E.x][E.y] == ishomeP))
			return true;
		else
			return false;
	}
	bool IsValidDestination()
	{
		int a;
		a = BB[S.x][S.y] + dicevalue;
		if (a > 52)
		{
			a = a - 52;
		}
		if ((dicevalue == 6) && ((turn == green && E.x == 6 && E.y == 1) || (turn == blue && E.x == 1 && E.y == 8)
			|| (turn == red && E.x == 8 && E.y == 13) || (turn == purple && E.x == 13 && E.y == 6)))
			return true;
		else if (Ishome() == true)
		{
			B[S.x][S.y]->IsHome = true;
			homecount[turn]++;
			return true;
		}
		else if (BB[E.x][E.y] == a )
		{
			if (B[E.x][E.y] != nullptr && B[E.x][E.y]->getcolor() != turn)
			{
				B[S.x][S.y]->CanGo = true;
				Iskill();
				return true;
			}
			return true;
		}
		else
		{
			gotoRowCol(82, 0);
			cout << "Invalid move";
			return false;
		}
	}
	void Move(Position S,Position E)
	{
		B[E.x][E.y] = B[S.x][S.y];
		if (((S.x == 1 || S.x == 3) && (S.y == 1 || S.y == 3)) || (S.x == 6 && S.y == 1))
			B[S.x][S.y]->DrawP(S.x, S.y, 5, 5, 10, -37);//green
		else if ((S.x == 1 || S.x == 3) && (S.y == 10 || S.y == 12) || (S.x == 1 && S.y == 8))
			B[S.x][S.y]->DrawP(S.x, S.y, 5, 5, 9, -37);//blue
		else if ((S.x == 10 || S.x == 13) && (S.y == 10 || S.y == 13) || (S.x == 13 && S.y == 15))
			B[S.x][S.y]->DrawP(S.x, S.y, 5, 5, 4, -37);//red
		else if ((S.x == 10 || S.x == 13) && (S.y == 1 || S.y == 3) || (S.x == 13 && S.y == 6))
			B[S.x][S.y]->DrawP(S.x, S.y, 5, 5, 5, -37);//purple
		else
			B[S.x][S.y]->DrawP(S.x, S.y, 5, 5, 0, -37);
		B[S.x][S.y] = nullptr;
		B[E.x][E.y]->DrawP(E.x, E.y, 5, 5, B[E.x][E.y]->getcolor(), -37);
	}
	void displayplayermsg()
	{
		if (turn == green)
		{
			PrintBox(30, 85,10, 10,-37, 10);//Green 
		}
		else if (turn == blue)
		{
			PrintBox(30, 85, 10, 10, -37, 9);//blue
		}
		else if (turn == red)
		{
			PrintBox(30, 85, 10, 10, -37, 4);//red
		}
		else if (turn == purple)
		{
			PrintBox(30, 85, 10, 10, -37, 5);//purple
		}
	}
	void backendboard()
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
	void PrintNumberInBox(int sr, int sc, int rdim, int cdim, int s)
	{
		color(1);
		gotoRowCol(sr + rdim / 2, sc + cdim / 2);
		if (s > 0 && s < 1000)
			cout << s;
	}
	void BoxNumbertosrsc(int n, int d, int& sr, int& sc, int rdim, int cdim)
	{
		sr = ((n - 1) / d) * rdim;
		sc = ((n - 1) % d) * cdim;

	}
	void Displaymarkedlocations(int sri, int sci, int rdim, int cdim)
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
	void Khel()
	{
		gotoRowCol(40, 40);
		cout << "How many players you want to play with 2/3/4 :";
		cin >> Nop;
		system("cls");
		Init();
		turn = green;
		PrintBoard();
		do
		{
			do
			{
				clstext();
				displayplayermsg();
				//PrintBoard();
				backendboard();
				Displaymarkedlocations(S.x, S.y, 5, 5);
				DiceRoll();
				Selection(S);
			} while (IsValidSelection() == false);
			do
			{
				Destination(E);
			} while (IsValidDestination() == false);
			Move(S, E);
			if(dicevalue!=6)
				changeturn();
		} while (!IsWin());
		system("cls");
		gotoRowCol(20, 20);
		cout << "Gameover!!!! ";
	}
};

