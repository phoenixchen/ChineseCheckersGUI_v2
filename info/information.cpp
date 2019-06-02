#include <string.h>

#include "information.h"

Info::Info(){

    int xtmp = 685;
    int ytmp = 85;

    for(int i=0;i<20;i++){
        x[i] = xtmp;
        y[i] = ytmp;
        ytmp = ytmp + 30;
    }

    xtmp = 685 + 275;
    ytmp = 85;
    for(int i=20;i<40;i++){
        x[i] = xtmp;
        y[i] = ytmp;
        ytmp = ytmp + 30;
    }
}

void Info::string_info_fit(char str_info[20],char buf[]){
    
    int length = strlen(buf);
    char temp[18];

    if(length<17)
        strcat(str_info,buf);
    else{
        strncpy(temp,buf,17);
        strcat(str_info,temp);
    }
}