#include "datastructure.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <sstream>

void initchess1v1(char * chess) {

    int i = 0;
	for (i = 0; i < 256; i++) {
		chess[i] = 0;
	}

	char wall[26] = { 5,15,22,25,29,35,36,43,50,52,67,69,84,85,86,92,95,99,101,103,105,106,113,115,118,125 };
	for (i = 0; i < 26; i++) {
		chess[wall[i]] = -1;
		chess[(wall[i]+128)] = -1;		//正的為該值+128，負的為該值取絕對值
	}

	char init1v1[10] = {75,65,55,45,82,72,62,89,79,96};
    for (i = 0; i < 10; i++) {
		chess[init1v1[i]] = 1;
		chess[(init1v1[i]+128)] = 2;		//正的為該值+128，負的為該值取絕對值
	}

}

void initchess1v1v1(char * chess) {

    int i = 0;
	for (i = 0; i < 256; i++) {
		chess[i] = 0;
	}

	char wall[26] = { 5,15,22,25,29,35,36,43,50,52,67,69,84,85,86,92,95,99,101,103,105,106,113,115,118,125 };
	for (i = 0; i < 26; i++) {
		chess[wall[i]] = -1;
		chess[(wall[i]+128)] = -1;		//正的為該值+128，負的為該值取絕對值
	}

	char init1v1v1[30] = {-75,-65,-55,-45,-82,-72,-62,-89,-79,-96,-12,-2,8, \
	18,-19,-9,1,-26,-16,-33,78,88,98,108,71,81,91,64,74,57};
    for (i = 0; i < 10; i++) {
        chess[locatetransform(init1v1v1[i])] = 1;
	}
    for (i = 10; i < 20; i++) {
        chess[locatetransform(init1v1v1[i])] = 2;
	}
    for (i = 20; i < 30; i++) {
        chess[locatetransform(init1v1v1[i])] = 3;
	}

}

void initchessTEST1v1(char * chess) {

    int i = 0;
	for (i = 0; i < 256; i++) {
		chess[i] = 0;
	}

	char wall[26] = { 5,15,22,25,29,35,36,43,50,52,67,69,84,85,86,92,95,99,101,103,105,106,113,115,118,125 };
	for (i = 0; i < 26; i++) {
		chess[wall[i]] = -1;
		chess[(wall[i]+128)] = -1;		//正的為該值+128，負的為該值取絕對值
	}

	char init1v1v1[20] = {96,89,72,62,45,58,51,24,7,21, \
	-17,-14,-31,-41,-51,-58,-75,-55,-45,-89};
    for (i = 0; i < 10; i++) {
        chess[locatetransform(init1v1v1[i])] = 2;
	}
    for (i = 10; i < 20; i++) {
        chess[locatetransform(init1v1v1[i])] = 1;
	}

}

void initchessTEST1v1v1(char * chess) {

    int i = 0;
	for (i = 0; i < 256; i++) {
		chess[i] = 0;
	}

	char wall[26] = { 5,15,22,25,29,35,36,43,50,52,67,69,84,85,86,92,95,99,101,103,105,106,113,115,118,125 };
	for (i = 0; i < 26; i++) {
		chess[wall[i]] = -1;
		chess[(wall[i]+128)] = -1;		//正的為該值+128，負的為該值取絕對值
	}

	char init1v1v1[30] = {-33,-16,-9,-6,11,4,28,38,14,7, \
	-75,-65,-72,-38,-41,-24,-14,-17,0,34   ,17,27,44,54,61,68,78,81,40,23};
    for (i = 0; i < 10; i++) {
        chess[locatetransform(init1v1v1[i])] = 2;
	}
    for (i = 10; i < 20; i++) {
        chess[locatetransform(init1v1v1[i])] = 1;
	}
	for (i = 20; i < 30; i++) {
        chess[locatetransform(init1v1v1[i])] = 3;
	}
}


void Locate_Data::init_1darray_locate(){

    for(int i=0;i<256;i++){
        x[i] = -1;
        y[i] = -1;
    }

    float tmpointx = 310;
    float tmpointy = 110;
    char tmpchar= 96;

    for(int i=1;i<=13;i++){
        for(int j=1;j<=i;j++){
            x[locatetransform(tmpchar)]=tmpointx;
            y[locatetransform(tmpchar)]=tmpointy;
            tmpchar = tmpchar + 10;
            tmpointx = tmpointx + 40;
        }
        tmpchar = tmpchar -10 -7 - i*10;
        tmpointx = tmpointx -40 - (i-1)*40 -20;
        tmpointy = tmpointy + 20*sqrt(3);
    }

    tmpointx = 310;
    tmpointy = 110+16*20*sqrt(3);
    tmpchar = -96;
    for(int i=1;i<=13;i++){
        for(int j=1;j<=i;j++){
            x[locatetransform(tmpchar)]=tmpointx;
            y[locatetransform(tmpchar)]=tmpointy;
            tmpchar = tmpchar + 10;
            tmpointx = tmpointx + 40;
        }
        tmpchar = tmpchar -10 + 17 - i*10;
        tmpointx = tmpointx -40 - (i-1)*40 -20;
        tmpointy = tmpointy - 20*sqrt(3);
    }

}

void Transform_1darray_2darray_Convert::transform_1darray_to_2darray(int input,int *x,int *y){

	//printf("%d\n",input);

	for(int i=0;i<17;i++){
		for(int j=0;j<17;j++){
			if(input == array_diamond[i][j]){
				*x = i;
				*y = j;
				//printf("%d -> %d,%d\n",array_diamond[i][j],*x,*y);
				//system("PAUSE");
				break;
			}
		}
	}
};


int Transform_1darray_2darray_Convert::transform_2darray_to_1darray(int inputx, int inputy){

	return array_diamond[inputx][inputy];
};

int locatetransform(char locate) {

    int after = 0;
	if (locate > 0)
		after = locate + 128;
	if (locate <= 0)
		after = abs(locate);
	return after;
}

char locatetransformrevers(int locate){

    int before = 0;
	if (locate > 128)
		before = locate - 128;
	if (locate <= 128)
		before = 0 - locate;
	return before;
}
