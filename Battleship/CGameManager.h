/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2021 Media Design School

File Name : CGameManager.h
Description : Serves as the game instance. Handles game flow and scoring
Author : Vincent Gray
Mail : Vincent.Gray@mds.ac.nz
**************************************************************************/

#pragma once
#include "CGrid.h"
#include "CBattleship.h"
#include <iostream>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_R 114 


class CGameManager
{
public:
    CGameManager(bool aimode = true);   
    ~CGameManager();

private:
    int P1Score_m = 0;  // TF: Variable Type
    int P2Score_m = 0;
    int Round_m = 0;
    bool continueGame = true;
    const bool AIMode;  //TF: Constant

    CGrid p1Grid;   // TF: Class Instance
    CGrid p2Grid;
    CBattleship *p1ShipList[5];
    CBattleship *p2ShipList[5];
    

    void PlacePlayerShips(int player = 0);  // TF: Default Parameter
    void PlaceAIShips();
    void DrawGrids();
    void DoGameLoop();
    void QueryGrid(CGrid& grid);
    void GameOver();

public:
    
    template<typename T>
    static T& ValidateInput(T& val)
    {
        while (true) {
            if (!(std::cin >> val))
            {
                std::cout << "Enter a valid value!\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else
            {
                break;
            }
        }
        return val;
    }
    
};
