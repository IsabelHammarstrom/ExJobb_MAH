#include <windows.h>

// Huvudfönstrets hanterare
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Id för knappen
#define ID_BUTTON 1001
// Id för redigeringsrutan
#define ID_EDIT 1002

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Skapa fönstret
    HWND hwnd;
    MSG Msg;
    WNDCLASS wc = { 0 };

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MyWindowClass";

    RegisterClass(&wc);

    hwnd = CreateWindowEx(0, "MyWindowClass", "Add Information Example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);

    // Skapa en knapp
    CreateWindow("BUTTON", "Add Information", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 150, 30, hwnd, (HMENU)ID_BUTTON, hInstance, NULL);

    // Skapa en redigeringsruta för att visa information
    CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 10, 50, 300, 200, hwnd, (HMENU)ID_EDIT, hInstance, NULL);

    // Main message loop
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}

// Hanterare för huvudfönstret
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hEdit;

    switch (msg) {
        case WM_CREATE:
            // Skapa redigeringsrutan när fönstret skapas
            hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 10, 50, 300, 200, hwnd, (HMENU)ID_EDIT, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            break;
        case WM_COMMAND:
            // Hantera knappklickhändelsen
            if (LOWORD(wParam) == ID_BUTTON) {
                // Lägg till information i redigeringsrutan när knappen klickas
                SendMessage(hEdit, EM_REPLACESEL, TRUE, (LPARAM)"Added information\n");
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
