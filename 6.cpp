#include <iostream>
#include <windows.h>
#include <cmath>
/*检查鼠标是否为类三角*/
double distance(POINT p1, POINT p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

bool check_mouse() {
    POINT p1, p2, p3;
    GetCursorPos(&p1);
    Sleep(3000);
    GetCursorPos(&p2);
    Sleep(3000);
    GetCursorPos(&p3);

    double d1 = distance(p1, p2);
    double d2 = distance(p2, p3);
    double d3 = distance(p3, p1);

    //检查距离是否可以形成三角形
    return (d1 + d2 > d3) && (d2 + d3 > d1) && (d1 + d3 > d2);
}

int main() {
    if (check_mouse()) {
        std::cout << "The points can form a triangle." << std::endl;
    }
    else {
        std::cout << "The points cannot form a triangle." << std::endl;
    }
    return 0;
}
