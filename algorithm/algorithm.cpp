
#include "algorithm.h"

void MouseClickAction(cv::Point mouse,bool *IsMouseClick,bool *InvalidTo,bool *InvalidFrom,bool *jumpfinish, \
                      int *mouseclickchess,Locate_Data coordinate,char *chess,struct multijump ** head, \
                      struct multijump ** prev,struct multijump ** current,char *GUIfrom,bool *movefinish,bool *JumpNeedUpdate){

    char temp;

    *mouseclickchess = -1;

    //尋找按到哪一顆棋子
    for(int i=0;i<256;i++){
        if(abs(coordinate.x[i]-mouse.x)<10 && abs(coordinate.y[i]-mouse.y)<10 )
           if(sqrt(pow((coordinate.x[i]-mouse.x),2)+pow((coordinate.y[i]-mouse.y),2))<=10){

                //按到這一顆
                *mouseclickchess = i;

                //按到以後確認prev是否有接東西，按到的東西一律存入prev，只有第一次呼叫這個函式時沒有prev
                //prev有接東西表示之前已經有current並處理完，每次current處理完會把current節點變成prev，current指標變成可用
                if(*prev != NULL)
                    if((*prev)->node == locatetransformrevers(i)){
                        *IsMouseClick = false;
                        *InvalidTo = false;
                        *jumpfinish = true;
                        break;
                    }

                //按到以後如果GUIfrom沒有人，表示這個是from
                if(*GUIfrom == -127){
                    if(chess[i]==1){    /*如果是自己的棋子*/
                        *GUIfrom = locatetransformrevers(i);
                        *IsMouseClick = false;
                        *InvalidFrom = false;
                    }
                    else{
                        *InvalidFrom = true;
                    }
                }
                else{//如果GUIfrom有人了，表示這個是to，所以要檢查from跟to之間是平移還跳躍，合不合法
                    if(*current == NULL){
                        //檢查是否平移
                        if(abs(locatetransformrevers(i) - *GUIfrom)==17 | abs(locatetransformrevers(i) - *GUIfrom)==10 \
                           | abs(locatetransformrevers(i) - *GUIfrom)==7){
                            if(chess[i]==0){//如果合法，創建current節點後存進去
                                *current = (struct multijump *)malloc(sizeof(struct multijump));
                                if(*head == NULL)
                                    *head = *current;
                                (*current)->node = locatetransformrevers(i);
                                (*current)->next = NULL;
                                *IsMouseClick = false;
                                *InvalidTo = false;
                                *movefinish = true;
                            }
                            else{
                                *InvalidTo = true;
                            }
                        }
                        else{
                            *InvalidTo = true;
                        }
                        //檢查是否跳躍
                        if(*InvalidTo){

                            if(*prev==NULL)
                                temp = *GUIfrom;
                            else
                                temp = (*prev)->node;

                            //若跳躍的間格正確
                            if(abs(locatetransformrevers(i) - temp)==34 | abs(locatetransformrevers(i) - temp)==20 \
                               | abs(locatetransformrevers(i) - temp)==14){
                                //若有旁邊有人可以當跳板
                                if((chess[locatetransform(temp + (locatetransformrevers(i) - temp)/2)] == 1) | \
                                   (chess[locatetransform(temp + (locatetransformrevers(i) - temp)/2)] == 2) |
                                   (chess[locatetransform(temp + (locatetransformrevers(i) - temp)/2)] == 3)){
                                        //若跳躍的目的地沒有其他人
                                        if(chess[i] == 0){
                                            *current = (struct multijump *)malloc(sizeof(struct multijump));

                                            if(*head == NULL)
                                                *head = *current;

                                            if(*prev!=NULL)
                                                (*prev)->next = *current;

                                            (*current)->node = locatetransformrevers(i);
                                            (*current)->next = NULL;
                                            *IsMouseClick = false;
                                            *InvalidTo = false;
                                            *JumpNeedUpdate = true;
                                        }
                                        else{
                                            *InvalidTo = true;
                                        }
                                }
                                else{
                                    *InvalidTo = true;
                                }
                            }
                            else{
                                *InvalidTo = true;
                            }
                        }




                    }
                }
           }
    }

}


void GUIJumpUpdate(bool *movefinish,bool *JumpNeedUpdate,char *chess,struct multijump ** prev, \
                   struct multijump ** current,char *GUIfrom){

    char temp;

    if(*movefinish){
        temp = chess[locatetransform(*GUIfrom)];
        chess[locatetransform(*GUIfrom)] = 0;
        chess[locatetransform((*current)->node)] = temp;
        *prev = *current;
        *current = (*current)->next;
    }
    if(*JumpNeedUpdate){       //每次jump都更新，包含jumpfinish時

        if(*prev == NULL){
            temp = chess[locatetransform(*GUIfrom)];
            chess[locatetransform(*GUIfrom)] = 0;
            chess[locatetransform((*current)->node)] = temp;
            *prev = *current;
            *current = (*current)->next;
        }
        else{
            temp = chess[locatetransform((*prev)->node)];
            chess[locatetransform((*prev)->node)] = 0;
            chess[locatetransform((*current)->node)] = temp;
            *prev = *current;
            *current = (*current)->next;
        }
        *JumpNeedUpdate = false;
    }
}


void GUISendString(char * GUIfrom,struct multijump ** current,struct multijump ** head,SOCKET sClient,Info *information,bool is_resend){

    //發送資料
    char * sendData;
    int i = *GUIfrom;
    std::stringstream stringfrom;
    std::stringstream stringto;
    std::string stringfinal;
    stringfrom << i;
    stringfinal = stringfrom.str() + ",";

    *current = *head;

    while(*current!=NULL){
        i = (*current)->node;
        stringto << i;
        stringfinal = stringfinal + stringto.str();
        stringto.str("");
        if((*current)->next!=NULL)
            stringfinal = stringfinal + ",";
        *current = (*current)->next;
    }

    sendData = new char[stringfinal.length() + 1];
    strcpy(sendData, stringfinal.c_str());

    if(!is_resend){
        char str_head[]="[1]";
        struct list_member *lm = (struct list_member *)malloc(sizeof(struct list_member));
        strcpy((*lm).str_info,str_head);
        (*lm).str_info[3] = '\0';
        (*information).string_info_fit(lm->str_info,sendData);
        if((*information).info_list.size()==40)
            (*information).info_list.pop_front();
        (*information).info_list.push_back(*lm);
    }

    send(sClient,sendData,strlen(sendData),0);
}


bool AISendString(char * AIfrom,struct multijump ** current,struct multijump ** head, \
                  struct multijump ** prev,char *chess,int max_clients,SOCKET client_socket[],int chesscolor,Info *information){

    bool IsDigital = true;
    int CheckAscii;

    char *token = ",";
    char *stringtok;
    char buf[255];
    bool AIInvalidFlag = false;

    //接收資料

    int len = recv(AutoSelect(max_clients,client_socket),buf,255,0);
    buf[len] = '\0';

    char str_head[4];
    if(chesscolor==1)
        strcpy(str_head,"[1]");
    if(chesscolor==2)
        strcpy(str_head,"[2]");
    if(chesscolor==3)
        strcpy(str_head,"[3]");
    struct list_member *lm = (struct list_member *)malloc(sizeof(struct list_member));
    strcpy((*lm).str_info,str_head);
    (*lm).str_info[3] = '\0';
    (*information).string_info_fit(lm->str_info,buf);
    if((*information).info_list.size()==40)
        (*information).info_list.pop_front();
    (*information).info_list.push_back(*lm);

    if(len > 0)
    {
        for(int i=0;buf[i]!='\0';i++){

            CheckAscii = buf[i];

            if( (CheckAscii < 48) || (CheckAscii > 57) )
              IsDigital = false;

            if(CheckAscii == '-' || CheckAscii == ',')
                IsDigital = true;

            if(!IsDigital)
                return false;
        }

        if(!IsDigital){
            printf("輸入錯誤，程式結束\n");
            return false;
        }

        stringtok = strtok(buf,token);

        *head = NULL;
        *prev = NULL;
        *current = NULL;
        char temp;

        while(stringtok!= NULL){

            if(*AIfrom== -127){
                *AIfrom = (char)atoi(stringtok);
                if(chess[locatetransform(*AIfrom)]!=chesscolor){
                    printf("起始點並非可操作的棋子，程式結束\n");
                    AIInvalidFlag = true;
                    return false;
                }
            }
            else{

                *current = (struct multijump *)malloc(sizeof(struct multijump));

                if( *head==NULL ){
                    *head = *current;
                }

                if(*prev!=NULL)
                    (*prev)->next = *current;

                (*current)->node = (char)atoi(stringtok);
                (*current)->next = NULL;
                *prev = *current;
                *current = (*current)->next;
            }

            stringtok = strtok(NULL, token);
        }

        if(AIInvalidFlag == true)
            return false;

        if( (*prev)->node == *AIfrom ){
            printf("走步頭尾相同，程式結束\n");
            return false;
        }

        *current = *head;
        int length = 0;

        while( *current!=NULL ){
            length++;
            *current = (*current)->next;
        }

        *current = *head;

        if(length==1 && (abs(*AIfrom - (*current)->node)<14 || abs(*AIfrom - (*current)->node)==17)){
            *current = *head;

            if(abs(*AIfrom - (*current)->node)==17 | abs(*AIfrom - (*current)->node)==10 \
                       | abs(*AIfrom - (*current)->node)==7){
                        if(chess[locatetransform((*current)->node)]==0){
                            temp = chess[locatetransform(*AIfrom)];
                            chess[locatetransform(*AIfrom)] = 0;
                            chess[locatetransform((*current)->node)] = temp;
                        }
                        else{
                            printf("不合法走步(目的地已有其他棋子)，程式結束\n");
                            return false;
                        }
            }
            else{
                printf("不合法走步(跳躍的間格不正確)，程式結束\n");
                return false;
            }

        }
        else{
            *current = *head;

            if(*current!=NULL){
                if(abs(*AIfrom - (*current)->node)==34 | abs(*AIfrom - (*current)->node)==20 \
                           | abs(*AIfrom - (*current)->node)==14){
                    if((chess[locatetransform(*AIfrom + ((*current)->node - *AIfrom)/2)] == 1) || \
                       (chess[locatetransform(*AIfrom + ((*current)->node - *AIfrom)/2)] == 2) ||
                       (chess[locatetransform(*AIfrom + ((*current)->node - *AIfrom)/2)] == 3)){
                            if(chess[locatetransform((*current)->node)]==0){
                                temp = chess[locatetransform(*AIfrom)];
                                chess[locatetransform(*AIfrom)] = 0;
                                chess[locatetransform((*current)->node)] = temp;
                            }
                            else{
                                printf("不合法走步(目的地已有其他棋子)，程式結束\n");
                                return false;
                            }
                    }
                    else{
                        printf("不合法走步(旁邊沒有棋子可以當跳板)，程式結束\n");
                        return false;
                    }
                }
                else{
                    printf("不合法走步(跳躍的間格不正確)，程式結束\n");
                    return false;
                }
            }

            *prev = *current;
            *current = (*current)->next;

            while( *current!=NULL ){

                //若跳躍的間格正確
                if(abs((*prev)->node - (*current)->node)==34 | abs((*prev)->node - (*current)->node)==20 \
                   | abs((*prev)->node - (*current)->node)==14){
                    //若有旁邊有人可以當跳板
                    if((chess[locatetransform((*prev)->node + ((*current)->node - (*prev)->node)/2)] == 1) || \
                       (chess[locatetransform((*prev)->node + ((*current)->node - (*prev)->node)/2)] == 2) ||
                       (chess[locatetransform((*prev)->node + ((*current)->node - (*prev)->node)/2)] == 3)){
                            //若跳躍的目的地沒有其他人
                            if(chess[locatetransform((*current)->node)] == 0){
                                temp = chess[locatetransform((*prev)->node)];
                                chess[locatetransform((*prev)->node)] = 0;
                                chess[locatetransform((*current)->node)] = temp;
                            }
                            else{
                                AIInvalidFlag = true;
                                printf("不合法走步(目的地已有其他棋子)，程式結束\n");
                                return false;
                            }
                    }
                    else{
                        AIInvalidFlag = true;
                        printf("不合法走步(旁邊沒有棋子可以當跳板)，程式結束\n");
                        return false;
                    }
                }
                else{
                    AIInvalidFlag = true;
                    printf("不合法走步(跳躍的間格不正確)，程式結束\n");
                    return false;
                }

                *prev = *current;
                *current = (*current)->next;

            }

            if(AIInvalidFlag == true)
                return false;

        }
    }

    return true;
}

SOCKET AutoSelect(int max_clients,SOCKET client_socket[]){

    fd_set readfds;
    FD_ZERO(&readfds);
    SOCKET tempsocket;
    int tempint;
    for (int i=0;i<max_clients;i++){
        tempsocket =client_socket[i];
        if(tempsocket> 0)
            FD_SET(tempsocket,&readfds);
    }

/*****************************************************/
    tempint = select(0,&readfds,NULL,NULL,NULL);
/*****************************************************/

    if ( tempint == SOCKET_ERROR ){
        printf("select call failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in remoteAddr;
    int nAddrlen = sizeof(remoteAddr);

    for(int i=0;i<max_clients;i++){

        tempsocket = client_socket[i];

        if (FD_ISSET(tempsocket,&readfds)){
            getpeername(tempsocket , (struct sockaddr*)&remoteAddr , (int*)&nAddrlen);
            return tempsocket;
        }
    }
    return NULL;
}

void TurnOrderSort(int max_clients,int socket_order_with_array,int order[]){

    for(int i=0;i<max_clients;i++){
        if(order[i]==0){
            order[i]=(socket_order_with_array+1);
            break;
        }
    }
}

void AIAfterSendStringINIT(char * AIfrom,struct multijump ** current,struct multijump ** head,struct multijump ** prev){

    *AIfrom = -127;

    *current = *head;
    while(*current!=NULL){
        *prev = *current;
        *current = (*current)->next;
        free(*prev);
    }
    *current = NULL;
    *head = NULL;
    *prev = NULL;
}

void FirstSendStandby(int max_clients,SOCKET client_socket[],int order[],int PlayWithHuman,int playercount){

    //發送資料
    char * sendData;
    std::stringstream stringcount;
    std::stringstream stringhuman;
    std::stringstream stringorder;
    std::string stringfinal;
    stringcount << playercount;
    stringhuman << PlayWithHuman;

    for(int i=0;i<max_clients;i++){
            if(order[i]!=0 && order[i]!=-1){
                stringorder << (i+1);
                stringfinal = stringcount.str() + "," +stringhuman.str() + "," +stringorder.str();
                stringorder.str("");
                sendData = new char[stringfinal.length() + 1];
                strcpy(sendData, stringfinal.c_str());
                send(client_socket[(order[i]-1)],sendData,strlen(sendData),0);
            }
    }
}
