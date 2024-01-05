#include <iostream>
using namespace std;
void A();
void B(){
    A();
    #ifdef A_VAR
    cout << "in B: A_VAR=" << A_VAR << endl;
    #endif
}
