/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2021 Media Design School

File Name : CGameManager.cpp
Description : Implementation of CGameManager.h
Author : Vincent Gray
Mail : Vincent.Gray@mds.ac.nz
**************************************************************************/

#include "CGameManager.h"
#include "termcolor.hpp"
#include <conio.h>

using namespace std;


//TODO Implement score and reset system


CGameManager::CGameManager(const bool aimode):AIMode_m(aimode)  //  TF: Constructor
{

    for (int i = 0; i < 5; i++)
    {
        P1ShipList_m[i] = new CBattleship(static_cast<CBattleship::EShipType>(i), CBattleship::ERotationDirection::RIGHT, 1, 1);  //TF: Dynamic Memory
        P2ShipList_m[i] = new CBattleship(static_cast<CBattleship::EShipType>(i), CBattleship::ERotationDirection::RIGHT, 5, 5);
    }

    PlacePlayerShips();
    PlaceAIShips();
    DoGameLoop();
    
}

CGameManager::~CGameManager()       // TF: Destructor
{
    for (int i = 0; i < 5; i++)
    {
        delete P1ShipList_m[i];
        delete P2ShipList_m[i];
    }
    system("cls");
}

void CGameManager::PlacePlayerShips(const int& player)
{
    CGrid& grid = player ? P2Grid_m : P1Grid_m;     // TF: Reference
    CBattleship** shipList = player ? P2ShipList_m : P1ShipList_m;

    
    
    for (int i = 0; i < 5; i++)
    {
        bool placing = true;
        grid.PlaceShipRandom(shipList[i], false);
        
        while (placing)
        {
            grid.PlaceShip(shipList[i], false);
			
            DrawGrids();
            std::cout << termcolor::yellow << "Move: Arrow Keys   |   Rotate: R   |   Confirm: Enter" << termcolor::reset << endl;
            const int c = _getch();
            if (c && c != 224)  // TF: Logical Operator
            {
                switch (c)
                {
                case KEY_ENTER:
                    placing = false;
                    break;

                case KEY_R:
                    grid.RotateShip(shipList[i]);
                    grid.MoveShip(shipList[i], shipList[i]->GetShipLocation().Row, shipList[i]->GetShipLocation().Col);
                    break;

                default:
                    std::cout << "?";
                    break;
                }
            }
			
            else
            {
                switch(_getch())
                {
                case KEY_LEFT:
                    grid.MoveShip(shipList[i], shipList[i]->GetShipLocation().Row, shipList[i]->GetShipLocation().Col-1);
                    break;
					
                case KEY_RIGHT:
                    grid.MoveShip(shipList[i], shipList[i]->GetShipLocation().Row, shipList[i]->GetShipLocation().Col+1);
                    break;
					
                case KEY_UP:
                    grid.MoveShip(shipList[i],shipList[i]->GetShipLocation().Row-1, shipList[i]->GetShipLocation().Col);
                    break;
					
                case KEY_DOWN:
                    grid.MoveShip(shipList[i],shipList[i]->GetShipLocation().Row+1, shipList[i]->GetShipLocation().Col);
                    break;
					
                default:
                    std::cout << "?";
                    break;
                }
            }
            DrawGrids();
        }
    }
}

void CGameManager::PlaceAIShips()
{
    std::cout  << termcolor::red << "Enemy is thinking..." << termcolor::reset;
    for (int i = 0; i < 5; i++)
    {
        P2Grid_m.PlaceShipRandom(P2ShipList_m[i], AIMode_m);
    }
}

void CGameManager::DrawGrids()
{
    system("cls");
    cout << termcolor::yellow << "Enemy Waters:       " << endl << termcolor::cyan << "Pieces Remaining: " << 17 - P1Score_m << termcolor::reset << endl;
    P2Grid_m.DrawGrid();
    
    cout << termcolor::yellow << "Your Ships:         " << endl << termcolor::cyan << "Pieces Remaining: " << 17 - P2Score_m << termcolor::reset << endl;
    P1Grid_m.DrawGrid();

    
}

void CGameManager::DoGameLoop()
{
    

    while (ContinueGame_m)
    {
        Round_m++;
        DrawGrids();
        
        P1Score_m += QueryGrid(P2Grid_m);

        DrawGrids();

        if (P1Score_m >= 17)
        {

            break;
        }


        cout << termcolor::red << "Enemy is thinking..." << termcolor::reset << endl;
        Sleep(1000);
        srand(static_cast<unsigned>(time(nullptr)));
        P2Score_m += P1Grid_m.GuessRandom();

        
        DrawGrids();

        if (P2Score_m >= 17)
        {

            break;
        }
    }

    GameOver();
}

bool CGameManager::QueryGrid(CGrid& grid)
{
    char xlet;
    int xloc;
    int yloc;
    
    std::cout << "Row (A - J): ";
    ValidateInput(xlet);
    if (xlet >= 97) { xloc = xlet - 96; }   //TF: Relational Operator
    else if (xlet >= 65) { xloc = xlet - 64; }  //TF: Arithmetic Operator
    else if (xlet >= 49) { xloc = xlet - 48; }

    std::cout << "Col (1 - 10): ";
    ValidateInput(yloc);

    return grid.CheckLocation(xloc, yloc);
}

void CGameManager::GameOver() const
{
    if (P1Score_m > P2Score_m)
    {
        cout << termcolor::green << "Player 1 wins!" << termcolor::reset << endl;
    }
    else
    {
        cout << termcolor::red << "Player 2 wins!" << termcolor::reset << endl;
    }
    system("pause");
    
}
