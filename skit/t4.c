#include <windows.h>

// Huvudfönstrets hanterare
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Id för den första listboxen
#define ID_LISTBOX1 1001
// Id för den andra listboxen
#define ID_LISTBOX2 1002

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Skapa fönstret
    HWND hwnd;
    MSG Msg;
    WNDCLASS wc = { 0 };

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MyWindowClass";

    RegisterClass(&wc);
    

    hwnd = CreateWindowEx(0, "MyWindowClass", "My First Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
    // (Optional window styles, Window class, window title, window style, ... , ... , ... , ... , Parent window, Menue, instace handle, additional application data)
    ShowWindow(hwnd, nCmdShow);

    // Skapa den första listboxen
    CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL, 10, 10, 150, 200, hwnd, (HMENU)ID_LISTBOX1, hInstance, NULL);

    // Lägg till alternativ i den första listboxen
    SendMessage(GetDlgItem(hwnd, ID_LISTBOX1), LB_ADDSTRING, 0, (LPARAM)"Alternativ 1");
    SendMessage(GetDlgItem(hwnd, ID_LISTBOX1), LB_ADDSTRING, 0, (LPARAM)"Alternativ 2");
    SendMessage(GetDlgItem(hwnd, ID_LISTBOX1), LB_ADDSTRING, 0, (LPARAM)"Alternativ 3");

    // Skapa den andra listboxen (initialt dold)
    CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_VSCROLL, 200, 10, 150, 200, hwnd, (HMENU)ID_LISTBOX2, hInstance, NULL);

    // Main message loop
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}

// Hanterare för huvudfönstret
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hListBox2;

    switch (msg) {
        case WM_COMMAND:
            // Hantera meddelanden från den första listboxen
            if (LOWORD(wParam) == ID_LISTBOX1 && HIWORD(wParam) == LBN_SELCHANGE) {
                // Visa den andra listboxen och uppdatera dess alternativ baserat på det valda alternativet i den första listboxen
                int selectedIndex = SendMessage((HWND)lParam, LB_GETCURSEL, 0, 0);
                if (selectedIndex != LB_ERR) {
                    // Rensa den andra listboxen
                    SendMessage(hListBox2, LB_RESETCONTENT, 0, 0);

                    // Lägg till alternativ i den andra listboxen baserat på det valda alternativet i den första listboxen
                    switch (selectedIndex) {
                        case 0: // Alternativ 1 valt
                            SendMessage(hListBox2, LB_ADDSTRING, 0, (LPARAM)"Alternativ 1.1");
                            SendMessage(hListBox2, LB_ADDSTRING, 0, (LPARAM)"Alternativ 1.2");
                            SendMessage(hListBox2, LB_ADDSTRING, 0, (LPARAM)"Alternativ 1.3");
                            break;
                        case 1: // Alternativ 2 valt
                            SendMessage(hListBox2, LB_ADDSTRING, 0, (LPARAM)"Alternativ 2.1");
                            SendMessage(hListBox2, LB_ADDSTRING, 0, (LPARAM)"Alternativ 2.2");
                            break;
                        case 2: // Alternativ 3 valt
                            SendMessage(hListBox2, LB_ADDSTRING, 0, (LPARAM)"Alternativ 3.1");
                            break;
                    }

                    // Visa den andra listboxen
                    EnableWindow(hListBox2, TRUE);
                    ShowWindow(hListBox2, TRUE);
                }
            }
            break;
        case WM_CREATE:
            // Skapa den andra listboxen när fönstret skapas
            hListBox2 = CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_VSCROLL, 200, 10, 150, 200, hwnd, (HMENU)ID_LISTBOX2, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
