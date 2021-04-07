#include <stdio.h>
#include <conio.h>

//Global
//to keep how much part of ship each player destroy and also to know the winner
int Score[2];

//Declaration
int Menu(void);
void DisplayMatrice(int dimension);

int main()
{
    printf("_______ Bataille Navale _______\n\n");
    
    Menu();

    DisplayMatrice(10);

    printf("\nGood Bye!\n");
    getch();

    return 0;
}

//Display a Menu to let the user choose what to do
int Menu()
{
    int choice, error;

    printf("Menu :\n\n");
    printf("1.Play\n");
    printf("2.How To Play\n");
    printf("0.Exit\n");

    do
    { 
        printf("\nChoice : ");
        fflush(stdin);
        error = !scanf("%d",&choice);
        error = error || choice > 2 || choice < 0 ? 1 : 0;
        if(error)
            printf("choice incorrect!\ntry again\n");
    } while (error);
    
    return choice;
}

//Display Matrix 10 x 10
void DisplayMatrice(int dimension)
{
    int i, j;

    printf("\n");

    for(i=0; i<dimension; i++)
    {
        for(j=0; j<dimension; j++)
        {
            if(j == 0 || j == dimension-1)
            {
                if(i!=0)
                {
                    if(j==0)
                        printf("%c",64+i);
                    else
                        printf("|"); 
                }
                else
                {
                    printf(" ");
                }
            }
            else if(i == 0 || i == dimension-1)
            {
                if(i==0)
                    printf("%d",j);
                else
                    printf("_");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}