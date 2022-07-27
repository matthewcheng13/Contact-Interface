#include <stdio.h>
/*
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include "contact.h"
#include "contact_list.h"

void process_file (char *filename);

char print_menu (void);

char print_format_menu (void);

void find_individual (char mode);

void print_tab (char mode);

void process_state_contacts (char mode);
*/
/*
int main() {
    //char option;
    //option = print_menu();

    //printf("Option is: %c",option);
    return 0;
}
 //*/

 ///*
//void main (int argc, char *argv []) {
int main() {
    char mode = 'c';
    char option;

    FILE *fp;
    char str[200];
    fp = fopen("addr.csv","r");
    //if (fp == NULL) {}
    while (fscanf(fp, "%[^\n] ",str) == 1) {
        printf("%s\n",str);
    }
    fclose(fp);
    return 0;
}