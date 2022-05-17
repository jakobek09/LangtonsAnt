
#include "engine.h"

engine::engine(int w, int k) : nw(w), nk(k)
{
	A = new int* [nw];

	for (int i = 0; i < nw; i++)
	{
		A[i] = new int[nk];
	}

}

engine::~engine()
{
	if (A)
	{
		for (int i = 0; i < nw; i++)
		{
			delete[] A[i];
		}
	}
}

void engine::init()
{
	for (int i = 0; i < nw; i++)
	{
		for (int j = 0; j < nk; j++)
			A[i][j] = 0;
	}
	PosY = nw / 2;
	PosX = nk / 2;
	dir = 0;
}

void engine::BorW()
{
	if (A[PosX][PosY] == 0)
	{
		A[PosX][PosY] = 1;
		switch (dir)
		{
		case  0:
			dir = 2;
			if (PosX - 1 < 0)
				PosX = nw - 1;
			else
				PosX -= 1;
			break;
		case  1:
			dir = 3;
			if (PosX + 1 == nw)
				PosX = 0;
			else
				PosX += 1;
			break;
		case  2:
			dir = 1;
			if (PosY + 1 == nk)
				PosY = 0;
			else
				PosY += 1;
			break;
		case  3:
			dir = 0;
			if (PosY - 1 < 0)
				PosY = nk - 1;
			else
				PosY -= 1;
			break;
		}
	}
	else
	{
		A[PosX][PosY] = 0;
		switch (dir)
		{
		case  0:
			dir = 3;
			if (PosX + 1 == nw)
				PosX = 0;
			else
				PosX += 1;
			break;
		case  1:
			dir = 2;
			if (PosX - 1 < 0)
				PosX = nw - 1;
			else
				PosX -= 1;
			break;
		case  2:
			dir = 0;
			if (PosY - 1 < 0)
				PosY = nk - 1;
			else
				PosY -= 1;
			break;
		case  3:
			dir = 1;
			if (PosY + 1 == nk)
				PosY = 0;
			else
				PosY += 1;
			break;
		}
	}
}
