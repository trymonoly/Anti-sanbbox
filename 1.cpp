#include <string>     // std::string
#include <regex>      // std::regex, std::regex_match
#include <windows.h>  // GetCurrentDirectoryA
/*����ɳ���Ŀ¼ȥ�жϷ�ɳ��*/
std::string workingdir()
{
    char buf[256];
    GetCurrentDirectoryA(256, buf);  //��ȡ��ǰĿ¼��pwd����һ��
    return std::string(buf);
}
bool check_run_path() {
    std::string test(workingdir());     //��ʼ����ǰĿ¼���ַ�������
    std::regex pattern("^C:\\\\Users\\\\Administrator\\\\Desktop");  // ����ģʽƥ��    // ����ģʽ
    if (std::regex_match(test, pattern)) {   //�ַ���ƥ��΢���ļ�
        return false;
    }
    else {
        return true;
    }
}

int main() {
    bool a = check_run_path();
    if (a) {
        MessageBoxA(0, "��ִ����", 0, 0);
        return 0;
    }
    MessageBoxA(0, "��ûִ��", 0, 0);
    return 0;
}