#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<iostream>
using namespace std;

typedef struct LoginDetail {

	char username[30];
	char password[30];
}LoginDetails;

typedef struct process {
	char name[30];
	int waitingCycles;
	int completionCycles;
}Process;

typedef struct procressInRun {
	char name[30];
	char status[30];
	int waitingCycles;
	int waitingCount;
	int completionCycles;
	int cyclesCount;
	int timeCount;
}processQueue;

class structures
{
};

