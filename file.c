#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.csv", "w");

    if (fp == NULL)
    {
        printf("File opening failed\n");
        return;
    }
    fprintf(fp, "%d\n", addressBook->contactCount);
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp);
}
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.csv", "r");

    if (fp == NULL)
    {
        printf("No contacts file found\n");
        return;
    }

    int count;
    fscanf(fp, "%d\n", &count);

    addressBook->contactCount = 0;

    for (int i = 0; i < count; i++)
    {
        Contact temp;

        if (fscanf(fp, "%29[^,],%10[^,],%29[^\n]\n",
                   temp.name,
                   temp.phone,
                   temp.email) == 3)
        {
            if (validate_name(temp.name) &&
                validate_phone(temp.phone) &&
                validate_email(temp.email))
                {   if (isPhoneUnique(addressBook, temp.phone) &&
                        isEmailUnique(addressBook, temp.email))
            {
                addressBook->contacts[addressBook->contactCount] = temp;
                addressBook->contactCount++;
            }
            
        }
        }
    }

    fclose(fp);
}