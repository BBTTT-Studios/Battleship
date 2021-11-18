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


CGameManager::CGameManager(bool aimode):AIMode(aimode)  //  TF: Constructor
{

    for (int i = 0; i < 5; i++)
    {
        p1ShipList[i] = new CBattleship(static_cast<CBattleship::EShipType>(i), CBattleship::ERotationDirection::RIGHT, 1, 1);  //TF: Dynamic Memory
        p2ShipList[i] = new CBattleship(static_cast<CBattleship::EShipType>(i), CBattleship::ERotationDirection::RIGHT, 5, 5);
    }

    PlacePlayerShips();
    PlaceAIShips();
    DoGameLoop();
    
}

CGameManager::~CGameManager()       // TF: Destructor
{
    for (int i = 0; i < 5; i++)
    {
        delete p1ShipList[i];
        delete p2ShipList[i];
    }
    system("cls");
}

void CGameManager::PlacePlayerShips(int player)
{
    CGrid& grid = player ? p2Grid : p1Grid;     // TF: Reference
    CBattleship** shipList = player ? p2ShipList : p1ShipList;
    
    for (int i = 0; i < 5; i++)
    {
        bool placing = true;
		
        while (placing)
        {
            grid.PlaceShip(shipList[i], false);
			
            DrawGrids();
            std::cout << "Move: Arrow Keys   |   Rotate: R   |   Confirm: Enter" << endl;
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
    std::cout << endl << termcolor::red << "Enemy is thinking..." << termcolor::reset << endl;
    for (int i = 0; i < 5; i++)
    {
        p2Grid.PlaceShipRandom(p2ShipList[i], AIMode);
    }
}

void CGameManager::DrawGrids()
{
    system("cls");
    cout << termcolor::yellow << "Enemy Waters:" << termcolor::reset << endl;
    p2Grid.DrawGrid();
    
    cout << termcolor::yellow << "Your Ships:" << termcolor::reset << endl;
    p1Grid.DrawGrid();

    
}

void CGameManager::DoGameLoop()
{
    

    while (continueGame)
    {
        Round_m++;
        DrawGrids();
        
        QueryGrid(p2Grid);

        DrawGrids();


        cout << termcolor::red << "Enemy is thinking..." << termcolor::reset << endl;
        Sleep(1000);
        srand(static_cast<unsigned>(time(NULL)));
        p1Grid.GuessRandom();

        
        DrawGrids();

    }
}

void CGameManager::QueryGrid(CGrid& grid)
{
    char xlet;
    int xloc;
    int yloc;
    
    std::cout << "Row: ";
    ValidateInput(xlet);
    if (xlet >= 97) { xloc = xlet - 96; }   //TF: Relational Operator
    else if (xlet >= 65) { xloc = xlet - 64; }  //TF: Arithmetic Operator

    std::cout << "Col: ";
    ValidateInput(yloc);

    grid.CheckLocation(xloc, yloc);
}
