// process scheduler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Admin.h"
#include<Windows.h>
#include "User.h"
using namespace std;

int main()
{
    Admin* admin = new Admin;
    User* user = new User;
    bool flag = true;
    while (flag)
    {
        cout << endl;
        cout << "Press 1 to login as Admin" << endl;
        cout << "Press 2 to login as User" << endl;
        cout << "Press 0 to quit" << endl;
       
        int input;
        cin >> input;
        cout << endl;
        switch (input)
        {
        case 1:admin->adminAutheniticate();break;
        case 2:user->authenticateUser();break;
        default :flag = false; break;
        }
    }
}
