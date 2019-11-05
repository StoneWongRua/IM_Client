#pragma once
#include <windows.h>
#include<iostream>
#pragma comment(lib, "ws2_32.lib")

using namespace std;
#define IP "192.168.1.131"
#define PORT 12000
#define CHECKNUM 1
#define MESSAGENUM 2
#define SIGNUPNUM 3
#define LOGOUTNUM 4
#define CHOOSENUM 5
#define ADDFRIENDNUM 6
#define CHOOSEFRIENDNUM 7



class HstConnect
{
public:
	HstConnect();
	~HstConnect();

	int Login(char* _name, char* _password);

	int Register(char* _name, char* _password);

	int ChoosePattern(int stutas);

	int SendMessage(char * buff);

	string ReceiveMessage();

	int AddFriend(char * name);

	int testFriend();

	string ReceiveFriendList();

	int ChooseFriend(int num);


private:

};

