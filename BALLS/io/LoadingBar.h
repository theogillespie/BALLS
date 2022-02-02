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
    unsigned int lpad = (int) (percentage * BARWIDTH);
    unsigned int rpad = BARWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s] \n", val, lpad, BARSTRING, rpad, "");
    fflush(stdout);
}