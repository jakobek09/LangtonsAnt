#include "App.h"
#include <string>
#include <sstream>

using namespace std;

App::App(int w, int k) : game(w, k) {}

void App::draw()
{
	for (int i = 0; i < nw; i++) {
		for (int j = 0; j < nk; j++) {
			if (A[i][j]) (HBRUSH)::SelectObject(_hdc, _BgBrush);
			else (HBRUSH)::SelectObject(_hdc, _MyBrush);
			
			if(i == PosX && j==PosY)
				(HBRUSH)::SelectObject(_hdc, _AntBrush);

			Rectangle(_hdc, i * dx, j * dx, i * dx + dx, j * dx + dx);
		}
	}
}

void App::init(HWND hwnd)
{
	for (int i = 0; i < nw; i++)
	{
		for (int j = 0; j < nk; j++)
			A[i][j] = 0;
	}
	PosY = nw / 2;
	PosX = nk / 2;
	dir = 0;
	_hwnd = hwnd;
	_hdc = GetDC(_hwnd);
	_MyBrush = ::CreateSolidBrush(0xffffff);
	_BgBrush = ::CreateSolidBrush(0x000000);
	_AntBrush = ::CreateSolidBrush(0x008000);
}

void App::setPosition(HWND hwnd, int text1, int text2)
{
	int x = GetDlgItemInt(hwnd, text1, NULL, false);
	int y = GetDlgItemInt(hwnd, text2, NULL, false);	

	if (!(x <= nw && y <= nk))
		::MessageBox(hwnd, (LPCWSTR)L"WRONG NUMBER! NUMBER MUST BE BETWEEN 0 AND 76!", (LPCWSTR)L"ERROR", MB_ICONERROR | MB_OK);
	else
	{
		PosX = x;
		PosY = y;
		draw();
	}
}

void App::paint(HWND hwnd, PAINTSTRUCT ps)
{
	RECT  rect;
	Txt = ::CreateSolidBrush(0xff0000);
	GetClientRect(hwnd, &rect);
	SetTextColor(_hdc, RGB(0xFF, 0x00, 0x00));
	rect.left = 450;
	rect.top = 10;
	DrawText(_hdc, L"       MRÓWKA LANGTONA         ", -1, &rect, DT_CENTER);
	SelectObject(_hdc, Txt);
	DeleteObject(Txt);
}

