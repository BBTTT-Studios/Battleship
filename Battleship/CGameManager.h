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
    explicit CGameManager(bool aimode = true);   
    ~CGameManager();


    
private:
    int P1Score_m = 0;  // TF: Variable Type
    int P2Score_m = 0;
    int Round_m = 0;
    bool ContinueGame_m = true;
    const bool AIMode_m;  //TF: Constant

    CGrid P1Grid_m;   // TF: Class Instance
    CGrid P2Grid_m;
    CBattleship *P1ShipList_m[5];
    CBattleship *P2ShipList_m[5];
    
    // Prompts player to move and place their ships
    void PlacePlayerShips(const int& player = 0);  // TF: Default Parameter

    // Auto places ships on the grid
    void PlaceAIShips();
    
    void DrawGrids();
    
    void DoGameLoop();

    // Prompts player to fire a missile at enemy grid. Returns true if hit
    static bool QueryGrid(CGrid& grid);
    
    void GameOver() const;



    
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
