
#include "rendering/cvui.h"

#include "predict/predict.h"
#include "rendering/foreground.h"
#include "rendering/background.h"
#include "battle_mode.h"
#include "info/information.h"
#include "replay_format/replay.h"

BattleMode::BattleMode(){
    strcpy(str_quit,"離開");
    strcpy(str_red,"紅方");
    strcpy(str_green,"綠方");
    strcpy(str_compare,"優勢預估");
    strcpy(str_blue,"藍方");
}

bool BattleMode::printUI(char *chess,cv::Mat* frame,int PlayWithHuman,int playercount,CvxText *text){

    cv::Mat preprocess_frame;
    preprocess(frame,true);
    preprocess_frame = (*frame).clone();
    char * str;

    cv::Point mouse;

    Locate_Data coordinate;
    coordinate.init_1darray_locate();

    Transform_1darray_2darray_Convert check;

    char AIfrom = -127;
    char GUIfrom = -127;
    struct multijump * current = NULL;
    struct multijump * prev = NULL;
    struct multijump * head = NULL;
    bool IsMouseClick = false;

    int LinuxRenderTimes = 1;

    bool IsFirstView = true;

    bool InvalidTo = false;
    bool InvalidFrom = false;
    int mouseclickchess = -1;
    bool jumpfinish = false;
    bool movefinish = false;
    bool JumpNeedUpdate = false;

    int turncount = 1;

    if(playercount==2)
        initchess1v1(chess);
    if(playercount==3)
        initchess1v1v1(chess);

    int socket_order_with_array = 0;
    int max_clients = 6;
    SOCKET sServer,sClient,client_socket[max_clients];

    WinINITServer(&sServer,max_clients,client_socket);

    int order[max_clients];
    for(int i=0;i<max_clients;i++)
        order[i] = 0;

    if(PlayWithHuman !=0)
        order[(PlayWithHuman-1)] = -1;

    sClient = NULL;
    while(sClient==NULL){
        sClient = WinConnectClient(&sServer,max_clients,client_socket,&socket_order_with_array);
    };
    TurnOrderSort(max_clients,socket_order_with_array,order);

    if(playercount == 2)
        if(PlayWithHuman ==0){
            sClient = NULL;
            while(sClient==NULL){
                sClient = WinConnectClient(&sServer,max_clients,client_socket,&socket_order_with_array);
            };
            TurnOrderSort(max_clients,socket_order_with_array,order);
        }

    if(playercount == 3){
        sClient = NULL;
        while(sClient==NULL){
            sClient = WinConnectClient(&sServer,max_clients,client_socket,&socket_order_with_array);
        };
        TurnOrderSort(max_clients,socket_order_with_array,order);
        if(PlayWithHuman ==0){
            sClient = NULL;
            while(sClient==NULL){
                sClient = WinConnectClient(&sServer,max_clients,client_socket,&socket_order_with_array);
            };
            TurnOrderSort(max_clients,socket_order_with_array,order);
        }
    }

    FirstSendStandby(max_clients,client_socket,order,PlayWithHuman,playercount);

int turn =0;
int undoturn=0;
Info information;
struct list_member *lm;
int list_iter_number;
double predict_output;

	while (true){

        (*frame) = preprocess_frame.clone();
        DrawLineCircle(frame,chess,coordinate,0);

        if (cvui::mouse(cvui::CLICK)) {
            IsFirstView = false;
			mouse.x = cvui::mouse().x;
			mouse.y = cvui::mouse().y;
			IsMouseClick = true;
		}

        if(IsMouseClick)
            MouseClickAction(mouse,&IsMouseClick,&InvalidTo,&InvalidFrom,&jumpfinish,&mouseclickchess,coordinate,chess, \
                             &head,&prev,&current,&GUIfrom,&movefinish,&JumpNeedUpdate);

        //DrawControlComponent(frame,&thinkingtime,&MCTScheck,&RuleBasecheck,&NeuralNetworkcheck,&turncount,&undoturn);

        if(InvalidFrom == true)
            cvui::printf(*frame, 175, 60, 0.4, 0xff0000, "Invalid StartingPoint");
        if(InvalidTo == true)
            cvui::printf(*frame, 175, 60, 0.4, 0xff0000, "Invalid destination");

		if (cvui::button(*frame, 600 , 10 ,60, 50, "")) {
		    break;
		}
        str = str_quit;
        DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),605,45,255,255,255);
        str = str_red;
        DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),510,50,0,0,255);
        str = str_green;
        DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),45,50,0,195,0);
        str = str_compare;
        DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),250,35,255,255,255);


        GUIJumpUpdate(&movefinish,&JumpNeedUpdate,chess,&prev,&current,&GUIfrom);

        list_iter_number = 0;
        for (information.list_iter=information.info_list.begin(); information.list_iter!=information.info_list.end(); ++information.list_iter){
            lm = &(*(information.list_iter));
            if((*lm).str_info[1]=='1')
                cvui::printf(*frame, information.x[list_iter_number], information.y[list_iter_number], 0.6, 0xff0000, (*lm).str_info);
            if((*lm).str_info[1]=='2')
                cvui::printf(*frame, information.x[list_iter_number], information.y[list_iter_number], 0.6, 0x008800, (*lm).str_info);
            if((*lm).str_info[1]=='3')
                cvui::printf(*frame, information.x[list_iter_number], information.y[list_iter_number], 0.6, 0x0000ff, (*lm).str_info);
            list_iter_number++;
        }

        predict_output = (double)predict(chess,check);

        if(predict_output != -1)
            cvui::trackbar(*frame, 100, 30, 400, &predict_output, 0., 100.);
        //cvui::printf(*frame, 175, 60, 0.4, 0xff0000, "This board's win rate: %2d%%",output_value);

        cvui::update();
		cvui::imshow("中國跳棋對戰程式", *frame);
        if (cv::waitKey(20) == 27)
			return true;

            if(order[turn]==-1){
                if(GUIfrom != -127 && head != NULL)
                    if( movefinish == true | jumpfinish == true ){
                        if(jumpfinish && GUIfrom == prev->node){//起始點與結束點相同，不合法走步
                            jumpfinish = false;
                            InvalidTo = true;
                            continue;
                        }

                        for(int j=0;j<max_clients;j++){
                            if(client_socket[j]!=0)
                                GUISendString(&GUIfrom,&current,&head,client_socket[j],&information,false);
                        }
                        turncount++;
                        turn++;
                    }
            }
            if(order[turn]==0){
                //do nothing
                turn++;
            }
            if(order[turn]!=-1 && order[turn]!=0 && turn!=6){

                if(PlayWithHuman!=0){
                    if(!AISendString(&AIfrom,&current,&head,&prev,chess,max_clients,client_socket,(order[turn]-1)+2,&information))
                        return true;
                }
                else{
                    if(!AISendString(&AIfrom,&current,&head,&prev,chess,max_clients,client_socket,(order[turn]-1)+1,&information))
                        return true;
                }

                for(int j=0;j<max_clients;j++){
                    if(client_socket[j]!=0 && j!=(order[turn]-1))
                        GUISendString(&AIfrom,&current,&head,client_socket[j],&information,true);
                }
                AIAfterSendStringINIT(&AIfrom,&current,&head,&prev);
                turncount++;
                turn++;
            }

            if(turn==6)
                turn = 0;


        if( jumpfinish || movefinish ){

            current = head;
            while(current!=NULL){
                prev = current;
                current = current->next;
                free(prev);
            }
            GUIfrom = -127;
            current = NULL;
            head = NULL;
            prev = NULL;
            jumpfinish = false;
            movefinish = false;
        }


	}

    closesocket(sServer);
    WSACleanup();
}


void BattleMode::WinINITServer(SOCKET *sServer,int max_clients,SOCKET client_socket[]){

    WSADATA wsa;
    struct sockaddr_in server;

    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0){
        printf("Failed. Error Code : %d",WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    if((*sServer = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET){
        printf("Could not create socket : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 894 );

    if( bind(*sServer ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    listen(*sServer , 3);

    for(int i = 0 ; i < max_clients;i++)
        client_socket[i] = 0;

}


SOCKET BattleMode::WinConnectClient(SOCKET *sServer,int max_clients,SOCKET client_socket[],int *socket_order_with_array){

    printf("wait for connection...\n");

    int tempint;
    fd_set readfds;
    SOCKET sClient = NULL;
    struct sockaddr_in remoteAddr;
    int nAddrlen = sizeof(remoteAddr);

    FD_ZERO(&readfds);
    FD_SET(*sServer, &readfds);

    for (int i =0;i<max_clients;i++){
        sClient = client_socket[i];
        if(sClient > 0)
            FD_SET(sClient,&readfds);
    }

    tempint = select(0,&readfds,NULL,NULL,NULL);

    if (tempint == SOCKET_ERROR){
        printf("select call failed with error code : %d",WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    if (FD_ISSET(*sServer,&readfds)){
        if ((sClient = accept(*sServer , (struct sockaddr *)&remoteAddr, (int *)&nAddrlen))<0){
            perror("accept");
            exit(EXIT_FAILURE);
        }
        printf("received a connection：socket_fd:%d ,ip %s:%d\n",sClient,inet_ntoa(remoteAddr.sin_addr),ntohs(remoteAddr.sin_port));

        for (*socket_order_with_array = 0; *socket_order_with_array < max_clients; (*socket_order_with_array)++){
            if (client_socket[*socket_order_with_array] == 0){
                client_socket[*socket_order_with_array] = sClient;
                break;
            }
        }
    }

    return sClient;
}
