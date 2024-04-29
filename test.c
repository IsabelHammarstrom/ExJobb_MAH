#include <windows.h> 
#include <stdio.h> // För filhantering 
#include "test.h" 
#include <string.h>
#include <stdlib.h>

#define CORRECT_CODE "1234"
#define ID_TEXTBOX 111
#define ID_BUTTON 112

#define ID_LISTBOX1 1
#define ID_LISTBOX2 2
#define ID_LISTBOX3 3
#define ID_LISTBOX4 11 // 10
#define ID_BUTTON1 4
#define ID_BUTTON2 5
#define ID_BUTTON3 6
#define ID_BUTTON4 7
#define ID_BUTTON5 8
#define ID_BUTTON6 9
#define ID_EDIT_BOX 12 // 101
#define ID_EDIT_BOX1 13 // 102
#define ID_EDIT_BOX2 14 // 103
#define ID_EDIT_BOX3 15 // 104
#define ID_SAVE_BUTTON1 10 // 105
#define ID_EDIT_BOX4 12 // 1001
#define ID_EDIT_BOX5 13 // 1002
#define ID_EDIT_BOX6 14 // 1003
#define ID_EDIT_BOX7 15 // 1004
#define ID_SAVE_BUTTON2 16 // 1005
#define MAXSIZE 1000
#define NAMESIZE 20

#define ID_DROPDOWNLIST 101 // 106
#define ID_DROPDOWNLIST1 102 // 1006
#define ID_DROPDOWNLIST2 103 // 1007

#define MAX_STRING_LENGTH 256

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK NewWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
int printFile(HWND hwnd, const char *filename, int listBox);
int printFileToDropdown(HWND hwnd, const char *filename, int dropdownID);
void OnButtonClick(HWND hwnd, WPARAM buttonID);
void SaveTextToFile(HWND hEdit1, HWND hEdit2, HWND hEdit3, HWND hEdit4, const char *filename);
HWND CreateLabelAndEdit(HWND parentWnd, int controlId1, int controlId2, int controlId3, int controlId4);

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void OnMenuClick(HWND hwnd, WPARAM buttonID);

wchar_t SelectedText[MAX_STRING_LENGTH] = L""; // Global sträng för att spara det valda alternativet

HWND g_addHjalpw; // Global variable to store handle to addHjaplw window
HWND g_addHjalpw1; // Global variable to store handle to addHjaplw window
HWND g_code;
int saveBUTTON = 0;
int OptionBUTTON = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HWND hwnd;
    MSG Msg;
    WNDCLASS wc = { 0 };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MyWindowClass";
    RegisterClass(&wc);

    hwnd = CreateWindow("MyWindowClass", "Listbox Example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1400, 600, NULL, NULL, hInstance, NULL);

    HWND hListBox = CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL, 10, 10, 350, 500, hwnd, (HMENU)ID_LISTBOX1, hInstance, NULL);

    printFile(hwnd, listFileName, ID_LISTBOX1);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&Msg, NULL, 0, 0)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            
            HMENU hMenu = CreateMenu();
            
            // Skapa undermenyer för varje huvudknapp
            HMENU hSubMenu1 = CreatePopupMenu();
            HMENU hSubMenu11 = CreatePopupMenu();
            HMENU hSubMenu12 = CreatePopupMenu();
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu1, "Installningar");
            AppendMenu(hSubMenu1, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu11, "Lagga till ny");
            AppendMenu(hSubMenu11, MF_STRING, 4, "Huvudhjalpmedel");
            AppendMenu(hSubMenu11, MF_STRING, 5, "Tillbehor");
            AppendMenu(hSubMenu11, MF_STRING, 6, "Reservdel");
            AppendMenu(hSubMenu1, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu12, "Andring av befintlig artikel");
            AppendMenu(hSubMenu12, MF_STRING, 7, "Huvudhjalpmedel");
            AppendMenu(hSubMenu12, MF_STRING, 8, "Tillbehor");
            AppendMenu(hSubMenu12, MF_STRING, 9, "Reservdel");

            // Associera menyn med fönstret
            SetMenu(hwnd, hMenu);

            break;
        }
        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            
            switch (wmId) {
                MessageBox(hwnd, "WM_COMMAND aktivt", "Meddelande", MB_OK | MB_ICONINFORMATION);
                case ID_LISTBOX1: // Klick på huvudlistboxen
                    if (HIWORD(wParam) == LBN_SELCHANGE) {
                        // Radera befintliga underlistor
                        HWND hPrevSubListBox = GetDlgItem(hwnd, ID_LISTBOX2);
                        if (hPrevSubListBox != NULL) {
                            DestroyWindow(hPrevSubListBox);
                             
                        }
                        HWND hPrevSubSubListBox = GetDlgItem(hwnd, ID_LISTBOX3);
                        if (hPrevSubSubListBox != NULL) {
                            DestroyWindow(hPrevSubSubListBox);
                             
                        }
                        
                        // Hämta det valda alternativet
                        HWND hListBox = (HWND)lParam;
                        int index = SendMessage(hListBox, LB_GETCURSEL, 0, 0);

                        // Skapa en ny listbox baserat på det valda alternativet
                        HWND hSubListBox = CreateWindow("LISTBOX", NULL, WS_VISIBLE | WS_CHILD | LBS_NOTIFY | WS_VSCROLL, 400, 10, 600, 500, hwnd, (HMENU)ID_LISTBOX2, NULL, NULL);

                        // Lägg till alternativ i den nya listboxen
                        printFile(hwnd, fileNames[index], ID_LISTBOX2);

                        // Create new third list box here
                        HWND hSubSubListBox = CreateWindow("LISTBOX", NULL, WS_VISIBLE | WS_CHILD | LBS_NOTIFY | WS_VSCROLL, 1050, 10, 150, 500, hwnd, (HMENU)ID_LISTBOX3, NULL, NULL);
                    }
                    break;
                
                case ID_LISTBOX2: // Klick på underlistboxen (val av underalternativ)
                    if (HIWORD(wParam) == LBN_SELCHANGE) {
                        // Radera befintliga underunderlistan
                        HWND hPrevSubSubListBox = GetDlgItem(hwnd, ID_LISTBOX3);
                        if (hPrevSubSubListBox != NULL) {
                            DestroyWindow(hPrevSubSubListBox);
                             
                        }

                        // Hämta det valda underalternativet
                        HWND hSubListBox = (HWND)lParam;
                        int index = SendMessage(hSubListBox, LB_GETCURSEL, 0, 0);

                        // Skapa en ny underlistbox baserat på det valda underalternativet
                        HWND hSubSubListBox = CreateWindow("LISTBOX", NULL, WS_VISIBLE | WS_CHILD | LBS_NOTIFY | WS_VSCROLL, 1050, 10, 150, 500, hwnd, (HMENU)ID_LISTBOX3, NULL, NULL);

                        // Lägg till alternativ i den nya underlistboxen
                        printFile(hwnd, trNames, ID_LISTBOX3);
                    }
                    break;
                
                case ID_LISTBOX3: // Öppna ett nytt fönster
                    if (HIWORD(wParam) == LBN_SELCHANGE) {
                        // Skapa ett nytt fönster
                        HWND hNewWindow = CreateWindowEx(0, "NewWindowClass", "New Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 400, NULL, NULL, GetModuleHandle(NULL), NULL);
                        
                        // Använd det nya fönsterprocet för det nya fönstret
                        WNDCLASS wc = { 0 };
                        wc.lpfnWndProc = NewWndProc;
                        wc.hInstance = GetModuleHandle(NULL);
                        wc.lpszClassName = "NewWindowClass"; // Sätt ett nytt namn för fönsterklassen
                        RegisterClass(&wc);
                        
                        // Hämta det valda underalternativet från den första listboxen
                        HWND hFirstListBox = GetDlgItem(hwnd, ID_LISTBOX1);
                        int indexFirstListBox = SendMessage(hFirstListBox, LB_GETCURSEL, 0, 0);

                        // Hämta det valda underalternativet från den andra listboxen
                        HWND hSecondListBox = GetDlgItem(hwnd, ID_LISTBOX2);
                        int indexSecondListBox = SendMessage(hSecondListBox, LB_GETCURSEL, 0, 0);

                        // Hämta det valda underalternativet från den tredje listboxen
                        HWND hThirdListBox = GetDlgItem(hwnd, ID_LISTBOX3);
                        int indexThirdListBox = SendMessage(hThirdListBox, LB_GETCURSEL, 0, 0);

                        // Skapa en ny listbox baserat på det valda underalternativet
                        HWND hNewListbox = CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL, 10, 10, 700, 200, hNewWindow, (HMENU)ID_LISTBOX4, NULL, NULL);
                        
                        SendMessage(hNewListbox, LB_ADDSTRING, 0, (LPARAM)"Namn       S2-nr         Leverantor       lev-nr");
                        SendMessage(hNewListbox, LB_ADDSTRING, 0, (LPARAM)"------------------------------------------------------------------------------");
                        // Lägg till alternativ i den nya listboxen
                        if (indexFirstListBox >= 0 && indexSecondListBox >= 0 && indexThirdListBox >= 0) {
                            const char** fileName = NULL;
                            const char* file = NULL;

                            if (indexThirdListBox == 0) { // tillbehör
                                fileName = listTill[indexFirstListBox];
                                file = fileName[indexSecondListBox];
                            } else { // reservdelar
                                fileName = listReserv[indexFirstListBox];
                                file = fileName[indexSecondListBox];
                            }
                            
                            printFile(hNewWindow, file, ID_LISTBOX4);
                        }
                        // Visa det nya fönstret
                        ShowWindow(hNewWindow, SW_SHOW);
                        UpdateWindow(hNewWindow);
                    }
                    break;
                
                case ID_BUTTON1:
                    {
                        OnMenuClick(hwnd, 1);
                    }
                    break;
                
                case ID_BUTTON2:
                    {
                        OnMenuClick(hwnd, 2);
                    }
                    break;
                
                case ID_BUTTON3:
                    {
                        OnButtonClick(hwnd, 3);
                    }
                    break;

                case ID_BUTTON4:
                    {
                        OnButtonClick(hwnd, 4);
                    }
                    break;
                
                case ID_BUTTON5:
                    {
                        OnButtonClick(hwnd, 5);
                    }
                    break;
                
                case ID_BUTTON6:
                    {
                        OnButtonClick(hwnd, 6);
                    }
                    break;
            }
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK NewWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_COMMAND:{
            int wmId = LOWORD(wParam);
            switch (wmId){
                case ID_DROPDOWNLIST:{
                    HWND hDropdown2 = GetDlgItem(g_addHjalpw, ID_DROPDOWNLIST);
                    int selectedItemIndex = SendMessageW(hDropdown2, CB_GETCURSEL, 0, 0);
                    int selectedValue = SendMessageW(hDropdown2, CB_GETITEMDATA, selectedItemIndex, 0);
                    OptionBUTTON = selectedValue;
                }break;
                case ID_SAVE_BUTTON1:{
                
                    HWND hEdit1 = GetDlgItem(g_addHjalpw, ID_EDIT_BOX);
                    HWND hEdit2 = GetDlgItem(g_addHjalpw, ID_EDIT_BOX1);
                    HWND hEdit3 = GetDlgItem(g_addHjalpw, ID_EDIT_BOX2);
                    HWND hEdit4 = GetDlgItem(g_addHjalpw, ID_EDIT_BOX3);

                    SaveTextToFile(hEdit1, hEdit2, hEdit3, hEdit4, fileNames[OptionBUTTON]);

                }break;
            }
            
        } break;
        case WM_CLOSE:
            // Stäng bara det nya fönstret när användaren klickar på krysset
            DestroyWindow(hwnd);
             
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK NewWndTillProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_COMMAND:{
            int wmId = LOWORD(wParam);
            int wmEvent = HIWORD(wParam);
            switch (wmId){
                case ID_DROPDOWNLIST:{
                    HWND hDropdown2 = GetDlgItem(g_addHjalpw, ID_DROPDOWNLIST);
                    int selectedItemIndex = SendMessageW(hDropdown2, CB_GETCURSEL, 0, 0);
                    int selectedValue = SendMessageW(hDropdown2, CB_GETITEMDATA, selectedItemIndex, 0);
                    OptionBUTTON = selectedValue;
                }break;
                case ID_SAVE_BUTTON2:{
                    HWND hEdit5 = GetDlgItem(g_addHjalpw1, ID_EDIT_BOX4);
                    HWND hEdit6 = GetDlgItem(g_addHjalpw1, ID_EDIT_BOX5);
                    HWND hEdit7 = GetDlgItem(g_addHjalpw1, ID_EDIT_BOX6);
                    HWND hEdit8 = GetDlgItem(g_addHjalpw1, ID_EDIT_BOX7);

                    HWND hDropdown = GetDlgItem(g_addHjalpw1, ID_DROPDOWNLIST1);
                    int selectedItemIndex1 = SendMessageW(hDropdown, CB_GETCURSEL, 0, 0);
                    int selectedValue1 = SendMessageW(hDropdown, CB_GETITEMDATA, selectedItemIndex1, 0);

                    HWND hDropdown3 = GetDlgItem(g_addHjalpw1, ID_DROPDOWNLIST2);
                    int selectedItemIndex = SendMessageW(hDropdown3, CB_GETCURSEL, 0, 0);
                    int selectedValue = SendMessageW(hDropdown3, CB_GETITEMDATA, selectedItemIndex, 0);
                    
                    const char** fileName1 = NULL;

                    fileName1 = listTill[selectedValue1];

                    SaveTextToFile(hEdit5, hEdit6, hEdit7, hEdit8, fileName1[selectedValue]);

                }break;
                case ID_DROPDOWNLIST1:{
                    if (wmEvent == CBN_SELCHANGE){
                        // Få det valda indexet från dropdownlist1
                        int selectedIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);

                        // Rensa och uppdatera dropdownlist2 baserat på det valda indexet
                        SendMessage(GetDlgItem(g_addHjalpw1, ID_DROPDOWNLIST2), CB_RESETCONTENT, 0, 0);

                        // Hämta filnamnet för dropdownlist2 baserat på det valda indexet från dropdownlist1
                        // Läs in alternativ från filen till dropdownlist2
                        printFileToDropdown(g_addHjalpw1, fileNames[selectedIndex], ID_DROPDOWNLIST2);
                    }
                }
            }
            
        } break;
        case WM_CLOSE:
            // Stäng bara det nya fönstret när användaren klickar på krysset
            DestroyWindow(hwnd);
             
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


int printFile(HWND hwnd, const char *filename, int listBox){
    FILE* listFile = fopen(filename, "r, ccs=UTF-8");
    if (listFile != NULL) {
        wchar_t line[MAXSIZE];
        while (fgetws(line, MAXSIZE, listFile) != NULL) {
            SendMessageW(GetDlgItem(hwnd, listBox), LB_ADDSTRING, 0, (LPARAM)line);
        }
        fclose(listFile);
    }
}

int printFileToDropdown(HWND hwnd, const char *filename, int dropdownID) {
    FILE* listFile = fopen(filename, "r, ccs=UTF-8");
    if (listFile != NULL) {
        wchar_t line[MAXSIZE];
        while (fgetws(line, MAXSIZE, listFile) != NULL) {
            // Lägg till varje rad som ett alternativ i dropdown-listan
            int index = SendMessageW(GetDlgItem(hwnd, dropdownID), CB_ADDSTRING, 0, (LPARAM)line);
            // Spara radens index som data för att använda senare
            SendMessageW(GetDlgItem(hwnd, dropdownID), CB_SETITEMDATA, index, (LPARAM)index);
        }
        fclose(listFile);
    }
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_COMMAND:
            switch (wp) {
                case ID_BUTTON:
                    {
                        char text[5];
                        GetDlgItemText(hWnd, ID_TEXTBOX, text, 5);
                        if (strcmp(text, CORRECT_CODE) == 0) {
                            HWND hEdit1 = GetDlgItem(g_code, ID_EDIT_BOX);
                            switch(saveBUTTON){
                                case 1: {
                                    OnButtonClick(hWnd, 1);
                                    DestroyWindow(hWnd);  // Close current window
                                     
                                }break;
                                case 2: {
                                    OnButtonClick(hWnd, 2);
                                    DestroyWindow(hWnd);  // Close current window
                                     
                                }break;
                            }
                        
                        } else {
                            MessageBox(hWnd, "Fel kod!", "Fel", MB_ICONERROR | MB_OK);
                        }
                    }
                    break;
            }
            break;
        case WM_DESTROY:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, msg, wp, lp);
    }
    return 0;
}

void OnMenuClick(HWND hwnd, WPARAM buttonID){
    saveBUTTON = buttonID;
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "CodeWindow"; // Set a new name for the window class
    RegisterClass(&wc);

    g_code = CreateWindowA("CodeWindow", "Code Entry", WS_OVERLAPPEDWINDOW, 100, 100, 250, 200, NULL, NULL, GetModuleHandle(NULL), NULL); // Använd CreateWindowW för breda tecken
    ShowWindow(g_code, SW_SHOW);
    UpdateWindow(g_code);

    CreateWindowW(L"static", L"Ange kod:", WS_VISIBLE | WS_CHILD, 50, 20, 100, 20, g_code, NULL, NULL, NULL);
    CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 50, 100, 20, g_code, (HMENU)ID_TEXTBOX, NULL, NULL);
    CreateWindowW(L"button", L"Bekräfta", WS_VISIBLE | WS_CHILD, 50, 80, 75, 20, g_code, (HMENU)ID_BUTTON, NULL, NULL);
}

void OnButtonClick(HWND hwnd, WPARAM buttonID) {
    switch (buttonID) {
        case 1:
            // Create a new window when the menu item "Huvudhjalpmedel" is clicked
            {
                // Register window class for the new window
                WNDCLASS wc = { 0 };
                wc.lpfnWndProc = NewWndProc;
                wc.hInstance = GetModuleHandle(NULL);
                wc.lpszClassName = "AddHjalpWindow"; // Set a new name for the window class
                RegisterClass(&wc);

                // Create the new window
                g_addHjalpw = CreateWindowEx(0, "AddHjalpWindow", "Nytt huvudhjalpmedel", WS_OVERLAPPEDWINDOW, 100, 100, 640, 400, NULL, NULL, GetModuleHandle(NULL), NULL);
                        
                ShowWindow(g_addHjalpw, SW_SHOW);
                UpdateWindow(g_addHjalpw);  

                HWND hStatic5 = CreateWindowW(L"STATIC", L"Till Vilken Produktgrupp:", WS_CHILD | WS_VISIBLE, 10, 110, 200, 20, g_addHjalpw, NULL, GetModuleHandle(NULL), NULL);

                CreateLabelAndEdit(g_addHjalpw, ID_EDIT_BOX, ID_EDIT_BOX1, ID_EDIT_BOX2, ID_EDIT_BOX3);
                
                HWND hSaveButton = CreateWindow("BUTTON", "Save", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 600, 25, g_addHjalpw, (HMENU)ID_SAVE_BUTTON1, GetModuleHandle(NULL), NULL);
                
                HWND hDropdown2 = CreateWindowW(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL , 10, 130, 200, 200, g_addHjalpw,(HMENU)ID_DROPDOWNLIST, NULL, NULL);

                printFileToDropdown(g_addHjalpw, listFileName, ID_DROPDOWNLIST);
            }
            break;

        case 2:
            {
                // Register window class for the new window
                WNDCLASS wc = { 0 };
                wc.lpfnWndProc = NewWndTillProc;
                wc.hInstance = GetModuleHandle(NULL);
                wc.lpszClassName = "AddTillWindow"; // Set a new name for the window class
                RegisterClass(&wc);

                g_addHjalpw1 = CreateWindowA("AddTillWindow", "Nytt tillbehor", WS_OVERLAPPEDWINDOW, 100, 100, 640, 400, NULL, NULL, GetModuleHandle(NULL), NULL); // Använd CreateWindowW för breda tecken
                ShowWindow(g_addHjalpw1, SW_SHOW);
                UpdateWindow(g_addHjalpw1);
                
                HWND hStatic4 = CreateWindowW(L"STATIC", L"Till Vilken Produktgrupp:", WS_CHILD | WS_VISIBLE, 10, 110, 200, 20, g_addHjalpw1, NULL, GetModuleHandle(NULL), NULL);
                HWND hStatic6 = CreateWindowW(L"STATIC", L"Till Vilket Huvudhjalpmedel:", WS_CHILD | WS_VISIBLE, 220, 110, 390, 20, g_addHjalpw1, NULL, GetModuleHandle(NULL), NULL);
                
                CreateLabelAndEdit(g_addHjalpw1, ID_EDIT_BOX4, ID_EDIT_BOX5, ID_EDIT_BOX6, ID_EDIT_BOX7);
        
                // Skapa en "Spara" -knapp
                HWND hButton = CreateWindowW(L"BUTTON", L"Spara", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 600, 25, g_addHjalpw1, (HMENU)ID_SAVE_BUTTON2, GetModuleHandle(NULL), NULL);
                
                // Skapa dropdown-menyn
                HWND hDropdown = CreateWindowW(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL  , 10, 130, 200, 200, g_addHjalpw1,(HMENU)ID_DROPDOWNLIST1, NULL, NULL); // Använd breda tecken här
                HWND hDropdown3 = CreateWindowW(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL  , 220, 130, 390, 200, g_addHjalpw1,(HMENU)ID_DROPDOWNLIST2, NULL, NULL);

                printFileToDropdown(g_addHjalpw1, listFileName, ID_DROPDOWNLIST1);

            }
            break;

        case 3:
            MessageBox(hwnd, "Du klickade på Alternativ ush!", "Meddelande", MB_OK | MB_ICONINFORMATION);
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

HWND CreateLabelAndEdit(HWND parentWnd, int controlId1, int controlId2, int controlId3, int controlId4){
    HWND hStatic = CreateWindowEx(0, "STATIC", "Namn:", WS_CHILD | WS_VISIBLE, 10, 60, 120, 20, parentWnd, NULL, GetModuleHandle(NULL), NULL);
    HWND hEdit = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 10, 80, 150, 20, parentWnd, (HMENU)controlId1, GetModuleHandle(NULL), NULL);
    HWND hStatic1 = CreateWindowEx(0, "STATIC", "S2-nr:", WS_CHILD | WS_VISIBLE, 160, 60, 120, 20, parentWnd, NULL, GetModuleHandle(NULL), NULL);
    HWND hEdit1 = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 160, 80, 150, 20, parentWnd, (HMENU)controlId2, GetModuleHandle(NULL), NULL);
    HWND hStatic2 = CreateWindowEx(0, "STATIC", "Leverantor:", WS_CHILD | WS_VISIBLE, 310, 60, 120, 20, parentWnd, NULL, GetModuleHandle(NULL), NULL);
    HWND hEdit2 = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 310, 80, 150, 20, parentWnd, (HMENU)controlId3, GetModuleHandle(NULL), NULL);
    HWND hStatic3 = CreateWindowEx(0, "STATIC", "Lev-nr:", WS_CHILD | WS_VISIBLE, 460, 60, 120, 20, parentWnd, NULL, GetModuleHandle(NULL), NULL);
    HWND hEdit3 = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 460, 80, 150, 20, parentWnd, (HMENU)controlId4, GetModuleHandle(NULL), NULL);
}

void SaveTextToFile(HWND hEdit1, HWND hEdit2, HWND hEdit3, HWND hEdit4, const char *filename) {
    // Beräkna total längd för den UTF-8-sträng som ska skrivas till filen
    int len = GetWindowTextLength(hEdit1) + GetWindowTextLength(hEdit2) + GetWindowTextLength(hEdit3) + GetWindowTextLength(hEdit4);
    wchar_t* wideTextBuffer = (wchar_t*)malloc((len + 1) * sizeof(wchar_t)); // Allokera minne för wide-characters sträng
    if (wideTextBuffer == NULL) {
        return;
    }
    wideTextBuffer[0] = L'\0'; // Nollterminerad sträng

    // Hämta texten från varje edit-box och lägg till den i wideTextBuffer med mellanslag
    GetWindowTextW(hEdit1, wideTextBuffer, GetWindowTextLength(hEdit1) + 1);
    wcscat(wideTextBuffer, L" ");
    GetWindowTextW(hEdit2, wideTextBuffer + wcslen(wideTextBuffer), GetWindowTextLength(hEdit2) + 1);
    wcscat(wideTextBuffer, L" ");
    GetWindowTextW(hEdit3, wideTextBuffer + wcslen(wideTextBuffer), GetWindowTextLength(hEdit3) + 1);
    wcscat(wideTextBuffer, L" ");
    GetWindowTextW(hEdit4, wideTextBuffer + wcslen(wideTextBuffer), GetWindowTextLength(hEdit4) + 1);

    // Beräkna antalet byte som behövs för att lagra UTF-8-strängen
    int utf8Length = WideCharToMultiByte(CP_UTF8, 0, wideTextBuffer, -1, NULL, 0, NULL, NULL);

    // Allokera minne för UTF-8-strängen
    char *utf8Buffer = (char *)malloc(utf8Length);
    if (utf8Buffer == NULL) {
        free(wideTextBuffer);
        return;
    }

    // Konvertera wide-characters strängen till UTF-8
    WideCharToMultiByte(CP_UTF8, 0, wideTextBuffer, -1, utf8Buffer, utf8Length, NULL, NULL);

    // Öppna filen för skrivning
    FILE* file = fopen(filename, "a");
    if (file != NULL) {
        // Skriv texten till filen
        fprintf(file, "%s\n", utf8Buffer);
        fclose(file); // Stäng filen
    } else {
        printf("Kunde inte öppna filen för skrivning.\n");
    }

    // Frigör minnet som allokerades för wide-characters och UTF-8-strängen
    free(wideTextBuffer);
    free(utf8Buffer);

    // Töm edit-boxarna genom att sätta deras text till en tom sträng 
    SetWindowText(hEdit1, "");
    SetWindowText(hEdit2, "");
    SetWindowText(hEdit3, "");
    SetWindowText(hEdit4, "");
}

