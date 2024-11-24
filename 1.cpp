#include <string>     // std::string
#include <regex>      // std::regex, std::regex_match
#include <windows.h>  // GetCurrentDirectoryA
/*根据沙箱的目录去判断反沙箱*/
std::string workingdir()
{
    char buf[256];
    GetCurrentDirectoryA(256, buf);  //获取当前目录，pwd功能一治
    return std::string(buf);
}
bool check_run_path() {
    std::string test(workingdir());     //初始化当前目录的字符串名字
    std::regex pattern("^C:\\\\Users\\\\Administrator\\\\Desktop");  // 正则模式匹配    // 正则模式
    if (std::regex_match(test, pattern)) {   //字符串匹配微步文件
        return false;
    }
    else {
        return true;
    }
}

int main() {
    bool a = check_run_path();
    if (a) {
        MessageBoxA(0, "我执行啦", 0, 0);
        return 0;
    }
    MessageBoxA(0, "我没执行", 0, 0);
    return 0;
}