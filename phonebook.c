#include <stdio.h>
#include <stdlib.h>
//Ahmet Faruk Yuksektepe 210101038

typedef struct phBook
{
    char name[30];
    char lname[30];
    unsigned int pnumber;
    char dept[100];
}book;

int menu();
void addinfo(FILE *fPtr);
void srchinfo(FILE *fPtr);
void listinfo(FILE *fPtr);
void delinfo(FILE *fPtr);
void updinfo(FILE *fPtr);

int main()
{
    FILE *fPtr;
    enbas:
    if(
        (fPtr =
        fopen("data.dat", "rb+"))
        == NULL
     )
     {
        printf("Trying the wb+...\n");
        if (
               (fPtr =
              fopen("data.dat", "wb+"))
              == NULL
        )
        {
            printf("Cannot open...");
            return EXIT_FAILURE;
        }
     }

    switch (menu()) {

    case 1:
        addinfo(fPtr);
        break;
    case 2:
        srchinfo(fPtr);
        break;
    case 3:
        updinfo(fPtr);
        break;
    case 4:
        delinfo(fPtr);
        break;
    case 5:
        listinfo(fPtr);
        break;
    case 6:
        printf("Exiting the program...");
        exit(0);
        break;
    case 7:
        createTextFile(fPtr);
        break;
    default:
        printf("Invalid choice. Please try again.\n");
        break;
    }

    fclose(fPtr);
    goto enbas;
}

int menu()
{
    int n;
    printf("Phonebook Application\n\n1. Add a number\n");
    printf("2. Search by\n");
    printf("3. Update\n");
    printf("4. Delete\n");
    printf("5. List\n");
    printf("6. Exit\n");
    printf("7. Print .txt file\n");
    scanf("%d", &n);
    return n;
}


void addinfo(FILE *fPtr)
{
    int n, i=0, flag = 1;
    book phone, a;

    printf("How many numbers will you add?");
    scanf("%d", &n);

    while(i < n)
    {
        printf("Enter the records (name, last name, number(4-digit) and department name): ");
        scanf("%s%s%d%s", phone.name, phone.lname, &phone.pnumber, phone.dept);
        while(fread(&a, sizeof(book), 1, fPtr) == 1)
        {
            if(a.pnumber == phone.pnumber)
            {
                printf("Person already exists!\n");
                flag = 0;
                break;
            }
        }
        if(flag == 0)
        {
            break;
        }
        if(phone.pnumber < 1000 || phone.pnumber > 9999)
            {
                printf("The phone number must be 4-digit!\n");
                break;
            }
        fseek(fPtr, (phone.pnumber-1000) * sizeof(book), SEEK_SET);
		fwrite(&phone, sizeof(book), 1, fPtr);
		printf("Successfully added!\n");
        i++;
    }
    fclose(fPtr);
}

void srchinfo(FILE *fPtr)
{
    book phone;
    int a, num;
    char name[30];

    printf("How will you search by?\n");
    printf("1. Name\n2. Last Name\n3. Phone\n4. Department\n");
    scanf("%d", &a);

    switch (a)
    {
        case 1:
            printf("Enter the name you want to search: ");
            scanf("%s", name);
            int i = 0;
            while(fread(&phone, sizeof(book), 1, fPtr) == 1)
            {
                if(strcmp(name, phone.name) == 0)
                {
                    i++;
                    printf("%d. Person!\n", i);
                    printf("First Name: %s\nLast Name: %s\nPhone Number: %d\nDepartment: %s\n", phone.name, phone.lname, phone.pnumber, phone.dept);
                }
            }
            printf("-------%d Person Found!--------\n", i);
            break;
        case 2:
            i = 0;
            printf("Enter the last name you want to search: ");
            scanf("%s", name);
            while(fread(&phone, sizeof(book), 1, fPtr) == 1)
            {
                if(strcmp(name, phone.lname) == 0)
                {
                    i++;
                    printf("%d. Person!\n", i);
                    printf("First Name: %s\nLast Name: %s\nPhone Number: %d\nDepartment: %s\n", phone.name, phone.lname, phone.pnumber, phone.dept);
                }
            }
            printf("-------%d Person Found!--------\n", i);
		break;

        case 3:
            printf("Enter the phone you want to search: ");
            scanf("%d", &num);
            fseek(fPtr, (num-1000) * sizeof(book), SEEK_SET);
            fread(&phone, sizeof(book), 1, fPtr);
            if (num == phone.pnumber)
            {
                printf("Person found!\n");
                printf("First Name: %s\nLast Name: %s\nPhone Number: %d\nDepartment: %s\n", phone.name, phone.lname, phone.pnumber, phone.dept);
            }
            break;
        case 4:
            i = 0;
            printf("Enter the department name you want to search: ");
            scanf("%s", name);
            while(fread(&phone, sizeof(book), 1, fPtr) == 1)
            {
                if(strcmp(name, phone.dept) == 0)
                {
                    i++;
                    printf("%d. Person!\n", i);
                    printf("First Name: %s\nLast Name: %s\nPhone Number: %d\nDepartment: %s\n", phone.name, phone.lname, phone.pnumber, phone.dept);
                }
            }
            printf("-------%d Person Found!--------\n", i);
            break;
    }

    fclose(fPtr);
}

void listinfo(FILE *fPtr)
{
    book phone;
    int i = 0;
    char name[30], lname[30], n[4], dept[100];

    while(fread(&phone, sizeof(book), 1, fPtr) == 1)
    {
        if(phone.name[2] != NULL)
        {
            printf("%d. Person-----------\n", i+1);
            printf("Name: %s\n", phone.name);
            printf("Last Name: %s\n", phone.lname);
            printf("Phone Number: %d\n", phone.pnumber);
            printf("Department: %s\n", phone.dept);
            i++;
        }
    }

    fclose(fPtr);
}

void delinfo(FILE *fPtr)
{
    book phone, emptybook = {"", "", 0, ""};
    int num, a;

    printf("Enter the phone number of the person you want to delete: ");
    scanf("%d", &num);

    fseek(fPtr, (num-1000) * sizeof(book), SEEK_SET);
    fread(&phone, sizeof(book), 1, fPtr);

    if(num == phone.pnumber)
    {
        printf("Person found!\n");
        printf("First Name: %s\nLast Name: %s\nPhone Number: %d\nDepartment: %s\nDo you want to delete(1/0)?: ", phone.name, phone.lname, phone.pnumber, phone.dept);
        scanf("%d", &a);

        switch (a)
        {
            case 1:
                fseek(fPtr, (num-1000) * sizeof(book), SEEK_SET);
                fwrite(&emptybook, sizeof(book), 1, fPtr);
                printf("Person deleted!\n");
                break;
            default:
                printf("Opening the main menu...\n");
                break;
        }

    }
    else
    {
        printf("Person doesn't exist!\n");
    }

    fclose(fPtr);

}

void updinfo(FILE *fPtr)
{
    book phone;
    int num, a;

    printf("Enter the phone number of the person you want to update: ");
    scanf("%d", &num);

    fseek(fPtr, (num-1000) * sizeof(book), SEEK_SET);
    fread(&phone, sizeof(book), 1, fPtr);

    if(num == phone.pnumber)
    {
        printf("Person found!\n");
        printf("First Name: %s\nLast Name: %s\nPhone Number: %d\nDepartment: %s\nDo you want to update(1/0)?: ", phone.name, phone.lname, phone.pnumber, phone.dept);
        scanf("%d", &a);

        switch (a)
        {
            case 1:
                printf("Enter the new records (name, lastname, phone, department): ");
                scanf("%s%s%d%s", phone.name, phone.lname, &phone.pnumber, phone.dept);
                fseek(fPtr, (phone.pnumber-1000) * sizeof(book), SEEK_SET);
                fwrite(&phone, sizeof(book), 1, fPtr);
                printf("Successfully Updated!\n");
                break;
            case 0:
                printf("Opening the main menu...\n");
                break;
        }

    }
    else
    {
        printf("Person doesn't exist!\n");
    }

    fclose(fPtr);

}

//kendi denemelerim icin
void createTextFile(FILE *fPtr)
{
	FILE *txtFile;
    book txt;
    if(
        (txtFile = fopen("customer.txt", "w"))
        == NULL
    )
    {
        printf("CANNOT OPEN THE FILE");
        return EXIT_FAILURE;
    }
    fprintf(txtFile,
            "%30s%30s%8s%20s\n",
            "name",
            "lastname",
            "phone",
            "Dept.");
    rewind(fPtr);
    fread(&txt, sizeof(book), 1, fPtr);
    while(!feof(fPtr))
    {
        if(txt.pnumber!=0)
        {
            fprintf(txtFile,
            "%30s%30s%8d%20s\n",
            txt.name,
            txt.lname,
            txt.pnumber,
            txt.dept);
        }
        fread(&txt, sizeof(book), 1, fPtr);
    }
    fclose(txtFile);
}
