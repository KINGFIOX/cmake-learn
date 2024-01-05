#include <iostream>
using namespace std;
int main(void) {
    void B ();  // 这里是我们自己做了一个声明，现在是找不到定义
    B();
    #ifdef STATIC
    cout << "in main: STATIC=" << STATIC << endl;
    #endif
    return 0;
}
