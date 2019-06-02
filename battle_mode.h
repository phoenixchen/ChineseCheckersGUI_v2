
#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#include "text/CvxText.h"

#include "algorithm/algorithm.h"

class BattleMode{

public:
	BattleMode();
	char str_quit[5];
	char str_red[5];
	char str_green[5];
	char str_blue[5];
	char str_compare[9];

void WinINITServer(SOCKET *sServer,int max_clients,SOCKET client_socket[]);
SOCKET WinConnectClient(SOCKET *sServer,int max_clients,SOCKET client_socket[],int *socket_order_with_array);
bool printUI(char *chess,cv::Mat* frame,int PlayWithHuman,int playercount,CvxText *text);
};
