#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
 

void listContacts(AddressBook *addressBook) 
{
    loadContactsFromFile(addressBook);
    // Bubble sort based on name

    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - 1 - i; j++)
        {
            if (strcasecmp(addressBook->contacts[j].name,
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
printf("------------------------------------------------------------------------- \n");
printf("| %-20s | %-15s | %-29s |\n",
       "Name", "Phone Number", "Email");
printf("------------------------------------------------------------------------- \n");

for (int i = 0; i < addressBook->contactCount; i++)
{
    printf("| %-20s | %-15s | %-29s |\n",
           addressBook->contacts[i].name,
           addressBook->contacts[i].phone,
           addressBook->contacts[i].email);
}

printf("------------------------------------------------------------------------- \n");
printf("Total number of contacts: %d\n", addressBook->contactCount);
}
 
 
void createContact(AddressBook *addressBook) // insted struct Addressbook (datatype)*addresbook due to typedef just addressbook
{
	/* Defining the logic to create a Contacts */

    char name[30], phone[11], email[50];
    int res;
    /*             Name            */
    do
    {
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
void searchContact(AddressBook *addressBook)
{
    int choice;
while(1)
{
    printf("\nSearch Contact\n");
    printf("1. Search by phone\n");
    printf("2. Search by email\n");
    printf("3. Search by name\n");

    printf("Enter your choice: ");
     if (scanf("%d", &choice) != 1)
    {
        printf("Invalid choice. Please enter a number.\n");

        while (getchar() != '\n')
        {
        }

        continue;
    }


    switch (choice)
    {
        case 1:
            search_by_phone(addressBook);
            return;

        case 2:
            search_by_email(addressBook);
            return;

        case 3:
            search_by_name(addressBook);
            return;

        default:
            printf("Invalid choice.\n");
    }
}

}int search_by_phone(AddressBook *addressBook)
{
    char phone[50];
    int count = 0;
    int index[100];

    printf("Enter phone number: ");
    scanf(" %[^\n]", phone);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].phone, phone) != NULL)
        {
            index[count] = i;
            count++;
        }
    }

    if (count == 0)
    {
        printf("Contact not found.\n");
        return -1;
    }

    if (count == 1)
    {
        int i = index[0];

        printf("\nContact found!\n");
        printf("Name  : %s\n", addressBook->contacts[i].name);
        printf("Phone : %s\n", addressBook->contacts[i].phone);
        printf("Email : %s\n", addressBook->contacts[i].email);

        return i;
    }

    printf("\nMultiple contacts found:\n");

    for (int i = 0; i < count; i++)
    {
        int actualIndex = index[i];

        printf("\n%d.\n", i + 1);
        printf("Name  : %s\n", addressBook->contacts[actualIndex].name);
        printf("Phone : %s\n", addressBook->contacts[actualIndex].phone);
        printf("Email : %s\n", addressBook->contacts[actualIndex].email);
    }

    int choice;

    while (1)
    {
        printf("\nEnter serial number to select contact: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid serial number. Please enter a number.\n");

            while (getchar() != '\n')
            {
            }

            continue;
        }

        if (choice < 1 || choice > count)
        {
            printf("Invalid serial number.\n");
            continue;
        }

        return index[choice - 1];
    }
}

int search_by_email(AddressBook *addressBook)
{
    char email[50];

printf("Enter email: ");
scanf(" %[^\n]", email);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
        {
            printf("\nContact found!\n");
            printf("Name  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);

            return i;
        }
    }

    printf("Contact not found.\n");
    return -1;
}


int search_by_name(AddressBook *addressBook)
{
    char name[30];
    int count = 0;
    int index[100];

    printf("Enter name: ");
    scanf(" %[^\n]", name);
for (int i = 0; i < addressBook->contactCount; i++)
{
    char temp[30];

    strcpy(temp, addressBook->contacts[i].name);

    for (int j = 0; temp[j] != '\0'; j++)
    {
        if (temp[j] >= 'A' && temp[j] <= 'Z')
        {
            temp[j] = temp[j] + 32;
        }
    }

    for (int j = 0; name[j] != '\0'; j++)
    {
        if (name[j] >= 'A' && name[j] <= 'Z')
        {
            name[j] = name[j] + 32;
        }
    }

    if (strstr(temp, name) != NULL)
    {
        index[count] = i;
        count++;
    }
}

    if (count == 0)
    {
        printf("Contact not found.\n");
        return -1;
    }

    if (count == 1)
    {
        int i = index[0];

        printf("\nContact found!\n");
        printf("Name  : %s\n", addressBook->contacts[i].name);
        printf("Phone : %s\n", addressBook->contacts[i].phone);
        printf("Email : %s\n", addressBook->contacts[i].email);

        return i;
    }

    printf("\nMultiple contacts found:\n");

    for (int i = 0; i < count; i++)
    {
        int actualIndex = index[i];

        printf("\n%d.\n", i + 1);
        printf("Name  : %s\n", addressBook->contacts[actualIndex].name);
        printf("Phone : %s\n", addressBook->contacts[actualIndex].phone);
        printf("Email : %s\n", addressBook->contacts[actualIndex].email);
    }

    int choice;
while (1){
 


    printf("\nEnter serial number to select contact: ");
    
if (scanf("%d", &choice) != 1)
{
    printf("Invalid serial number. Please enter a number.\n");

    while (getchar() != '\n')
    {
    }

   continue;
}

    if (choice < 1 || choice > count)
    {
        printf("Invalid serial number.\n");
        continue;
    }

    return index[choice - 1];
}}
void editContact(AddressBook *addressBook)
{
    int choice;
    int index;
while(1){
    printf("\nEdit Contact\n");
    printf("1. Search by phone\n");
    printf("2. Search by email\n");
    printf("3. Search by name\n");
    printf("4. Cancel\n");

    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1)
    {
        printf("Invalid choice. Please enter a number.\n");

        while (getchar() != '\n')
        {
        }

        continue;
    }

    if (choice < 1 || choice > 4)
    {
        printf("Invalid choice.\n");
        continue;
    }

    break;
}

    switch (choice)
    {
        case 1:
            index = search_by_phone(addressBook);
            break;

        case 2:
            index = search_by_email(addressBook);
            break;

        case 3:
            index = search_by_name(addressBook);
            break;
        
        case 4:
        printf("Edit cancelled.\n");
        return;
          
        default:
            printf("Invalid choice.\n");
            return;
    }

    /* Contact not found */
    if (index == -1)
    {
        return;
    }

    printf("\nContact selected:\n");
    printf("Name  : %s\n", addressBook->contacts[index].name);
    printf("Phone : %s\n", addressBook->contacts[index].phone);
    printf("Email : %s\n", addressBook->contacts[index].email);
while(1){
    printf("\nWhat do you want to edit?\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. Cancel\n");

    printf("Enter your choice: ");
   if (scanf("%d", &choice) != 1)
    {
        printf("Invalid choice. Please enter a number.\n");

        while (getchar() != '\n')
        {
        }

        continue;
    }

    if (choice < 1 || choice > 4)
    {
        printf("Invalid choice.\n");
        continue;
    }

    break;
}

    switch (choice)
    {
        /* ---------- EDIT NAME ---------- */

        case 1:
        {
            char name[30];
            int res;

            do
            {
                printf("Enter new name: ");
                scanf(" %[^\n]", name);

                res = validate_name(name);

            } while (res == 0);

            strcpy(addressBook->contacts[index].name, name);

            printf("Name updated successfully!\n");
            break;
        }


        /* ---------- EDIT PHONE ---------- */

        case 2:
        {
            int res;
           char phone[50];

            do
            {
            printf("Enter new phone number: ");
            scanf(" %[^\n]", phone);

            res = validate_phone(phone);

            if (res == 1)
            {
                if (isPhoneUnique(addressBook, phone) == 0)
                {
                    if (strcmp(addressBook->contacts[index].phone, phone) != 0)
                    {
                         printf("Phone number already exists. Enter another number.\n");
                         res = 0;
                     }
        }
    }

} while (res == 0);

            strcpy(addressBook->contacts[index].phone, phone);

            printf("Phone number updated successfully!\n");
            break;
        }


        /* ---------- EDIT EMAIL ---------- */

        case 3:
             {
            char email[50];
            int res;

            do
            {
                printf("Enter new email: ");
                scanf(" %[^\n]", email);

                res = validate_email(email);

                if (res == 1)
                {
                    if (isEmailUnique(addressBook, email) == 0)
                    {
                        if (strcmp(addressBook->contacts[index].email, email) != 0)
                        {
                            printf("Email already exists. Enter another email.\n");
                            res = 0;
                        }
                    }
                }

            } while (res == 0);

            strcpy(addressBook->contacts[index].email, email);

            printf("Email updated successfully!\n");
            break;
        }
           case 4:
        printf("Edit cancelled.\n");
        return;
        
        default:
            printf("Invalid choice.\n");
            return;
    }

    /* Save the updated contact permanently into CSV */

    saveContactsToFile(addressBook);

    printf("Changes saved successfully.\n");
}
 
 
void deleteContact(AddressBook *addressBook)
{
    int choice;
    int index;

    printf("\nDelete Contact\n");
    printf("1. Search by phone\n");
    printf("2. Search by email\n");
    printf("3. Search by name\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            index = search_by_phone(addressBook);
            break;

        case 2:
            index = search_by_email(addressBook);
            break;

        case 3:
            index = search_by_name(addressBook);
            break;

        default:
            printf("Invalid choice.\n");
            return;
    }

    if (index == -1)
    {
        return;
    }

    printf("\nContact selected for deletion:\n");
    printf("Name  : %s\n", addressBook->contacts[index].name);
    printf("Phone : %s\n", addressBook->contacts[index].phone);
    printf("Email : %s\n", addressBook->contacts[index].email);

    char confirm;

    printf("\nDo you want to delete this contact? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y')
    {
        printf("Deletion cancelled.\n");
        return;
    }

    /* Shift contacts to the left */

    for (int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    saveContactsToFile(addressBook);

    printf("Contact deleted successfully.\n");
}