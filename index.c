#include <stdio.h>
#include <string.h>
const int sz = 255;
char userName[20], userPassword[20], strid[100], strpass[100];
int count = 1, flag = 0, logFlag = 0;
void addUserItems()
{
}
void printSlip()
{
}
void showItems()
{
    FILE *fptr;
    char buffer[100];
    fptr = fopen("items.txt", "r");
    while (fgets(buffer, sizeof(buffer), fptr) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        printf("%s\n", buffer);
    }
}
void addItems()
{
    char item[50];
    int n;
    FILE *fptr;
    fptr = fopen("items.txt", "a");
    printf("Enter the Item Name\n");
    scanf("%s", &item);
    printf("Enter the amount\n");
    scanf("%d", &n);
    printf("%s %d", item, n);
    fprintf(fptr, "%s %d\n", item, n);
    fclose(fptr);
}
void editItems()
{
    char item[50], buffer[100], itemName[50];
    int quantity, found = 0, n;
    FILE *fptr, *fptrWrite;
    showItems();
    fptrWrite = fopen("tempItems.txt", "w");
    fptr = fopen("items.txt", "r");
    printf("Enter the Item you want to edit: ");
    scanf("%s", &itemName);
    printf("Enter the amount: ");
    scanf("%d", &n);
    while (fscanf(fptr, "%s %d", item, &quantity) != EOF)
    {

        if (strcmp(item, itemName) == 0)
        {
            quantity += n;
            found = 1;
        }

        fprintf(fptrWrite, "%s %d\n", item, quantity);
    }
    if (found == 0)
    {
        printf("No items have been found");
    }
    fclose(fptr);
    fclose(fptrWrite);
    fptrWrite = fopen("tempItems.txt", "r");
    fptr = fopen("items.txt", "w");
    while (fscanf(fptrWrite, "%s %d", item, &quantity) != EOF)
    {

        fprintf(fptr, "%s %d\n", item, quantity);
    }
    fclose(fptr);
    fclose(fptrWrite);
}
void show()
{
    int n;
    printf("\e[1;1H\e[2J");
    printf("Choose an Option\n");

    printf("1. Show Items\n");
    printf("2. Add Items to cart\n");
    printf("3. Check Slip\n");
    scanf("%d", &n);
    if (n == 1)
    {
        showItems();
    }
    else if (n == 2)
    {
        addUserItems();
    }
    else if (n == 3)
    {
        printSlip();
    }
}
void adminPanel()
{
    int n;
    printf("\e[1;1H\e[2J");
    printf("Choose an Option\n");

    printf("1. Show Items\n");
    printf("2. Add Items\n");
    printf("3. Edit Items\n");
    scanf("%d", &n);
    if (n == 1)
    {
        showItems();
    }
    else if (n == 2)
    {
        addItems();
    }
    else if (n == 3)
    {
        editItems();
    }
}
void userLogin()
{

    FILE *fptr;
here1:

    printf("Enter Username\n");
    scanf("%s", &userName);

    printf("Enter Password\n");
    scanf("%s", &userPassword);

    fptr = fopen("filename.txt", "r");
    while (fscanf(fptr, "%s %s", strid, strpass) != EOF)
    {
        if (strcmp(strid, userName) == 0)
        {
            flag = 1;
            if (strcmp(strpass, userPassword) == 0)
            {
                logFlag = 1;
                break;
            }
            else
            {
                printf("Wrong password, try again\n");

                goto here1;
            }
        }
    }
    fclose(fptr);

    if (logFlag == 1)
    {
        show();
    }
    if (flag == 0)
    {
        printf("No user have been found");
    }
}
void userSignup()
{
    char str[100];

    FILE *fptr, *fptr1;
here2:
    fptr = fopen("filename.txt", "a");
    fptr1 = fopen("filename.txt", "r");
    printf("Enter Username\n");
    scanf("%s", &userName);

    while (fscanf(fptr1, "%s %s", strid, strpass) != EOF)
    {

        if (strcmp(strid, userName) == 0)
        {
            printf("already exists, choose another name\n");
            goto here2;
        }
    }
    printf("Enter Password\n");
    scanf("%s", &userPassword);

    fprintf(fptr, "%s %s\n", userName, userPassword);
    fclose(fptr);
    fclose(fptr1);
}
int main()
{
    int n;

    FILE *fptr;
    char ch;
here:
    printf("\e[1;1H\e[2J");
    printf("Press 1 to Login\n");
    printf("Press 2 to Signup\n");
    printf("Press 3 for Owner Login\n");
    scanf("%d", &n);
    if (n == 1)
    {
        userLogin();
    }
    else if (n == 2)
    {
        userSignup();
        goto here;
    }
    else if (n == 3)
    {
        adminPanel();
    }

    return 0;
}