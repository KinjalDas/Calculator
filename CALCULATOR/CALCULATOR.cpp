// CALCULATOR.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "CALCULATOR.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
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

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CALCULATOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CALCULATOR));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CALCULATOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(180, 180, 180));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CALCULATOR);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,
      CW_USEDEFAULT, 0, 205, 520, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	long int number,result; 
	int op;
    switch (message)
    {
	case WM_CREATE:
		{
			CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("0"), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP, 105, 10, 50, 20, hWnd, (HMENU)IDC_NSTACK, GetModuleHandle(NULL), NULL);
			CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP, 160, 10, 20, 20, hWnd, (HMENU)IDC_OPSTACK, GetModuleHandle(NULL), NULL);
			CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("0"), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP, 10, 50, 170, 35, hWnd, (HMENU)IDC_OPONE, GetModuleHandle(NULL), NULL);
			CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "), WS_CHILD | ES_AUTOHSCROLL | WS_TABSTOP, 160, 10, 20, 20, hWnd, (HMENU)IDC_OP, GetModuleHandle(NULL), NULL);
			CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("+"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 10, 95, 50, 50, hWnd, (HMENU)IDC_ADD, GetModuleHandle(NULL), NULL);
			CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("-"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 70, 95, 50, 50, hWnd, (HMENU)IDC_SUB, GetModuleHandle(NULL), NULL);
			CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("x"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 130, 95, 50, 50, hWnd, (HMENU)IDC_MULT, GetModuleHandle(NULL), NULL);
			CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("/"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 10, 155, 50, 50, hWnd, (HMENU)IDC_DIV, GetModuleHandle(NULL), NULL);
			CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("%"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 70, 155, 50, 50, hWnd, (HMENU)IDC_REM, GetModuleHandle(NULL), NULL);
			CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("="), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 130, 155, 50, 50, hWnd, (HMENU)IDC_RESULT, GetModuleHandle(NULL), NULL);
			CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("C"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 10, 215, 50, 50, hWnd, (HMENU)IDC_C, GetModuleHandle(NULL), NULL);
			CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("AC"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 70, 215, 50, 50, hWnd, (HMENU)IDC_AC, GetModuleHandle(NULL), NULL);
			CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("1"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 130, 215, 50, 50, hWnd, (HMENU)IDC_ONE, GetModuleHandle(NULL), NULL);
			CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("2"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 10, 275, 50, 50, hWnd, (HMENU)IDC_TWO, GetModuleHandle(NULL), NULL);
			CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("3"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 70, 275, 50, 50, hWnd, (HMENU)IDC_THREE, GetModuleHandle(NULL), NULL);
			CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("4"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 130, 275, 50, 50, hWnd, (HMENU)IDC_FOUR, GetModuleHandle(NULL), NULL);
			CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("5"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 10, 335, 50, 50, hWnd, (HMENU)IDC_FIVE, GetModuleHandle(NULL), NULL);
			CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("6"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 70, 335, 50, 50, hWnd, (HMENU)IDC_SIX, GetModuleHandle(NULL), NULL);
			CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("7"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 130, 335, 50, 50, hWnd, (HMENU)IDC_SEVEN, GetModuleHandle(NULL), NULL);
			CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("8"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 10, 395, 50, 50, hWnd, (HMENU)IDC_EIGHT, GetModuleHandle(NULL), NULL);
			CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("9"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 70, 395, 50, 50, hWnd, (HMENU)IDC_NINE, GetModuleHandle(NULL), NULL);
			CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("0"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 130, 395, 50, 50, hWnd, (HMENU)IDC_ZERO, GetModuleHandle(NULL), NULL);
		}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case IDC_C:
				SetDlgItemInt(hWnd,IDC_OPONE,0,true);
				break;
			case IDC_AC:
				SetDlgItemInt(hWnd,IDC_OPONE,0,true);
				SetDlgItemText(hWnd,IDC_OPSTACK,TEXT(" "));
				SetDlgItemInt(hWnd, IDC_OP, 0, true);
				SetDlgItemInt(hWnd, IDC_NSTACK, 0, true);
				break;
			case IDC_ADD:
				op = GetDlgItemInt(hWnd, IDC_OP, NULL, true);
				number = GetDlgItemInt(hWnd, IDC_OPONE, NULL, true);
				if (op>0) {
					result = GetDlgItemInt(hWnd, IDC_NSTACK, NULL, true);
					switch (op) {
					case 1:
						number = result + number;
						break;
					case 2:
						number = result - number;
						break;
					case 3:
						number = result * number;
						break;
					case 4:
						if (number == 0) {
							MessageBox(hWnd, TEXT("division by 0 not allowed"), TEXT("ERROR!!!"), MB_OK);
							break;
						}
						number = result / number;
						break;
					case 5:
						if (number == 0) {
							MessageBox(hWnd, TEXT("division by 0 not allowed"), TEXT("ERROR!!!"), MB_OK);
							break;
						}
						number = result % number;
						break;
					default:break;
					}
				}
				SetDlgItemInt(hWnd, IDC_NSTACK, number, true);
				SetDlgItemText(hWnd, IDC_OPSTACK,TEXT("+"));
				SetDlgItemInt(hWnd, IDC_OP, 1, true);
				SetDlgItemInt(hWnd, IDC_OPONE, 0, true);
				break;
			case IDC_SUB:
				op = GetDlgItemInt(hWnd, IDC_OP, NULL, true);
				number = GetDlgItemInt(hWnd, IDC_OPONE, NULL, true);
				if (op>0) {
					result = GetDlgItemInt(hWnd, IDC_NSTACK, NULL, true);
					switch (op) {
					case 1:
						number = result + number;
						break;
					case 2:
						number = result - number;
						break;
					case 3:
						number = result * number;
						break;
					case 4:
						if (number == 0) {
							MessageBox(hWnd, TEXT("division by 0 not allowed"), TEXT("ERROR!!!"), MB_OK);
							break;
						}
						number = result / number;
						break;
					case 5:
						if (number == 0) {
							MessageBox(hWnd, TEXT("division by 0 not allowed"), TEXT("ERROR!!!"), MB_OK);
							break;
						}
						number = result % number;
						break;
					default:break;
					}
				}
				SetDlgItemInt(hWnd, IDC_NSTACK, number, true);
				SetDlgItemText(hWnd, IDC_OPSTACK, TEXT("-"));
				SetDlgItemInt(hWnd, IDC_OP, 2, true);
				SetDlgItemInt(hWnd, IDC_OPONE, 0, true);
				break;
			case IDC_MULT:
				op = GetDlgItemInt(hWnd, IDC_OP, NULL, true);
				number = GetDlgItemInt(hWnd, IDC_OPONE, NULL, true);
				if (op>0) {
					result = GetDlgItemInt(hWnd, IDC_NSTACK, NULL, true);
					switch (op) {
					case 1:
						number = result + number;
						break;
					case 2:
						number = result - number;
						break;
					case 3:
						number = result * number;
						break;
					case 4:
						if (number == 0) {
							MessageBox(hWnd, TEXT("division by 0 not allowed"), TEXT("ERROR!!!"), MB_OK);
							break;
						}
						number = result / number;
						break;
					case 5:
						if (number == 0) {
							MessageBox(hWnd, TEXT("division by 0 not allowed"), TEXT("ERROR!!!"), MB_OK);
							break;
						}
						number = result % number;
						break;
					default:break;
					}
				}
				SetDlgItemInt(hWnd, IDC_NSTACK, number, true);
				SetDlgItemText(hWnd, IDC_OPSTACK, TEXT("X"));
				SetDlgItemInt(hWnd, IDC_OP, 3, true);
				SetDlgItemInt(hWnd, IDC_OPONE, 0, true);
				break;
			case IDC_DIV:
				op = GetDlgItemInt(hWnd, IDC_OP, NULL, true);
				number = GetDlgItemInt(hWnd, IDC_OPONE, NULL, true);
				if (op>0) {
					result = GetDlgItemInt(hWnd, IDC_NSTACK, NULL, true);
					switch (op) {
					case 1:
						number = result + number;
						break;
					case 2:
						number = result - number;
						break;
					case 3:
						number = result * number;
						break;
					case 4:
						if (number == 0) {
							MessageBox(hWnd, TEXT("division by 0 not allowed"), TEXT("ERROR!!!"), MB_OK);
							break;
						}
						number = result / number;
						break;
					case 5:
						if (number == 0) {
							MessageBox(hWnd, TEXT("division by 0 not allowed"), TEXT("ERROR!!!"), MB_OK);
							break;
						}
						number = result % number;
						break;
					default:break;
					}
				}
				SetDlgItemInt(hWnd, IDC_NSTACK, number, true);
				SetDlgItemText(hWnd, IDC_OPSTACK, TEXT("/"));
				SetDlgItemInt(hWnd, IDC_OP, 4, true);
				SetDlgItemInt(hWnd, IDC_OPONE, 0, true);
				break;
			case IDC_REM:
				op = GetDlgItemInt(hWnd, IDC_OP, NULL, true);
				number = GetDlgItemInt(hWnd, IDC_OPONE, NULL, true);
				if (op>0) {
					result = GetDlgItemInt(hWnd, IDC_NSTACK, NULL, true);
					switch (op) {
					case 1:
						number = result + number;
						break;
					case 2:
						number = result - number;
						break;
					case 3:
						number = result * number;
						break;
					case 4:
						if (number == 0) {
							MessageBox(hWnd, TEXT("division by 0 not allowed"), TEXT("ERROR!!!"), MB_OK);
							break;
						}
						number = result / number;
						break;
					case 5:
						if (number == 0) {
							MessageBox(hWnd, TEXT("division by 0 not allowed"), TEXT("ERROR!!!"), MB_OK);
							break;
						}
						number = result % number;
						break;
					default:break;
					}
				}
				SetDlgItemInt(hWnd, IDC_NSTACK, number, true);
				SetDlgItemText(hWnd, IDC_OPSTACK, TEXT("%"));
				SetDlgItemInt(hWnd, IDC_OP, 5, true);
				SetDlgItemInt(hWnd, IDC_OPONE, 0, true);
				break;
			case IDC_RESULT:
				op=GetDlgItemInt(hWnd, IDC_OP, NULL,true);
				number = GetDlgItemInt(hWnd, IDC_NSTACK, NULL, true);
				result = GetDlgItemInt(hWnd, IDC_OPONE, NULL, true);
				if (op == 0) {
					SetDlgItemInt(hWnd, IDC_OPONE, result, true);
				}
				else if (op == 1) {
					number += result;
					SetDlgItemInt(hWnd, IDC_OPONE, number, true);
				}
				else if (op == 2) {
					number -= result;
					SetDlgItemInt(hWnd, IDC_OPONE, number, true);
				}
				else if (op == 3) {
					number *= result;
					SetDlgItemInt(hWnd, IDC_OPONE, number, true);
				}
				else if (op == 4) {
					if (result == 0) {
						MessageBox(hWnd, TEXT("division by 0 not allowed"), TEXT("ERROR!!!"), MB_OK);
						break;
					}
					number /= result;
					SetDlgItemInt(hWnd, IDC_OPONE, number, true);
				}
				else if (op == 5) {
					if (result == 0) {
						MessageBox(hWnd, TEXT("division by 0 not allowed"), TEXT("ERROR!!!"), MB_OK);
						break;
					}
					number %= result;
					SetDlgItemInt(hWnd, IDC_OPONE, number, true);
				}
				SetDlgItemInt(hWnd, IDC_OP, 0, true);
				SetDlgItemInt(hWnd, IDC_NSTACK, number, true);
				SetDlgItemText(hWnd,IDC_OPSTACK,TEXT(" "));
				break;
			case IDC_ZERO:
			{
			number = GetDlgItemInt(hWnd, IDC_OPONE, NULL, true);
			number = (number * 10) + 0;
			SetDlgItemInt(hWnd, IDC_OPONE, number, true);
			}
			break;
			case IDC_ONE:
			{
			number = GetDlgItemInt(hWnd, IDC_OPONE, NULL, true);
			number = (number * 10) + 1;
			SetDlgItemInt(hWnd, IDC_OPONE, number, true);
			}
			break;
			case IDC_TWO:
			{
			number = GetDlgItemInt(hWnd, IDC_OPONE, NULL, true);
			number = (number * 10) + 2;
			SetDlgItemInt(hWnd, IDC_OPONE, number, true);
			}
			break;
			case IDC_THREE:
			{
			number = GetDlgItemInt(hWnd, IDC_OPONE, NULL, true);
			number = (number * 10) + 3;
			SetDlgItemInt(hWnd, IDC_OPONE, number, true);
			}
			break;
			case IDC_FOUR:
			{
			number = GetDlgItemInt(hWnd, IDC_OPONE, NULL, true);
			number = (number * 10) + 4;
			SetDlgItemInt(hWnd, IDC_OPONE, number, true);
			}
			break;
			case IDC_FIVE:
			{
			number = GetDlgItemInt(hWnd, IDC_OPONE, NULL, true);
			number = (number * 10) + 5;
			SetDlgItemInt(hWnd, IDC_OPONE, number, true);
			}
			break;
			case IDC_SIX:
			{
			number = GetDlgItemInt(hWnd, IDC_OPONE, NULL, true);
			number = (number * 10) + 6;
			SetDlgItemInt(hWnd, IDC_OPONE, number, true);
			}
			break;
			case IDC_SEVEN:
			{
			number = GetDlgItemInt(hWnd, IDC_OPONE, NULL, true);
			number = (number * 10) + 7;
			SetDlgItemInt(hWnd, IDC_OPONE, number, true);
			}
			break;
			case IDC_EIGHT:
			{
			number = GetDlgItemInt(hWnd, IDC_OPONE, NULL, true);
			number = (number * 10) + 8;
			SetDlgItemInt(hWnd, IDC_OPONE, number, true);
			}
			break;
			case IDC_NINE:
			{
			number=GetDlgItemInt(hWnd, IDC_OPONE, NULL, true);
			number = (number * 10) + 9;
			SetDlgItemInt(hWnd, IDC_OPONE, number, true);
			}
			break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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
