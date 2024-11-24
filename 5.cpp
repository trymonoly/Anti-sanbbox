#include <windows.h>
#include <winhttp.h>
#include <iostream>
#include <string>

#pragma comment(lib, "winhttp.lib")

/*通过在线网站判断主机ip位置对抗外国的沙箱*/
bool check_ip() {
    std::string ip_str;

    // Open a session
    HINTERNET hSession = WinHttpOpen(L"WinHTTP Example/1.0",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS, 0);

    if (hSession) {
        // Connect to ip-api.com
        HINTERNET hConnect = WinHttpConnect(hSession, L"ip-api.com", INTERNET_DEFAULT_HTTP_PORT, 0);

        if (hConnect) {
            // Create an HTTP request handle
            HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", L"/csv",
                NULL, WINHTTP_NO_REFERER,
                WINHTTP_DEFAULT_ACCEPT_TYPES, 0);

            if (hRequest) {
                // Send a request
                BOOL bResult = WinHttpSendRequest(hRequest,
                    WINHTTP_NO_ADDITIONAL_HEADERS,
                    0, WINHTTP_NO_REQUEST_DATA, 0,
                    0, 0);

                // Receive a response
                if (bResult && WinHttpReceiveResponse(hRequest, NULL)) {
                    DWORD dwSize = 0;
                    DWORD dwDownloaded = 0;
                    char buffer[1024];

                    // Read data until there's none left
                    do {
                        dwSize = 0;
                        if (WinHttpQueryDataAvailable(hRequest, &dwSize) && dwSize > 0) {
                            if (WinHttpReadData(hRequest, (LPVOID)buffer, dwSize, &dwDownloaded)) {
                                ip_str.append(buffer, dwDownloaded);
                            }
                        }
                    } while (dwSize > 0);
                }
                WinHttpCloseHandle(hRequest);
            }
            WinHttpCloseHandle(hConnect);
        }
        WinHttpCloseHandle(hSession);
    }

    // Check if "China" is in the response
    if (ip_str.find("China") != std::string::npos) {
        return true;
    }
    else {
        exit(0);
        return false;
    }
}

int main() {
    if (check_ip()) {
        std::cout << "IP location is in China." << std::endl;
    }
    else {
        std::cout << "IP location is not in China." << std::endl;
    }
    return 0;
}