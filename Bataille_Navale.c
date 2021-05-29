#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include "console.h"

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
    char name[20];
    int time;
    int score;
}Winner;

typedef struct
{
    char name[20];
    char score[5];
}scores;

typedef struct
{
    char word[100][100];
}language;

//Function Declaration
//UI
void Splash(void);
void Title(void);
void TitleAscii(void);
void BoatAscii(void);
int Menu(void);
void DisplayGrid(int choice, int posX);
//Mode
int ModeClassic(void);
void PlaceShips_Computer(void);
//Ships Placing
void PlaceShips(int player);
void SetShip(char name, char data[][6]);
//Ships Destroying
void DestroyShips(int player);
void DestroyShips_Multiplayer(void);
int MissileLauncher(int x, int y, int nbrCases, int player, int offset);
void SetPlayerScore(void);
void GetPlayerScore(void);
//How To Play
void HowToPlay(int guide);
//Highscore
void Scores(char name[20]);
int SetScore(char text[50], char* _Mode);
void SetScores(void);
int GetScores(void);
int FindScoreByName(char name[20]);
void SortScores(void);
void DisplayScores(char name[20]);
//Settings
void Settings(void);
void DarkMode(int on);
//About
void About(void);
//Tools
void InitData(char str[][6],int len,char c);
void GetCoordinate(int *x, int *y, int posX);
int CoordinateConverter(int *x, int *y, char *v);
void SetPlayersNickname(int vsComputer);
void SetName(char *title, char *_name);
void DeleteBlankSpaces(char *s);
void Path(int argc, char* argv[], char fileName[20]);
int Random(int first, int last);
//Language
int GetLang(int index);

//Global
GameTime gameTime;
Winner _player[2];
scores Score[100]; int ScoreIndex;
language Lang[2]; //two languages En and Fr

char path[MAX_PATH];
int darkMode=0; //0 = off - 1 = on
char dataShip[6][6], dataMissile[6][6];
char dataShip2[6][6], dataMissile2[6][6];
int MissileHit=0;
int lang=0; //en : 0 | fr : 1

int main(int argc, char* argv[])
{
    int result, classicResult, advancedResult;
    
    //Change Application Font size
    FontSize(28);
    //Maximize Application in Start
    MaximizeOutputWindow();
    //Game Main Title
    system("title Bataille Navale");
    //Set Seed for rand() Function
    srand(time(0));
    //Game Background Color
    textcolor(WHITE);
    //Charge languages
    //Get the Directory Path and set it the global variable path + language files
    Path(argc, argv, "lang\\en.txt");
    GetLang(0);
    Path(argc, argv, "lang\\fr.txt");
    GetLang(1);
    //Get All Scores
    //Get the Directory Path and set it the global variable path + score file name
    Path(argc, argv, "scores.uu");
    ScoreIndex = GetScores();
    //Splash screen
    Splash();
    do
    {
        DarkMode(darkMode);
        system("cls");
        Title();
        result = Menu();

        switch(result)
        {
            case 1:
                //Initialize string by spaces
                InitData(dataShip,6,' ');
                InitData(dataMissile,6,' ');
                //Initialize score
                _player[1].score = 0;
                MissileHit = 0;
                clrscr();
                //Mode vs Computer or vs Human
                classicResult = ModeClassic();
                //go back to home scene
                if(classicResult == 0)
                    break;
                //Vs Computer
                else if(classicResult == 1)
                {
                    clrscr();
                    //Set Name 
                    SetPlayersNickname(1);
                    //Computer place ships
                    gotoXY(35,wherey()+2);
                    printf("%s\n\n",Lang[lang].word[60]); //Computer did Place ships successfully
                    PlaceShips_Computer();
                }
                //Vs Human
                else if(classicResult == 2)
                {
                    clrscr();
                    //Set Names
                    SetPlayersNickname(0);
                    //Player 1 place ships
                    PlaceShips(0);
                }
                getch();
                //Player 2 destroy ships
                DestroyShips(0);
                //Set and Get Score
                SetPlayerScore();
                GetPlayerScore();
                getch();
                break;
            case 2:  
                //Initialize string by spaces
                InitData(dataShip,6,' ');
                InitData(dataMissile,6,' ');
                InitData(dataShip2,6,' ');
                InitData(dataMissile2,6,' ');
                clrscr();
                //Set Names
                SetPlayersNickname(0);
                //Player1 place ships
                PlaceShips(0);
                getch();
                //Player2 place ships
                PlaceShips(1);
                getch();
                //Player1 place ships
                DestroyShips_Multiplayer();
                getch();
                break;
            case 3: HowToPlay(lang); break;
            case 4:
                //Get the Directory Path and set it the global variable path + score file name
                Path(argc, argv, "scores.uu");
                clrscr();
                Scores("");
                getch();
                break;
            case 5: Settings(); break;
            case 6: About(); break;
            case 0: exit(0);
        }
        system("cls");
    } while (result);

    return 0;
}
//UI Functions Declaration
void Splash()
{
    int i;
    textbackground(CYAN);
    clrscr();
    gotoXY(30,10); printf(" _     _ _     _                ___      \n");
    gotoXY(30,wherey()); printf("| |   | | |   | |              / __)_  \n");
    gotoXY(30,wherey()); printf("| |   | | |   | |    ___  ___ | |__| |_ \n");
    gotoXY(30,wherey()); printf("| |   | | |   | |   /___)/ _ \\|  __)  _)\n");
    gotoXY(30,wherey()); printf("| |___| | |___| |  |___ | |_| | |  | |__\n");
    gotoXY(30,wherey()); printf(" \\______|\\______|  (___/ \\___/|_|   \\___)\n");   
    for(i=0; i<=8; i++)
    {
        FontSize(20+i);
        delay(20);
    }
    delay(1000);
    clrscr();                           
}
void Title()
{
    TitleAscii();
    BoatAscii();
}
void TitleAscii()
{
    gotoXY(15,0);printf("___  ____ ___ ____ _ _    _    ____    _  _ ____ _  _ ____ _    ____\n");
    gotoXY(15,1);printf("|__] |__|  |  |__| | |    |    |___    |\\ | |__| |  | |__| |    |___\n");
    gotoXY(15,2);printf("|__] |  |  |  |  | | |___ |___ |___    | \\| |  |  \\/  |  | |___ |___\n\n\n");
}
void BoatAscii()
{
    gotoXY(30,4);textcolor(BROWN);printf("              |    |    |\n");
    gotoXY(30,5);textcolor(WHITE);printf("             )_)  )_)  )_)\n");
    gotoXY(30,6);printf("            )___))___))___)");
    textcolor(BROWN);printf("\\\n");
    gotoXY(30,7);textcolor(WHITE);printf("           )____)____)_____)");
    textcolor(BROWN);printf("\\\\\n");
    gotoXY(30,8);textcolor(BROWN);printf("         _____|____|____|____\\\\\\__\n");
    gotoXY(30,9);textcolor(WHITE); printf("---------");
    textcolor(BROWN);printf("\\___________________/");
    textcolor(WHITE);printf("---------\n");
    gotoXY(30,10);printf("  ^^^^^ ^^^^^^^^^^^^^^^^^^^^^\n");
    gotoXY(30,11);printf("    ^^^^      ^^^^     ^^^    ^^\n");
    gotoXY(30,12);printf("         ^^^^      ^^^\n\n\n");
    textcolor(WHITE);
}
//Display a Menu to let the user choose what to do
int Menu()
{
    int choice, error;

    gotoXY(43,wherey());printf("1.%s\n",Lang[lang].word[0]); //Play Classic
    gotoXY(43,wherey());printf("2.%s\n",Lang[lang].word[1]);//Play Extended
    gotoXY(43,wherey());printf("3.%s\n",Lang[lang].word[2]);  //How To Play
    gotoXY(43,wherey());printf("4.%s\n",Lang[lang].word[3]);       //Scores
    gotoXY(43,wherey());printf("5.%s\n",Lang[lang].word[4]);     //Settings
    gotoXY(43,wherey());printf("6.%s\n",Lang[lang].word[5]);        //About
    gotoXY(43,wherey());printf("0.%s\n",Lang[lang].word[6]);         //Exit

    do
    {
        gotoXY(42,wherey()+1);
        printf("%s : ",Lang[lang].word[7]);//Choice
        fflush(stdin);
        error = !scanf("%d",&choice);
        error = error || choice > 6 || choice < 0 ? 1 : 0;
        
        if(error)
        {
            gotoXY(40,wherey());textcolor(RED);printf("\a%s!",Lang[lang].word[8]);textcolor(WHITE); //incorrect choice
            delay(1000); printf("\x1b[2K\x1b[1F\x1b[2K\x1b[1F");
        }
    } while (error);

    return choice;
}
//Display Matrix 6 x 6
//choice (0==dataShip, 1==dataShip2, 2==dataMissile, 3==dataMissile2)
void DisplayGrid(int choice, int posX)
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
            switch(choice)
            {
                case 0: 
                    grid[i][j] = dataShip[k][l] != '#' ? dataShip[k][l] : ' ';
                    break;
                case 1: 
                    grid[i][j] = dataShip2[k][l] != '#' ? dataShip2[k][l] : ' ';
                    break;
                case 2: 
                    grid[i][j] = dataMissile[k][l];
                    break;
                case 3: 
                    grid[i][j] = dataMissile2[k][l];
                    break;
            }
        }
    }

    //Display Grid
    for(i=0; i<14; i++)
    {
        gotoXY(posX,wherey());
        for(j=0; j<26; j++)
        {
            printf("%c",grid[i][j]);
        }
        printf("\n");
    }
}
//Mode
int ModeClassic()
{
    int result, error;

    do
    {
        gotoXY(45,wherey()); printf("%s\n\n",Lang[lang].word[56]); //Classic Mode

        gotoXY(43,wherey()); printf("1.%s\n",Lang[lang].word[57]);   //Versus Computer
        gotoXY(43,wherey()); printf("2.%s\n",Lang[lang].word[58]);   //Versus Human
        gotoXY(43,wherey()); printf("0.%s\n\n",Lang[lang].word[59]); //Back To Home

        gotoXY(43,wherey()); printf("%s : ",Lang[lang].word[7]);
        error = scanf("%d",&result);

        if(error == 1 && result >= 0 && result < 3) break;
        //Incorrect choice error message
        gotoXY(40,wherey());textcolor(RED);
        printf("\a%s!",Lang[lang].word[8]);textcolor(WHITE); //incorrect choice
        delay(1000); printf("\x1b[2K\x1b[1F\x1b[2K\x1b[1F");
    }while(1);

    return result;
}
void PlaceShips_Computer()
{
    //10 possible position
    //Computer choose randomly
    position pos[5][9];
    int i, _rand;

    //case 1
    //ship A (xy:00 Horizontal right)
    pos[0][0].x = 0; pos[0][0].y = 0; pos[0][1].x = 0; pos[0][1].y = 1; pos[0][2].x = 0; pos[0][2].y = 2;
    //ship B (xy:05 Secondary Diagonal down)
    pos[0][3].x = 0; pos[0][3].y = 5; pos[0][4].x = 1; pos[0][4].y = 4; pos[0][5].x = 2; pos[0][5].y = 3;
    //ship C (xy:05 Secondary Diagonal down)
    pos[0][6].x = 5; pos[0][6].y = 0; pos[0][7].x = 5; pos[0][7].y = 1; pos[0][8].x = 5; pos[0][8].y = 2;

    //case 2
    //ship A (xy:00 Diagonal up)
    pos[1][0].x = 2; pos[1][0].y = 0; pos[1][1].x = 1; pos[1][1].y = 1; pos[1][2].x = 0; pos[1][2].y = 2;
    //ship B (xy:05 Diagonal up)
    pos[1][3].x = 2; pos[1][3].y = 3; pos[1][4].x = 1; pos[1][4].y = 4; pos[1][5].x = 0; pos[1][5].y = 5;
    //ship C (xy:05 Diagonal up)
    pos[1][6].x = 5; pos[1][6].y = 3; pos[1][7].x = 4; pos[1][7].y = 4; pos[1][8].x = 3; pos[1][8].y = 5;

    //case 3
    //ship A (xy:00 Vertical down)
    pos[2][0].x = 2; pos[2][0].y = 1; pos[2][1].x = 3; pos[2][1].y = 1; pos[2][2].x = 4; pos[2][2].y = 1;
    //ship B (xy:05 Horizontal right)
    pos[2][3].x = 3; pos[2][3].y = 3; pos[2][4].x = 3; pos[2][4].y = 4; pos[2][5].x = 3; pos[2][5].y = 5;
    //ship C (xy:05 Horizontal right)
    pos[2][6].x = 0; pos[2][6].y = 2; pos[2][7].x = 0; pos[2][7].y = 3; pos[2][8].x = 0; pos[2][8].y = 4;

    //case 4
    //ship A (xy:00 Diagonal down)
    pos[3][0].x = 2; pos[3][0].y = 0; pos[3][1].x = 3; pos[3][1].y = 1; pos[3][2].x = 4; pos[3][2].y = 2;
    //ship B (xy:05 Horizontal right)
    pos[3][3].x = 0; pos[3][3].y = 1; pos[3][4].x = 0; pos[3][4].y = 2; pos[3][5].x = 0; pos[3][5].y = 3;
    //ship C (xy:05 Vertical down)
    pos[3][6].x = 2; pos[3][6].y = 4; pos[3][7].x = 3; pos[3][7].y = 4; pos[3][8].x = 4; pos[3][8].y = 4;

    //case 5
    //ship A (xy:00 Scondary digonal up)
    pos[4][0].x = 5; pos[4][0].y = 3; pos[4][1].x = 4; pos[4][1].y = 4; pos[4][2].x = 3; pos[4][2].y = 5;
    //ship B (xy:05 Horizontal right)
    pos[4][3].x = 2; pos[4][3].y = 1; pos[4][4].x = 2; pos[4][4].y = 2; pos[4][5].x = 2; pos[4][5].y = 3;
    //ship C (xy:05 Horizontal right)
    pos[4][6].x = 0; pos[4][6].y = 1; pos[4][7].x = 0; pos[4][7].y = 2; pos[4][8].x = 0; pos[4][8].y = 3;

    _rand = Random(0,4);
    for(i=0; i<9; i++)
    {
        dataShip[pos[_rand][i].x][pos[_rand][i].y] = 65+i/3;
    }

    gotoXY(44,wherey()); printf("%s!\n",Lang[lang].word[11]);//Press any Key
}
void PlaceShips(int player)
{
    int i;
    char navire[3]={'A','B','C'};
    char _name[20];

    strcpy(_name,_player[player].name);

    for(i=0; i<3; i++)
    {
        system("cls");
        gotoXY(40,wherey());printf("%s (%s)\n\n",_name,Lang[lang].word[9]);//place the ships
        DisplayGrid(player,37);
        if(player == 0) SetShip(navire[i], dataShip);
        else SetShip(navire[i], dataShip2);
    }
    system("cls");
    gotoXY(42,wherey()); textcolor(LIGHTGREEN); printf("%s!\n\n",Lang[lang].word[10]); textcolor(WHITE); //Ships are placed
    DisplayGrid(player,37);
    gotoXY(44,wherey()); printf("%s!\n",Lang[lang].word[11]);//Press any Key
}
void SetShip(char name, char data[][6])
{
    position pos;
    position posBloc[2];
    int rotation;
    do
    {
        GetCoord:
        GetCoordinate(&pos.x,&pos.y, 37);
        if(data[pos.x][pos.y] == ' ')
        {
            int available[8]={-1}; int i=0,j,k;
            do
            {
                gotoXY(40,wherey()+1); printf("%s :\n",Lang[lang].word[12]); //Rotation
                //Vertical Up
                if(pos.x>=2 && data[pos.x-1][pos.y] == ' ' && data[pos.x-2][pos.y] == ' '){gotoXY(40,wherey()); printf(" 0.%s\n",Lang[lang].word[13]); available[i++]=0;}
                //Vertical Down
                if(pos.x<4 && data[pos.x+1][pos.y] == ' ' && data[pos.x+2][pos.y] == ' '){gotoXY(40,wherey()); printf(" 1.%s\n",Lang[lang].word[14]); available[i++]=1;}
                //Horizontal Right
                if(pos.y<4 && data[pos.x][pos.y+1] == ' ' && data[pos.x][pos.y+2] == ' '){gotoXY(40,wherey()); printf(" 2.%s\n",Lang[lang].word[15]); available[i++]=2;}
                //Horizontal Left
                if(pos.y>=2 && data[pos.x][pos.y-1] == ' ' && data[pos.x][pos.y-2] == ' '){gotoXY(40,wherey()); printf(" 3.%s\n",Lang[lang].word[16]); available[i++]=3;}
                //Diagonal Up
                if(pos.x>=2 && pos.y>=2 && data[pos.x-1][pos.y-1] == ' ' && data[pos.x-2][pos.y-2] == ' '){gotoXY(40,wherey()); printf(" 4.%s\n",Lang[lang].word[17]); available[i++]=4;}
                //Diagonal Down
                if(pos.x<4 && pos.y<4 && data[pos.x+1][pos.y+1] == ' ' && data[pos.x+2][pos.y+2] == ' '){gotoXY(40,wherey()); printf(" 5.%s\n",Lang[lang].word[18]); available[i++]=5;}
                //Secondary Diagonal Down
                if(pos.x<4 && pos.y>=2 && data[pos.x+1][pos.y-1] == ' ' && data[pos.x+2][pos.y-2] == ' '){gotoXY(40,wherey()); printf(" 6.%s\n",Lang[lang].word[19]); available[i++]=6;}
                //Secondary Diagonal Up
                if(pos.x>=2 && pos.y<4 && data[pos.x-1][pos.y+1] == ' ' && data[pos.x-2][pos.y+2] == ' '){gotoXY(40,wherey()); printf(" 7.%s\n",Lang[lang].word[20]); available[i++]=7;}
                if(available[0] == -1)
                {
                    // Move to beginning of previous line and Clear entire line
                    textcolor(RED); 
                    printf("\x1b[1F\x1b[2K");
                    gotoXY(34,wherey());
                    printf("\a%s",Lang[lang].word[21]);//impossible to set a navy here
                    textcolor(WHITE);
                    delay(1000);
                    printf("\x1b[2K\x1b[2F\x1b[2K");
                    goto GetCoord;
                }
                j = i;
                do {
                    getRotation:
                    fflush(stdin);
                    gotoXY(40,wherey()+1); printf("%s : ",Lang[lang].word[7]);//choice
                    if(scanf("%d",&rotation)) break;
                    textcolor(RED); gotoXY(38,wherey()); printf("\a%s\n",Lang[lang].word[22]); textcolor(WHITE);//Error! rotation incorrect
                    delay(1000); printf("\x1b[1F\x1b[2K\x1b[1F\x1b[2K\x1b[1F");
                }while(1);
                //check if the rotation selected is available
                for(i=j;i>0;i--) if(rotation == available[i-1]) break;
                if(i) break;
                textcolor(RED); gotoXY(38,wherey()); printf("\a%s\n",Lang[lang].word[22]); textcolor(WHITE);//Error! rotation incorrect
                delay(1000); printf("\x1b[1F\x1b[2K\x1b[1F\x1b[2K\x1b[1F");
                goto getRotation;
            }while(1);

            //Set
            posBloc[0].x = pos.x; posBloc[0].y = pos.y;
            posBloc[1].x = pos.x; posBloc[1].y = pos.y;
            data[pos.x][pos.y] = name;
            switch(rotation)
            {
                case 0:
                    //Vertical Up
                    posBloc[0].x = pos.x-1;
                    posBloc[1].x = pos.x-2;
                    data[pos.x-1][pos.y] = name; data[pos.x-2][pos.y] = name;
                    break;
                case 1:
                    //Vertical Down
                    posBloc[0].x = pos.x+1;
                    posBloc[1].x = pos.x+2;
                    data[pos.x+1][pos.y] = name; data[pos.x+2][pos.y] = name;
                    break;
                case 2:
                    //Horizontal Right
                    posBloc[0].y = pos.y+1;
                    posBloc[1].y = pos.y+2;
                    data[pos.x][pos.y+1] = name; data[pos.x][pos.y+2] = name;
                    break;
                case 3:
                    //Horizontal Left
                    posBloc[0].y = pos.y-1;
                    posBloc[1].y = pos.y-2;
                    data[pos.x][pos.y-1] = name; data[pos.x][pos.y-2] = name;
                    break;
                case 4:
                    //Diagonal Up
                    posBloc[0].x = pos.x-1; posBloc[0].y = pos.y-1;
                    posBloc[1].x = pos.x-2; posBloc[1].y = pos.y-2;
                    data[pos.x-1][pos.y-1] = name; data[pos.x-2][pos.y-2] = name;
                    break;
                case 5:
                    //Diagonal Down
                    posBloc[0].x = pos.x+1; posBloc[0].y = pos.y+1;
                    posBloc[1].x = pos.x+2; posBloc[1].y = pos.y+2;
                    data[pos.x+1][pos.y+1] = name; data[pos.x+2][pos.y+2] = name;
                    break;
                case 6:
                    //Diagonal Reverse Down
                    posBloc[0].x = pos.x+1; posBloc[0].y = pos.y-1;
                    posBloc[1].x = pos.x+2; posBloc[1].y = pos.y-2;
                    data[pos.x+1][pos.y-1] = name; data[pos.x+2][pos.y-2] = name;
                    break;
                case 7:
                    //Diagonal Reverse Up
                    posBloc[0].x = pos.x-1; posBloc[0].y = pos.y+1;
                    posBloc[1].x = pos.x-2; posBloc[1].y = pos.y+2;
                    data[pos.x-1][pos.y+1] = name; data[pos.x-2][pos.y+2] = name;
                    break;
            }

            //make the bloc next to the navire inavailable to put other navire in them
            //first bloc
            //3 top
            if(data[pos.x-1][pos.y] == ' ' && pos.x>0) data[pos.x-1][pos.y] = '#';
            if(data[pos.x-1][pos.y-1] == ' ' && pos.x>0 && pos.y>0) data[pos.x-1][pos.y-1] = '#';
            if(data[pos.x-1][pos.y+1] == ' ' && pos.x>0 && pos.y<5) data[pos.x-1][pos.y+1] = '#';
            //left right
            if(data[pos.x][pos.y-1] == ' ' && pos.y>0) data[pos.x][pos.y-1] = '#';
            if(data[pos.x][pos.y+1] == ' ' && pos.y<5) data[pos.x][pos.y+1] = '#';
            //3bottom
            if(data[pos.x+1][pos.y] == ' ' && pos.x<5) data[pos.x+1][pos.y] = '#';
            if(data[pos.x+1][pos.y-1] == ' ' && pos.x<5 && pos.y>0) data[pos.x+1][pos.y-1] = '#';
            if(data[pos.x+1][pos.y+1] == ' ' && pos.x<5 && pos.y<5) data[pos.x+1][pos.y+1] = '#';

            for(k=0; k<2; k++)
            {
                //second n third bloc
                //3 top
                if(data[posBloc[k].x-1][posBloc[k].y] == ' ' && posBloc[k].x>0) data[posBloc[k].x-1][posBloc[k].y] = '#';
                if(data[posBloc[k].x-1][posBloc[k].y-1] == ' ' && posBloc[k].x>0 && posBloc[k].y>0) data[posBloc[k].x-1][posBloc[k].y-1] = '#';
                if(data[posBloc[k].x-1][posBloc[k].y+1] == ' ' && posBloc[k].x>0 && posBloc[k].y<5) data[posBloc[k].x-1][posBloc[k].y+1] = '#';
                //left right
                if(data[posBloc[k].x][posBloc[k].y-1] == ' ' && posBloc[k].y>0) data[posBloc[k].x][posBloc[k].y-1] = '#';
                if(data[posBloc[k].x][posBloc[k].y+1] == ' ' && posBloc[k].y<5) data[posBloc[k].x][posBloc[k].y+1] = '#';
                //3bottom
                if(data[posBloc[k].x+1][posBloc[k].y] == ' ' && posBloc[k].x<5) data[posBloc[k].x+1][posBloc[k].y] = '#';
                if(data[posBloc[k].x+1][posBloc[k].y-1] == ' ' && posBloc[k].x<5 && posBloc[k].y>0) data[posBloc[k].x+1][posBloc[k].y-1] = '#';
                if(data[posBloc[k].x+1][posBloc[k].y+1] == ' ' && posBloc[k].x<5 && posBloc[k].y<5) data[posBloc[k].x+1][posBloc[k].y+1] = '#';
            }
            break;
        }
        else
        {
            if(data[pos.x][pos.y] == '#')
            {
                textcolor(RED); gotoXY(32,wherey()+1); printf("\a%s\n",Lang[lang].word[23]); textcolor(WHITE); //You can't set navy close to other navy
                delay(1000); printf("\x1b[1F\x1b[2K\x1b[2F\x1b[2K");
            }
            else
            {
                textcolor(RED); gotoXY(37,wherey()+1); printf("\a%s!\n",Lang[lang].word[24]); textcolor(WHITE); //The ship block is occupied
                delay(1000); printf("\x1b[1F\x1b[2K\x1b[2F\x1b[2K");
            }
        }
    }while(1);
}
void DestroyShips(int player)
{
    position pos;
    char _name[20];

    gameTime.start = time(&gameTime.start);
    strcpy(_name,_player[player==0?1:0].name);

    do
    {
        system("cls");
        gotoXY(38,wherey());printf("%s (%s)\n\n",_name, Lang[lang].word[25]); //destroy the ships
        DisplayGrid(player+2,37);
        GetCoordinate(&pos.x,&pos.y, 37);
    } while (MissileLauncher(pos.x,pos.y,9,player,37));
    system("cls");
    gotoXY(47,wherey()); textcolor(LIGHTGREEN); printf("%s!\n\n",Lang[lang].word[26]); textcolor(WHITE); //Good Job
    DisplayGrid(player+2,37);
}
void DestroyShips_Multiplayer()
{
    int player=0, r;
    int displayY; // to have two Grids in the same horizontal line 
    position pos;

    do
    {
        system("cls");
        gotoXY(43,wherey());printf("(%s)\n\n",Lang[lang].word[25]);//destroy the ships
        //Display Player 1 Grid
        displayY = wherey();
        textcolor(player?WHITE:LIGHTGREEN); gotoXY(25,displayY);printf("%s\n\n",_player[0].name); 
        textcolor(WHITE); DisplayGrid(2,16);
        //Display Player 2 Grid
        textcolor(player?LIGHTGREEN:WHITE); gotoXY(74,displayY);printf("%s\n\n",_player[1].name);
        textcolor(WHITE); DisplayGrid(3,65);
        //Get Coordinate
        GetCoordinate(&pos.x,&pos.y,player?65:16);
        r = MissileLauncher(pos.x,pos.y,9,1-player,player?65:16);
        if(!r) break;
        if(r == -1) player = 1-player; //change player turn
    }while (1);
    system("cls");
    gotoXY(49,wherey()); textcolor(LIGHTGREEN); printf("%s!\n\n",Lang[lang].word[27]); textcolor(WHITE);//Awesome
    //Display Player 1 Grid
    displayY = wherey();
    gotoXY(25,displayY);printf("%s\n\n",_player[0].name); 
    DisplayGrid(2,16);
    //Display Player 2 Grid
    gotoXY(74,displayY);printf("%s\n\n",_player[1].name);
    DisplayGrid(3,65);

    gotoXY(40,wherey()+1);
    textcolor(LIGHTGREEN); printf("%s %s",_player[player].name, Lang[lang].word[28]); //Won
    textcolor(WHITE); printf(" - ");
    textcolor(RED); printf("%s %s",_player[1-player].name, Lang[lang].word[29]); //Lost
    textcolor(WHITE);
    gotoXY(44,wherey()+1);printf("%s!",Lang[lang].word[11]);//Press any key
}
int MissileLauncher(int x, int y, int nbrCases, int player, int offset)
{
    static int hits=0, hits2=0;

    if(player == 0)
    {
        if(dataMissile[x][y] == ' ')
        {
            if(dataShip[x][y] == ' ' || dataShip[x][y] == '#')
            {
                //Score
                MissileHit++; 
                dataMissile[x][y] = 'X';
                return -1;
            }
            else
            {
                dataMissile[x][y] = dataShip[x][y];
                
                hits++;
                if(hits >= nbrCases)
                {
                    hits = 0;
                    return 0;
                }
                return 1;
            }
        }
        else
        {
            textcolor(RED);
            gotoXY(offset,wherey()+1);
            printf("\a%s!\n",Lang[lang].word[30]);//The Box already striked
            textcolor(WHITE);
            delay(1000);
            return 1;
        }
    }
    else
    {
        if(dataMissile2[x][y] == ' ')
        {
            if(dataShip2[x][y] == ' ' || dataShip2[x][y] == '#')
            {
                dataMissile2[x][y] = 'X';
                return -1;
            }
            else
            {
                dataMissile2[x][y] = dataShip2[x][y];
                
                hits2++;
                if(hits2 >= nbrCases)
                {
                    hits2 = 0;
                    return 0;
                }
                return 1;
            }
        }
        else
        {
            textcolor(RED);
            gotoXY(16,wherey()+1);
            printf("\a%s!\n",Lang[lang].word[30]);//The Box already striked
            textcolor(WHITE);
            delay(1000);
            return 1;
        }
    }
}
void SetPlayerScore()
{
    gameTime.end = time(&gameTime.end);
    _player[1].time = difftime(gameTime.end,gameTime.start);
    _player[1].score = (100 - MissileHit*2) - ((_player[1].time - 10) / 3);
    if(_player[1].score>100) _player[1].score = 100;
    else if(_player[1].score<0) _player[1].score = 0;
}
void GetPlayerScore()
{
    char player[56], _score[5];
    int scoreConvInt, result;
    char scoreConvChar[5];

    delay(500); clrscr();

    //file not found
    ScoreIndex = ScoreIndex == -1 ? 0 : ScoreIndex;

    result = FindScoreByName(_player[1].name);

    //Player 2 info
    gotoXY(45,wherey());
    if(_player[1].score >= 80) printf("%s\n",Lang[lang].word[47]);      //Fascinating
    else if(_player[1].score >= 50) printf("%s\n",Lang[lang].word[48]); //Well played
    else if(_player[1].score >= 20) printf("%s\n",Lang[lang].word[49]); //Not bad
    else printf("%s\n",Lang[lang].word[50]);                            //Very bad

    gotoXY(42,wherey()+1); printf("%s       = %s\n",Lang[lang].word[51] ,_player[1].name);   //Nickname
    gotoXY(42,wherey());   printf("%s       = %d\n",Lang[lang].word[52] ,MissileHit+9);      //Missiles
    gotoXY(42,wherey());   printf("%s   = %d s\n",Lang[lang].word[53] ,_player[1].time); //Time elapsed 
    gotoXY(42,wherey());   printf("%s          = %d\n\n",Lang[lang].word[54] ,_player[1].score);//Score
    if(result != -1) //the nickname is found
    {
        gotoXY(42,wherey());
        textcolor(LIGHTRED);
        printf("%s = %s\n\n",Lang[lang].word[55] ,Score[result].score); //previous score
        textcolor(WHITE);
    }

    gotoXY(44,wherey()+2);printf("%s!",Lang[lang].word[11]);//Press any Key
    getch();
    clrscr();

    if(result != -1)
    {
        sscanf(Score[result].score, "%d", &scoreConvInt);
        if(scoreConvInt < _player[1].score)
        {
            sprintf(scoreConvChar,"%ld", _player[1].score);
            strcpy(Score[result].score, scoreConvChar);
        }
        SetScores();
    }
    else
    {
        strcpy(Score[ScoreIndex].name, _player[1].name);
        sprintf(_score,"%ld", _player[1].score);
        strcpy(Score[ScoreIndex].score, _score);

        strcpy(player,Score[ScoreIndex].name);
        strcat(player," ");
        strcat(player,Score[ScoreIndex].score);
        //Add player name and score to local DB
        SetScore(player,"a");

        ScoreIndex++;
    }
    //Sort scores from the highest to the lowest score
    SortScores();
    //Display other score from local DB
    Scores(_player[1].name);
}
//Functions Definition
//How To Play 
//guide = 1 (francais) || guide = 2 (anglais)
void HowToPlay(int guide)
{
    clrscr();
    FontSize(24);

    if (guide == 0) {
        
        gotoXY(52, wherey());
        printf("Welcome to our game!! \n");

        gotoXY(22, wherey()+2);
        printf(" I'll be your guide for today, and walk you through how our game works:  \n");
        gotoXY(10, wherey()+1);
        printf("1-For starters Our game is a board game that requires 2 players (2 humans against each other or 1 human against the robot).\n");
        gotoXY(10, wherey()+1);
        printf("2- The goal is : \n");
        gotoXY(12, wherey());
        printf(" \xAF 1 of the 2 players must place the ships on a grid which will be displayed on the screen by entering the coordinates of the chosen box .\n");
        gotoXY(12, wherey());
        printf(" \xAF While the second player's job is to : 'search and hit the enemy ships' .\n");
        gotoXY(10, wherey()+1);
        printf("3-To win it is necessary that the second player reaches a certain score by destroying all the ships. the first player will win if the second player fails.\n");

        gotoXY(8, wherey()+2);
        textcolor(LIGHTRED); printf(" *PAY ATTENTION:* \n"); textcolor(WHITE);
        gotoXY(10, wherey());
        printf("When placing ships, you will have 3 main choices: horizontal, vertical or diagonal boat.\n ");
        gotoXY(10, wherey());
        printf("The dimension of your boat will be : 3 boxes . ");
        gotoXY(10, wherey()+1);
        printf("While placing the ships, a dialogue box will appear it will make the rotation of your boat easier for you.");
        
    } else if (guide == 1) {
        gotoXY(50, wherey());
        printf("Bienvenue \x85 notre jeu !! \n");

        gotoXY(10, wherey()+2);
        printf("Je serais votre guide pour aujourd'hui , et je vous expliquerai alors comment notre jeu fonctionne :  \n");
        gotoXY(10, wherey()+1);
        printf("1- Bon pour commencer Notre jeu est un jeu de societe qui necessite 2 joueurs( 2 humains l'un contre l'autre ou 1 humain contre le robot) .\n");
        gotoXY(10, wherey()+1);
        printf("2- Le but est : \n");
        gotoXY(12, wherey());
        printf(" \xAF 1 de ces 2 joueurs doit placer les navires sur une grille qui va etre afficher sur l'\x82""cran en entrant les coordonn\x82""es de la case choisi. \n");
        gotoXY(12, wherey());
        printf(" \xAF Alors que le deuxieme joueur a comme travail:'rechercher et toucher les navires adverses'.\n");
        gotoXY(10, wherey()+1);
        printf("3- Pour Gagner il faut que le 2 eme joueur atteint un certain score en detruisant tout les navires.le premier joueur gagnera si le 2 eme echoue.\n");

        gotoXY(8, wherey()+2);
        textcolor(LIGHTRED); printf(" *NOTEZ BIEN:* \n"); textcolor(WHITE);
        gotoXY(10, wherey());
        printf("Lors du placement des navires, vous aurez 3 choix principaux: bateau horizontal, vertical ou diagonal. \n ");
        gotoXY(10, wherey());
        printf("La dimension de votre bateau sera : 3 cases.");
        gotoXY(10, wherey()+1);
        printf("Lors du placement des navires, une bo\x8Cte de dialogue appara\x8Ctra pour vous faciliter la rotation de votre bateau.");
    }
    gotoXY(56,wherey()+2);printf("%s!",Lang[lang].word[11]);//Press any Key
    getch();
    FontSize(28);
}
//Scores
void Scores(char name[20])
{
    gotoXY(50,wherey());
    printf("%s\n\n",Lang[lang].word[31]);//Scores
    DisplayScores(name);
    gotoXY(46,wherey()+2);printf("%s!",Lang[lang].word[11]); //press any key
}
int SetScore(char text[50], char* _Mode)
{
    FILE* file;

    file = fopen(path, _Mode);
    if(file == NULL)
    {
        printf("\a");
        return -1;
    }

    fputs(text,file);
    fputs("\n",file);
    
    fclose(file);
    return 0;
}
void SetScores()
{
    int i;
    char player[56];

    if(ScoreIndex == 0) return;

    strcpy(player,Score[0].name);
    strcat(player," ");
    strcat(player,Score[0].score);
    //Add player name and score to local DB
    SetScore(player,"w");

    for(i=1; i<ScoreIndex; i++)
    {
        strcpy(player,Score[i].name);
        strcat(player," ");
        strcat(player,Score[i].score);
        //Add player name and score to local DB
        SetScore(player,"a");
    }
}
int GetScores()
{
    int i,j,c;
    int len;
    FILE* file;

    file = fopen(path,"r");
    if(file == NULL)
    {   
        printf("\a");
        return -1;
    }

    i = 0;
    while(fgets(Score[i].name, 50, file) != NULL)
    {
        int j,k;
        //remove '\n' character
        len = strlen(Score[i].name) - 1;
        //divide name and score
        for(j=0; Score[i].name[j] != ' ' && j<len; j++);
        Score[i].name[j] = '\0';
        for(j++,k=0;j<len;j++,k++) Score[i].score[k] = Score[i].name[j];
        Score[i].score[k] = '\0';
        i++;
    }
    
    fclose(file);

    return i;
}
int FindScoreByName(char name[20])
{
    int i;
    
    for(i=0; i<ScoreIndex; i++)
    {
        if(strcmp(Score[i].name, name) == 0) return i;
    }
    //Not found
    return -1;
}
void SortScores()
{
    //sort the Scores and set them back to DB
    int i, j, max=-1, maxIndex;
    int _score;
    scores swap; 

    for(i=0; i<ScoreIndex-1; i++)
    {
        for(j=i; j<ScoreIndex; j++)
        {
            sscanf(Score[j].score, "%d", &_score);
            if(max < _score)
            {
                max = _score;
                maxIndex = j;
            }
        }
        swap = Score[i];
        Score[i] = Score[maxIndex];
        Score[maxIndex] = swap;
        max = -1;
    }
    SetScores();
}
void DisplayScores(char name[20])
{
    int i,y,max=0,len;

    if(ScoreIndex == -1 || ScoreIndex == 0)
    {
        gotoXY(47,wherey()+2);
        printf("*%s!*\n",Lang[lang].word[32]);//list empty
        return;
    }
    y = wherey();
    for(i=0; i<ScoreIndex; i++)
    {
        if(strcmp(name,Score[i].name) == 0)
        {
            gotoXY(43,wherey());
            textcolor(LIGHTRED);
            printf("\xAF ");
        }
        else gotoXY(45,wherey());
        len = printf("%s\n",Score[i].name);
        if(max < len) max = len;

        textcolor(WHITE);
    }
    gotoXY(20,y);
    for(i=0; i<ScoreIndex; i++)
    {
        gotoXY(50+max,wherey());
        if(strcmp(name,Score[i].name) == 0) textcolor(LIGHTRED);
        printf("%s\n",Score[i].score);
        textcolor(WHITE);
    }
}
//Settings
void Settings(void)
{
    int choice, error;

    do
    {
        system("cls");
        gotoXY(47,wherey()); 
        printf("%s\n\n",Lang[lang].word[33]);//Settings

        //settings menu
        gotoXY(46,wherey());printf("1.%s\n",Lang[lang].word[34]); //Language
        gotoXY(46,wherey());printf("2.%s\n",Lang[lang].word[35]); //Dark mode
        gotoXY(46,wherey());printf("0.%s\n",Lang[lang].word[6]);  //Exit

        do
        {
            gotoXY(46,wherey()+1);
            printf("%s : ",Lang[lang].word[7]); //Choice
            
            fflush(stdin);
            error = !scanf("%d",&choice);
            error = error || choice > 2 || choice < 0 ? 1 : 0;
            
            if(error)
            {
                gotoXY(40,wherey());
                textcolor(RED);
                printf("\a%s!",Lang[lang].word[8]);//incorrect choice
                textcolor(WHITE);
                delay(1000); printf("\x1b[2K\x1b[1F\x1b[2K\x1b[1F");
            }
        } while (error);

        switch(choice)
        {
            case 1:
                gotoXY(46,wherey()); 
                printf("%s : \n",Lang[lang].word[34]); //Language
                gotoXY(46,wherey()); printf(" 1.En\n");
                gotoXY(46,wherey()); printf(" 2.Fr\n");
                gotoXY(46,wherey());
                printf("%s : ",Lang[lang].word[7]); //Choice
                do{
                    scanf("%d",&lang);
                    if(lang==1 || lang==2)
                    {
                        lang--;
                        break;
                    }
                    textcolor(RED); gotoXY(46,wherey());
                    printf("\a( En : 1 or Fr : 2 )");
                    textcolor(WHITE);
                }while(1);
                break;
            case 2:
                gotoXY(43,wherey()+1); printf("ON  : 1 | OFF : 0\n\n");
                gotoXY(40,wherey());
                printf("%s : ",Lang[lang].word[35]); //Dark mode
                do{
                    scanf("%d",&darkMode);
                    if(darkMode==0 || darkMode==1) break;
                    textcolor(RED); gotoXY(40,wherey());
                    printf("\a( On : 1 or Off : 0 )");
                    textcolor(WHITE);
                }while(1);
                DarkMode(darkMode);
                break;
        }
    }while(choice);
}
void DarkMode(int on)
{
    if(on) { textbackground(BLACK); return;}
    textbackground(CYAN);
}
//About
void About()
{
    system("cls");
    //About
    gotoXY(49,wherey()); printf("%s\n\n",Lang[lang].word[5]);
    //This Game was made for a school project
    gotoXY(33,wherey()); printf("%s\n\n",Lang[lang].word[37]);
    //Developed by
    gotoXY(42,wherey()); printf("%s :\n",Lang[lang].word[38]);

    gotoXY(44,wherey());   printf("-YAHYA LAZREK");
    gotoXY(44,wherey()+1); printf("-BADR TEBAA");
    gotoXY(44,wherey()+1); printf("-ZAKARIA MESSOUS");
    gotoXY(44,wherey()+1); printf("-SALMA ROUIBAH\n\n");
    //Special Thanks To
    gotoXY(38,wherey()); printf("*** %s ***\n",Lang[lang].word[39]);
    gotoXY(30,wherey());printf(" Pr.MEHDI EL HAIRIBI %s Pr.YOUSSEF MOURDI",Lang[lang].word[40]); //and

    gotoXY(22,wherey()+2); printf("Github (Code Source): https://github.com/UUinc/BatailleNavale\n\n");

    gotoXY(44,wherey());printf("%s!",Lang[lang].word[11]);//Press any Key
    getch();
}
//Tools
void InitData(char str[][6],int len,char c)
{
    int i,j;
    
    for(i=0; i<len; i++)
        for(j=0; j<len; j++)
            str[i][j] = c;
}
void GetCoordinate(int *x, int *y, int posX)
{
    char *coordinate = (char *) malloc(sizeof(char));
    do
    {
        gotoXY(posX,wherey()); printf("%s : ",Lang[lang].word[41]); /*Give Coordinate*/ fflush(stdin); gets(coordinate);
        if(CoordinateConverter(x,y,coordinate)) break;
        gotoXY(posX-3,wherey()); textcolor(RED); printf("\a%s! (ex: A1)\n",Lang[lang].word[42]); /*Incorrect Coordinate*/ textcolor(WHITE);
        delay(1000); printf("\x1b[1F\x1b[2K\x1b[1F\x1b[2K");
    }while(1);
    free(coordinate);
}
int CoordinateConverter(int *x, int *y, char *v)
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
void SetPlayersNickname(int vsComputer)
{
    gotoXY(40,wherey());printf("%s ?\n",Lang[lang].word[43]); //Whats is your nickname
    if(vsComputer == 0)
    {
        SetName("1", _player[0].name);
        SetName("2", _player[1].name);
    }
    else
    {
        strcpy(_player[0].name, "Computer");
        SetName("", _player[1].name);
    }
}
void SetName(char *title, char *_name)
{
    while(1)
    {
        gotoXY(40,wherey());printf(" -%s %s : ",Lang[lang].word[44] ,title); /*Player*/ fflush(stdin); gets(_name);
        DeleteBlankSpaces(_name);
        if(strcmp(_name,"")!=0) break;
        textcolor(RED); gotoXY(32, wherey()+1); printf("\a%s\n",Lang[lang].word[45]); /*Error! please enter a valid nickname*/ textcolor(WHITE);
        delay(1000); printf("\x1b[1F\x1b[2K\x1b[2F\x1b[2K");
    }
}
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
void Path(int argc, char* argv[], char fileName[20])
{
    int i,len = strlen(argv[0]);

    if(!len)
    {
        //Error! Empty Path
        printf("\a%s\n",Lang[lang].word[46]);
        return;
    }

    for(i=0; i<=len; i++)
        path[i] = argv[0][i];

    while(path[(len--)-2] != '\\');

    path[len] = '\0';

    strcat(path,fileName);
}
int Random(int first, int last)
{
    int r;
    last += (1-first);
    r = rand()%last + first;
    return r;
}
//Get language
int GetLang(int index)
{
    int i,len;
    FILE* file;

    file = fopen(path,"r");
    if(file == NULL)
    {   
        printf("\a");
        return -1;
    }

    i = 0;
    while(fgets(Lang[index].word[i], 100, file) != NULL)
    {
        //remove '\n' character
        len = strlen(Lang[index].word[i]) - 1;
        if(Lang[index].word[i][len] == '\n')
            Lang[index].word[i][len] = '\0';
        i++;
    }
    
    fclose(file);

    return i;
}