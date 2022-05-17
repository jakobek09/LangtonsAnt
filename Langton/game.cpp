#include "game.h"

game::game(int w, int k) : engine(w, k) {}

void game::play()
{
    BorW();
    draw();
}

void game::playWithoutDraw(int n)
{

    for (int i = 0; i < n; i++)
    {
        BorW();
    }
    draw();
}

void game::reset()
{
    for (int i = 0; i < nw; i++)
    {
        for (int j = 0; j < nk; j++)
        {
            A[i][j] = 0;
        }
    }
    PosX = nw / 2;
    PosY = nk / 2;
    dir = 0;
    draw();
}
