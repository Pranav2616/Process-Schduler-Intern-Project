
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <conio.h>
#include <string.h> 
#include <list>
#include <Windows.h>
#include "User.h"

using namespace std;

User::User()
{
	CPUcount = 0;
}

void User::authenticateUser()
{
	readProcess();
	readUsers();
	char username[30], password[30];
	bool flag = true;
	while (flag) {
		cout << "Enter your username" << endl;
		cin >> username;
		cout << endl;
		cout << "Enter your password" << endl;
		cin >> password;
		cout << endl; 
		for (int i = 0; i < sizeOfLoginList; i++)
		{
			if (!strcmp(loginDetailsList[i].username, username) && !strcmp(loginDetailsList[i].password, password))
			{
				cout << "Logged in as " << loginDetailsList[i].username << endl;
				initiateUser();
				flag = false;
				break;
			}
		}
		if (flag)
			cout << "Invalid username or password!!!" << endl << "Renter the password" << endl;
	}

}

void User::initiateUser()
{

	cout << "Enter the number of processor" << endl;
	cin >> CPUcount;
	cout << endl; 
	cout << "Enter the number of process" << endl;
	cin >> processCount;
	cout << endl; 
	addProcessByUser();
	cout << "Type 'stop' to see process which are stopped" << endl<<endl;
	
	bool flag = true;
	while (flag)
	{
		int readytoRuncount = CPUcount;
		for (int i = 0; i < processCount && readytoRuncount; i++)
		{
			if (!strcmp(readyToRun[i].status, yetToRun))
			{
				strcpy(readyToRun[i].status, running);
				readyToRun[i].completionCycles--;
				if (readyToRun[i].completionCycles == 0)
				{
					strcpy(readyToRun[i].status, completed);
					cout << readyToRun[i].name << " completed" << endl << endl;
				}
				readytoRuncount--;
			}
		}
		Sleep(1000);
		waitingTimeReduction();
		randomStatusAssignment();
		if (_kbhit()) {
			char ch[10];
			cin >> ch;
			if (!strcmp(ch, "stop"))
				restartProcess();
			else if (!strcmp(ch, "progress"))
				processStatus();
		}
		flag = processCompletionCheck();
	}
	cout << "\nAll processes are successfully completed\n" << endl<<endl;
	processLog();

}

void User::processLog()
{
	cout << "Process log : \n";
	cout << "Process Name\t Time taken" << endl;
	for (int i = 0; i < processCount; i++)
		cout << readyToRun[i].name << "\t" << readyToRun[i].timeCount << endl;
	cout << endl;
}

void User::addProcessByUser()
{
	processQueue temp;
	temp.waitingCount = 0;
	temp.cyclesCount = 0;
	temp.timeCount = 0;
	strcpy(temp.status, yetToRun);

	for (int i = 0; i < processCount; i++)
	{
		showProcessList();
		int selection;
		cout << "Enter the process ID to be done" << endl;
		cin >> selection;
		cout << endl;
		if (selection > sizeofProcessList)
		{
			i--;
			cout << "Process ID does not exist" << endl;
			continue;
		}
		strcpy(temp.name, processList[selection - 1].name);
		temp.waitingCycles = processList[selection - 1].waitingCycles;
		temp.completionCycles = processList[selection - 1].completionCycles;
		readyToRun.push_back(temp);
	}
	cout << "Process selected are :" << endl;
	for (auto i : readyToRun)
		cout << i.name << endl;
	cout << endl;
}

void User::waitingTimeReduction()
{
	for (int i = 0; i < processCount; i++)
	{
		if (!strcmp(readyToRun[i].status, waiting))
		{
			readyToRun[i].waitingCount--;
			if (readyToRun[i].waitingCount <= 0)
				strcpy(readyToRun[i].status, yetToRun);

		}
		if (strcmp(readyToRun[i].status, completed))
			readyToRun[i].timeCount++; // Counting the time taken to extcute the process
	}

}

void User::randomStatusAssignment()
{
	int randInt;
	for (int i = 0; i < processCount; i++)
	{
		randInt = 1 + (rand() % 10);
		if (!strcmp(readyToRun[i].status, yetToRun) || !strcmp(readyToRun[i].status, running))
		{
			switch (randInt)
			{
			case 2: strcpy(readyToRun[i].status, stopped); break;
			case 3: strcpy(readyToRun[i].status, waiting); break;
			default: strcpy(readyToRun[i].status, yetToRun); break;
			}
		}
	}
}

void User::restartProcess()
{
	cout << "Press 1 to start the process and 0 to skip for now" << endl;
	for (int i = 0; i < processCount; i++)
		if (!strcmp(readyToRun[i].status, stopped))
		{
			cout << readyToRun[i].name << " stopped " << endl;
			int input;
			cin >> input;
			if (input)
				strcpy(readyToRun[i].status, yetToRun);
			cout << readyToRun[i].name << " Status changed to " << readyToRun[i].status << endl << endl;
		}
}

void User::processStatus()
{
	cout << endl;
	for (int i = 0; i < processCount; i++)
	{
		cout << readyToRun[i].name << " " << readyToRun[i].status << endl;
	}
	cout << endl;
}

bool User::processCompletionCheck()
{
	for (auto i : readyToRun)
		if (strcmp(i.status, completed))
			return true;
	return false;
}

void User::readUsers()
{
	LoginDetails login;
	FILE* fp;
	fp = fopen("UserDetail.txt", "r");
	//fread(&login, sizeof(LoginDetails), 1, fp);
	while (!feof(fp))
	{
		fread(&login, sizeof(LoginDetails), 1, fp);
		loginDetailsList.push_back(login);
	}
	sizeOfLoginList = loginDetailsList.size();
	fclose(fp);
}

void User::readProcess()
{
	FILE* fp = fopen("ProcessList.txt", "r");
	Process process;
	//fread(&process, sizeof(Process), 1, fpa);
	//processList.push_back(process);
	while (!feof(fp))
	{

		fread(&process, sizeof(Process), 1, fp);
		processList.push_back(process);
	}
	fclose(fp);
	processList.erase(processList.end() - 1);
	sizeofProcessList = processList.size();
}

void User::showProcessList()
{
	for (int i = 0; i < sizeofProcessList; i++)
		cout << i + 1 << "\t" << processList[i].name << endl;
	cout << endl;

}