#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    // Bubble sort based on name

    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - 1 - i; j++)
        {
            if (strcmp(addressBook->contacts[j].name,
                       addressBook->contacts[j + 1].name) > 0)
            {
                Contact temp;

                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }

    // Print contacts

    printf("----------------------------------------------------------------------\n");
    printf("| %-20s | %-15s | %-25s |\n",
           "Name", "Phone Number", "Email");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("| %-20s | %-15s | %-35s|\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("----------------------------------------------------------------------\n");
}
// void initialize(AddressBook *addressBook) {
//     addressBook->contactCount = 0;
//     populateAddressBook(addressBook);
    
//     // Load contacts from file during initialization (After files)
//     //loadContactsFromFile(addressBook);
// }

// void saveAndExit(AddressBook *addressBook) {
//     saveContactsToFile(addressBook); // Save contacts to file
//     exit(EXIT_SUCCESS); // Exit the program
// }


void createContact(AddressBook *addressBook) // insted struct Addressbook (datatype)*addresbook due to typedef just addressbook
{
	/* Define the logic to create a Contacts */

    char name[30], phone[11], email[30];
    int res;
    /*             Name            */
    do{
        printf("Enter the name : ");
        scanf(" %[^\n]", name);

        res = validate_name(name);

    }while(res == 0);
   
    


    /* ---------- PHONE ---------- */

    do
    {
        printf("Enter the phone number: ");
        scanf("%10s", phone);

        res = validate_phone(phone);

        if (res == 1)
        {
            if (isPhoneUnique(addressBook, phone) == 0)
            {
                printf("Phone number already exists. Enter another number.\n");
                res = 0;
            }
        }

    } while (res == 0);


    /* ---------- EMAIL ---------- */

    do
    {
        printf("Enter the email: ");
        scanf("%49s", email);

        res = validate_email(email);

        if (res == 1)
        {
            if (isEmailUnique(addressBook, email) == 0)
            {
                printf("Email already exists. Enter another email.\n");
                res = 0;
            }
        }

    } while (res == 0);


    strcpy(addressBook->contacts[addressBook->contactCount].name, name);

    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);

    strcpy(addressBook->contacts[addressBook->contactCount].email, email);


    /* ---------- INCREMENT COUNT ---------- */

    addressBook->contactCount++;

    printf("Contact created successfully!\n");
}


// void searchContact(AddressBook *addressBook) 
// {
//     /* Define the logic for search */

//     int choise;

//     // print promt

//     scanF("%d", &choise);

//     switch(choise)
//     {
//         case 1:
//             search_by_name(addressBook);
//             break;
//         case 2:
//             search_by_phone(addressBook);
//             break;
//     }

// }

// void editContact(AddressBook *addressBook)
// {
// 	/* Define the logic for Editcontact */
    
// }

// void deleteContact(AddressBook *addressBook)
// {
// 	/* Define the logic for deletecontact */
   
// }


int validate_name(char *str)
{
    int i = 0;

    while (str[i] == ' ')
    {
        i++;
    }

    if (str[i] == '\0')
    {
        printf("Invalid name. Please enter a valid name.\n");
        return 0;
    }

    for (; str[i] != '\0'; i++)
    {
        if (!((str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= 'a' && str[i] <= 'z') ||
              str[i] == ' ' ||
              str[i] == '.'))
        {
            printf("Invalid name. Use only alphabets, spaces and '.'\n");
            return 0;
        }
    }

    return 1;
}int validate_phone(char *str)
{
    int i;

    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            printf("Invalid phone number. Enter only digits.\n");
            return 0;
        }
    }

    if (i != 10)
    {
        printf("Invalid phone number. Enter exactly 10 digits.\n");
        return 0;
    }

    return 1;
}
int isPhoneUnique(AddressBook *addressBook, char *phone)
{
    int i;

    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            return 0;
        }
    }

    return 1;
}
 int validate_email(char *str)
{
    int i;
    int at = 0;
    int len;

    // First character must be lowercase
    if (!(str[0] >= 'a' && str[0] <= 'z'))
    {
        printf("Invalid email: first character must be lowercase\n");
        return 0;
    }

    // Check characters and count @
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ' ')
        {
            printf("Invalid email: spaces are not allowed\n");
            return 0;
        }

        if (str[i] == '@')
        {
            at++;
        }
    }

    // Exactly one @
    if (at != 1)
    {
        printf("Invalid email\n");
        return 0;
    }

    // Check .com at the end
    len = strlen(str);

    if (len < 5)
    {
        printf("Invalid email\n");
        return 0;
    }

    if (str[len - 4] != '.' ||
        str[len - 3] != 'c' ||
        str[len - 2] != 'o' ||
        str[len - 1] != 'm')
    {
        printf("Invalid email: email must end with .com\n");
        return 0;
    }

    return 1;
}
int isEmailUnique(AddressBook *addressBook, char *email)
{
    int i;

    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
        {
            return 0;
        }
    }

    return 1;
}
 
// int search_by_name(AddressBook *addressBook)
// {
//     char str[30];

//     //Get the name

//     Loop from 0 to cc-1
//         if (str == addressBook->contacts[i].name)
//         {
//             print the contact
//             count++;
//             // return i;
//         }

//     count ==> 0 ==> return -1;
//     count ==> more then 1 ==> return search_by_phone(addressBook);
//     count ==> 1 ==> return matching index
// }


// int search_by_phone(AddressBook * addressBook)
// {
//     char str[11];

//     //Get the phone number 

//     Loop from 0 to cc-1
//         if (str == addressBook->contacts[i].phone)
//         {
//             print the contact
//             return i;
//         }

//     return -1;
// }