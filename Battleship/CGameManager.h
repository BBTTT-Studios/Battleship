#pragma once

class CGameManager
{
public:
    CGameManager();
    ~CGameManager();

private:
    int P1Score_m = 0;
    int P2Score_m = 0;
    int Round_m = 0;
    

    void InitialiseGame();

    void GameOver();
    
};
