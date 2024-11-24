#include <windows.h>
#include <winhttp.h>
#include <iostream>
#include <string>
#include <ctime>

#pragma comment(lib, "winhttp.lib")

/*¼ÆËãÊ±¼ä²î*/
std::string GetServerTime() {
    std::string time_str;
    // Open a session
    HINTERNET hSession = WinHttpOpen(L"WinHTTP Example/1.0",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS, 0);

    if (hSession) {
        // Specify the server
        HINTERNET hConnect = WinHttpConnect(hSession, L"api.pinduoduo.com",
            INTERNET_DEFAULT_HTTP_PORT, 0);

        if (hConnect) {
            // Create an HTTP request handle
            HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET",
                L"/api/server/_stm",
                NULL, WINHTTP_NO_REFERER,
                WINHTTP_DEFAULT_ACCEPT_TYPES,
                0);

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

                    // Keep checking for data until there¡¯s nothing left
                    do {
                        dwSize = 0;
                        if (WinHttpQueryDataAvailable(hRequest, &dwSize) && dwSize > 0) {
                            if (WinHttpReadData(hRequest, (LPVOID)buffer, dwSize, &dwDownloaded)) {
                                for (DWORD i = 0; i < dwDownloaded; i++) {
                                    if (buffer[i] >= '0' && buffer[i] <= '9') {
                                        time_str += buffer[i];
                                    }
                                }
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
    return time_str;
}

bool check_time() {
    std::string time_str1 = GetServerTime();
    if (time_str1.empty()) {      
        return false; // Return false if the first request fails
    }

    // Convert the extracted string to a numeric time
    long long api_time1 = std::stoll(time_str1);

    // Sleep for 300 seconds (5 minutes)
    HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    WaitForSingleObject(hEvent, 300000); // 300 seconds
    CloseHandle(hEvent);

    // Second API call to get the server time after sleep
    std::string time_str2 = GetServerTime();
    if (time_str2.empty()) {
        return false; // Return false if the second request fails
    }

    // Convert the extracted string to a numeric time
    long long api_time2 = std::stoll(time_str2);

    // Check if the time difference is greater than 290 seconds (290,000 ms)
    if (api_time2 - api_time1 > 290000) {
        return true; // Time difference is within expected bounds
    }
    else {
        exit(0);
        return false;
    }
}

int main() {
    if (check_time()) {
        std::cout << "Time check passed." << std::endl;
    }
    else {
        std::cout << "Time check failed." << std::endl;
    }
    system("pause");
    return 0;
}