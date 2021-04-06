#include <stdio.h>

//Global

//Declaration
int Menu(void);

int main()
{
    printf("\\_____Bataille Navale_____/\n\n");
    Menu();
    return 0;
}

//Display a Menu to let the user choose what to do
int Menu()
{
    int choice, error;

    printf("Menu :\n\n");
    printf("1.Play\n");
    printf("0.Exit\n");

    do
    { 
        printf("\nChoice : ");
        fflush(stdin);
        error = !scanf("%d",&choice);

        if(error)
            printf("choice incorrect!\ntry again\n");
    } while (error);
    
    return choice;
}