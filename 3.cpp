#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm> 
/*判断桌面文件是否有qq或微信或其他等等*/
bool Check_Decktop(const std::string& directory) {
	WIN32_FIND_DATAA findFileData;   //存储着文件名，大小，属性等结构体
	HANDLE hFind;

	std::string searchPath = "C:\\Users\\"+ directory + "\\Desktop\\*.*";
	hFind = FindFirstFileA(searchPath.c_str(), &findFileData);
	do {
		std::string filename = findFileData.cFileName;

		// 跳过.和..目录
		if (filename == "." || filename == "..") {
			continue;
        }
		// 找到最后一个'.'的位置
		size_t dotPos = filename.rfind('.');
		
		if (dotPos != std::string::npos) {   // std::string::npos空的意思
			// 如果找到了'.'，截取从开头到这个位置的子串
			std::string nameWithoutExtension = (dotPos != std::string::npos)
				? filename.substr(0, dotPos)
				: filename;
			if (nameWithoutExtension == "Notion") {  //修改为想要的文件
				return true;
			}

		}
    } while (FindNextFileA(hFind, &findFileData) != 0);

	return false;
}

std::string getUser() {
	char username[256];
	DWORD username_len = sizeof(username);
	if (GetUserNameA(username, &username_len)) {
		return std::string(username);
	}
	else {
		return "Unknown"; // 如果获取失败，返回默认值
	}
}

int main() {
	std::string test(getUser());
	std::cout << test << std::endl;

	bool p = Check_Decktop(test);
	if (p) {
		MessageBoxA(0, 0, 0, 0);
	}
	return 0;
}