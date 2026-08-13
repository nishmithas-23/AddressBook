/*
Nishmitha S  
Date :-31/7/2026
Time : From 8.30pm 
Description Added functions to  Creating a contact and started on do other operations...
*/

#include<stdio.h>
#include "contact.h"


 
int main()
{
    int choice;
    AddressBook addressBook;

    addressBook.contactCount = 0;

    loadContactsFromFile(&addressBook);
    printf("Total number of contacts: %d\n", addressBook.contactCount);
    do 
    {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save and Exit\n");		
        printf("7. Exit\n");
        printf("Please, Enter your choice: ");
        
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
                createContact(&addressBook);
                break;
            case 2:
                 searchContact(&addressBook);
                break;
            case 3:
                 editContact(&addressBook);
                break;
            case 4:
                 deleteContact(&addressBook);
                break;
            case 5:          
                 listContacts(&addressBook);
                break;
            case 6:
            saveContactsToFile(&addressBook);
            printf("Saving and Exiting...\n");
            break;
            
            case 7:
            return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
    return 0;
} 