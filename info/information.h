#pragma once

#include <list>

struct list_member{
    char str_info[20];
};

class Info{
public:
	Info();
	
    int x[40];
    int y[40];
    std::list<struct list_member> info_list;
    std::list<struct list_member> ::iterator list_iter;

    void string_info_fit(char str_info[20],char buf[]);
};
