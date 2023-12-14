#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

// Ensure DLL_EXPORT is defined appropriately
#ifdef COLORPICKERDLL_EXPORTS
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

// Function declaration
DLL_EXPORT int WINAPI AnotherWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, HWND hMainWindow);

#ifdef __cplusplus
}
#endif

#endif
