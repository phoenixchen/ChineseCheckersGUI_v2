#include <ctime>
#include <cstring>
#include <iostream>

void getTime(char time_text[]){

    char strTime1[]="現在時間: ";
    char strTime2[]=":";
    char strTime3[]="0";

    time_t curr;
    tm local;
    std::string str_temp;
    char char_temp[5];

    curr = time(0);
    local=*(localtime(&curr));

    strcpy(time_text,strTime1);
    str_temp = std::to_string(local.tm_hour);
    if(local.tm_hour<10){
        strcat(time_text,strTime3);
    }
    strncpy(char_temp,str_temp.c_str(),str_temp.length()+1);
    strcat(time_text,char_temp);
    strcat(time_text,strTime2);
    str_temp = std::to_string(local.tm_min);
    if(local.tm_min<10){
        strcat(time_text,strTime3);
    }
    strncpy(char_temp,str_temp.c_str(),str_temp.length()+1);
    strcat(time_text,char_temp);
    strcat(time_text,strTime2);
    str_temp = std::to_string(local.tm_sec);
    if(local.tm_sec<10){
        strcat(time_text,strTime3);
    }
    strncpy(char_temp,str_temp.c_str(),str_temp.length()+1);
    strcat(time_text,char_temp);
}