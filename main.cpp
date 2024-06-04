#include <iostream>

#include "robot.h"
using namespace std;
int main() {
    string command;
    int n;
    cin>>n;
    while(n--) {
        commandin();
    }
    cout<<Manage::getrobnum();
    return 0;
}
