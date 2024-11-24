#include <iostream>
#include <string>
#include <windows.h>
/*ͳ��doc���ļ���������ɳ��*/

void countFilesWithExtensions(const std::string& directory, int& docCount, int& xlsCount, int& pptCount) {
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind;

    // ��ǰĿ¼�������ļ�
    std::string searchPath = directory + "\\*.*";
    hFind = FindFirstFileA(searchPath.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
       /* std::cerr << "Error: Could not open directory " << directory << std::endl;*/
        return;
    }

    do {
        std::string filename = findFileData.cFileName;

        // ����.��..Ŀ¼
        if (filename == "." || filename == "..") {
            continue;
        }

        std::string fullPath = directory + "\\" + filename;

        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            // ��ȵݹ��õ�Ŀ¼�µ�ȫ���ļ�
            countFilesWithExtensions(fullPath, docCount, xlsCount, pptCount);
        }
        else {
            // ƥ���ļ���׺
            size_t pos = filename.rfind('.');
            if (pos != std::string::npos) {
                std::string extension = filename.substr(pos + 1);

                if (extension == "doc" || extension == "docx") {
                    ++docCount;
                }
                else if (extension == "xls" || extension == "xlsx") {
                    ++xlsCount;
                }
                else if (extension == "ppt" || extension == "pptx") {
                    ++pptCount;
                }
            }
        }
    } while (FindNextFileA(hFind, &findFileData) != 0);

    FindClose(hFind);
}

int main() {
    std::string directory;
    /*std::cout << "Enter the directory to search: ";*/
    /*std::getline(std::cin, directory);*/
    directory = "C:";

    int docCount = 0; 
    int xlsCount = 0;
    int pptCount = 0;

    countFilesWithExtensions(directory, docCount, xlsCount, pptCount);

    std::cout << "DOC files: " << docCount << std::endl;
    std::cout << "XLS files: " << xlsCount << std::endl;
    std::cout << "PPT files: " << pptCount << std::endl;
    std::cout << "Total matching files: " << (docCount + xlsCount + pptCount) << std::endl;
    system("pause");

    return 0;
}
