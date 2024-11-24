#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm> 
/*�ж������ļ��Ƿ���qq��΢�Ż������ȵ�*/
bool Check_Decktop(const std::string& directory) {
	WIN32_FIND_DATAA findFileData;   //�洢���ļ�������С�����ԵȽṹ��
	HANDLE hFind;

	std::string searchPath = "C:\\Users\\"+ directory + "\\Desktop\\*.*";
	hFind = FindFirstFileA(searchPath.c_str(), &findFileData);
	do {
		std::string filename = findFileData.cFileName;

		// ����.��..Ŀ¼
		if (filename == "." || filename == "..") {
			continue;
        }
		// �ҵ����һ��'.'��λ��
		size_t dotPos = filename.rfind('.');
		
		if (dotPos != std::string::npos) {   // std::string::npos�յ���˼
			// ����ҵ���'.'����ȡ�ӿ�ͷ�����λ�õ��Ӵ�
			std::string nameWithoutExtension = (dotPos != std::string::npos)
				? filename.substr(0, dotPos)
				: filename;
			if (nameWithoutExtension == "Notion") {  //�޸�Ϊ��Ҫ���ļ�
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
		return "Unknown"; // �����ȡʧ�ܣ�����Ĭ��ֵ
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