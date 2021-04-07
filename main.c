#include <stdio.h>
#include <windows.h>

//Global
//to keep how much part of ship each player destroy and also to know the winner
int Score[2];

//Declaration
int Menu(void);

int main()
{
    printf("_______ Bataille Navale _______\n\n");
    Menu();
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