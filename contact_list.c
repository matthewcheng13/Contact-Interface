//
// Created by Matthew Cheng on 4/13/21.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact_list.h"
#include "contact.h"
#include "utils.h"

//creates  static variable for bucket list (an array of linked lists for each letter of the alphabet)
static CONTACT_T *list [26];

void init_contact_list (void) {
    //initializes each list in the bucket list to NULL
    int i;
    for (i=0;i<26;i++) {
        list[i] = NULL;
    }
}

void insert_contact (CONTACT_T *contact) {
    //finds the correct bucket list using the first letter of the last name field
    //uses strcmp to find the correct location within the list to insert contact
    char letter;
    letter = contact->last_name[0];
    letter -= 'A';

    if (list[letter] == NULL) {
        list[letter] = contact;
    } else {
        CONTACT_T* curr = list[letter]->next;
        CONTACT_T* prev = list[letter];
        //case for the beginning of the list
        if (strcmp(contact->last_name,prev->last_name) < 0) {
            list[letter] = contact;
            contact->next = prev;
        } else {
            while (curr != NULL && (strcmp(contact->last_name,curr->last_name) > 0)) {
                curr = curr->next;
                prev = prev->next;
            }

            //every other case
            prev->next = contact;
            contact->next = curr;
        }
    }

}

void print_contact_list (char mode) {
    int i;
    int nodes = 0;

    //loops through each element in the bucket list
    for (i=0;i<26;i++) {
        CONTACT_T *curr = list[i];

        //traverses linked list in bucket and calls print_contact for each node
        while (curr != NULL) {
            print_contact(curr,mode);
            curr = curr->next;
            nodes++;
        }
    }

    //if no nodes in entire bucket list
    if (nodes == 0) {
        printf("No contacts found");
    }
}

CONTACT_T *find_contact (NAME_T last_name, NAME_T first_name) {
    //uses last_name to find correct bucket
    char letter;
    letter = last_name[0];
    letter -= 'A';

    CONTACT_T *result = NULL;
    CONTACT_T *curr = list[letter];
    char last[15];
    char first[15];

    while (curr != NULL) {
        //first and last names from the list must be capitalized using upper for comparison
        //purposes; however, capitalization should not permanently change names in the list
        strcpy(last,curr->last_name);
        strcpy(first,curr->first_name);
        upper(last);
        upper(first);

        //uses strcmp to find the correct node in the list
        if (strcmp(last,last_name) == 0 && strcmp(first,first_name) == 0) {
            result = curr;
            break;
        } else {
            curr = curr->next;
        }
    }

    //returns pointer to correct node
    return result;
}

CONTACT_T *get_next_contact (char letter) {
    static CONTACT_T *curr = NULL;

    if (curr == NULL) {
        //if current pointer is NULL, it is set to first element in correct bucket
        curr = list[letter - 'A'];
    } else {
        //returns next element in list from array (use static variable to hold current pointer)
        curr = curr->next;
    }

    return curr;
}

void print_state_contacts (char state [], char mode) {
    int i;
    int count = 0;

    //loops through all bucket lists
    for (i=0;i<26;i++) {
        CONTACT_T *curr = list[i];
        while (curr != NULL) {
            //uses strcmp to find any node with matching state and calls print_contact
            if (strcmp(state,curr->state) == 0) {
                print_contact(curr,mode);
                count++;
            }
            curr = curr->next;
        }
    }

    //prints appropriate message if no contacts found with matching state
    if (count == 0) {
        printf("No contacts found\n");
    }
}

void free_contact_list (void) {
    int i;
    CONTACT_T *curr;
    CONTACT_T *prev;

    //deallocates space for all nodes in each bucket list
    for (i=0;i<26;i++) {
        curr = list[i];

        while (curr != NULL) {
            prev = curr;
            curr = curr->next;
            free(prev);
            prev = NULL;
        }
    }
}