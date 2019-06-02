
#include "algorithm.h"

void MouseClickAction(cv::Point mouse,bool *IsMouseClick,bool *InvalidTo,bool *InvalidFrom,bool *jumpfinish, \
                      int *mouseclickchess,Locate_Data coordinate,char *chess,struct multijump ** head, \
                      struct multijump ** prev,struct multijump ** current,char *GUIfrom,bool *movefinish,bool *JumpNeedUpdate){

    char temp;

    *mouseclickchess = -1;

    //�M�������@���Ѥl
    for(int i=0;i<256;i++){
        if(abs(coordinate.x[i]-mouse.x)<10 && abs(coordinate.y[i]-mouse.y)<10 )
           if(sqrt(pow((coordinate.x[i]-mouse.x),2)+pow((coordinate.y[i]-mouse.y),2))<=10){

                //����o�@��
                *mouseclickchess = i;

                //����H��T�{prev�O�_�����F��A���쪺�F��@�ߦs�Jprev�A�u���Ĥ@���I�s�o�Ө禡�ɨS��prev
                //prev�����F���ܤ��e�w�g��current�óB�z���A�C��current�B�z���|��current�`�I�ܦ�prev�Acurrent�����ܦ��i��
                if(*prev != NULL)
                    if((*prev)->node == locatetransformrevers(i)){
                        *IsMouseClick = false;
                        *InvalidTo = false;
                        *jumpfinish = true;
                        break;
                    }

                //����H��p�GGUIfrom�S���H�A��ܳo�ӬOfrom
                if(*GUIfrom == -127){
                    if(chess[i]==1){    /*�p�G�O�ۤv���Ѥl*/
                        *GUIfrom = locatetransformrevers(i);
                        *IsMouseClick = false;
                        *InvalidFrom = false;
                    }
                    else{
                        *InvalidFrom = true;
                    }
                }
                else{//�p�GGUIfrom���H�F�A��ܳo�ӬOto�A�ҥH�n�ˬdfrom��to�����O�����ٸ��D�A�X���X�k
                    if(*current == NULL){
                        //�ˬd�O�_����
                        if(abs(locatetransformrevers(i) - *GUIfrom)==17 | abs(locatetransformrevers(i) - *GUIfrom)==10 \
                           | abs(locatetransformrevers(i) - *GUIfrom)==7){
                            if(chess[i]==0){//�p�G�X�k�A�Ы�current�`�I��s�i�h
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
                        //�ˬd�O�_���D
                        if(*InvalidTo){

                            if(*prev==NULL)
                                temp = *GUIfrom;
                            else
                                temp = (*prev)->node;

                            //�Y���D�����楿�T
                            if(abs(locatetransformrevers(i) - temp)==34 | abs(locatetransformrevers(i) - temp)==20 \
                               | abs(locatetransformrevers(i) - temp)==14){
                                //�Y�����䦳�H�i�H����O
                                if((chess[locatetransform(temp + (locatetransformrevers(i) - temp)/2)] == 1) | \
                                   (chess[locatetransform(temp + (locatetransformrevers(i) - temp)/2)] == 2) |
                                   (chess[locatetransform(temp + (locatetransformrevers(i) - temp)/2)] == 3)){
                                        //�Y���D���ت��a�S����L�H
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
    if(*JumpNeedUpdate){       //�C��jump����s�A�]�tjumpfinish��

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

    //�o�e���
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

    //�������

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
            printf("��J���~�A�{������\n");
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
                    printf("�_�l�I�ëD�i�ާ@���Ѥl�A�{������\n");
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
            printf("���B�Y���ۦP�A�{������\n");
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
                            printf("���X�k���B(�ت��a�w����L�Ѥl)�A�{������\n");
                            return false;
                        }
            }
            else{
                printf("���X�k���B(���D�����椣���T)�A�{������\n");
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
                                printf("���X�k���B(�ت��a�w����L�Ѥl)�A�{������\n");
                                return false;
                            }
                    }
                    else{
                        printf("���X�k���B(����S���Ѥl�i�H����O)�A�{������\n");
                        return false;
                    }
                }
                else{
                    printf("���X�k���B(���D�����椣���T)�A�{������\n");
                    return false;
                }
            }

            *prev = *current;
            *current = (*current)->next;

            while( *current!=NULL ){

                //�Y���D�����楿�T
                if(abs((*prev)->node - (*current)->node)==34 | abs((*prev)->node - (*current)->node)==20 \
                   | abs((*prev)->node - (*current)->node)==14){
                    //�Y�����䦳�H�i�H����O
                    if((chess[locatetransform((*prev)->node + ((*current)->node - (*prev)->node)/2)] == 1) || \
                       (chess[locatetransform((*prev)->node + ((*current)->node - (*prev)->node)/2)] == 2) ||
                       (chess[locatetransform((*prev)->node + ((*current)->node - (*prev)->node)/2)] == 3)){
                            //�Y���D���ت��a�S����L�H
                            if(chess[locatetransform((*current)->node)] == 0){
                                temp = chess[locatetransform((*prev)->node)];
                                chess[locatetransform((*prev)->node)] = 0;
                                chess[locatetransform((*current)->node)] = temp;
                            }
                            else{
                                AIInvalidFlag = true;
                                printf("���X�k���B(�ت��a�w����L�Ѥl)�A�{������\n");
                                return false;
                            }
                    }
                    else{
                        AIInvalidFlag = true;
                        printf("���X�k���B(����S���Ѥl�i�H����O)�A�{������\n");
                        return false;
                    }
                }
                else{
                    AIInvalidFlag = true;
                    printf("���X�k���B(���D�����椣���T)�A�{������\n");
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

    //�o�e���
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
