#include <stdio.h>
#include <conio.h>

//Global
//to keep how much part of ship each player destroy and also to know the winner
int Score[2];
/*deleted after */char data[6][6]={{'A','A','A',' ',' ',' '},
                                   {' ',' ',' ',' ',' ',' '},
                                   {' ',' ',' ','C',' ',' '},
                                   {'B',' ',' ',' ','C',' '},
                                   {'B',' ',' ',' ',' ','C'},
                                   {'B',' ',' ',' ',' ',' '}};

//Declaration
int Menu(void);
void DisplayMatrice(void);

int main()
{
    printf("_______ Bataille Navale _______\n\n");

    Menu();

    DisplayMatrice();

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

//Display Matrix 6 x 6
void DisplayMatrice()
{
    int i, j, k, l;
    char grid[14][14]={{' ',' ','1',' ','2',' ','3',' ','4',' ','5',' ','6',' '},
                       {' ',' ','_','_','_','_','_','_','_','_','_','_','_',' '},
                       {'A','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
                       {' ','|','-','-','-','-','-','-','-','-','-','-','-','|'},
                       {'B','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
                       {' ','|','-','-','-','-','-','-','-','-','-','-','-','|'},
                       {'C','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
                       {' ','|','-','-','-','-','-','-','-','-','-','-','-','|'},
                       {'D','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
                       {' ','|','-','-','-','-','-','-','-','-','-','-','-','|'},
                       {'E','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
                       {' ','|','-','-','-','-','-','-','-','-','-','-','-','|'},
                       {'F','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
                       {' ','|','_','|','_','|','_','|','_','|','_','|','_','|'}};
    
    for(i=0,k=0; i<14; i++)
    {
        for(j=0,l=0; j<14; j++)
        {
            if(i>1 && j>1 && i%2==0 && j%2==0) 
            {
                printf("%c ",data[k][l]);
                l++; k+= l>5?1:0;
            }
            else printf("%c ",grid[i][j]);   
        }
        printf("\n");
    }
}