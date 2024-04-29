#include <windows.h>

// Prototyper för händelseskedehanterare
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void OnButtonClick(HWND hwnd);

// Huvudfunktionen
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Registrera fönsterklassen
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "WindowClass";

    RegisterClass(&wc);

    // Skapa fönstret
    HWND hwnd = CreateWindowEx(0, "WindowClass", "Windows Desktop App (test)", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);

    // Skapa en knapp
    HWND button = CreateWindow("BUTTON", "Alternativ 1", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 200, 30, hwnd, NULL, hInstance, NULL);
    HWND button2 = CreateWindow("BUTTON", "Alternativ 2", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 40, 200, 30, hwnd, NULL, hInstance, NULL);
    HWND button3 = CreateWindow("BUTTON", "Alternativ 3", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 70, 200, 30, hwnd, NULL, hInstance, NULL);

    // Visa fönstret
    ShowWindow(hwnd, nCmdShow);

    // Main message loop
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Händelseskedehanterare
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_COMMAND:
            if (LOWORD(wParam) == BN_CLICKED) {
                OnButtonClick(hwnd);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// Hantera knappklickhändelsen
void OnButtonClick(HWND hwnd) {
    MessageBox(hwnd, "Knappen klickades!", "Meddelande", MB_OK | MB_ICONINFORMATION);
}
