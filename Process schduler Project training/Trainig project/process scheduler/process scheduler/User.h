#pragma once
#include<iostream>
#include <list>
#include<vector>
#include "structures.h"

using namespace std;


class User
{protected:
	vector<processQueue> readyToRun;
	vector<LoginDetails> loginDetailsList;
	int sizeOfLoginList;
	vector<Process> processList;
	int CPUcount;
	int processCount;
	int sizeofProcessList;
	const char* yetToRun = "Ready to Run";
	const char* stopped = "Stopped";
	const char* waiting = "Waiting";
	const char* running  = "Running";
	const char* completed = "Completed";

	void initiateUser();
	void readUsers();
	void readProcess();
	void showProcessList();
	
	void addProcessByUser();	
	void waitingTimeReduction();
	void randomStatusAssignment();
	void restartProcess();
	void processStatus();
	bool processCompletionCheck();
	void processLog();	

public:	
	User();
	void authenticateUser();


};

