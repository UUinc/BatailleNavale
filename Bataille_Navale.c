#include <stdio.h>
#include <stdlib.h>
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

//Function Declaration
//UI
void Title(void);
void TitleAscii(void);
void BoatAscii(void);
int Menu(void);
void DisplayGrid(int choice, int posX);
//Ships Placing
void PlaceShips(int player);
void SetShip(char name, char data[][6]);
//Ships Destroying
void DestroyShips(int player);
void DestroyShips_Multiplayer(void);
int MissileLauncher(int x, int y, int nbrCases, int player);
void SetScore(void);
void GetScore(void);
//How To Play
void HowToPlay(void);
//Settings
void Settings(void);
void DarkMode(int on);
//About
void About(void);
//Tools
void InitData(char str[][6],int len,char c);
void GetCoordinate(int *x, int *y, int posX);
int CoordinateConverter(int *x, int *y, char *v);
void SetPlayersNickname(void);
void SetName(char *title, char *_name);
void DeleteBlankSpaces(char *s);

//Global
GameTime gameTime;
Winner _player[2];

int darkMode=0; //0 = off - 1 = on
char dataShip[6][6], dataMissile[6][6];
char dataShip2[6][6], dataMissile2[6][6];
int scoreMissile=36;

int main()
{
    int result;
    
    //Change Application Font size
    FontSize(28);
    //Maximize Application in Start
    MaximizeOutputWindow();
    //Game Main Title
    system("title Bataille Navale");

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
                //Initialize string by spaces
                InitData(dataShip,6,' ');
                InitData(dataMissile,6,' ');
                //Initialize score
                _player[0].score = 0;
                clrscr();
                //Set Names
                SetPlayersNickname();
                //Player 1 place ships
                PlaceShips(0);
                getch();
                //Player 2 destroy ships
                DestroyShips(0);
                //Set and Get Score
                SetScore();
                GetScore();
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
                SetPlayersNickname();
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
            case 3: HowToPlay(); break;
            case 4: /*Highscore();*/printf("Highscore\n"); break;
            case 5: Settings(); break;
            case 6: About(); break;
            case 0: exit(0);
        }
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

    gotoXY(43,wherey());printf("1.Play Classic\n");
    gotoXY(43,wherey());printf("2.Play Extended\n");
    gotoXY(43,wherey());printf("3.How To Play\n");
    gotoXY(43,wherey());printf("4.Highscore\n");
    gotoXY(43,wherey());printf("5.Settings\n");
    gotoXY(43,wherey());printf("6.About\n");
    gotoXY(43,wherey());printf("0.Exit\n");

    do
    {
        gotoXY(42,wherey()+1);
        printf("Choice : ");
        fflush(stdin);
        error = !scanf("%d",&choice);
        error = error || choice > 6 || choice < 0 ? 1 : 0;
        
        if(error)
        {
            gotoXY(40,wherey());textcolor(RED);printf("\achoice incorrect!");textcolor(WHITE);
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
void PlaceShips(int player)
{
    int i;
    char navire[3]={'A','B','C'};
    char _name[20];

    strcpy(_name,_player[player].name);

    for(i=0; i<3; i++)
    {
        system("cls");
        gotoXY(40,wherey());printf("%s (place the ships)\n\n",_name);
        DisplayGrid(player,37);
        if(player == 0) SetShip(navire[i], dataShip);
        else SetShip(navire[i], dataShip2);
    }
    system("cls");
    gotoXY(42,wherey()); textcolor(LIGHTGREEN); printf("Ships are placed!\n\n"); textcolor(WHITE);
    DisplayGrid(player,37);
    gotoXY(44,wherey()); printf("Press any Key!\n");
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
                gotoXY(40,wherey()+1); printf("Rotation :\n");
                //Vertical Up
                if(pos.x>=2 && data[pos.x-1][pos.y] == ' ' && data[pos.x-2][pos.y] == ' '){gotoXY(40,wherey()); printf(" 0.Vertical Up\n"); available[i++]=0;}
                //Vertical Down
                if(pos.x<4 && data[pos.x+1][pos.y] == ' ' && data[pos.x+2][pos.y] == ' '){gotoXY(40,wherey()); printf(" 1.Vertical Down\n"); available[i++]=1;}
                //Horizontal Right
                if(pos.y<4 && data[pos.x][pos.y+1] == ' ' && data[pos.x][pos.y+2] == ' '){gotoXY(40,wherey()); printf(" 2.Horizontal Right\n"); available[i++]=2;}
                //Horizontal Left
                if(pos.y>=2 && data[pos.x][pos.y-1] == ' ' && data[pos.x][pos.y-2] == ' '){gotoXY(40,wherey()); printf(" 3.Horizontal Left\n"); available[i++]=3;}
                //Diagonal Up
                if(pos.x>=2 && pos.y>=2 && data[pos.x-1][pos.y-1] == ' ' && data[pos.x-2][pos.y-2] == ' '){gotoXY(40,wherey()); printf(" 4.Diagonal Up\n"); available[i++]=4;}
                //Diagonal Down
                if(pos.x<4 && pos.y<4 && data[pos.x+1][pos.y+1] == ' ' && data[pos.x+2][pos.y+2] == ' '){gotoXY(40,wherey()); printf(" 5.Diagonal Down\n"); available[i++]=5;}
                //Diagonal Reverse Down
                if(pos.x<4 && pos.y>=2 && data[pos.x+1][pos.y-1] == ' ' && data[pos.x+2][pos.y-2] == ' '){gotoXY(40,wherey()); printf(" 6.Diagonal Reverse Down\n"); available[i++]=6;}
                //Diagonal Reverse Up
                if(pos.x>=2 && pos.y<4 && data[pos.x-1][pos.y+1] == ' ' && data[pos.x-2][pos.y+2] == ' '){gotoXY(40,wherey()); printf(" 7.Diagonal Reverse Up\n"); available[i++]=7;}
                if(available[0] == -1)
                {
                    // Move to beginning of previous line and Clear entire line
                    textcolor(RED); gotoXY(34,wherey()); printf("\x1b[1F\x1b[2K\aimpossible to set a navy here\n"); textcolor(WHITE);
                    delay(1000); printf("\x1b[1F\x1b[2K\x1b[1F\x1b[2K");
                    goto GetCoord;
                }
                j = i;
                do {
                    getRotation:
                    fflush(stdin);
                    gotoXY(40,wherey()+1); printf("choice : ");
                    if(scanf("%d",&rotation)) break;
                    textcolor(RED); gotoXY(38,wherey()); printf("\aError! rotation incorrect\n"); textcolor(WHITE);
                    delay(1000); printf("\x1b[1F\x1b[2K\x1b[1F\x1b[2K\x1b[1F");
                }while(1);
                //check if the rotation selected is available
                for(i=j;i>0;i--) if(rotation == available[i-1]) break;
                if(i) break;
                textcolor(RED); gotoXY(38,wherey()); printf("\aError! rotation incorrect\n"); textcolor(WHITE);
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
                textcolor(RED); gotoXY(32,wherey()+1); printf("\aYou can't set navy close to other navy\n"); textcolor(WHITE);
                delay(1000); printf("\x1b[1F\x1b[2K\x1b[2F\x1b[2K");
            }
            else
            {
                textcolor(RED); gotoXY(37,wherey()+1); printf("\aThe ship block is occupied!\n"); textcolor(WHITE);
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
        gotoXY(38,wherey());printf("%s (destroy the ships)\n\n",_name);
        DisplayGrid(player+2,37);
        GetCoordinate(&pos.x,&pos.y, 37);
    } while (MissileLauncher(pos.x,pos.y,9,player));
    system("cls");
    gotoXY(47,wherey()); textcolor(LIGHTGREEN); printf("Good Job!\n\n"); textcolor(WHITE);
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
        gotoXY(43,wherey());printf("(destroy the ships)\n\n");
        //Display Player 1 Grid
        displayY = wherey();
        textcolor(player?WHITE:LIGHTGREEN); gotoXY(25,displayY);printf("%s\n\n",_player[0].name); 
        textcolor(WHITE); DisplayGrid(2,16);
        //Display Player 2 Grid
        textcolor(player?LIGHTGREEN:WHITE); gotoXY(74,displayY);printf("%s\n\n",_player[1].name);
        textcolor(WHITE); DisplayGrid(3,65);
        //Get Coordinate
        GetCoordinate(&pos.x,&pos.y,player?65:16);
        r = MissileLauncher(pos.x,pos.y,9,1-player);
        if(!r) break;
        if(r == -1) player = 1-player; //change player turn
    }while (1);
    system("cls");
    gotoXY(49,wherey()); textcolor(LIGHTGREEN); printf("Awesome!\n\n"); textcolor(WHITE);
    //Display Player 1 Grid
    displayY = wherey();
    gotoXY(25,displayY);printf("%s\n\n",_player[0].name); 
    DisplayGrid(2,16);
    //Display Player 2 Grid
    gotoXY(74,displayY);printf("%s\n\n",_player[1].name);
    DisplayGrid(3,65);

    gotoXY(40,wherey()+1);
    textcolor(LIGHTGREEN); printf("%s Won",_player[player].name);
    textcolor(WHITE); printf(" - ");
    textcolor(RED); printf("%s Lost",_player[1-player].name);
    textcolor(WHITE);
    gotoXY(44,wherey()+1);printf("Press any key!");
}
int MissileLauncher(int x, int y, int nbrCases, int player)
{
    static int hits=0, hits2=0;

    if(player == 0)
    {
        if(dataMissile[x][y] == ' ')
        {
            if(dataShip[x][y] == ' ' || dataShip[x][y] == '#')
            {
                dataMissile[x][y] = 'X';
                //Score
                scoreMissile-= 10; 
                return -1;
            }
            else
            {
                dataMissile[x][y] = dataShip[x][y];
                //Score
                _player[0].score += scoreMissile;
                scoreMissile = 36;
                
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
            gotoXY(38,wherey()+1);
            printf("\aThe Box already striked!\n");
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
                //Score
                scoreMissile-= 10;
                return -1;
            }
            else
            {
                dataMissile2[x][y] = dataShip2[x][y];
                //Score
                _player[0].score += scoreMissile;
                scoreMissile = 36;
                
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
            gotoXY(38,wherey()+1);
            printf("\aThe Box already striked!\n");
            textcolor(WHITE);
            delay(1000);
            return 1;
        }
    }
}
void SetScore()
{
    gameTime.end = time(&gameTime.end);
    _player[0].time = difftime(gameTime.end,gameTime.start);

    if(_player[0].time < 10) _player[0].time += 100;
    else if(_player[0].time < 30) _player[0].score += 75;
    else if(_player[0].time < 60) _player[0].score += 50;
    else if(_player[0].time < 100) _player[0].score += 25;
    else _player[0].score += 5;    
}
void GetScore()
{
    delay(500); clrscr();
    gotoXY(40,wherey());printf("****** Scores ******\n\n");
    gotoXY(40,wherey());printf("    %s : %d\n",_player[0].name, _player[0].score);
    //Add other score from local DB
    //here...
    printf("\n\n");
    gotoXY(42,wherey()); printf("Press any Key!\n");
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

    gotoXY(44,wherey());printf("Press any Key!");
    getch();
}
//Settings Functions Definition
void Settings(void)
{
    int choice, error;

    do
    {
        system("cls");
        gotoXY(47,wherey()); printf("Settings\n\n");

        //settings menu
        gotoXY(46,wherey());printf("1.Dark Mode\n");
        gotoXY(46,wherey());printf("0.Exit\n");

        do
        {
            gotoXY(46,wherey()+1);
            printf("Choice : ");
            fflush(stdin);
            error = !scanf("%d",&choice);
            error = error || choice > 1 || choice < 0 ? 1 : 0;
            
            if(error)
            {
                gotoXY(40,wherey());textcolor(RED);printf("\achoice incorrect!");textcolor(WHITE);
                delay(1000); printf("\x1b[2K\x1b[1F\x1b[2K\x1b[1F");
            }
        } while (error);

        gotoXY(43,wherey()+1); printf("ON  : 1 | OFF : 0\n\n");

        switch(choice)
        {
            case 1:
                gotoXY(40,wherey()); printf("Dark Mode : ");
                do{
                    scanf("%d",&darkMode);
                    if(darkMode==0 || darkMode==1) break;
                    textcolor(RED); gotoXY(40,wherey());
                    printf("\aError! Only ( ON : 1 or OFF : 0 )");
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
//About Functions Definition
void About()
{
    system("cls");
    gotoXY(49,wherey()); printf("About\n\n");
    gotoXY(33,wherey()); printf("This Game was made for a school project\n\n");
    gotoXY(42,wherey()); printf("Developed by :\n");

    gotoXY(44,wherey());   printf("-YAHYA LAZREK");
    gotoXY(44,wherey()+1); printf("-BADR TEBAA");
    gotoXY(44,wherey()+1); printf("-ZAKARIA MESSOUS");
    gotoXY(44,wherey()+1); printf("-SALMA ROUIBAH\n\n");

    gotoXY(38,wherey()); printf("*** Special Thanks To ***\n");
    gotoXY(30,wherey());printf(" Mr.MEHDI EL HAIRIBI and Mr.YOUSSEF MOURDI");

    gotoXY(22,wherey()+2); printf("Github (Code Source): https://github.com/UUinc/BatailleNavale\n\n");

    gotoXY(44,wherey());printf("Press any Key!");
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
        gotoXY(posX,wherey()); printf("Give Coordinate : "); fflush(stdin); gets(coordinate);
        if(CoordinateConverter(x,y,coordinate)) break;
        gotoXY(posX-3,wherey()); textcolor(RED); printf("\aIncorrect Coordinate! (ex: A1)\n"); textcolor(WHITE);
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
void SetPlayersNickname()
{
    gotoXY(40,wherey());printf("Whats is your nickname ?\n");
    SetName("Player 1", _player[0].name);
    gotoXY(40,wherey());printf("-Player 2 : ");
    SetName("Player 2", _player[1].name);
}
void SetName(char *title, char *_name)
{
    while(1)
    {
        gotoXY(40,wherey());printf(" -%s : ",title); fflush(stdin); gets(_name);
        DeleteBlankSpaces(_name);
        if(strcmp(_name,"")!=0) break;
        textcolor(RED); gotoXY(32, wherey()+1); printf("\aError! please enter a valid nickname\n"); textcolor(WHITE);
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