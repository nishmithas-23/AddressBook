#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[11];
    char email[50];
    
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount; 
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);

void deleteContact(AddressBook   *addressBook);
void listContacts(AddressBook *addressBook);
 
void saveContactsToFile(AddressBook *AddressBook);

int validate_name(char *str);
int validate_phone(char *str);
int validate_email(char *str);

int isPhoneUnique(AddressBook *addressBook, char *phone);
int isEmailUnique(AddressBook *addressBook, char *email);

void loadContactsFromFile(AddressBook *addressBook);
 

int search_by_phone(AddressBook *addressBook);
int search_by_email(AddressBook *addressBook);
int search_by_name(AddressBook *addressBook);

 
 
#endif
