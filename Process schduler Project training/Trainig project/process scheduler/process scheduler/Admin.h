#pragma once
#include<iostream>
#include "User.h"
#include<vector>
#define _CRT_SECURE_NO_WARNINGS
#include "structures.h"
using namespace std;

class Admin:private User{
private:	 	
	int printAdminOptions(); //
	void initiateAdminProcess();

	void createUser();
	void writeUsers();
	void printsUsers();
	void deleteuser();
	
	void createProcess();
	void writeProcess();	
	void deleteProcess();
public:
	void adminAutheniticate();
	


};

