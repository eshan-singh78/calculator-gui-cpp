#include <windows.h>
#include <string>
#include <sstream>
#include <cmath>

const char g_szClassName[] = "CalculatorWindow";

const char* operations[] = {"+", "-", "*", "/"};

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hwndEdit;
    static std::string input;

    switch(msg) {
        case WM_CREATE:
            hwndEdit = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_READONLY, 10, 10, 200, 30, hwnd, NULL, NULL, NULL);
            
            for(int i = 0; i < 10; ++i) {
                std::ostringstream oss;
                oss << i;
                CreateWindow("BUTTON", oss.str().c_str(), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10 + (i % 3) * 50, 50 + (i / 3) * 50, 50, 50, hwnd, (HMENU)(1000 + i), NULL, NULL);
            }
            
            for(int i = 0; i < 4; ++i) {
                CreateWindow("BUTTON", operations[i], WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 160, 50 + i * 50, 50, 50, hwnd, (HMENU)(2000 + i), NULL, NULL);
            }

            CreateWindow("BUTTON", "C", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 60, 200, 50, 50, hwnd, (HMENU)3000, NULL, NULL);
            CreateWindow("BUTTON", "=", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 110, 200, 50, 50, hwnd, (HMENU)3001, NULL, NULL);
            break;
        
        case WM_COMMAND:
            switch(LOWORD(wParam)) {
                case 1000: // Digits
                case 1001:
                case 1002:
                case 1003:
                case 1004:
                case 1005:
                case 1006:
                case 1007:
                case 1008:
                case 1009:
                    {
                        char buf[2] = {0};
                        buf[0] = '0' + LOWORD(wParam) - 1000;
                        input += buf;
                        SetWindowText(hwndEdit, input.c_str());
                    }
                    break;
                
                case 2000: // Operations
                case 2001:
                case 2002:
                case 2003:
                    {
                        char buf[2] = {0};
                        buf[0] = LOWORD(wParam) - 2000 == 0 ? '+' :
                                 LOWORD(wParam) - 2000 == 1 ? '-' :
                                 LOWORD(wParam) - 2000 == 2 ? '*' : '/';
                        input += buf;
                        SetWindowText(hwndEdit, input.c_str());
                    }
                    break;

                case 3000: // Clear
                    input.clear();
                    SetWindowText(hwndEdit, input.c_str());
                    break;

                case 3001: // Equal sign
                    {
                        std::istringstream iss(input);
                        double result = 0.0;
                        char op;
                        iss >> result;
                        while (iss >> op) {
                            double operand;
                            iss >> operand;
                            switch (op) {
                                case '+':
                                    result += operand;
                                    break;
                                case '-':
                                    result -= operand;
                                    break;
                                case '*':
                                    result *= operand;
                                    break;
                                case '/':
                                    if (operand != 0.0) {
                                        result /= operand;
                                    } else {
                                        MessageBox(hwnd, "Error: Division by zero", "Error", MB_OK | MB_ICONERROR);
                                        result = NAN;
                                    }
                                    break;
                                default:
                                    MessageBox(hwnd, "Error: Invalid operation", "Error", MB_OK | MB_ICONERROR);
                                    result = NAN;
                                    break;
                            }
                        }
                        std::ostringstream oss;
                        oss << result;
                        input = oss.str();
                        SetWindowText(hwndEdit, input.c_str());
                    }
                    break;
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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(0, g_szClassName, "Calculator", WS_OVERLAPPEDWINDOW | WS_SIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 240, 300, NULL, NULL, hInstance, NULL);

    if(hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

