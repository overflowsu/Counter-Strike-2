#pragma once
#include <windows.h>
#include <Lmcons.h>
#include <iostream>

std::string GetWindowsUsername() {
    char username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    if (GetUserNameA(username, &username_len)) {
        return std::string(username);
    }
    return "Unknown";
}