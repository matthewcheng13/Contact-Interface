//
// Created by Matthew Cheng on 4/13/21.
//
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "utils.h"
#include "contact.h"
#include "contact_list.h"

//function prototypes
void process_file (char *filename);

char print_menu (void);

char print_format_menu (void);

void find_individual (char mode);

void print_tab (char mode);

void process_state_contacts (char mode);


void main (int argc, char *argv []) {
    //declare and initialize mode, declare option
    char mode = 'c';
    char option;

    //checks command line argument info to ensure contact file is specified; if not a message is
    //printed and exit is called with a EXIT_FAILURE status
    if (argc < 2) {
        exit(EXIT_FAILURE);
    }

    //initializes empty contact list, reads in file, fills contact list, and prints finished list
    init_contact_list();
    process_file(argv[1]);
    print_contact_list(mode);
    printf("\n");

    //do while loop that keeps the program running until q is selected
    do {
        //get the user's selected option
        option = print_menu();

        //calls various functions based on option selected
        switch(option) {
            case 'c':
                mode = print_format_menu();
                break;
            case 'i':
                find_individual(mode);
                break;
            case 't':
                print_tab(mode);
                break;
            case 's':
                process_state_contacts(mode);
                break;
            default:
                ;
        }
    } while (option != 'q');
    //frees up allocated memory after quit is selected
    free_contact_list();
}

void process_file (char *filename) {
    //opens filename for processing (no error checking required)
    FILE *fp;
    CONTACT_T contact;
    fp = fopen(filename,"r");

    //gets rid of first line (header)
    char *first[89];
    fscanf(fp, "%[^\n] ", first);

    //while fscanf returns info for each contact
    //call create_contact and insert_contact to place contact in list
    while (fscanf(fp, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%s ",
                  contact.first_name,contact.last_name,contact.co_name,contact.addr,contact.city,
                  contact.county,contact.state,contact.zip,contact.phone1,contact.phone2,
                  contact.email,contact.web) == 12) {
        insert_contact(create_contact(&contact));
    }

    //close file when done
    fclose(fp);
}

char print_menu (void) {
    //declare input and option used for getting user's selection
    char input[10];
    char option;

    //used for validating user's selection
    char valid[] = "citsq";

    //used to determine if an invalid option was entered
    int condition = 1;

    //prints until valid option
    do {
        //if running for the first time, does nothing
        //if running multiple times, the option was invalid
        if (!condition) {
            printf("\nInvalid option entered\n");
        }

        //prints the menu
        printf("\nPlease select one of the following: \n\n");

        printf(" c  Change output format\n");
        printf(" i  Search for individual\n");
        printf(" t  Print tab\n");
        printf(" s  Look up by state\n");
        printf(" q  Quit\n\n");

        //gets user's input
        printf("Option: ");
        scanf("%s", &input);
        printf("%s\n",input);

        //casts the input to lower
        option = tolower(input[0]);

        //allows for invalid option to be printed
        condition = 0;
    } while (!strchr(valid, option) || strlen(input) > 1);

    return option;
}

char print_format_menu (void) {
    char input[2];

    //prints format menu
    printf("\nPlease select one of the following: \n\n");

    printf(" c  Condensed output information\n");
    printf(" f  Full output information\n\n");

    //gets user's input
    printf("Option: ");
    scanf("%s", input);
    printf("%s\n",input);

    return tolower(input[0]);
}

void find_individual (char mode) {
    //used to compare to contacts
    NAME_T last;
    NAME_T first;
    CONTACT_T *find;

    //gets name from user
    printf("\nPlease enter last name: ");
    scanf("%s", last);
    printf("%s\n",last);
    printf("Please enter first name: ");
    scanf("%s", first);
    printf("%s\n\n",first);

    //casts the name to upper
    upper(last);
    upper(first);

    //if a contact is found, print it, else let user know
    if ((find = find_contact(last, first))){
        print_contact(find, mode);
    } else {
        printf("Contact not found\n");
    }
}

void print_tab (char mode) {
    char tab[2];
    CONTACT_T *contact;

    //prompts for tab letter and uppercases it using upper
    printf("\nPlease enter last name tab letter: ");
    scanf("%s", tab);
    printf("%s\n\n", tab);
    upper(tab);

    //calls get_next_contact using tab letter and prints message that contact was not found
    contact = get_next_contact(tab[0]);
    if (contact == NULL) {
        printf("No contacts found\n");
    }
    //otherwise, calls print_contact using return pointer and mode, and calls
    //get_next_contact until no more elements are in the list
    else {
        print_contact(contact, mode);
        while ((contact = get_next_contact(tab[0])) != NULL) {
            print_contact(contact, mode);
        }
    }
}

void process_state_contacts (char mode) {
    char abbr[3];

    //prompts for two-letter state and uppercases it using upper
    printf("\nPlease enter two-letter state abbreviation: ");
    scanf("%s", abbr);
    printf("%s\n\n",abbr);
    upper(abbr);

    //calls print_state_contacts using state and mode
    print_state_contacts(abbr, mode);
}