//#include <windows.h>
//#include<iostream>
//#include <regex>
//
//#include"InitConnect.h"
//#include "Sha256.h"
//#pragma comment(lib, "ws2_32.lib")
//
//using namespace std;
//
//
//int prepare();
//
//HstConnect* hstConnect = new HstConnect();
//
//void recive() {
//	string message;
//	while (1) {
//		message = hstConnect->ReceiveMessage();
//		//std::cout << message << endl;
//		if (message[0] != 0) {
//			std::cout << message[0] << endl;
//		}
//	}
//}
//
//int main() {
//	if (prepare() < 0) {
//		return -1;
//	}
//
//	//登录或注册
//	char op;
//	std::cout << ">>>>> 请登录或注册(登录输1,注册输2):";
//	std::cin >> op;
//
//	if (op == '1') {
//		while (1) {
//			SetConsoleTitle("登录");
//			char name[1024];
//			char password[1024];
//			std::cout << ">>> 登录" << endl;
//			std::cout << ">>>>> 用户名:";
//			std::cin >> name;
//			std::cout << ">>>>> 密码:";
//			std::cin >> password;
//			
//			int l = hstConnect->Login(name, password);
//			if (l == 0) {
//				std::cout << "登录成功！" << endl;
//				break;
//			}
//			else {
//				std::cout << "登陆失败，请检查账号密码！" << endl;
//			}
//		}
//	}
//	else if (op == '2') {
//		while (1) {
//			SetConsoleTitle("注册");
//			char name[1024];
//			char password[1024];
//			std::cout << ">>>注册" << endl;
//			std::cout << ">>>>>用户名:";
//			std::cin >> name;
//			std::cout << ">>>>>密码(仅支持9~16 位数字和字母的组合):";
//			std::cin >> password;
//
//			
//			regex repPattern("[0-9a-zA-Z]{9,16}", regex_constants::extended);
//
//			// 进行匹配
//			bool bValid = regex_match(password, repPattern);
//
//			if (bValid)
//			{
//				// 匹配成功
//
//				char sha256[256];
//				Sha256* sha_hst = nullptr;
//				sha_hst->StrSHA256(password, sizeof(password) - 1, sha256);  // sizeof()包含了末尾的终止符'\0'故 -1
//
//				int r = hstConnect->Register(name, sha256);
//
//				if (r == 0) {
//					std::cout << "注册成功！" << endl;
//					break;
//					
//				}
//				else {
//					std::cout << "注册失败！用户名已被占用" << endl;
//					
//				}
//			}
//			else
//			{
//				std::cout << "注册失败！密码输入格式有误！" << endl;
//				std::cout << "再次进入注册页面！" << endl;
//			}
//		}
//
//	}
//
//	std::cout << "请选择输入1开始你的聊天功能选择。" << endl;
//	int choose;
//	std::cin >> choose;
//	getchar();
//
//	if (choose == 1)
//	{
//		// 操作选择：
//		// 聊天：单聊or群聊
//		// 好友：添加or删除
//		std::cout << "请选择群聊或单聊或者添加好友（群聊1，单聊2，加好友3）" << endl;
//		int choosenum;
//		std::cin >> choosenum;
//		getchar();
//
//		int c = hstConnect->ChoosePattern(choosenum);
//		if (c == 0)
//		{
//			std::cout << "选择成功！" << endl;
//		}
//		else {
//			std::cout << "选择失败！" << endl;
//		}
//
//		//接收服务器消息
//		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recive, NULL, NULL, NULL);
//
//		if (choosenum == 1) {
//			SetConsoleTitle("群聊界面");
//			std::cout << "进入群聊界面" << endl;
//			while (1) {
//				char message[1024];
//				gets_s(message);
//				int s = hstConnect->SendMessage(message);
//				if (s == 0) {
//					std::cout << "发送成功！" << endl;
//				}
//				else {
//					std::cout << "发送失败！" << endl;
//				}
//			}
//		}
//
//		else if (choosenum == 2) {
//			SetConsoleTitle("单聊界面");
//			std::cout << "进入单聊界面" << endl;
//			string friendList;
//			friendList = hstConnect->ReceiveFriendList();
//			std::cout << "您的好友有：";
//			if (friendList[0])
//			{
//				std::cout << friendList << endl;
//			}
//
//			std::cout << "请选择聊天对象：";
//			int friendNum;
//			cin >> friendNum;
//			getchar();
//			int c = hstConnect->ChooseFriend(friendNum);
//			if (c == 0) {
//				std::cout << "选择成功！" << endl;
//			}
//			else {
//				std::cout << "选择失败！" << endl;
//			}
//
//
//			//发送消息
//			while (1) {
//				char message[1024];
//				gets_s(message);
//				int s = hstConnect->SendMessage(message);
//				if (s == 0)
//				{
//					std::cout << "发送成功！" << endl;
//				}
//				else
//				{
//					std::cout << "发送失败！" << endl;
//				}
//			}
//}
//		else if (choosenum == 3) {
//			cout << "tst";
//			SetConsoleTitle("添加好友");
//
//			std::cout << "\n输入你要添加的用户名";
//
//
//			char addName[1024];
//			gets_s(addName);
//
//			int c = hstConnect->AddFriend(addName);
//
//			system("pause");
//
//			if (c == 0) {
//				std::cout << "操作选择成功！" << endl;
//			}
//			else {
//				std::cout << "操作选择失败！" << endl;
//			}
//			system("pause");
//		}
//	return 0;
//}
//
//
//}
//
//
