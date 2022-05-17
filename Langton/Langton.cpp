// Langton.cpp : Definiuje punkt wejścia dla aplikacji.
//

#include "framework.h"
#include "Langton.h"
#include "App.h"

#define MAX_LOADSTRING 100

// Zmienne globalne:
HINSTANCE hInst;                                // bieżące wystąpienie
WCHAR szTitle[MAX_LOADSTRING];                  // Tekst paska tytułu
WCHAR szWindowClass[MAX_LOADSTRING];            // nazwa klasy okna głównego
HWND hedit;
HWND hedit2;

// Przekaż dalej deklaracje funkcji dołączone w tym module kodu:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    

    // Inicjuj ciągi globalne
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LANGTON, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Wykonaj inicjowanie aplikacji:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LANGTON));

    MSG msg;

    // Główna pętla komunikatów:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNKCJA: MyRegisterClass()
//
//  PRZEZNACZENIE: Rejestruje klasę okna.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LANGTON));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(RGB(125,24,200));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LANGTON);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}



BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      400, 100, 1000, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static App ant(77, 77);
    switch (message)
    {

    case WM_CREATE:
    {
        ant.init(hwnd);

        HWND button1 = CreateWindow(TEXT("button"), TEXT("1 STEP"),
            WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            580, 100, 100, 100,
            hwnd, (HMENU)1, NULL, NULL);
        HWND button2 = CreateWindow(TEXT("button"), TEXT("100 STEPS"),
            WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            750, 100, 100, 100,
            hwnd, (HMENU)2, NULL, NULL);
        HWND button3 = CreateWindow(TEXT("button"), TEXT("1000 STEPS"),
            WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            580, 250, 100,100,
            hwnd, (HMENU)3, NULL, NULL);
        HWND button4 = CreateWindow(TEXT("button"), TEXT("RESET"),
            WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            750, 250, 100,100,
            hwnd, (HMENU)4, NULL, NULL);
         hedit = CreateWindow(TEXT("EDIT"), TEXT("Set Ant X position"), WS_CHILD | WS_VISIBLE, 575,400, 120, 20, hwnd, (HMENU)7, 0, 0, 0);
         hedit2 = CreateWindow(TEXT("EDIT"), TEXT("Set Ant Y position"), WS_CHILD | WS_VISIBLE, 700, 400, 120, 20, hwnd,(HMENU)6, 0, 0, 0);

        HWND button5 = CreateWindow(TEXT("button"), TEXT("SUBMIT POSITION"),
            WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            830, 380, 130, 60,
            hwnd, (HMENU)5, NULL, NULL);

    }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analizuj zaznaczenia menu:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hwnd);
                break;
            case 1:
            {
                ant.play();
            }
            break;
            case 2:
            {
                ant.playWithoutDraw(100);    
            }
            break;
            case 3:
            {
                ant.playWithoutDraw(1000);
            }
            break;
            case 4:
            {
                ant.reset();
            }
            break;
            case 5:
            {
                ant.setPosition(hwnd, 7, 6);
            }
            break;
            break;
            default:
                return DefWindowProc(hwnd, message, wParam, lParam);
            } 
        }
        break;
        //        case WM_SIZE:
    case WM_LBUTTONDOWN:
        break;
    case WM_RBUTTONDOWN:
        ::SendMessage(hwnd, WM_DESTROY, 0, 0L);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        
        ant.paint(hwnd, ps);
        ant.draw();
        EndPaint(hwnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

// Procedura obsługi komunikatów dla okna informacji o programie.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
