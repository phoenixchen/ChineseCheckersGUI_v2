#pragma once

class Locate_Data {
public:
    float x[256];
    float y[256];

    void init_1darray_locate();
};

class Transform_1darray_2darray_Convert {
public:
    int array_star[17][17] = {
           -1, -1, -1, -1, 96, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
           -1, -1, -1, -1, 79, 89, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
           -1, -1, -1, -1, 62, 72, 82, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
           -1, -1, -1, -1, 45, 55, 65, 75, -1, -1, -1, -1, -1, -1, -1, -1, -1,
           12,  2,  8, 18, 28, 38, 48, 58, 68, 78, 88, 98,108, -1, -1, -1, -1,
           -1,-19, -9,  1, 11, 21, 31, 41, 51, 61, 71, 81, 91, -1, -1, -1, -1,
           -1, -1,-26,-16, -6,  4, 14, 24, 34, 44, 54, 64, 74, -1, -1, -1, -1,
           -1, -1, -1,-33,-23,-13, -3,  7, 17, 27, 37, 47, 57, -1, -1, -1, -1,
           -1, -1, -1, -1,-40,-30,-20,-10,  0, 10, 20, 30, 40, -1, -1, -1, -1,
           -1, -1, -1, -1,-57,-47,-37,-27,-17, -7,  3, 13, 23, 33, -1, -1, -1,
           -1, -1, -1, -1,-74,-64,-54,-44,-34,-24,-14, -4,  6, 16, 26, -1, -1,
           -1, -1, -1, -1,-91,-81,-71,-61,-51,-41,-31,-21,-11, -1,  9, 19, -1,
           -1, -1, -1, -1,-108,-98,-88,-78,-68,-58,-48,-38,-28,-18, -8, 2, 12,
           -1, -1, -1, -1, -1, -1, -1, -1, -1,-75,-65,-55,-45, -1, -1, -1, -1,
           -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-82,-72,-62, -1, -1, -1, -1,
           -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-89,-79, -1, -1, -1, -1,
           -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-96, -1, -1, -1, -1,
    };
    int array_diamond[17][17] = {
           -5, -5, -5, -5, 96, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5,
           -5, -5, -5, -5, 79, 89, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5,
           -5, -5, -5, -5, 62, 72, 82, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5,
           -5, -5, -5, -5, 45, 55, 65, 75, -5, -5, -5, -5, -5, -5, -5, -5, -5,
           -5, -5, -5, -5, 28, 38, 48, 58, 68, -5, -5, -5, -5, -5, -5, -5, -5,
           -5, -5, -5, -5, 11, 21, 31, 41, 51, 61, -5, -5, -5, -5, -5, -5, -5,
           -5, -5, -5, -5, -6,  4, 14, 24, 34, 44, 54, -5, -5, -5, -5, -5, -5,
           -5, -5, -5, -5,-23,-13, -3,  7, 17, 27, 37, 47, -5, -5, -5, -5, -5,
           -5, -5, -5, -5,-40,-30,-20,-10,  0, 10, 20, 30, 40, -5, -5, -5, -5,
           -5, -5, -5, -5, -5,-47,-37,-27,-17, -7,  3, 13, 23, -5, -5, -5, -5,
           -5, -5, -5, -5, -5, -5,-54,-44,-34,-24,-14, -4,  6, -5, -5, -5, -5,
           -5, -5, -5, -5, -5, -5, -5,-61,-51,-41,-31,-21,-11, -5, -5, -5, -5,
           -5, -5, -5, -5, -5, -5, -5, -5,-68,-58,-48,-38,-28, -5, -5, -5, -5,
           -5, -5, -5, -5, -5, -5, -5, -5, -5,-75,-65,-55,-45, -5, -5, -5, -5,
           -5, -5, -5, -5, -5, -5, -5, -5, -5, -5,-82,-72,-62, -5, -5, -5, -5,
           -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5,-89,-79, -5, -5, -5, -5,
           -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5,-96, -5, -5, -5, -5,
    };

    void transform_1darray_to_2darray(int input,int *x,int *y);
    int transform_2darray_to_1darray(int inputx, int inputy);
};

void initchess1v1(char * chess) ;
void initchess1v1v1(char * chess) ;
void initchessTEST1v1(char * chess);
void initchessTEST1v1v1(char * chess);
int locatetransform(char locate);
char locatetransformrevers(int locate);