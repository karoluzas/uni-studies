#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <windows.h>
#include <iostream>
#include <wingdi.h>
#include <tchar.h>
#include "resource.h"
#include "DrawingState.h"
#include "ColorPicker.h"
#include "SharedData.h"
#include <stdio.h>
#include <stdlib.h>

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
void SaveImage(HWND hwnd);
void LoadPixels(HWND hwnd);

TCHAR szClassName[ ] = _T("paintexe");
DrawingState drawingState;
HINSTANCE thisInstance;
HWND hMainWindow;
POINT prevPos;
HPEN hOldPen;
HPEN hPen;
HDC hdc;

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;
    thisInstance = hThisInstance;

    // The Window structure
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);

    wincl.hIcon = LoadIcon (hThisInstance, MAKEINTRESOURCE(IDI_PAINT));
    wincl.hIconSm = LoadIcon (hThisInstance, MAKEINTRESOURCE(IDI_PAINT));
    wincl.hCursor = LoadCursor (NULL, IDC_CROSS);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));

    HMENU hMenuFile = LoadMenu(hThisInstance, MAKEINTRESOURCE(IDR_MENU_FILE));
    HMENU hMenuTools = LoadMenu(hThisInstance, MAKEINTRESOURCE(IDR_MENU_TOOLS));
    HMENU hMenuBar = CreateMenu();

    // Attach the loaded menus to the menu bar
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hMenuFile, TEXT("&File"));
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hMenuTools, TEXT("&Tools"));

    // Instantiating drawing state as pen with black color
    drawingState.currentTool = IDM_TOOL_PEN;
    drawingState.currentColor = RGB(0, 0, 0);
    drawingState.toolSize = 10;

    if (!RegisterClassEx (&wincl))
        return 0;

    // Creating the program
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("paintexe"),       /* Title Text */
           WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           800,                 /* The programs width */
           800,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           hMenuBar,            /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    SetMenu(hwnd, hMenuBar);
    ShowWindow (hwnd, nCmdShow);

    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}

// Called by DispatchMessage()
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    ColorData* receivedColor = nullptr;
    switch (message)
    {
        case WM_CREATE:
            hMainWindow = hwnd;
            break;
        case WM_DESTROY:
            PostQuitMessage (0);
            break;
        // Menu commands
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDM_FILE_SAVE:
                    SaveImage(hwnd);
                    break;
                case IDM_FILE_LOAD:
                    LoadPixels(hwnd);
                    break;
                case IDM_FILE_EXIT:
                    PostMessage(hwnd, WM_CLOSE, 0, 0);
                    break;
                case IDM_TOOL_PEN:
                    drawingState.currentTool = IDM_TOOL_PEN;
                    drawingState.toolSize = 10;
                    drawingState.currentColor = RGB(0,0,0);
                    break;
                case IDM_TOOL_ERASER:
                    drawingState.currentTool = IDM_TOOL_ERASER;
                    drawingState.currentColor = RGB(255,255,255);
                    break;
                case IDM_TOOL_BRUSH_CUSTOMIZATION:
                    AnotherWindow(thisInstance, NULL, NULL, TRUE, hwnd);
                    break;
                case IDM_TOOL_LINE:
                    drawingState.currentTool = IDM_TOOL_LINE;
                    break;
                case IDM_TOOL_CIRCLE:
                    drawingState.currentTool = IDM_TOOL_CIRCLE;
                    break;
                case IDM_TOOL_RECTANGLE:
                    drawingState.currentTool = IDM_TOOL_RECTANGLE;
                    break;
            }
            break;
        case WM_LBUTTONDOWN:
            hdc = GetDC(hwnd);
            prevPos.x = LOWORD(lParam);
            prevPos.y = HIWORD(lParam);

            if (drawingState.currentTool == IDM_TOOL_ERASER || drawingState.currentTool == IDM_TOOL_PEN || drawingState.currentTool == IDM_TOOL_LINE) {
                hPen = CreatePen(PS_SOLID, drawingState.toolSize, drawingState.currentColor);
                hOldPen = (HPEN)SelectObject(hdc, hPen);

                MoveToEx(hdc, prevPos.x, prevPos.y, NULL);
                LineTo(hdc, prevPos.x, prevPos.y);
                SelectObject(hdc, hOldPen);

                // Clean up resources
                DeleteObject(hPen);
                ReleaseDC(hwnd, hdc);
            }
            break;
        case WM_MOUSEMOVE:
        {
            // Check if left mouse button is down
            if (wParam & MK_LBUTTON)
            {
                hdc = GetDC(hwnd);
                int xPos = LOWORD(lParam);
                int yPos = HIWORD(lParam);

                if (drawingState.currentTool == IDM_TOOL_PEN || drawingState.currentTool == IDM_TOOL_ERASER) {
                    // Draw a line from previous position to current position
                    hPen = CreatePen(PS_SOLID, drawingState.toolSize, drawingState.currentColor);

                    SelectObject(hdc, hPen);
                    MoveToEx(hdc, prevPos.x, prevPos.y, NULL);
                    LineTo(hdc, xPos, yPos);

                    prevPos.x = xPos;
                    prevPos.y = yPos;

                    // Cleaning up resources
                    ReleaseDC(hwnd, hdc);
                    DeleteObject(hPen);
                }
            }
            break;
        case WM_LBUTTONUP:
            hdc = GetDC(hwnd);
            int xPos = LOWORD(lParam);
            int yPos = HIWORD(lParam);

            hPen = CreatePen(PS_SOLID, drawingState.toolSize, drawingState.currentColor);
            SelectObject(hdc, hPen);

            if (drawingState.currentTool == IDM_TOOL_LINE) {
                MoveToEx(hdc, prevPos.x, prevPos.y, NULL);
                LineTo(hdc, xPos, yPos);
            } else if (drawingState.currentTool == IDM_TOOL_CIRCLE) {
                Ellipse(hdc, prevPos.x, prevPos.y, xPos, yPos);
            } else if (drawingState.currentTool == IDM_TOOL_RECTANGLE) {
                Rectangle(hdc, prevPos.x, prevPos.y, xPos, yPos);
            }

            // Cleaning up resources
            DeleteObject(hPen);
            ReleaseDC(hwnd, hdc);
            break;
        }
        case WM_KEYDOWN:
            // 16 corresponds to control key and 17 to shift key
            if (wParam == 16) {
                drawingState.toolSize++;
            } else if (wParam == 17 && drawingState.toolSize != 0) {
                drawingState.toolSize--;
            }
            break;
        case WM_COLOR_SELECTED:
            // Message from ColorPicker when pressing ok button
            receivedColor = reinterpret_cast<ColorData*>(wParam);
            drawingState.currentColor = RGB(receivedColor->red, receivedColor->green, receivedColor->blue);
            break;
        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

void LoadPixels(HWND hwnd) {
    HDC hWndDC = GetDC(hwnd);
    FILE *inputFile = fopen("pixel_info.txt", "r");

    if (inputFile != NULL) {
        char buffer[256];

        while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {
            // Extracting pixel info from file and drawing the pixel
            int x, y, red, green, blue;
            if (sscanf(buffer, "(%d, %d): %d %d %d\n", &x, &y, &red, &green, &blue) == 5) {
                COLORREF color = RGB(red, green, blue);
                SetPixel(hWndDC, x, y, color);
            }
        }
        fclose(inputFile);
        MessageBox(hwnd, TEXT("Image loaded"), TEXT("Success"), MB_OK);
    } else {
        printf("Error opening file for reading.\n");
    }
}

void SaveImage (HWND hwnd) {
    HDC hWndDC = GetDC(hwnd);

    RECT windowRect;
    GetWindowRect(hwnd, &windowRect);
    int width = windowRect.right - windowRect.left;
    int height = windowRect.bottom - windowRect.top;

    // Creating bitmap of current main window, to get pixel information
    HDC bitmapDC = CreateCompatibleDC(hWndDC);
    HBITMAP bitmap = CreateCompatibleBitmap(hWndDC, width, height);
    SelectObject(bitmapDC, bitmap);
    BitBlt(bitmapDC, 0, 0, width, height, hWndDC, 0, 0, SRCCOPY);
    BYTE* bitmapBits = new BYTE[width * height * 3];
    // 3 bytes per pixel (RGB)
    GetBitmapBits(bitmap, width * height * 3, bitmapBits);

    FILE *outputFile = fopen("pixel_info.txt", "w");
    if (outputFile != NULL) {
        for (int y = 0; y  < height; y++) {
            for (int x = 0; x < width; x++) {
                COLORREF color = GetPixel(bitmapDC, x, y);
                BYTE blue = GetBValue(color);
                BYTE green = GetGValue(color);
                BYTE red = GetRValue(color);

                // For optimization, to not store unnecessary white pixel data
                if (red != 255 && green != 255 && blue != 255) {
                    fprintf(outputFile, "(%d, %d): %d %d %d\n", x, y, (int)red, (int)green, (int)blue);
                }
            }
        }

        fclose(outputFile);
        MessageBox(hwnd, TEXT("Image saved"), TEXT("Success"), MB_OK);
    } else {
        printf("Error opening file for writing.\n");
    }

    delete[] bitmapBits;
    DeleteObject(bitmap);
    DeleteDC(bitmapDC);
    ReleaseDC(hwnd, hWndDC);
}
