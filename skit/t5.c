#include <windows.h>

// Huvudfönstrets hanterare
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Id för listboxen
#define ID_LISTBOX 1001

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Skapa fönstret
    HWND hwnd;
    MSG Msg;
    WNDCLASS wc = { 0 };

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MyWindowClass";

    RegisterClass(&wc);

    hwnd = CreateWindowEx(0, "MyWindowClass", "Listbox Example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);

    // Skapa listboxen
    CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL | WS_BORDER, 10, 10, 150, 200, hwnd, (HMENU)ID_LISTBOX, hInstance, NULL);

    // Lägg till alternativ i listboxen
    SendMessage(GetDlgItem(hwnd, ID_LISTBOX), LB_ADDSTRING, 0, (LPARAM)"Alternativ 1");
    SendMessage(GetDlgItem(hwnd, ID_LISTBOX), LB_ADDSTRING, 0, (LPARAM)"Alternativ 2");
    SendMessage(GetDlgItem(hwnd, ID_LISTBOX), LB_ADDSTRING, 0, (LPARAM)"Alternativ 3");

    // Main message loop
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}

// Hanterare för huvudfönstret
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_COMMAND:
            // Hantera meddelanden från listboxen
            if (LOWORD(wParam) == ID_LISTBOX && HIWORD(wParam) == LBN_SELCHANGE) {
                // Hämta index för det valda alternativet
                int selectedIndex = SendMessage((HWND)lParam, LB_GETCURSEL, 0, 0);
                if (selectedIndex != LB_ERR) {
                    // Rensa listboxen
                    SendMessage((HWND)lParam, LB_RESETCONTENT, 0, 0);

                    // Lägg till alternativ i listboxen baserat på det valda alternativet
                    switch (selectedIndex) {
                        case 0: // Alternativ 1 valt
                            SendMessage((HWND)lParam, LB_ADDSTRING, 0, (LPARAM)"Alternativ 1");
                            SendMessage((HWND)lParam, LB_ADDSTRING, 0, (LPARAM)"    Alternativ 1.1");
                            SendMessage((HWND)lParam, LB_ADDSTRING, 0, (LPARAM)"    Alternativ 1.2");
                            SendMessage((HWND)lParam, LB_ADDSTRING, 0, (LPARAM)"    Alternativ 1.3");
                            SendMessage((HWND)lParam, LB_ADDSTRING, 0, (LPARAM)"Alternativ 2");
                            SendMessage((HWND)lParam, LB_ADDSTRING, 0, (LPARAM)"Alternativ 3");
                            break;
                        case 1: // Alternativ 2 valt
                            SendMessage((HWND)lParam, LB_ADDSTRING, 0, (LPARAM)"Alternativ 1");
                            SendMessage((HWND)lParam, LB_ADDSTRING, 0, (LPARAM)"Alternativ 2");
                            SendMessage((HWND)lParam, LB_ADDSTRING, 0, (LPARAM)"    Alternativ 2.1");
                            SendMessage((HWND)lParam, LB_ADDSTRING, 0, (LPARAM)"    Alternativ 2.2");
                            SendMessage((HWND)lParam, LB_ADDSTRING, 0, (LPARAM)"Alternativ 3");
                            break;
                        case 2: // Alternativ 3 valt
                            SendMessage((HWND)lParam, LB_ADDSTRING, 0, (LPARAM)"Alternativ 1");
                            SendMessage((HWND)lParam, LB_ADDSTRING, 0, (LPARAM)"Alternativ 2");
                            SendMessage((HWND)lParam, LB_ADDSTRING, 0, (LPARAM)"Alternativ 3");
                            SendMessage((HWND)lParam, LB_ADDSTRING, 0, (LPARAM)"    Alternativ 3.1");
                            break;
                    }
                }
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
