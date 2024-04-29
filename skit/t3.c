#include <windows.h>

// Huvudfönstrets hanterare
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Id för knappen
#define ID_BUTTON 1001

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Skapa fönstret
    HWND hwnd;
    MSG Msg;
    WNDCLASS wc = { 0 };

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MyWindowClass";

    RegisterClass(&wc);

    hwnd = CreateWindowEx(0, "MyWindowClass", "Child Windows Example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);

    // Skapa en knapp
    CreateWindow("BUTTON", "Change Content", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 150, 30, hwnd, (HMENU)ID_BUTTON, hInstance, NULL);

    // Main message loop
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}

// Hanterare för huvudfönstret
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hChildWindow = NULL;

    switch (msg) {
        case WM_CREATE:
            // Skapa ett barnfönster när fönstret skapas
            hChildWindow = CreateWindow("STATIC", "Initial Content", WS_CHILD | WS_VISIBLE, 50, 50, 200, 100, hwnd, NULL, NULL, NULL);
            break;
        case WM_COMMAND:
            // Hantera knappklickhändelsen
            if (LOWORD(wParam) == ID_BUTTON) {
                // Byt ut innehållet i barnfönstret när knappen klickas
                SetWindowText(hChildWindow, "New Content");
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
