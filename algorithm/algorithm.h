#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <opencv2/opencv.hpp>

#include "../info/information.h"
#include "../datastructure/datastructure.h"

struct multijump{
    char node;
    struct multijump * next;
};

void MouseClickAction(cv::Point mouse,bool *IsMouseClick,bool *InvalidTo,bool *InvalidFrom,bool *jumpfinish, \
                      int *mouseclickchess,Locate_Data coordinate,char *chess,struct multijump ** head, \
                      struct multijump ** prev,struct multijump ** current,char *GUIfrom,bool *movefinish,bool *JumpNeedUpdate);

void GUIJumpUpdate(bool *movefinish,bool *JumpNeedUpdate,char *chess,struct multijump ** prev, \
                   struct multijump ** current,char *GUIfrom);

void GUISendString(char * GUIfrom,struct multijump ** current,struct multijump ** head,SOCKET sClient,Info *imformation,bool is_resend);

bool AISendString(char * AIfrom,struct multijump ** current,struct multijump ** head, \
                  struct multijump ** prev,char *chess,int max_clients,SOCKET client_socket[],int chesscolor,Info *information);

SOCKET AutoSelect(int max_clients,SOCKET client_socket[]);

void TurnOrderSort(int max_clients,int socket_order_with_array,int order[]);

void AIAfterSendStringINIT(char * AIfrom,struct multijump ** current,struct multijump ** head,struct multijump ** prev);

void FirstSendStandby(int max_clients,SOCKET client_socket[],int order[],int PlayWithHuman,int playercount);