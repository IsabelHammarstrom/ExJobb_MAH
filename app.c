#include <windows.h> 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <wchar.h>  
#include <CommCtrl.h>
#include <stdbool.h>
#include "app.h" 

#define CORRECT_CODE "1234"
#define ID_TEXTBOX 111
#define ID_BUTTON 112

#define ID_LISTBOX1 1
#define ID_LISTBOX2 2
#define ID_LISTBOX3 3
#define ID_LISTBOX4 10
#define ID_LISTBOX5 11
#define ID_LISTBOX6 12
#define ID_LISTBOX7 13

#define ID_BUTTON1 4
#define ID_BUTTON2 5
#define ID_BUTTON3 6
#define ID_BUTTON4 7
#define ID_BUTTON5 8
#define ID_BUTTON6 9

#define ID_EDIT_BOX 101
#define ID_EDIT_BOX1 102
#define ID_EDIT_BOX2 103
#define ID_EDIT_BOX3 104
#define ID_SAVE_BUTTON1 105
#define ID_DROPDOWNLIST 106

#define ID_EDIT_BOX4 1001
#define ID_EDIT_BOX5 1002
#define ID_EDIT_BOX6 1003
#define ID_EDIT_BOX7 1004
#define ID_SAVE_BUTTON2 1005
#define ID_DROPDOWNLIST1 1006
#define ID_DROPDOWNLIST2 1007

#define ID_SAVE_BUTTON3 121
#define ID_DROPDOWNLIST3 122
#define ID_DROPDOWNLIST4 123
#define ID_DROPDOWNLIST5 124

#define ID_SAVE_BUTTON4 131
#define ID_DROPDOWNLIST6 132
#define ID_DROPDOWNLIST7 133

#define ID_EDIT_BOX8 1011
#define ID_EDIT_BOX9 1012
#define ID_EDIT_BOX10 1013
#define ID_EDIT_BOX11 1014
#define ID_DROPDOWNLIST11 1015
#define ID_DROPDOWNLIST12 1016
#define ID_SAVE_BUTTON5 1017

#define ID_SAVE_BUTTON6 141
#define ID_DROPDOWNLIST8 142
#define ID_DROPDOWNLIST9 143
#define ID_DROPDOWNLIST10 144

#define MAXSIZE 1000
#define NAMESIZE 20
#define MAX_STRING_LENGTH 256
#define TOKEN_WIDTH 20

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK NewHelpWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK NewTillWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
LRESULT CALLBACK PrintWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK EditTillWinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK EditHelpWinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK NewResWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK EditResWinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int printArtikel(HWND hParent, const wchar_t *filename);
int printFile(HWND hwnd, const char *filename, int listBox);
int printOneArtikel(HWND hwnd, const char *filename, int lineNr);
int printFileToDropdown(HWND hwnd, const char *filename, int dropdownID);
void OnMenuClick(HWND hwnd, WPARAM buttonID);
void OnButtonClick(HWND hwnd, WPARAM buttonID);
void SaveTextToFile(HWND hEdit1, HWND hEdit2, HWND hEdit3, HWND hEdit4, const char *filename);
void SaveToFile(HWND hEdit1, const char *filename);
void removeLine(const char *filename, int lineToRemove);
void CopyFileContents(const char *sourceFilename, const char *destinationFilename);
void ClearFile(const char *filename);
bool isFileEmpty(const char *filename);
wchar_t* ConvertToWideChar(const char* str);

HWND g_addHjalpw;
HWND g_addTillpw; 
HWND g_code;
HWND g_EditTill;
HWND g_EditHelp;
HWND hListName;
HWND hListS2Nr;
HWND hListLeverantor;
HWND hListLevNr;
HWND g_addRespw;
HWND g_EditRes;
HWND hControl;
HWND hTillName;

int saveBUTTON = 0;
int OptionBUTTON = 0;
int OptionBUTTON1 = 0;
int OptionBUTTON2 = 0;
int OptionList = 0;
int NextOption = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HWND hwnd;
    MSG Msg;
    WNDCLASS wc = { 0 };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MyWindowClass";
    RegisterClass(&wc);

    hwnd = CreateWindow("MyWindowClass", "Start", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1400, 600, NULL, NULL, hInstance, NULL);

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

// -------------------------------------------- Windows ----------------------------------------------------

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {  
            HMENU hMenu = CreateMenu();
            HMENU hSubMenu1 = CreatePopupMenu();
            HMENU hSubMenu11 = CreatePopupMenu();
            HMENU hSubMenu12 = CreatePopupMenu();
            AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu1, L"Inställningar");
            AppendMenuW(hSubMenu1, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu11, L"Lägga till ny");
            AppendMenuW(hSubMenu11, MF_STRING, 4, L"Huvudhjälpmedel");
            AppendMenuW(hSubMenu11, MF_STRING, 5, L"Tillbehör");
            AppendMenuW(hSubMenu11, MF_STRING, 6, L"Reservdel");
            AppendMenuW(hSubMenu1, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu12, L"Ta bort befintlig artikel");
            AppendMenuW(hSubMenu12, MF_STRING, 7, L"Huvudhjälpmedel");
            AppendMenuW(hSubMenu12, MF_STRING, 8, L"Tillbehör");
            AppendMenuW(hSubMenu12, MF_STRING, 9, L"Reservdel");
            SetMenu(hwnd, hMenu);
        }break;
        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            switch (wmId) {
                case ID_LISTBOX1:
                    if (HIWORD(wParam) == LBN_SELCHANGE) {
                        HWND hPrevSubListBox = GetDlgItem(hwnd, ID_LISTBOX2);
                        if (hPrevSubListBox != NULL) {
                            DestroyWindow(hPrevSubListBox);
                        }
                        HWND hPrevSubSubListBox = GetDlgItem(hwnd, ID_LISTBOX3);
                        if (hPrevSubSubListBox != NULL) {
                            DestroyWindow(hPrevSubSubListBox);
                        }
                        HWND hListBox = (HWND)lParam;
                        int index = SendMessage(hListBox, LB_GETCURSEL, 0, 0);

                        HWND hSubListBox = CreateWindow("LISTBOX", NULL, WS_VISIBLE | WS_CHILD | LBS_NOTIFY | WS_VSCROLL, 400, 10, 600, 500, hwnd, (HMENU)ID_LISTBOX2, NULL, NULL);
                        printFile(hwnd, fileNames[index], ID_LISTBOX2);
                        HWND hSubSubListBox = CreateWindow("LISTBOX", NULL, WS_VISIBLE | WS_CHILD | LBS_NOTIFY | WS_VSCROLL, 1050, 10, 150, 500, hwnd, (HMENU)ID_LISTBOX3, NULL, NULL);
                    }break;

                case ID_LISTBOX2:
                    if (HIWORD(wParam) == LBN_SELCHANGE) {
                        HWND hPrevSubSubListBox = GetDlgItem(hwnd, ID_LISTBOX3);
                        if (hPrevSubSubListBox != NULL) {
                            DestroyWindow(hPrevSubSubListBox);
                        }
                        HWND hSubListBox = (HWND)lParam;
                        int index = SendMessage(hSubListBox, LB_GETCURSEL, 0, 0);

                        HWND hSubSubListBox = CreateWindow("LISTBOX", NULL, WS_VISIBLE | WS_CHILD | LBS_NOTIFY | WS_VSCROLL, 1050, 10, 150, 500, hwnd, (HMENU)ID_LISTBOX3, NULL, NULL);
                        printFile(hwnd, trNames, ID_LISTBOX3);
                    }break;
                
                case ID_LISTBOX3:
                    if (HIWORD(wParam) == LBN_SELCHANGE) {
                        HWND hNewWindow = CreateWindowEx(0, "NewWindowClass", "Tillbehor/Reservdelar", WS_OVERLAPPEDWINDOW | WS_VSCROLL, CW_USEDEFAULT, CW_USEDEFAULT, 955, 580, NULL, NULL, GetModuleHandle(NULL), NULL);
                        
                        WNDCLASS wc = { 0 };
                        wc.lpfnWndProc = PrintWndProc;
                        wc.hInstance = GetModuleHandle(NULL);
                        wc.lpszClassName = "NewWindowClass";
                        RegisterClass(&wc);
                        
                        HWND hFirstListBox = GetDlgItem(hwnd, ID_LISTBOX1);
                        int indexFirstListBox = SendMessage(hFirstListBox, LB_GETCURSEL, 0, 0);
                        HWND hSecondListBox = GetDlgItem(hwnd, ID_LISTBOX2);
                        int indexSecondListBox = SendMessage(hSecondListBox, LB_GETCURSEL, 0, 0);
                        HWND hThirdListBox = GetDlgItem(hwnd, ID_LISTBOX3);
                        int indexThirdListBox = SendMessage(hThirdListBox, LB_GETCURSEL, 0, 0);

                        HWND hListName1 = CreateWindow("STATIC", "Namn", WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_BORDER, 510, 40, 410, 20, hNewWindow, NULL, NULL, NULL);
                        HWND hListS2Nr1 = CreateWindow("STATIC", "S2-nr", WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_BORDER, 410, 40, 100, 20, hNewWindow, NULL, NULL, NULL);
                        HWND hListLeverantor1 = CreateWindow("STATIC", "Leverantor", WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_BORDER, 160, 40, 250, 20, hNewWindow, NULL, NULL, NULL);
                        HWND hListLevNr1 = CreateWindow("STATIC", "Lev-nr", WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_BORDER, 10, 40, 150, 20, hNewWindow, NULL, NULL, NULL);
                   
                        if (indexFirstListBox >= 0 && indexSecondListBox >= 0 && indexThirdListBox >= 0) {
                            const char** fileName = NULL;
                            const char* file = NULL;

                            if (indexThirdListBox == 0) { 
                                fileName = listTill[indexFirstListBox];
                                file = fileName[indexSecondListBox];
                                HWND hTill = CreateWindowW(L"STATIC", L"Tillbehör", WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_BORDER, 10, 10, 100, 20, hNewWindow, NULL, NULL, NULL);
                            } else { 
                                fileName = listReserv[indexFirstListBox];
                                file = fileName[indexSecondListBox];
                                HWND hRes = CreateWindowW(L"STATIC", L"Reservdelar", WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_BORDER, 10, 10, 100, 20, hNewWindow, NULL, NULL, NULL);
                            }

                            printOneArtikel(hNewWindow, fileNames[indexFirstListBox], indexSecondListBox);
                            wchar_t* wFile = ConvertToWideChar(file);
                            if (wFile != NULL) {
                                printArtikel(hNewWindow, wFile);
                                free(wFile); 
                            }
                        }
                        ShowWindow(hNewWindow, SW_SHOW);
                        UpdateWindow(hNewWindow);
                    }break;

                case ID_BUTTON1:
                        OnMenuClick(hwnd, 1);
                    break;

                case ID_BUTTON2:
                        OnMenuClick(hwnd, 2);
                    break;

                case ID_BUTTON3:
                        OnMenuClick(hwnd, 3);
                    break;

                case ID_BUTTON4:
                        OnMenuClick(hwnd, 4);
                    break;

                case ID_BUTTON5:
                        OnMenuClick(hwnd, 5);
                    break;

                case ID_BUTTON6:
                        OnMenuClick(hwnd, 6);
                    break;
            }break;
        }break;
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK NewHelpWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
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
                    SaveToFile(hEdit1, fileNames[OptionBUTTON]);
                    SendMessage(GetDlgItem(g_addHjalpw, ID_DROPDOWNLIST), CB_RESETCONTENT, 0, 0);
                    printFileToDropdown(g_addHjalpw, listFileName, ID_DROPDOWNLIST);
                }break;
            }
        }break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK NewTillWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_COMMAND:{
            int wmId = LOWORD(wParam);
            int wmEvent = HIWORD(wParam);
            switch (wmId){
                case ID_SAVE_BUTTON2:{
                    HWND hEdit5 = GetDlgItem(g_addTillpw, ID_EDIT_BOX7);
                    HWND hEdit6 = GetDlgItem(g_addTillpw, ID_EDIT_BOX6);
                    HWND hEdit7 = GetDlgItem(g_addTillpw, ID_EDIT_BOX5);
                    HWND hEdit8 = GetDlgItem(g_addTillpw, ID_EDIT_BOX4);
                    
                    const char** fileName1 = NULL;
                    fileName1 = listTill[OptionList];
                    SaveTextToFile(hEdit5, hEdit6, hEdit7, hEdit8, fileName1[OptionBUTTON]);

                    SendMessage(GetDlgItem(g_addTillpw, ID_DROPDOWNLIST1), CB_RESETCONTENT, 0, 0);
                    printFileToDropdown(g_addTillpw, listFileName, ID_DROPDOWNLIST1);
                    SendMessage(GetDlgItem(g_addTillpw, ID_DROPDOWNLIST2), CB_RESETCONTENT, 0, 0);
                }break;
                case ID_DROPDOWNLIST1:{
                    if (wmEvent == CBN_SELCHANGE){
                        int selectedIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
                        SendMessage(GetDlgItem(g_addTillpw, ID_DROPDOWNLIST2), CB_RESETCONTENT, 0, 0);
                        printFileToDropdown(g_addTillpw, fileNames[selectedIndex], ID_DROPDOWNLIST2);

                        HWND hDropdown1 = GetDlgItem(g_addTillpw, ID_DROPDOWNLIST1);
                        int selectedItemIndex = SendMessageW(hDropdown1, CB_GETCURSEL, 0, 0);
                        int selectedValue = SendMessageW(hDropdown1, CB_GETITEMDATA, selectedItemIndex, 0);
                        OptionList = selectedValue;
                    }
                }break;
                case ID_DROPDOWNLIST2:{
                    if (wmEvent == CBN_SELCHANGE){
                        HWND hDropdown3 = GetDlgItem(g_addTillpw, ID_DROPDOWNLIST2);
                        int selectedItemIndex = SendMessageW(hDropdown3, CB_GETCURSEL, 0, 0);
                        int selectedValue = SendMessageW(hDropdown3, CB_GETITEMDATA, selectedItemIndex, 0);
                        OptionBUTTON = selectedValue;
                    }
                }break;
            }
        }break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_COMMAND:
            switch (wp) {
                case ID_BUTTON:{
                    char text[5];
                    GetDlgItemText(hWnd, ID_TEXTBOX, text, 5);
                    if (strcmp(text, CORRECT_CODE) == 0) {
                        HWND hEdit1 = GetDlgItem(g_code, ID_EDIT_BOX);
                        switch(saveBUTTON){
                            case 1: {
                                OnButtonClick(hWnd, 1);
                                DestroyWindow(hWnd);
                            }break;
                            case 2: {
                                OnButtonClick(hWnd, 2);
                                DestroyWindow(hWnd);
                            }break;
                            case 3:{
                                OnButtonClick(hWnd, 3);
                                DestroyWindow(hWnd);
                            }break;
                            case 4:{
                                OnButtonClick(hWnd, 4);
                                DestroyWindow(hWnd);
                            }break;
                            case 5:{
                                OnButtonClick(hWnd, 5);
                                DestroyWindow(hWnd);
                            }break;
                            case 6:{
                                OnButtonClick(hWnd, 6);
                                DestroyWindow(hWnd);
                            }break;
                        }
                    }else{
                        MessageBox(hWnd, "Fel kod!", "Fel", MB_ICONERROR | MB_OK);
                    }
                }break;
            }break;
        case WM_DESTROY:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, msg, wp, lp);
    }
    return 0;
}

LRESULT CALLBACK PrintWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_VSCROLL: {
            SCROLLINFO si = {0};
            si.cbSize = sizeof(SCROLLINFO);
            si.fMask = SIF_ALL;
            GetScrollInfo(hwnd, SB_VERT, &si);
            int yPos = si.nPos;

            switch (LOWORD(wParam)) {
                case SB_LINEUP: yPos -= 20; break;
                case SB_LINEDOWN: yPos += 20; break;
                case SB_PAGEUP: yPos -= si.nPage; break;
                case SB_PAGEDOWN: yPos += si.nPage; break;
                case SB_THUMBTRACK: yPos = si.nTrackPos; break;
            }

            yPos = max(0, min(yPos, si.nMax - (int)si.nPage));
            
            if (yPos != si.nPos) {
                SetScrollPos(hwnd, SB_VERT, yPos, TRUE);
                ScrollWindow(hwnd, 0, si.nPos - yPos, NULL, NULL);
            }
        }break;
        case WM_DESTROY:
            DestroyWindow(hwnd);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK EditTillWinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch (msg) {
        case WM_COMMAND:{
            int wmId = LOWORD(wParam);
            int wmEvent = HIWORD(wParam);
            switch (wmId){
                case ID_SAVE_BUTTON3:{
                    const char** fileName = NULL;
                    const char* file = NULL;

                    fileName = listTill[OptionList];
                    file = fileName[OptionBUTTON1];

                    removeLine(file, OptionBUTTON2);
                    SendMessage(GetDlgItem(g_EditTill, ID_DROPDOWNLIST3), CB_RESETCONTENT, 0, 0);
                    printFileToDropdown(g_EditTill, listFileName, ID_DROPDOWNLIST3);
                    SendMessage(GetDlgItem(g_EditTill, ID_DROPDOWNLIST4), CB_RESETCONTENT, 0, 0);
                    SendMessage(GetDlgItem(g_EditTill, ID_DROPDOWNLIST5), CB_RESETCONTENT, 0, 0);
                }break;
                case ID_DROPDOWNLIST3:{
                    if (wmEvent == CBN_SELCHANGE){
                        int selectedIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
                        SendMessage(GetDlgItem(g_EditTill, ID_DROPDOWNLIST4), CB_RESETCONTENT, 0, 0);
                        SendMessage(GetDlgItem(g_EditTill, ID_DROPDOWNLIST5), CB_RESETCONTENT, 0, 0);
                        printFileToDropdown(g_EditTill, fileNames[selectedIndex], ID_DROPDOWNLIST4);

                        HWND hDropdown3 = GetDlgItem(g_EditTill, ID_DROPDOWNLIST3);
                        int selectedItemIndex = SendMessageW(hDropdown3, CB_GETCURSEL, 0, 0);
                        int selectedValue = SendMessageW(hDropdown3, CB_GETITEMDATA, selectedItemIndex, 0);
                        OptionList = selectedValue;
                        NextOption = selectedIndex;
                    }
                }break;
                case ID_DROPDOWNLIST4:{
                    if (wmEvent == CBN_SELCHANGE){
                        const char** fileName = NULL;
                        const char* file = NULL;
                        int selectedIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
                        SendMessage(GetDlgItem(g_EditTill, ID_DROPDOWNLIST5), CB_RESETCONTENT, 0, 0);
                        
                        fileName = listTill[NextOption];
                        file = fileName[selectedIndex];
                        printFileToDropdown(g_EditTill, file, ID_DROPDOWNLIST5);
                        
                        HWND hDropdown4 = GetDlgItem(g_EditTill, ID_DROPDOWNLIST4);
                        int selectedItemIndex = SendMessageW(hDropdown4, CB_GETCURSEL, 0, 0);
                        int selectedValue = SendMessageW(hDropdown4, CB_GETITEMDATA, selectedItemIndex, 0);
                        OptionBUTTON1 = selectedValue;
                    }
                }break;
                case ID_DROPDOWNLIST5:{
                    if (wmEvent == CBN_SELCHANGE){
                        HWND hDropdown5 = GetDlgItem(g_EditTill, ID_DROPDOWNLIST5);
                        int selectedItemIndex = SendMessageW(hDropdown5, CB_GETCURSEL, 0, 0);
                        int selectedValue = SendMessageW(hDropdown5, CB_GETITEMDATA, selectedItemIndex, 0);
                        OptionBUTTON2 = selectedValue;
                    }
                }
            }
        }break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK EditHelpWinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch (msg) {
        case WM_COMMAND:{
            int wmId = LOWORD(wParam);
            int wmEvent = HIWORD(wParam);
            switch (wmId){
                case ID_SAVE_BUTTON4:{
                    const char** fileName = NULL;
                    const char** fileName2 = NULL;
                    const char* fileToClear = NULL;
                    const char* fileToCopy = NULL;
                    const char* fileToClear2 = NULL;
                    const char* fileToCopy2 = NULL;

                    fileName = listTill[OptionList];
                    fileName2 = listReserv[OptionList];
                    fileToClear = fileName[OptionBUTTON1];
                    fileToClear2 = fileName2[OptionBUTTON1];
                    
                    removeLine(fileNames[OptionList], OptionBUTTON1);
                    
                    OptionBUTTON2 = OptionBUTTON1 + 1;
                    fileToCopy = fileName[OptionBUTTON2];
                    fileToCopy2 = fileName2[OptionBUTTON2];
                    
                    while(!isFileEmpty(fileToCopy)||!isFileEmpty(fileToCopy2)){
                        ClearFile(fileName[OptionBUTTON1]);
                        ClearFile(fileName2[OptionBUTTON1]);
                        CopyFileContents(fileName[OptionBUTTON2], fileName[OptionBUTTON1]);
                        CopyFileContents(fileName2[OptionBUTTON2], fileName2[OptionBUTTON1]);
                        OptionBUTTON2++;
                        OptionBUTTON1++;
                    }

                    SendMessage(GetDlgItem(g_EditHelp, ID_DROPDOWNLIST6), CB_RESETCONTENT, 0, 0);
                    printFileToDropdown(g_EditHelp, listFileName, ID_DROPDOWNLIST6);
                    SendMessage(GetDlgItem(g_EditHelp, ID_DROPDOWNLIST7), CB_RESETCONTENT, 0, 0);
                }break;
                case ID_DROPDOWNLIST6:{
                    if (wmEvent == CBN_SELCHANGE){
                        int selectedIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
                        SendMessage(GetDlgItem(g_EditHelp, ID_DROPDOWNLIST7), CB_RESETCONTENT, 0, 0);
                        printFileToDropdown(g_EditHelp, fileNames[selectedIndex], ID_DROPDOWNLIST7);

                        HWND hDropdown6 = GetDlgItem(g_EditHelp, ID_DROPDOWNLIST6);
                        int selectedItemIndex = SendMessageW(hDropdown6, CB_GETCURSEL, 0, 0);
                        int selectedValue = SendMessageW(hDropdown6, CB_GETITEMDATA, selectedItemIndex, 0);
                        OptionList = selectedValue;
                    }
                }break;
                case ID_DROPDOWNLIST7:{
                    if (wmEvent == CBN_SELCHANGE){
                        HWND hDropdown7 = GetDlgItem(g_EditHelp, ID_DROPDOWNLIST7);
                        int selectedItemIndex = SendMessageW(hDropdown7, CB_GETCURSEL, 0, 0);
                        int selectedValue = SendMessageW(hDropdown7, CB_GETITEMDATA, selectedItemIndex, 0);
                        OptionBUTTON1 = selectedValue;
                    }
                }
            }
        }break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK NewResWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_COMMAND:{
            int wmId = LOWORD(wParam);
            int wmEvent = HIWORD(wParam);
            switch (wmId){
                case ID_SAVE_BUTTON5:{
                    HWND hEdit11 = GetDlgItem(g_addRespw, ID_EDIT_BOX11);
                    HWND hEdit10 = GetDlgItem(g_addRespw, ID_EDIT_BOX10);
                    HWND hEdit9 = GetDlgItem(g_addRespw, ID_EDIT_BOX9);
                    HWND hEdit8 = GetDlgItem(g_addRespw, ID_EDIT_BOX8);
                    
                    const char** fileName1 = NULL;
                    fileName1 = listReserv[OptionList];
                    SaveTextToFile(hEdit11, hEdit10, hEdit9, hEdit8, fileName1[OptionBUTTON]);

                    SendMessage(GetDlgItem(g_addRespw, ID_DROPDOWNLIST11), CB_RESETCONTENT, 0, 0);
                    printFileToDropdown(g_addRespw, listFileName, ID_DROPDOWNLIST11);
                    SendMessage(GetDlgItem(g_addRespw, ID_DROPDOWNLIST12), CB_RESETCONTENT, 0, 0);
                }break;
                case ID_DROPDOWNLIST11:{
                    if (wmEvent == CBN_SELCHANGE){
                        int selectedIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
                        SendMessage(GetDlgItem(g_addRespw, ID_DROPDOWNLIST12), CB_RESETCONTENT, 0, 0);
                        printFileToDropdown(g_addRespw, fileNames[selectedIndex], ID_DROPDOWNLIST12);

                        HWND hDropdown11 = GetDlgItem(g_addRespw, ID_DROPDOWNLIST11);
                        int selectedItemIndex = SendMessageW(hDropdown11, CB_GETCURSEL, 0, 0);
                        int selectedValue = SendMessageW(hDropdown11, CB_GETITEMDATA, selectedItemIndex, 0);
                        OptionList = selectedValue;
                    }
                }break;
                case ID_DROPDOWNLIST12:{
                    if (wmEvent == CBN_SELCHANGE){
                        HWND hDropdown12 = GetDlgItem(g_addRespw, ID_DROPDOWNLIST12);
                        int selectedItemIndex = SendMessageW(hDropdown12, CB_GETCURSEL, 0, 0);
                        int selectedValue = SendMessageW(hDropdown12, CB_GETITEMDATA, selectedItemIndex, 0);
                        OptionBUTTON = selectedValue;
                    }
                }break;
            }
        } break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK EditResWinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch (msg) {
        case WM_COMMAND:{
            int wmId = LOWORD(wParam);
            int wmEvent = HIWORD(wParam);
            switch (wmId){
                case ID_SAVE_BUTTON6:{
                    const char** fileName = NULL;
                    const char* file = NULL;

                    fileName = listReserv[OptionList];
                    file = fileName[OptionBUTTON1];

                    removeLine(file, OptionBUTTON2);
                    SendMessage(GetDlgItem(g_EditRes, ID_DROPDOWNLIST8), CB_RESETCONTENT, 0, 0);
                    printFileToDropdown(g_EditRes, listFileName, ID_DROPDOWNLIST8);
                    SendMessage(GetDlgItem(g_EditRes, ID_DROPDOWNLIST9), CB_RESETCONTENT, 0, 0);
                    SendMessage(GetDlgItem(g_EditRes, ID_DROPDOWNLIST10), CB_RESETCONTENT, 0, 0);
                }break;
                case ID_DROPDOWNLIST8:{
                    if (wmEvent == CBN_SELCHANGE){
                        int selectedIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
                        SendMessage(GetDlgItem(g_EditRes, ID_DROPDOWNLIST9), CB_RESETCONTENT, 0, 0);
                        SendMessage(GetDlgItem(g_EditRes, ID_DROPDOWNLIST10), CB_RESETCONTENT, 0, 0);
                        printFileToDropdown(g_EditRes, fileNames[selectedIndex], ID_DROPDOWNLIST9);

                        HWND hDropdown8 = GetDlgItem(g_EditRes, ID_DROPDOWNLIST8);
                        int selectedItemIndex = SendMessageW(hDropdown8, CB_GETCURSEL, 0, 0);
                        int selectedValue = SendMessageW(hDropdown8, CB_GETITEMDATA, selectedItemIndex, 0);
                        OptionList = selectedValue;
                        NextOption = selectedIndex;
                    }
                }break;
                case ID_DROPDOWNLIST9:{
                    if (wmEvent == CBN_SELCHANGE){
                        const char** fileName = NULL;
                        const char* file = NULL;
                        int selectedIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
                        SendMessage(GetDlgItem(g_EditRes, ID_DROPDOWNLIST10), CB_RESETCONTENT, 0, 0);
                        
                        fileName = listReserv[NextOption];
                        file = fileName[selectedIndex];
                        printFileToDropdown(g_EditRes, file, ID_DROPDOWNLIST10);
                        
                        HWND hDropdown9 = GetDlgItem(g_EditRes, ID_DROPDOWNLIST9);
                        int selectedItemIndex = SendMessageW(hDropdown9, CB_GETCURSEL, 0, 0);
                        int selectedValue = SendMessageW(hDropdown9, CB_GETITEMDATA, selectedItemIndex, 0);
                        OptionBUTTON1 = selectedValue;
                    }
                }break;
                case ID_DROPDOWNLIST10:{
                    if (wmEvent == CBN_SELCHANGE){
                        HWND hDropdown10 = GetDlgItem(g_EditRes, ID_DROPDOWNLIST10);
                        int selectedItemIndex = SendMessageW(hDropdown10, CB_GETCURSEL, 0, 0);
                        int selectedValue = SendMessageW(hDropdown10, CB_GETITEMDATA, selectedItemIndex, 0);
                        OptionBUTTON2 = selectedValue;
                    }
                }
            }
        }break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// -------------------------------------------------------------- Funktioner ---------------------------------------------------------------------------

int printArtikel(HWND hParent, const wchar_t *filename) {
    FILE* listFile = _wfopen(filename, L"r, ccs=UTF-8");
    if (listFile == NULL) {
        return -1;
    }

    wchar_t line[MAXSIZE];
    const wchar_t *delimiters = L"|";
    int yPos = 60;

    while (fgetws(line, MAXSIZE, listFile) != NULL) {
        line[wcslen(line)-1] = L'\0';

        wchar_t *token = wcstok(line, delimiters);
        int colIndex = 0;
        int xPos = 10;
        const int widths[4] = {150, 250, 100, 410};

        while (token != NULL && colIndex < 4) {
            if (colIndex > 0) {
                xPos += widths[colIndex - 1];
            }
            if (colIndex == 3) { 
                hControl = CreateWindowW(L"EDIT", token, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY | WS_VSCROLL | ES_MULTILINE, xPos, yPos, widths[colIndex], 20, hParent, NULL, (HINSTANCE)GetWindowLongPtr(hParent, GWLP_HINSTANCE), NULL);
            }else{
                hControl = CreateWindowW(L"STATIC", token, WS_VISIBLE | WS_CHILD | SS_LEFT | WS_BORDER, xPos, yPos, widths[colIndex], 20, hParent, NULL, (HINSTANCE)GetWindowLongPtr(hParent, GWLP_HINSTANCE), NULL);
            }
            token = wcstok(NULL, delimiters);
            colIndex++;
        }
        yPos += 20; 
    }

    SCROLLINFO si = {0};
    si.cbSize = sizeof(si);
    si.fMask = SIF_RANGE | SIF_PAGE;
    si.nMin = 0;
    si.nMax = yPos;
    si.nPage = 530;
    SetScrollInfo(hParent, SB_VERT, &si, TRUE);

    fclose(listFile);
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

int printOneArtikel(HWND hwnd, const char *filename, int lineNr){
    FILE* listFile = fopen(filename, "r, ccs=UTF-8");
    if (listFile != NULL) {
        wchar_t line[MAXSIZE];
        int currentLine = 0;
        while(fgetws(line, MAXSIZE, listFile) != NULL){
            if(currentLine == lineNr){
                hTillName = CreateWindowW(L"STATIC", line, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_BORDER, 120, 10, 800, 20, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
                fclose(listFile);
                return 0;
            }
            currentLine++;
        }
        fclose(listFile);
        return -1;
    }
}

int printFileToDropdown(HWND hwnd, const char *filename, int dropdownID) {
    FILE* listFile = fopen(filename, "r, ccs=UTF-8");
    if (listFile != NULL) {
        wchar_t line[MAXSIZE];
        while (fgetws(line, MAXSIZE, listFile) != NULL) {
            int index = SendMessageW(GetDlgItem(hwnd, dropdownID), CB_ADDSTRING, 0, (LPARAM)line);
            SendMessageW(GetDlgItem(hwnd, dropdownID), CB_SETITEMDATA, index, (LPARAM)index);
        }
        fclose(listFile);
    }
}

void OnMenuClick(HWND hwnd, WPARAM buttonID){
    saveBUTTON = buttonID;
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "CodeWindow";
    RegisterClass(&wc);

    g_code = CreateWindowA("CodeWindow", "Code Entry", WS_OVERLAPPEDWINDOW, 100, 100, 250, 200, NULL, NULL, GetModuleHandle(NULL), NULL);
    ShowWindow(g_code, SW_SHOW);
    UpdateWindow(g_code);

    CreateWindowW(L"static", L"Ange kod:", WS_VISIBLE | WS_CHILD, 50, 20, 100, 20, g_code, NULL, NULL, NULL);
    CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 50, 100, 20, g_code, (HMENU)ID_TEXTBOX, NULL, NULL);
    CreateWindowW(L"button", L"Bekräfta", WS_VISIBLE | WS_CHILD, 50, 80, 75, 20, g_code, (HMENU)ID_BUTTON, NULL, NULL);
}

void OnButtonClick(HWND hwnd, WPARAM buttonID) {
    switch (buttonID) {
        case 1: {
                WNDCLASS wc = { 0 };
                wc.lpfnWndProc = NewHelpWndProc;
                wc.hInstance = GetModuleHandle(NULL);
                wc.lpszClassName = "AddHjalpWindow"; 
                RegisterClass(&wc);

                g_addHjalpw = CreateWindowEx(0, "AddHjalpWindow", "Nytt huvudhjalpmedel", WS_OVERLAPPEDWINDOW, 100, 100, 640, 400, NULL, NULL, GetModuleHandle(NULL), NULL);
                ShowWindow(g_addHjalpw, SW_SHOW);
                UpdateWindow(g_addHjalpw);  

                HWND hStatic5 = CreateWindowW(L"STATIC", L"Till Vilken Produktgrupp:", WS_CHILD | WS_VISIBLE, 10, 110, 200, 20, g_addHjalpw, NULL, GetModuleHandle(NULL), NULL);
                HWND hStatic = CreateWindowEx(0, "STATIC", "Namn:", WS_CHILD | WS_VISIBLE, 10, 60, 600, 20, g_addHjalpw, NULL, GetModuleHandle(NULL), NULL);
                HWND hEdit = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 10, 80, 600, 20, g_addHjalpw, (HMENU)ID_EDIT_BOX, GetModuleHandle(NULL), NULL);
                HWND hSaveButton = CreateWindow("BUTTON", "Spara", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 600, 25, g_addHjalpw, (HMENU)ID_SAVE_BUTTON1, GetModuleHandle(NULL), NULL);
                HWND hDropdown2 = CreateWindowW(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL , 10, 130, 200, 200, g_addHjalpw,(HMENU)ID_DROPDOWNLIST, NULL, NULL);
                printFileToDropdown(g_addHjalpw, listFileName, ID_DROPDOWNLIST);
            }break;
        case 2: {
                WNDCLASS wc = { 0 };
                wc.lpfnWndProc = NewTillWndProc;
                wc.hInstance = GetModuleHandle(NULL);
                wc.lpszClassName = "AddTillWindow";
                RegisterClass(&wc);

                g_addTillpw = CreateWindowA("AddTillWindow", "Nytt tillbehor", WS_OVERLAPPEDWINDOW, 100, 100, 640, 400, NULL, NULL, GetModuleHandle(NULL), NULL); 
                ShowWindow(g_addTillpw, SW_SHOW);
                UpdateWindow(g_addTillpw);
                
                HWND hStatic4 = CreateWindowW(L"STATIC", L"Till Vilken Produktgrupp:", WS_CHILD | WS_VISIBLE, 10, 110, 200, 20, g_addTillpw, NULL, GetModuleHandle(NULL), NULL);
                HWND hStatic6 = CreateWindowW(L"STATIC", L"Till Vilket Huvudhjälpmedel:", WS_CHILD | WS_VISIBLE, 220, 110, 390, 20, g_addTillpw, NULL, GetModuleHandle(NULL), NULL);
                HWND hStatic = CreateWindowEx(0, "STATIC", "Namn:", WS_CHILD | WS_VISIBLE, 10, 60, 120, 20, g_addTillpw, NULL, GetModuleHandle(NULL), NULL);
                HWND hEdit = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 10, 80, 150, 20, g_addTillpw, (HMENU)ID_EDIT_BOX4, GetModuleHandle(NULL), NULL);
                HWND hStatic1 = CreateWindowEx(0, "STATIC", "S2-nr:", WS_CHILD | WS_VISIBLE, 160, 60, 120, 20, g_addTillpw, NULL, GetModuleHandle(NULL), NULL);
                HWND hEdit1 = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 160, 80, 150, 20, g_addTillpw, (HMENU)ID_EDIT_BOX5, GetModuleHandle(NULL), NULL);
                HWND hStatic2 = CreateWindowW(L"STATIC", L"Leverantör:", WS_CHILD | WS_VISIBLE, 310, 60, 120, 20, g_addTillpw, NULL, GetModuleHandle(NULL), NULL);
                HWND hEdit2 = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 310, 80, 150, 20, g_addTillpw, (HMENU)ID_EDIT_BOX6, GetModuleHandle(NULL), NULL);
                HWND hStatic3 = CreateWindowEx(0, "STATIC", "Lev-nr:", WS_CHILD | WS_VISIBLE, 460, 60, 120, 20, g_addTillpw, NULL, GetModuleHandle(NULL), NULL);
                HWND hEdit3 = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 460, 80, 150, 20, g_addTillpw, (HMENU)ID_EDIT_BOX7, GetModuleHandle(NULL), NULL);
                HWND hButton = CreateWindowW(L"BUTTON", L"Spara", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 600, 25, g_addTillpw, (HMENU)ID_SAVE_BUTTON2, GetModuleHandle(NULL), NULL);
                HWND hDropdown = CreateWindowW(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL  , 10, 130, 200, 200, g_addTillpw,(HMENU)ID_DROPDOWNLIST1, NULL, NULL); 
                HWND hDropdown3 = CreateWindowW(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL  , 220, 130, 390, 200, g_addTillpw,(HMENU)ID_DROPDOWNLIST2, NULL, NULL);
                printFileToDropdown(g_addTillpw, listFileName, ID_DROPDOWNLIST1);
            }break;
        case 3: {
                WNDCLASS wc = { 0 };
                wc.lpfnWndProc = NewResWndProc;
                wc.hInstance = GetModuleHandle(NULL);
                wc.lpszClassName = "AddResWindow";
                RegisterClass(&wc);

                g_addRespw = CreateWindowA("AddResWindow", "Ny Reservdel", WS_OVERLAPPEDWINDOW, 100, 100, 640, 400, NULL, NULL, GetModuleHandle(NULL), NULL); 
                ShowWindow(g_addRespw, SW_SHOW);
                UpdateWindow(g_addRespw);
                
                HWND hStatic4 = CreateWindowW(L"STATIC", L"Till Vilken Produktgrupp:", WS_CHILD | WS_VISIBLE, 10, 110, 200, 20, g_addRespw, NULL, GetModuleHandle(NULL), NULL);
                HWND hStatic6 = CreateWindowW(L"STATIC", L"Till Vilket Huvudhjälpmedel:", WS_CHILD | WS_VISIBLE, 220, 110, 390, 20, g_addRespw, NULL, GetModuleHandle(NULL), NULL); 
                HWND hStatic = CreateWindowEx(0, "STATIC", "Namn:", WS_CHILD | WS_VISIBLE, 10, 60, 120, 20, g_addRespw, NULL, GetModuleHandle(NULL), NULL);
                HWND hEdit = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 10, 80, 150, 20, g_addRespw, (HMENU)ID_EDIT_BOX8, GetModuleHandle(NULL), NULL);
                HWND hStatic1 = CreateWindowEx(0, "STATIC", "S2-nr:", WS_CHILD | WS_VISIBLE, 160, 60, 120, 20, g_addRespw, NULL, GetModuleHandle(NULL), NULL);
                HWND hEdit1 = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 160, 80, 150, 20, g_addRespw, (HMENU)ID_EDIT_BOX9, GetModuleHandle(NULL), NULL);
                HWND hStatic2 = CreateWindowW(L"STATIC", L"Leverantör:", WS_CHILD | WS_VISIBLE, 310, 60, 120, 20, g_addRespw, NULL, GetModuleHandle(NULL), NULL);
                HWND hEdit2 = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 310, 80, 150, 20, g_addRespw, (HMENU)ID_EDIT_BOX10, GetModuleHandle(NULL), NULL);
                HWND hStatic3 = CreateWindowEx(0, "STATIC", "Lev-nr:", WS_CHILD | WS_VISIBLE, 460, 60, 120, 20, g_addRespw, NULL, GetModuleHandle(NULL), NULL);
                HWND hEdit3 = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 460, 80, 150, 20, g_addRespw, (HMENU)ID_EDIT_BOX11, GetModuleHandle(NULL), NULL);
                HWND hButton = CreateWindowW(L"BUTTON", L"Spara", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 600, 25, g_addRespw, (HMENU)ID_SAVE_BUTTON5, GetModuleHandle(NULL), NULL);
                HWND hDropdown = CreateWindowW(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL  , 10, 130, 200, 200, g_addRespw,(HMENU)ID_DROPDOWNLIST11, NULL, NULL);
                HWND hDropdown3 = CreateWindowW(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL  , 220, 130, 390, 200, g_addRespw,(HMENU)ID_DROPDOWNLIST12, NULL, NULL);
                printFileToDropdown(g_addRespw, listFileName, ID_DROPDOWNLIST11);
            }break;
        case 4: {
                WNDCLASS wc = { 0 };
                wc.lpfnWndProc = EditHelpWinProc;
                wc.hInstance = GetModuleHandle(NULL);
                wc.lpszClassName = "EditHelpWindow";
                RegisterClass(&wc);

                g_EditHelp = CreateWindowA("EditHelpWindow", "Ta bort Huvudhjaplmedel", WS_OVERLAPPEDWINDOW, 100, 100, 640, 400, NULL, NULL, GetModuleHandle(NULL), NULL); 
                ShowWindow(g_EditHelp, SW_SHOW);
                UpdateWindow(g_EditHelp);
                
                HWND hStatic4 = CreateWindowW(L"STATIC", L"Vilken Produktgrupp:", WS_CHILD | WS_VISIBLE, 10, 60, 200, 20, g_EditHelp, NULL, GetModuleHandle(NULL), NULL);
                HWND hStatic6 = CreateWindowW(L"STATIC", L"Vilket Huvudhjälpmedel:", WS_CHILD | WS_VISIBLE, 220, 60, 390, 20, g_EditHelp, NULL, GetModuleHandle(NULL), NULL);
                HWND hButton = CreateWindowW(L"BUTTON", L"Ta bort", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 600, 25, g_EditHelp, (HMENU)ID_SAVE_BUTTON4, GetModuleHandle(NULL), NULL);
                HWND hDropdown3 = CreateWindowW(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL  , 10, 80, 200, 200, g_EditHelp,(HMENU)ID_DROPDOWNLIST6, NULL, NULL);
                HWND hDropdown4 = CreateWindowW(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL  , 220, 80, 390, 200, g_EditHelp,(HMENU)ID_DROPDOWNLIST7, NULL, NULL);
                printFileToDropdown(g_EditHelp, listFileName, ID_DROPDOWNLIST6);
            }break;
        case 5: {
                WNDCLASS wc = { 0 };
                wc.lpfnWndProc = EditTillWinProc;
                wc.hInstance = GetModuleHandle(NULL);
                wc.lpszClassName = "EditTillWindow";
                RegisterClass(&wc);

                g_EditTill = CreateWindowA("EditTillWindow", "Ta bort tillbehor", WS_OVERLAPPEDWINDOW, 100, 100, 1040, 400, NULL, NULL, GetModuleHandle(NULL), NULL); 
                ShowWindow(g_EditTill, SW_SHOW);
                UpdateWindow(g_EditTill);
                
                HWND hStatic4 = CreateWindowW(L"STATIC", L"Vilken Produktgrupp:", WS_CHILD | WS_VISIBLE, 10, 60, 200, 20, g_EditTill, NULL, GetModuleHandle(NULL), NULL);
                HWND hStatic6 = CreateWindowW(L"STATIC", L"Vilket Huvudhjälpmedel:", WS_CHILD | WS_VISIBLE, 220, 60, 390, 20, g_EditTill, NULL, GetModuleHandle(NULL), NULL);
                HWND hStatic7 = CreateWindowW(L"STATIC", L"Vilket Tillbehör:", WS_CHILD | WS_VISIBLE, 620, 60, 390, 20, g_EditTill, NULL, GetModuleHandle(NULL), NULL);
                HWND hButton = CreateWindowW(L"BUTTON", L"Ta bort", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 1000, 25, g_EditTill, (HMENU)ID_SAVE_BUTTON3, GetModuleHandle(NULL), NULL);
                HWND hDropdown3 = CreateWindowW(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL  , 10, 80, 200, 200, g_EditTill,(HMENU)ID_DROPDOWNLIST3, NULL, NULL); 
                HWND hDropdown4 = CreateWindowW(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL  , 220, 80, 390, 200, g_EditTill,(HMENU)ID_DROPDOWNLIST4, NULL, NULL);
                HWND hDropdown5 = CreateWindowW(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL  , 620, 80, 390, 200, g_EditTill,(HMENU)ID_DROPDOWNLIST5, NULL, NULL);
                printFileToDropdown(g_EditTill, listFileName, ID_DROPDOWNLIST3);
            }break;
        case 6: {
                WNDCLASS wc = { 0 };
                wc.lpfnWndProc = EditResWinProc;
                wc.hInstance = GetModuleHandle(NULL);
                wc.lpszClassName = "EditResWindow";
                RegisterClass(&wc);

                g_EditRes = CreateWindowA("EditResWindow", "Ta bort Reservdel", WS_OVERLAPPEDWINDOW, 100, 100, 1040, 400, NULL, NULL, GetModuleHandle(NULL), NULL); 
                ShowWindow(g_EditRes, SW_SHOW);
                UpdateWindow(g_EditRes);
                
                HWND hStatic4 = CreateWindowW(L"STATIC", L"Vilken Produktgrupp:", WS_CHILD | WS_VISIBLE, 10, 60, 200, 20, g_EditRes, NULL, GetModuleHandle(NULL), NULL);
                HWND hStatic6 = CreateWindowW(L"STATIC", L"Vilket Huvudhjälpmedel:", WS_CHILD | WS_VISIBLE, 220, 60, 390, 20, g_EditRes, NULL, GetModuleHandle(NULL), NULL);
                HWND hStatic7 = CreateWindowW(L"STATIC", L"Vilket Tillbehör:", WS_CHILD | WS_VISIBLE, 620, 60, 390, 20, g_EditRes, NULL, GetModuleHandle(NULL), NULL);
                HWND hButton = CreateWindowW(L"BUTTON", L"Ta bort", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 1000, 25, g_EditRes, (HMENU)ID_SAVE_BUTTON6, GetModuleHandle(NULL), NULL);
                HWND hDropdown3 = CreateWindowW(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL  , 10, 80, 200, 200, g_EditRes,(HMENU)ID_DROPDOWNLIST8, NULL, NULL); 
                HWND hDropdown4 = CreateWindowW(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL  , 220, 80, 390, 200, g_EditRes,(HMENU)ID_DROPDOWNLIST9, NULL, NULL);
                HWND hDropdown5 = CreateWindowW(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL  , 620, 80, 390, 200, g_EditRes,(HMENU)ID_DROPDOWNLIST10, NULL, NULL);
                printFileToDropdown(g_EditRes, listFileName, ID_DROPDOWNLIST8);
            }break;
    }
}

void SaveTextToFile(HWND hEdit1, HWND hEdit2, HWND hEdit3, HWND hEdit4, const char *filename) {
    int len = GetWindowTextLength(hEdit1) + GetWindowTextLength(hEdit2) + GetWindowTextLength(hEdit3) + GetWindowTextLength(hEdit4);
    wchar_t* wideTextBuffer = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
    if (wideTextBuffer == NULL) {
        return;
    }
    wideTextBuffer[0] = L'\0';

    GetWindowTextW(hEdit1, wideTextBuffer, GetWindowTextLength(hEdit1) + 1);
    wcscat(wideTextBuffer, L"| ");
    GetWindowTextW(hEdit2, wideTextBuffer + wcslen(wideTextBuffer), GetWindowTextLength(hEdit2) + 1);
    wcscat(wideTextBuffer, L"| ");
    GetWindowTextW(hEdit3, wideTextBuffer + wcslen(wideTextBuffer), GetWindowTextLength(hEdit3) + 1);
    wcscat(wideTextBuffer, L"| ");
    GetWindowTextW(hEdit4, wideTextBuffer + wcslen(wideTextBuffer), GetWindowTextLength(hEdit4) + 1);
    wcscat(wideTextBuffer, L"| ");

    int utf8Length = WideCharToMultiByte(CP_UTF8, 0, wideTextBuffer, -1, NULL, 0, NULL, NULL);
    char *utf8Buffer = (char *)malloc(utf8Length);
    
    if (utf8Buffer == NULL) {
        free(wideTextBuffer);
        return;
    }

    WideCharToMultiByte(CP_UTF8, 0, wideTextBuffer, -1, utf8Buffer, utf8Length, NULL, NULL);

    FILE* file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "%s\n", utf8Buffer);
        fclose(file);
    }

    free(wideTextBuffer);
    free(utf8Buffer);

    SetWindowText(hEdit1, "");
    SetWindowText(hEdit2, "");
    SetWindowText(hEdit3, "");
    SetWindowText(hEdit4, "");
}

void SaveToFile(HWND hEdit1, const char *filename) {
    int len = GetWindowTextLength(hEdit1);
    wchar_t* wideTextBuffer = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
    if (wideTextBuffer == NULL) {
        return;
    }
    wideTextBuffer[0] = L'\0';

    GetWindowTextW(hEdit1, wideTextBuffer, GetWindowTextLength(hEdit1) + 1);

    int utf8Length = WideCharToMultiByte(CP_UTF8, 0, wideTextBuffer, -1, NULL, 0, NULL, NULL);
    char *utf8Buffer = (char *)malloc(utf8Length);
    
    if (utf8Buffer == NULL) {
        free(wideTextBuffer);
        return;
    }

    WideCharToMultiByte(CP_UTF8, 0, wideTextBuffer, -1, utf8Buffer, utf8Length, NULL, NULL);

    FILE* file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "%s\n", utf8Buffer);
        fclose(file);
    }

    free(wideTextBuffer);
    free(utf8Buffer);

    SetWindowText(hEdit1, "");
}

void removeLine(const char *filename, int lineToRemove) {
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char buffer[1000];
    int currentLine = 0;

    while (fgets(buffer, 1000, file) != NULL) {
        if (currentLine != lineToRemove) {
            fputs(buffer, tempFile);
        }
        currentLine++;
    }

    fclose(file);
    fclose(tempFile);

    remove(filename);
    rename("temp.txt", filename);
}

void CopyFileContents(const char *sourceFilename, const char *destinationFilename) {
    FILE *sourceFile = fopen(sourceFilename, "r");
    FILE *destinationFile = fopen(destinationFilename, "w");

    if (sourceFile == NULL || destinationFile == NULL) {
        printf("Error opening files.\n");
        return;
    }

    char buffer[1000];
    while (fgets(buffer, sizeof(buffer), sourceFile) != NULL) {
        fputs(buffer, destinationFile);
    }

    fclose(sourceFile);
    fclose(destinationFile);
}

void ClearFile(const char *filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Kunde inte öppna filen för skrivning.\n");
        return;
    }
    fclose(file);
}

bool isFileEmpty(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Kan inte öppna filen.\n");
        return true;
    }
    int ch = fgetc(file);
    fclose(file);
    return ch == EOF;
}

wchar_t* ConvertToWideChar(const char* str) {
    if (str == NULL){
        return NULL;
    } 
    int len = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    wchar_t* wstr = malloc(len * sizeof(wchar_t));
    if (wstr == NULL){
        return NULL;
    }
    MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, len);
    return wstr;
}
