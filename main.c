#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

//Structs
typedef struct
{
    time_t start;
    time_t end;
}GameTime;

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
//UI
void Title();
void TitleAscii();
void BoatAscii();
int Menu(void);
void DisplayGrid(int choice);
//Player 1
//Player 2
void Player2();
int MissileLauncher(int x, int y, int nbrCases);
int CoordinateConverter(int *x, int *y, char v[]);
void SetWinner(void);
void GetWinner(void);
//How To Play
void HowToPlay(void);
//Settings
void Settings(void);
void DarkMode(int on);
//Tools
void DeleteBlankSpaces(char *s);

//Global
//to keep how much part of ship each player destroy and also to know the winner
GameTime gameTime;
Winner player2;
int darkMode=0;//0 = off - 1 = on
char data[6][6]={{'A','A','A',' ',' ',' '},
                 {' ',' ',' ',' ',' ',' '},
                 {' ',' ',' ','C',' ',' '},
                 {'B',' ',' ',' ','C',' '},
                 {'B',' ',' ',' ',' ','C'},
                 {'B',' ',' ',' ',' ',' '}};

char data2[6][6]={{' ',' ',' ',' ',' ',' '},
                  {' ',' ',' ',' ',' ',' '},
                  {' ',' ',' ',' ',' ',' '},
                  {' ',' ',' ',' ',' ',' '},
                  {' ',' ',' ',' ',' ',' '},
                  {' ',' ',' ',' ',' ',' '}};

int main()
{
    int result;
    //Game Background Color
    textcolor(WHITE);
    
    do
    {
        DarkMode(darkMode);
        system("cls");
        Title();
        result = Menu();

        switch(result)
        {
            case 1:
                DisplayGrid(0);
                // //Player 1 funtion here ...

                // //Player 2
                // gameTime.start = time(0);
                // Player2 function here ...
                Player2();
                // gameTime.end = time(0);
                break;
            case 2: HowToPlay(); break;
            case 3: Settings(); break;
            case 0: exit(0);
        }
        getch();
        system("cls");
    } while (result);

    return 0;
}
//UI Functions Declaration
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
    textcolor(BROWN);printf("              |    |    |\n");
    textcolor(WHITE);printf("             )_)  )_)  )_)\n");
    printf("            )___))___))___)");
    textcolor(BROWN);printf("\\\n");
    textcolor(WHITE);printf("           )____)____)_____)");
    textcolor(BROWN);printf("\\\\\n");
    textcolor(BROWN);printf("         _____|____|____|____\\\\\\__\n");
    textcolor(WHITE); printf("---------");
    textcolor(BROWN);printf("\\___________________/");
    textcolor(WHITE);printf("---------\n");
    printf("  ^^^^^ ^^^^^^^^^^^^^^^^^^^^^\n");
    printf("    ^^^^      ^^^^     ^^^    ^^\n");
    printf("         ^^^^      ^^^\n\n");
    textcolor(WHITE);
}
//Display a Menu to let the user choose what to do
int Menu()
{
    int choice, error;

    printf("Menu :\n\n");
    printf("1.Play\n");
    printf("2.How To Play\n");
    printf("3.Settings\n");
    printf("0.Exit\n");

    do
    {
        printf("\nChoice : ");
        fflush(stdin);
        error = !scanf("%d",&choice);
        error = error || choice > 3 || choice < 0 ? 1 : 0;
        if(error)
            printf("choice incorrect!\n");
    } while (error);

    return choice;
}
//Display Matrix 6 x 6
//choice (0==data, 1==data2)
void DisplayGrid(int choice)
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
            if(!choice) grid[i][j] = data[k][l];
            else  grid[i][j] = data2[k][l];
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
// Player 1 functions Definition
// Player 2 functions Definition
void Player2()
{
    int x,y;
    char coordinate[2];
    do
    {
        system("cls");
        printf("          Player 2\n\n");
        DisplayGrid(1);
        do
        {
            printf("Give Coordinate : "); fflush(stdin); gets(coordinate);
            if(CoordinateConverter(&x,&y,coordinate)) break;
            printf("Incorrect Coordinate! (ex: A4)\n");
        }while(1);
    } while (!MissileLauncher(x,y,9));
    system("cls");
    printf("          Player 2\n\n");
    DisplayGrid(1);
}
int MissileLauncher(int x, int y, int nbrCases)
{
    static int hits=0;

    if(data2[x][y] == ' ')
    {
        if(data[x][y] == ' ') data2[x][y] = 'X';
        else
        {
            data2[x][y] = data[x][y]; hits++;
        }
    }
    else{ printf("\nThe Box already striked!\n"); getch();}

    return hits >= nbrCases ? 1 : 0;
}
int CoordinateConverter(int *x, int *y, char v[])
{
    int len;
    DeleteBlankSpaces(v); len = strlen(v);

    if(len != 2) return 0;
    if((!(((v[0]>='A' && v[0]<='F') || (v[0]>='a' && v[0]<='f')) && (v[1]>='1' && v[1]<='6')))
    && (!(((v[1]>='A' && v[1]<='F') || (v[1]>='a' && v[1]<='f')) && (v[0]>='1' && v[0]<='6'))))
        return 0;

    if(islower(v[0])) v[0]=toupper(v[0]); if(islower(v[1])) v[1]=toupper(v[1]);

    if(v[0]>='A' && v[0]<='F') *x = v[0]-65; else *x = v[1]-65;
    if(v[0]>='1' && v[0]<='6') *y = (v[0]-'0')-1; else *y = (v[1]-'0')-1;

    return 1;
}
void SetWinner()
{
    printf("\n****** Player 2 ******\n\n");
    printf("    Your Name : "); fflush(stdin); gets(player2.name);
}
void GetWinner()
{
    float score;

    //player2.time = difftime(gameTime.end,gameTime.start);
    score = player2.time > player2.missiles ? (float)player2.missiles / (float)player2.time : (float)player2.time / (float)player2.missiles;
    score *= 100; score = score<1 ? 1 : 0;

    printf("\n****** Score ******\n\n");
    printf("    Name  : %s\n",player2.name);
    printf("    Score : %.0f\n",score);
}
//How To Play Functions Definition
void HowToPlay()
{
    system("cls");
    printf("\nHow To Play : Bataille Navale\n\n");
    printf("Au d\x82""but du jeu, chaque joueur place \x85 sa guise tous les bateaux sur sa grille de fa\x87on strat\x82gique. ");
    printf("Le but \x82tant de compliquer au maximum la tache de son adversaire, c'est-\x85-dire d\x82truire tous vos navires.");
    printf("\nLorem ipsum dolor sit amet, consectetur adipiscing elit, "
    "sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, "
    "quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. "
    "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur."
    " Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.\n");
}
//Settings Functions Definition
void Settings(void)
{
    system("cls");
    printf("Settings\n\n");
    printf("-Dark Mode (1:ON or 0:OFF): ");
    do{
        scanf("%d",&darkMode);
        if(darkMode==0 || darkMode==1) break;
        printf("Error! only (1:ON or 0:OFF)");
    }while(1);
}
void DarkMode(int on)
{
    if(on) { textbackground(BLACK); return;}
    textbackground(CYAN);
}
//Tools
void DeleteBlankSpaces(char *s)
{
	int i,k=0;
 
	for(i=0;s[i];i++)
    {
     	s[i]=s[i+k];
     	if(s[i]==' '|| s[i]=='\t')
     	{
		  k++; i--;
	    }
    }
}