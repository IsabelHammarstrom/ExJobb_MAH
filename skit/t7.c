#include <windows.h>

// Prototyper för händelseskedehanterare
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void OnButtonClick(HWND hwnd, WPARAM buttonID);

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
        case WM_CREATE: {
            // Skapa huvudmenyn
            HMENU hMenu = CreateMenu();
            
            // Skapa undermenyer för varje huvudknapp
            HMENU hSubMenu1 = CreatePopupMenu();
            HMENU hSubMenu11 = CreatePopupMenu();
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu1, "Alternativ 1");
            AppendMenu(hSubMenu1, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu11, "Alternativ 1.1");
            AppendMenu(hSubMenu11, MF_STRING, 1, "Alternativ 1.1.1");
            AppendMenu(hSubMenu1, MF_STRING, 2, "Alternativ 1.2");
            AppendMenu(hSubMenu1, MF_STRING, 3, "Alternativ 1.3");

            HMENU hSubMenu2 = CreatePopupMenu();
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu2, "Alternativ 2");
            AppendMenu(hSubMenu2, MF_STRING, 4, "Alternativ 2.1");
            AppendMenu(hSubMenu2, MF_STRING, 5, "Alternativ 2.2");

            HMENU hSubMenu3 = CreatePopupMenu();
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu3, "Alternativ 3");
            AppendMenu(hSubMenu3, MF_STRING, 6, "Alternativ 3.1");

            // Associera menyn med fönstret
            SetMenu(hwnd, hMenu);
        }
        break;
        case WM_COMMAND:
            // Kalla på funktionen OnButtonClick med parametern som motsvarar vilken knapp som har tryckts på
            OnButtonClick(hwnd, wParam);
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
void OnButtonClick(HWND hwnd, WPARAM buttonID) {
    // Visa olika meddelanden baserat på vilken knapp som klickades på
    switch (buttonID) {
        case 1:
            MessageBox(hwnd, "Du klickade på Alternativ 1.1.1!", "Meddelande", MB_OK | MB_ICONINFORMATION);
            break;
        case 2:
            MessageBox(hwnd, "Du klickade på Alternativ 1.2!", "Meddelande", MB_OK | MB_ICONINFORMATION);
            break;
        case 3:
            MessageBox(hwnd, "Du klickade på Alternativ 1.3!", "Meddelande", MB_OK | MB_ICONINFORMATION);
            break;
        case 4:
            MessageBox(hwnd, "Du klickade på Alternativ 2.1!", "Meddelande", MB_OK | MB_ICONINFORMATION);
            break;
        case 5:
            MessageBox(hwnd, "Du klickade på Alternativ 2.2!", "Meddelande", MB_OK | MB_ICONINFORMATION);
            break;
        case 6:
            MessageBox(hwnd, "Du klickade på Alternativ 3.1!", "Meddelande", MB_OK | MB_ICONINFORMATION);
            break;
    }
}
