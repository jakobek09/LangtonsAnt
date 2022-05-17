
#ifndef GAME_H
#define GAME_H
#include "engine.h"
class game : public engine
{
public:
	game(int w, int k);
	void play();
	void playWithoutDraw(int n);
	virtual void draw() = 0;
	void reset();
private:
	game(const game&);
	game& operator=(const game&);
};
#endif
