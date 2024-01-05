#include <iostream>
using namespace std;
void A(){
    #ifdef A_VAR
    cout << "in A " << A_VAR << endl;
    #endif
}
