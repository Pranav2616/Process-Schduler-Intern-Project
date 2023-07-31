
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Admin.h"
#include <vector>
#include "structures.h"

using namespace std;

void Admin::adminAutheniticate()
{
	char username[30], password[30];
	cout << "Enter your username" << endl;
	cin >> username;
	cout << "Enter your password" << endl;
	cin >> password;
	cout << endl;
	if (!strcmp(username, "admin") && !strcmp(password, "admin"))
		initiateAdminProcess();
	else
		cout << "Invalid admin username or password" << endl;
}

void Admin::initiateAdminProcess()
{
	readUsers();
	readProcess();
	bool flag = true;
	while (flag)
	{		
		switch (printAdminOptions())
		{
		case 1: createUser(); break;
		case 2: printsUsers(); break;
		case 3: deleteuser(); break;
		case 4: createProcess(); break;

		case 5:showProcessList(); break;
		case 6: deleteProcess(); break;
		default : flag = false; break;
		}
	}
	loginDetailsList.clear();
	processList.clear();
}

int Admin::printAdminOptions()
{
	int adminInput;
	cout << "Press 1 to create the user" << endl;
	cout << "Press 2 to see all the user" << endl;
	cout << "Press 3 to delete the user" << endl;
	cout << "Press 4 to create a process" << endl;
	cout << "Press 5 to see all process" << endl;
	cout << "Press 6 to delete a process" << endl;
	cout << "Press 0 to exit" << endl;
	cout << endl;
	cin >> adminInput;
	cout << endl;
	return adminInput;

}

void Admin::createUser()
{
	
	cout << "Enter the user name of the user\n";
	LoginDetails LD ;
	cin >> LD.username;
	cout << "Enter the password of the user\n";
	cin >> LD.password;	
	loginDetailsList.push_back(LD);
	writeUsers();

}

void Admin::printsUsers()
{
	int n = loginDetailsList.size();
	for (int i =0 ;i<n;i++)
		cout <<i+1<<"\t"<< loginDetailsList[i].username<<"\t"<<loginDetailsList[i].password  << endl;	
}

void Admin::writeUsers() {
	FILE* fp = fopen("UserDetail.txt", "wt");
	for (auto i : loginDetailsList)
		fwrite(&i, sizeof(LoginDetails), 1, fp);
	fclose(fp);

}

void Admin::deleteuser()
{
	int n;
	cout << "Enter the use ID to delete the user\n";
	while (true)
	{
		printsUsers();		
		cin >> n;
		if (n <= sizeOfLoginList)
			break;		
		cout << "User Id not in the list!! Renter the ID properly\n";
	}
	cout << "User " << n << " deleted successfully\n";
	loginDetailsList.erase(loginDetailsList.begin() + n - 1);
	writeUsers();
}

void Admin::createProcess()
{
	Process process;	
	cout << "Enter the name of the process\n";
	cin >> process.name;
	char ch = getchar();
	cout << "Enter the time cycles required to complete the process" << endl;
	cin >> process.completionCycles;
	cout << "Enter the waiting cycles of the process" << endl;
	cin >> process.waitingCycles;
	processList.push_back(process);
	sizeofProcessList = processList.size();
	writeProcess();

}

void Admin::writeProcess()
{
	FILE* fp;
	fp = fopen("ProcessList.txt", "wt");
	for (auto i : processList)
		fwrite(&i, sizeof(Process), 1, fp);
	fclose(fp);
}

void Admin::deleteProcess()
{
	int input;
	cout << "Enter the process Id to be deleted" << endl;
	while (true)
	{
		showProcessList();
		cout << "Press 0 to cancel deletion" << endl;
		cin >> input;
		if (input <= sizeofProcessList &&input!=0)
		{
			processList.erase(processList.begin() + input - 1);
			break;
		}
		cout << "Process Id not in the list!! Renter the ID properly" << endl;
		if (input == 0)
			break;
		
	}
	
	sizeofProcessList = processList.size();
	writeProcess();

}
