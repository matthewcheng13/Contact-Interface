//
// Created by Matthew Cheng on 4/13/21.
//

#ifndef ASSIGNMENT_6_CONTACT_H
#define ASSIGNMENT_6_CONTACT_H

//NAME_T of 15 char’s
typedef char NAME_T[15];

//CONTACT_T with necessary fields
typedef struct contact_t {
    NAME_T first_name;
    NAME_T last_name;
    char co_name[35];
    char addr[35];
    char city[20];
    char county[25];
    char state[3];
    char zip[6];
    char phone1[15];
    char phone2[15];
    char email[35];
    char web[45];
    struct contact_t *next;
} CONTACT_T;

CONTACT_T *create_contact (CONTACT_T *contact);

void print_contact (CONTACT_T *contact, char mode);

#endif //ASSIGNMENT_6_CONTACT_H
