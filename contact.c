//
// Created by Matthew Cheng on 4/13/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"


CONTACT_T *create_contact (CONTACT_T *contact) {
    //uses malloc to dynamically allocate memory for new contact node
    CONTACT_T *new;
    new = (CONTACT_T *) malloc (sizeof (CONTACT_T));

    //calls strcpy to copy all field data from contact to newly allocated node
    strcpy(new->first_name,contact->first_name);
    strcpy(new->last_name,contact->last_name);
    strcpy(new->co_name,contact->co_name);
    strcpy(new->addr,contact->addr);
    strcpy(new->city,contact->city);
    strcpy(new->county,contact->county);
    strcpy(new->state,contact->state);
    strcpy(new->zip,contact->zip);
    strcpy(new->phone1,contact->phone1);
    strcpy(new->phone2,contact->phone2);
    strcpy(new->email,contact->email);
    strcpy(new->web,contact->web);
    new->next = NULL;

    //returns pointer to newly allocated node
    return new;
}

void print_contact (CONTACT_T *contact, char mode) {
    //prints contact information in condensed or full mode
    if (mode == 'c') {
        printf("%-18s%-18s%-15s%s\n",contact->last_name,contact->first_name,contact->phone1,contact->email);
    } else {
        printf("Name:    %s %s\n",contact->first_name,contact->last_name);
        printf("Address: %s, %s, %s %s  (%s County)\n", contact->addr, contact->city, contact->state, contact->zip, contact->county);
        printf("Phone:   %s (primary)  %s\n", contact->phone1, contact->phone2);
        printf("email:   %s\n", contact->email);
        printf("web:     %s\n\n", contact->web);
    }
}
