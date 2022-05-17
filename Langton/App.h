#ifndef APP_H
#define APP_H
#include "game.h"
#include <windows.h>


class App : public game
{
public:
	const static int dx = 7;
	App(int w, int k);
	virtual void draw();
	void init(HWND hwnd);
	void setPosition(HWND hwnd, int text1, int text2);
	void paint(HWND hwnd, PAINTSTRUCT ps);
private:
	HDC _hdc;
	HWND _hwnd;
	HBRUSH _MyBrush, _BgBrush, _AntBrush, Txt;
};
#endif

