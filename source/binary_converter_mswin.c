#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "resource.h"
#include "binary_converter_base.h"

#define ID_INPUT1 1
#define ID_STRING 3
#define ID_BUTTON 4
#define ID_OUTPUT 5
#define ID_STATIC_TEXT 2
#define ID_STATIC_TEXT2 6
#define MAX_INPUT_LENGTH 512

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hInput1, hString, hOutput, hButton;

    switch (uMsg) {
    case WM_CREATE:
		HWND hStaticText = CreateWindow("STATIC", "Binary places:", WS_CHILD | WS_VISIBLE, 10, 10, 100, 20, hwnd, (HMENU)ID_STATIC_TEXT, NULL, NULL);
        hInput1 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 110, 10, 45, 20, hwnd, (HMENU)ID_INPUT1, NULL, NULL);
		HWND hStaticText2 = CreateWindow("STATIC", "Decimal number:", WS_CHILD | WS_VISIBLE, 10, 40, 300, 20, hwnd, (HMENU)ID_STATIC_TEXT2, NULL, NULL);
        hString = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE, 10, 60, 300, 60, hwnd, (HMENU)ID_STRING, NULL, NULL);
        hButton = CreateWindow("BUTTON", "Convert", WS_CHILD | WS_VISIBLE, 10, 130, 100, 30, hwnd, (HMENU)ID_BUTTON, NULL, NULL);
        hOutput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_READONLY, 10, 170, 300, 100, hwnd, (HMENU)ID_OUTPUT, NULL, NULL);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == ID_BUTTON) {
            char input1[9], inpstr[MAX_INPUT_LENGTH];
            int prec, result;

            GetWindowText(hInput1, input1, sizeof(input1));
            GetWindowText(hString, inpstr, sizeof(inpstr));

            prec = atoi(input1);
            result = prec;
			
			int buflen = MAX_INPUT_LENGTH + prec;
			if (prec < 0) buflen = 100;
			char buffer[buflen];
			for(int i = 0; i < buflen; i++)
				buffer[i] = '0';
			
			char neg = 0;
			
			if (*inpstr == '-'){
				*inpstr = '0';
				neg = 1;
			}
			
			int dot = check(inpstr, MAX_INPUT_LENGTH);
			
			char *rem = inpstr + dot;
			
			

			if (prec < 0)
				snprintf(buffer, sizeof(buffer), "Precision must not be negative!");
			else
			{
				//snprintf(buffer, sizeof(buffer), "Result: %d, String: %s", result, inpstr);
				if (dot) {
					if (neg) buffer[0] = '-';
					divide_by_2(inpstr + count_leading_0s(inpstr), buffer + neg);
					multiply_by_2(rem, prec, buffer + neg);
					snprintf(buffer, sizeof(buffer), "%s", buffer);
				} else snprintf(buffer, sizeof(buffer), "Invalid number format!");
			}
            SetWindowText(hOutput, buffer);
        }
        break;
	
	case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
			HBRUSH hBrush = CreateSolidBrush(RGB(184, 184, 184));
			//HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
            FillRect(hdc, &ps.rcPaint, hBrush);
			DeleteObject(hBrush);
            EndPaint(hwnd, &ps);
        } return 0;
	
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "SampleWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON));

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, "Decimal to binary converter", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 340, 320, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}