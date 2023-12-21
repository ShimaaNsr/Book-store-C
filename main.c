#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//menu details
COORD coord = {0, 0};
void gotoxy(int x, int y, int fontSize) {
    coord.X = x;
    coord.Y = y;
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = fontSize;      // Width of each character
    cfi.dwFontSize.Y = fontSize * 2;  // Height of each character
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void SetColor(int ForgC) {
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

typedef struct Book Book;
struct Book
{
    char Name[20];
    int Price;
    int Quantity;
};

typedef struct Category Category;
struct Category
{
    char CategoryName[20];
    Book *Books;
    int number_Of_Books;
};
Category *categories=NULL;
int number_Of_Categories=0;
void AddCategory() {
    char option;
    do
    {
        char category_name[50];
        printf("Enter category name: \n");
        scanf(" %[^\n]s", category_name);
        getchar();
        categories = realloc(categories, (number_Of_Categories + 1) * sizeof(Category));
        strcpy(categories[number_Of_Categories].CategoryName, category_name);
        categories[number_Of_Categories].number_Of_Books = 0;
        categories[number_Of_Categories].Books = NULL;
        number_Of_Categories++;
        printf("To Enter New Category Enter -> (Y)\nTo Return To The Main Page Enter -> (N)\n");
        option=getche();
        printf("\n");

    }
    while(option!='n');

}

void Display()
{
    for(int index=0;index<number_Of_Categories;index++)
    {
        if(categories[index].number_Of_Books==0)
        {
            printf("\t%s\n",categories[index].CategoryName);
            printf("\t\tIn %s We Have Do not Have Any Books\n",categories[index].CategoryName);
        }
        else
        {
            printf("\t%s\n",categories[index].CategoryName);
            printf("\t\tIn %s We Have %d Different Books\n",categories[index].CategoryName,categories[index].number_Of_Books);
            for(int j=0;j<categories[index].number_Of_Books;j++)
            {
                printf("\t\t\t%s\n",categories[index].Books[j].Name);
                printf("\t\t\t%d\n",categories[index].Books[j].Price);
                printf("\t\t\t%d\n",categories[index].Books[j].Quantity);
                printf("\t\t\t-------\n");
            }
        }

    }
}

void AddBook()
{
    int index;
    int number;
    char option;
    printf("\n\tThis Is Our Categories Which In You Can Add The New BOOK\n\n");
    for(int index=0;index<number_Of_Categories;index++)
    {
        printf("\t\t%d-%s\n",index+1,categories[index].CategoryName);
    }
    printf("\tEnter The Number Of Category: ");
    scanf("%d",&index);

    if (index < 1 || index > number_Of_Categories) {
        printf("Invalid category number.\n");
        return;
    }

    do
    {
        categories[index-1].Books=realloc(categories[index-1].Books,(categories[index-1].number_Of_Books+1)*sizeof(Book));
        printf("\tBook Number %d\n",categories[index-1].number_Of_Books+1);
        printf("\t\tName: ");
        scanf(" %[^\n]s",categories[index-1].Books[categories[index-1].number_Of_Books].Name);
        printf("\t\tPrice: ");
        scanf("%d",&categories[index-1].Books[categories[index-1].number_Of_Books].Price);
        printf("\t\tQuantity: ");
        scanf("%d",&categories[index-1].Books[categories[index-1].number_Of_Books].Quantity);
        categories[index-1].number_Of_Books++;
        printf("\tTo Enter New Book Enter -> (Y)\n\tTo Return To The Main Page Enter -> (N)\n");
        printf("\t");
        option=getche();
        printf("\n");

    }

    while(option!='n');

}

void MakeOrder()
{
    char nameOFBook[40];
    int numberOfBooks;
    printf("Enter The Name Of Book You Need To Sell: ");
    scanf("%s",nameOFBook);
    printf("Enter The Number Of Books You Need To Sell: ");
    scanf("%d",&numberOfBooks);
    for(int i=0;i<number_Of_Categories;i++)
    {
        for(int j=0;j<categories[i].number_Of_Books;j++)
        {


                if(strcmp(categories[i].Books[j].Name,nameOFBook)==0)
                {
                    if(categories[i].Books[j].Quantity>=numberOfBooks)
                    {
                        if(categories[i].Books[j].Quantity>=numberOfBooks)
                        {
                            categories[i].Books[j].Quantity-=numberOfBooks;
                            printf("You Selled %d \n",numberOfBooks);
                            printf("The Price Of One Copy Is %d\n",categories[i].Books[j].Price);
                            printf("Total Price Is %d\n",numberOfBooks*categories[i].Books[j].Price);
                        }
                        else
                        {
                            printf("We Don't Have Enough copies\n");
                            return;
                        }

                    }

                }
        }
    }
}

void moveBook()
{

    int sourceIndex;
    int destinationIndex;
    char bookName[50];
    printf("\n\tThis Is Our Categories\n\n");
    for(int index=0;index<number_Of_Categories;index++)
    {
        printf("\t\t%d-%s\n",index+1,categories[index].CategoryName);
    }
        printf("Enter The Name Of The Book You Need To Move: ");
        scanf(" %[^\n]s",bookName);
        printf("Enter The Number Of The Category You Need To Move The Book From It: ");
        scanf(" %d",&sourceIndex);
        printf("Enter The Number Of The Category You Need To Move The Book To It: ");
        scanf(" %d",&destinationIndex);
    if((sourceIndex>=0&&sourceIndex<=number_Of_Categories)&&(destinationIndex>=0&&destinationIndex<=number_Of_Categories))
    {
        for(int i=0;i<categories[sourceIndex-1].number_Of_Books;i++)
        {
            if(strcmp(bookName,categories[sourceIndex-1].Books[i].Name)==0)
            {
                categories[destinationIndex-1].Books=realloc(categories[destinationIndex-1].Books,(categories[destinationIndex-1].number_Of_Books+1)*sizeof(Book));
                categories[destinationIndex-1].Books[categories[destinationIndex-1].number_Of_Books]=categories[sourceIndex-1].Books[i];
                categories[destinationIndex-1].number_Of_Books++;
                for(int j=i;j<categories[sourceIndex-1].number_Of_Books-1;j++)
                {
                    categories[sourceIndex-1].Books[j]=categories[sourceIndex-1].Books[j+1];
                }
                categories[sourceIndex-1].number_Of_Books--;
            }
            else
            {
                printf("We Don't Have This Book\n");
            }

        }
        printf("We Move %s Book From %s Category To %s Category\n",bookName,categories[sourceIndex-1].CategoryName,categories[destinationIndex-1].CategoryName);
    }
    else
    {
        printf("Enter Valid Number\n");
    }
}
void freeMemory()
{
    for(int i=0;i<number_Of_Categories;i++)
    {
        free(categories[i].Books);
    }
    free(categories);
}
void editCategory()
{
    char oldName [50];
    char newName [50];
    int flag=0;
    printf("Enter The Old Name Of The Category You Want To Change: ");
    scanf(" %[^\n]s",oldName);
    printf("Enter The New Name: ");
    scanf(" %[^\n]s",newName);
    for(int i=0; i<number_Of_Categories;i++)
    {
        if(strcmp(oldName,categories[i].CategoryName)==0)
        {
            strcpy(categories[i].CategoryName, newName);
            flag=1;
        }
    }
    if(flag==0)
    {
        printf("We Don't Have This Category\n");
    }
    else
    {
        printf("The Name Updated Successfully\n");
    }
}
void editBook()
{
    int categoryChoice;
    int bookOption;
    char bookName[50];
    int bookIndex;
    printf("The Book You Need To Edit In Which Category?\n");
    for(int index=0;index<number_Of_Categories;index++)
    {
        printf("\t%d-%s\n",index+1,categories[index].CategoryName);
    }
    printf("Enter The Number Of Category: ");
    scanf("\t%d",&categoryChoice);
    for(int i=0;i<categories[categoryChoice-1].number_Of_Books;i++)
    {
        printf("\t%d-%s\n",i+1,categories[categoryChoice-1].Books[i].Name);
    }

    printf("Enter The Number Of The Book: ");
    scanf("%d",&bookIndex);
    printf("This Is The Options You Can Edit\n");
    printf("    1-Name\n    2-Price\n    3-Quantity\n");
    printf("Enter The Option You Need To Change: ");
    scanf("\t%d",&bookOption);
    if(bookOption==1||bookOption==2||bookOption==3)
    {
        if(bookOption==1)
        {
            char newBookName[50];
            printf("\tEnter The New Name: ");
            printf("\t");
            scanf(" %[^\n]s",newBookName);
            strcpy(categories[categoryChoice-1].Books[bookIndex-1].Name,newBookName);
        }
        else if(bookOption==2)
        {
            int newPrice;
            printf("\tEnter The New Price: ");
            printf("\t");
            scanf("%d",&newPrice);
            categories[categoryChoice-1].Books[bookIndex-1].Price=newPrice;

        }
        else if(bookOption==3)
        {
            int newQuantity;
            printf("\tEnter The New Quantity: ");
            printf("\t");
            scanf("%d",&newQuantity);
            categories[categoryChoice-1].Books[bookIndex-1].Quantity=newQuantity;
        }
    }
    else
    {
        printf("Enter Valid Option\n");
        editBook();
    }
}
void menu()
{
    int choice = 1;
    int maxChoice = 8;
    int ch;

    while (1) {
        system("cls");
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int x = (screenWidth - 10) / 2;
        gotoxy(15, 5,3);
        SetColor(14);
        printf("Your Book");
        SetColor(15);


        for (int i = 1; i <= maxChoice; i++) {
            gotoxy(10, 6 + i,8);
            if (i == choice) {
                SetColor(13);
            } else {
                SetColor(15);
            }
            printf(i == choice ? ">> %d. " : "%d. ", i);

            switch (i) {
                case 1:
                    printf("Display");
                    break;
                case 2:
                    printf("Add New Category");
                    break;
                case 3:
                    printf("Add New BOOK");
                    break;
                case 4:
                    printf("Change Book Category");
                    break;
                case 5:
                    printf("Make Order");
                    break;
                case 6:
                    printf("Edit Category Name");
                    break;
                case 7:
                    printf("Edit Book");
                    break;
                case 8:
                    printf("Free Memory");
                    break;


            }
        }




        ch = _getch();
        switch (ch) {
            case 72:
                if (choice > 1) {
                    choice--;
                } else {
                    choice = maxChoice;
                }
                break;
            case 80:
                if (choice < maxChoice) {
                    choice++;
                } else {
                    choice = 1;
                }
                break;
            case 13:
                switch (choice) {
                    case 1:
                        system("cls");
                        gotoxy(50,5,10);
                        printf(" My Library \n");
                        Display();
                        system("pause");
                        break;
                    case 2:
                        system("cls");
                        AddCategory();
                        system("pause");
                        break;
                    case 3:
                        system("cls");
                        AddBook();
                        system("pause");
                        break;
                    case 4:
                        system("cls");
                        moveBook();
                        system("pause");
                        break;
                    case 5:
                        system("cls");
                        MakeOrder();
                        system("pause");
                        break;
                    case 6:
                        system("cls");
                        editCategory();
                        system("pause");
                        break;
                    case 7:
                        system("cls");
                        editBook();
                        system("pause");
                        break;
                    case 8:
                        system("cls");
                        freeMemory();
                        system("pause");
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}


//New Category

int main()
{
    menu();

    return 0;
}
