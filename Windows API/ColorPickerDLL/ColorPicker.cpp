#include "ColorPicker.h"
#include "resource.h"
#include <iostream>
#include "windows.h"
#include "SharedData.h"

HINSTANCE hColorPickerInstance;
HWND hwnd;
HWND hMain;
static bool classRegistered = false;
HBITMAP hBitmap;

extern "C" DLL_EXPORT int WINAPI AnotherWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, HWND hMainWindow);

LRESULT CALLBACK ColorPickerProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void ShowColorPicker();

int WINAPI AnotherWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, HWND hMainWindow) {
    hColorPickerInstance = hInstance;
    hMain = hMainWindow;

    hBitmap = (HBITMAP)LoadImageA(hColorPickerInstance, TEXT("colorpicker.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    if (!hBitmap) {
        MessageBox(NULL, TEXT("Failed to load image"), TEXT("Error"), MB_ICONERROR | MB_OK);
        return 0;
    }

    ShowColorPicker();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

void ShowColorPicker() {
    // If class is registered, no need to repeat this code
    if (!classRegistered) {
        WNDCLASSEX wc;
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = 0;
        wc.lpfnWndProc = ColorPickerProcedure;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hColorPickerInstance;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName = NULL;
        wc.lpszClassName = TEXT("ColorPickerClass");
        wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

        if (!RegisterClassEx(&wc)) {
            return;
        }

        classRegistered = true;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        TEXT("ColorPickerClass"),
        TEXT("Color Picker"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        610,
        345,
        NULL,
        NULL,
        hColorPickerInstance,
        NULL);

    if (hwnd == NULL) {
        return;
    }

    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);
}

LRESULT CALLBACK ColorPickerProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_ERASEBKGND:
        {
            HDC hdc = (HDC)wParam;
            RECT rcClient;
            GetClientRect(hwnd, &rcClient);

            HDC hdcMem = CreateCompatibleDC(hdc);
            HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hBitmap);

            BITMAP bm;
            GetObject(hBitmap, sizeof(bm), &bm);
            StretchBlt(hdc, 0, 0, rcClient.right, rcClient.bottom, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

            SelectObject(hdcMem, hbmOld);
            DeleteDC(hdcMem);

            return 1;
        }
        case WM_CREATE:
            // Create input fields for red green and blue
            CreateWindowEx(
                0,
                TEXT("EDIT"),
                TEXT("0"),
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
                150, 165, 50, 20,
                hwnd,
                (HMENU)ID_EDIT_RED,
                NULL,
                NULL
            );

            CreateWindowEx(
                0,
                TEXT("EDIT"),
                TEXT("0"),
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
                270, 165, 50, 20,
                hwnd,
                (HMENU)ID_EDIT_GREEN,
                NULL,
                NULL
            );

            CreateWindowEx(
                0,
                TEXT("EDIT"),
                TEXT("0"),
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
                370, 165, 50, 20,
                hwnd,
                (HMENU)ID_EDIT_BLUE,
                NULL,
                NULL
            );

            // Button to apply colors
            CreateWindowEx(
                0,
                TEXT("BUTTON"),
                TEXT("OK"),
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                500, 250, 50, 20,
                hwnd,
                (HMENU)ID_BUTTON_OK,
                NULL,
                NULL
            );

            break;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_BUTTON_OK:
                    TCHAR red[4], green[4], blue[4];
                    GetWindowText(GetDlgItem(hwnd, ID_EDIT_RED), red, 4);
                    GetWindowText(GetDlgItem(hwnd, ID_EDIT_GREEN), green, 4);
                    GetWindowText(GetDlgItem(hwnd, ID_EDIT_BLUE), blue, 4);

                    BYTE numeric_red = static_cast<BYTE>(atoi(red));
                    BYTE numeric_green = static_cast<BYTE>(atoi(green));
                    BYTE numeric_blue = static_cast<BYTE>(atoi(blue));


                    ColorData color = { numeric_red, numeric_green, numeric_blue };
                    SendMessage(hMain, WM_COLOR_SELECTED, WPARAM(&color), LPARAM(0));
                    break;
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            hwnd = NULL;
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            UnregisterClassA(TEXT("ColorPickerClass"), hColorPickerInstance);
            break;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
