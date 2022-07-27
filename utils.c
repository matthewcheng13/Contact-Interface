//
// Created by Matthew Cheng on 4/13/21.
//

#include "utils.h"

void upper (char str []) {
    int i = 0;

    //changes any lowercase character to uppercase using char arithmetic (i.e., no toupper)
    while (str[i]) {
        if (96 < str[i] && 123 > str[i]) {
            str[i] -= 32;
        }
        i++;
    }
}