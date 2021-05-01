#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//Structs
typedef struct
{
    int x,y;
}position;
typedef struct
{
    char name[10];
    //position of each box
    position pos[3];
}Navire;
typedef struct
{
    char name[20];
    int missiles;
    int time;
}Winner;

//Function Declaration
void Title();
void TitleAscii();
void BoatAscii();
int Menu(void);
void DisplayGrid(void);
void SetWinner(void);
void GetWinner(void);
void HowToPlay(void);

//Global
//to keep how much part of ship each player destroy and also to know the winner
Winner player2;
/*deleted after */char data[6][6]={{'A','A','A',' ',' ',' '},
                                   {' ',' ',' ',' ',' ',' '},
                                   {' ',' ',' ','C',' ',' '},
                                   {'B',' ',' ',' ','C',' '},
                                   {'B',' ',' ',' ',' ','C'},
                                   {'B',' ',' ',' ',' ',' '}};

int main()
{
    int result;

    do
    {
        Title();
        result = Menu();

        switch(result)
        {
            case 1:
                //Testing
                DisplayGrid();
                printf("Missiles and Time : ");scanf("%d%d",&player2.missiles,&player2.time);
                SetWinner();
                GetWinner();
                break;
            case 2: HowToPlay(); break;
            case 0: printf("\nGood Bye!\n"); break;
        }
        getch();
        system("cls");
    } while (result);

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

void SetWinner()
{
    printf("\n****** Winner ******\n\n");
    printf("    Your Name : "); fflush(stdin); gets(player2.name);
}

void GetWinner()
{
    float score;

    score = player2.time < player2.missiles ? (float)player2.missiles / (float)player2.time : (float)player2.time / (float)player2.missiles;
    score *= 10;

    printf("\n****** Winner ******\n\n");
    printf("    Name  : %s\n",player2.name);
    printf("    Score : %.0f\n",score);
}

void HowToPlay()
{
    printf("\nHow To Play : Bataille Navale\n\n");
    printf("Au d\x82""but du jeu, chaque joueur place \x85 sa guise tous les bateaux sur sa grille de fa\x87on strat\x82gique. ");
    printf("Le but \x82tant de compliquer au maximum la tache de son adversaire, c'est-\x85-dire d\x82truire tous vos navires.");
    printf("\nLorem ipsum dolor sit amet, consectetur adipiscing elit, "
    "sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, "
    "quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. "
    "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur."
    " Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.\n");
}