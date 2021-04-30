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
void Title();
void TitleAscii();
void BoatAscii();
int Menu(void);
void DisplayGrid(void);

int main()
{
    printf("_______ Bataille Navale _______\n\n");
    
    Title();
    
    Menu();

    DisplayGrid();

    printf("\nGood Bye!\n");
    getch();

    return 0;
}

void Title()
{
    TitleAscii();
    BoatAscii();
}
void TitleAscii()
{
    printf("___  ____ ___ ____ _ _    _    ____    _  _ ____ _  _ ____ _    ____\n");
    printf("|__] |__|  |  |__| | |    |    |___    |\\ | |__| |  | |__| |    |___\n");
    printf("|__] |  |  |  |  | | |___ |___ |___    | \\| |  |  \\/  |  | |___ |___\n\n\n");
}
void BoatAscii()
{
    printf("              |    |    |\n");
    printf("             )_)  )_)  )_)\n");
    printf("            )___))___))___)\\\n");
    printf("           )____)____)_____)\\\\\n");
    printf("         _____|____|____|____\\\\\\__\n");
    printf("---------\\                   /---------\n");
    printf("  ^^^^^ ^^^^^^^^^^^^^^^^^^^^^\n");
    printf("    ^^^^      ^^^^     ^^^    ^^\n");
    printf("         ^^^^      ^^^\n\n");
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
void DisplayGrid()
{
    int i, j, k, l;
    char grid[14][26]={{' ',' ',' ','1',' ',' ',' ','2',' ',' ',' ','3',' ',' ',' ','4',' ',' ',' ','5',' ',' ',' ','6',' ',' '},
                       {' ','\xDA','\xC4','\xC4','\xC4','\xC2','\xC4','\xC4','\xC4','\xC2','\xC4','\xC4','\xC4','\xC2','\xC4','\xC4','\xC4','\xC2','\xC4','\xC4','\xC4','\xC2','\xC4','\xC4','\xC4','\xBF'},
                       {'A','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3'},
                       {' ','\xC3','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xB4'},
                       {'B','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3'},
                       {' ','\xC3','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xB4'},
                       {'C','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3'},
                       {' ','\xC3','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xB4'},
                       {'D','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3'},
                       {' ','\xC3','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xB4'},
                       {'E','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3'},
                       {' ','\xC3','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xC5','\xC4','\xC4','\xC4','\xB4'},
                       {'F','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3',   ' ',   ' ',   ' ','\xB3'},
                       {' ','\xC0','\xC4','\xC4','\xC4','\xC1','\xC4','\xC4','\xC4','\xC1','\xC4','\xC4','\xC4','\xC1','\xC4','\xC4','\xC4','\xC1','\xC4','\xC4','\xC4','\xC1','\xC4','\xC4','\xC4','\xD9'}};
    
    //Change Grid Value
    for(i=2,k=0; i<14; i+=2,k++)
    {
        for(j=3,l=0;j<26;j+=4,l++)
        {
            grid[i][j] = data[k][l];
        }
    }

    //Display Grid
    for(i=0,k=0; i<14; i++)
    {
        for(j=0,l=0; j<26; j++)
        {
            printf("%c",grid[i][j]);
        }
        printf("\n");
    }
}