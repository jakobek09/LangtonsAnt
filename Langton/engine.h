
#ifndef ENGINE_H
#define ENGINE_H
class engine
{
protected:
	int** A;
	int nw;
	int nk;
	int PosX;
	int PosY;
	int dir; // 0 - UP  1 - DOWN  2 - LEFT  3 - RIGHT
protected:
	engine(int w, int k);
	virtual ~engine();
	void init();
	void BorW();
};
#endif
