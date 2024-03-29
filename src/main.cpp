#include <windows.h>
#include<iostream>
#include <regex>

#include"InitConnect.h"
#include "Sha256.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;


int prepare();
int lo_menu();

HstConnect* hstConnect = new HstConnect();

void recive() {
	string message;
	while (1) {
		message = hstConnect->ReceiveMessage();
		//std::cout << message << endl;
		if (message[0] != 0) {
			std::cout << message << endl;
		}
	}
}

int re_menu()
{
	{
		while (1) {
			SetConsoleTitle("注册");
			char name[1024];
			char password[1024];
			std::cout << ">>>注册" << endl;
			std::cout << ">>>>>用户名:";
			std::cin >> name;
			std::cout << ">>>>>密码(仅支持9~16 位数字和字母的组合):";
			std::cin >> password;


			regex repPattern("[0-9a-zA-Z]{9,16}", regex_constants::extended);

			// 进行匹配
			bool bValid = regex_match(password, repPattern);

			if (bValid)
			{
				// 匹配成功

				char sha256[256];
				Sha256* sha_hst = nullptr;
				sha_hst->StrSHA256(password, sizeof(password) - 1, sha256);  // sizeof()包含了末尾的终止符'\0'故 -1

				int r = hstConnect->Register(name, sha256);

				if (r == 0) {
					std::cout << "注册成功！" << endl;
					break;

				}
				else {
					std::cout << "注册失败！用户名已被占用" << endl;
					
				}
			}
			else
			{
				std::cout << "注册失败！密码输入格式有误！" << endl;
				std::cout << "再次进入注册页面！" << endl;
			}
		}
		return 1;
	}
}

int lo_menu()
{
	{
		while (1) {
			SetConsoleTitle("登录");
			char name[1024];
			char password[1024];
			std::cout << ">>> 登录" << endl;
			std::cout << ">>>>> 用户名:";
			std::cin >> name;
			std::cout << ">>>>> 密码:";
			std::cin >> password;

			int l = hstConnect->Login(name, password);

			if (l == 0) {
				std::cout << "登录成功！" << endl;
				break;
				return 1;
			}
			else {
				std::cout << "登陆失败，请检查账号密码！" << endl;
			}
		}
	}
}


int index_ui()
{
	char option;
	cin >> option;

	if (option == 1) {
		cout << "登入您的账号：" << endl;
		lo_menu();
	}
	else if (option == 2)
	{
		cout << "注册新的账号：" << endl;
		re_menu();
	}
	else
	{
		cout << "输入命令有误。请重新输入。";
	}
	cout << "register";
	system("pause");
	return 0;

}

void onechat_ui(){

	SetConsoleTitle("单聊界面");
	std::cout << "进入单聊界面" << endl;

	string friendList;

	friendList = hstConnect->ReceiveFriendList();

	std::cout << "您的好友有：";

	if (!friendList.empty())
	{
		std::cout << friendList << endl;
	}

	std::cout << "请选择聊天对象（从0开始的数字标号）：";
	int friendNum;
	cin >> friendNum;
	getchar();

	int c = hstConnect->ChooseFriend(friendNum);

	if (c == 0) {
		std::cout << "选择成功！" << endl;
	}
	else {
		std::cout << "选择失败！" << endl;
	}


	//发送消息
	while (1) {
		char message[1024];
		gets_s(message);
		int s = hstConnect->SendMessage(message);
		if (s == 0)
		{
			std::cout << "发送成功！" << endl;
		}
		else
		{
			std::cout << "发送失败！" << endl;
		}
	}
}

void groupchat_ui()
{
	SetConsoleTitle("群聊界面");
	std::cout << "进入群聊界面" << endl;
	while (1) {
		char message[1024];
		gets_s(message);
		int s = hstConnect->SendMessage(message);
		if (s == 0) {
			std::cout << "发送成功！" << endl;
		}
		else {
			std::cout << "发送失败！" << endl;
		}
	}
}

int main()

{

		if (prepare() < 0) {
		return -1;
		}
	cout << "欢迎来到聊天系统！首先请选择你的操作登录（REGISTER）/注册（LOGIN）/退出（EXIT）";

	char functionName[30];

	do
	{
		cout << ">>> ";

		char fullCommand[30];
		cin.getline(fullCommand, 30);

		char command[300];

		int i = 0;

		for (i = 0; fullCommand[i] != '\0' && fullCommand[i] != ' '; ++i)
		{
			functionName[i] = fullCommand[i];
		}

		functionName[i] = '\0';

		if (strlen(functionName) != strlen(fullCommand))
		{
			strcpy_s(command, 35, fullCommand + i + 1);
		}

		if (strcmp(functionName, "LOGIN") == 0)
		{
			cout << "开始登录"<<endl;

			if (lo_menu())
			{
				cout << "登录成功，请选择你的聊天类型：单聊(ONE)/群聊(GROUP)/加好友(ADD)" << endl;


				while (true)
				{
					

					char optionChat[30];
					cin.getline(optionChat, 30);



					if (strcmp(optionChat, "ONE") == 0)
					{
						cout << "one";
						int choosenum = 2;
						int c = hstConnect->ChoosePattern(choosenum);
						if (c == 0)
						{
							std::cout << "选择成功！" << endl;
						}
						else {
							std::cout << "选择失败！" << endl;
						}

						//接收服务器消息
						CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recive, NULL, NULL, NULL);

						onechat_ui();
						break;
					}
					else if (strcmp(optionChat, "GROUP") == 0)
					{
						cout << "group";

						int choosenum = 1;
						int c = hstConnect->ChoosePattern(choosenum);
						if (c == 0)
						{
							std::cout << "选择成功！" << endl;
						}
						else {
							std::cout << "选择失败！" << endl;
						}

						//接收服务器消息
						CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recive, NULL, NULL, NULL);


						groupchat_ui();
						break;
					}
					else if(strcmp(optionChat, "ADD") == 0)
					{



						SetConsoleTitle("添加好友");
						std::cout << "\n输入你要添加的用户名";
						char addName[1024];
						gets_s(addName);

						int c = hstConnect->AddFriend(addName);

						if (c == 0) {
							std::cout << "操作选择成功！" << endl;
							hstConnect->testFriend();
						}
						else {
							std::cout << "操作选择失败！" << endl;
						}


						}
				}


			}
			break;
			
		}
		else if (strcmp(functionName, "REGISTER") == 0)
		{
			cout << "进入注册"<<endl;
			if (re_menu())
			{
				cout << "注册成功，请选择你的聊天类型：单聊(ONE)/群聊(GROUP)" << endl;


				while (true)
				{


					char optionChat[30];
					cin.getline(optionChat, 30);



					if (strcmp(optionChat, "ONE") == 0)
					{
						cout << "one";
						int choosenum = 2;
						int c = hstConnect->ChoosePattern(choosenum);
						if (c == 0)
						{
							std::cout << "选择成功！" << endl;
						}
						else {
							std::cout << "选择失败！" << endl;
						}

						while (1) {
							//接收服务器消息
							CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recive, NULL, NULL, NULL);

							onechat_ui();
						}

						break;
					}
					else if (strcmp(optionChat, "GROUP") == 0)
					{
						cout << "group";

						int choosenum = 1;
						int c = hstConnect->ChoosePattern(choosenum);
						if (c == 0)
						{
							std::cout << "选择成功！" << endl;
						}
						else {
							std::cout << "选择失败！" << endl;
						}

						//接收服务器消息
						CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recive, NULL, NULL, NULL);


						groupchat_ui();
						break;
					}
				}


			}
			break;
		}
		else if (strcmp(functionName, "EXIT") == 0)
		{
			cout << "EXIT";

		}
		else
		{
			break;
		}
	} while (1);




	system("PAUSE");

}