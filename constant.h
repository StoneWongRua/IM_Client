#pragma once

#define RT_REQUEST_CHAT		0
#define RT_REGISTERED		1
#define RT_AGREE			2
#define RT_EXIT_CHAT		3
#define RT_SEND				4
#define RT_GET_LIST			5
#define RT_EXIT				6

#define RE_CHAT_REQUEST		7
#define RE_AGREE_RETURN		8
#define RE_EXIT_CHAT_RETURN	9
#define RE_RECEIVE			10
#define RE_SEND_LIST		11
#define RE_ERROR			12

#define BUFFER_SIZE 1024

union REQUEST
{
	union {
		struct { int flag; char userName[12]; }requestChat;
		struct { int flag; char userName[12]; char password[256]; }registered;
		struct { int flag; int isAgree; char userName[12]; }agree;
		struct { int flag; }exitChat;
		struct { int flag; char message[124]; }send;
		struct { int flag; }getList;
		struct { int flag; }exit;
	}data;

	char ruler[BUFFER_SIZE];
};

union RESPONSE
{
	union {
		struct { int flag; char userName[12]; }chatRequest;
		struct { int flag; int isAgree; }agreeReturn;
		struct { int flag; }exitChatReturn;
		struct { int flag; char message[124]; }receive;
		struct { int flag; char list[124]; }sendList;
		struct { int flag; char errorMsg[28]; }error;
	}data;

	char ruler[BUFFER_SIZE];
};