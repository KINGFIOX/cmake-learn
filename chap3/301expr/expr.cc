#include <iostream>
using namespace std;

int main(void)
{
    cout << "hello" << endl;
#ifdef TEST1
    cout << TEST1 << endl;
#endif
}