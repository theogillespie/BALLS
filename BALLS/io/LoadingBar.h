#pragma once


#include <cstdio>

#ifndef BARSTRING
    #define BARSTRING "##################################################"
#endif
#ifndef BARWIDTH
    #define BARWIDTH 50
#endif

void loadingBar(double percentage) {
    unsigned int val = (int) (percentage * 100);
    unsigned int left = (int) (percentage * BARWIDTH);
    unsigned int right = BARWIDTH - left;
    printf("\r%3d%% [%.*s%*s] \n", val, left, BARSTRING, right, "");
    fflush(stdout);
}