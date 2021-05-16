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
int MissileLauncher(int x, int y, int nbrCases, int player);
void SetScore(void);
void GetScore(void);
//How To Play
void HowToPlay(void);
//Settings
void Settings(void);
void DarkMode(int on);
//Tools
void InitData(char str[][6],int len,char c);
void GetCoordinate(int *x, int *y);
int CoordinateConverter(int *x, int *y, char *v);
void DeleteBlankSpaces(char *s);
void MaximizeOutputWindow(void);

//Global
GameTime gameTime;
Winner Player;

int darkMode=0; //0 = off - 1 = on
char dataShip[6][6], dataMissile[6][6];
char dataShip2[6][6], dataMissile2[6][6];
int scoreMissile=36;

int main()
{
    int result;
    
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
                Player.score = 0;
                PlaceShips(0);
                getch();
                DestroyShips(0);
                SetScore();
                GetScore();
                break;
            case 2:  
                //Initialize string by spaces
                InitData(dataShip,6,' ');
                InitData(dataMissile,6,' ');
                InitData(dataShip2,6,' ');
                InitData(dataMissile2,6,' ');
                break;
            case 3: HowToPlay(); break;
            case 4: /*Highscore();*/printf("Highscore\n"); break;
            case 5: Settings(); break;
            case 6: /*Info();*/printf("Info\n"); break;
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
    gotoXY(43,wherey());printf("6.Info\n");
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
//choice (0==dataShip, 1==dataMissile, 2==dataShip2, 3==dataMissile2)
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
                    grid[i][j] = dataMissile[k][l];
                    break;
                case 2: 
                    grid[i][j] = dataShip2[k][l] != '#' ? dataShip2[k][l] : ' ';
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
// Player 1 functions Definition
void PlaceShips(int player)
{
    int i;
    char navire[3]={'A','B','C'};

    for(i=0; i<3; i++)
    {
        system("cls");
        gotoXY(37,wherey());printf("(place the ships)\n\n");
        DisplayGrid(0,37);
        if(player == 0) SetShip(navire[i], dataShip);
        else SetShip(navire[i], dataShip2);
    }
    system("cls");
    gotoXY(42,wherey()); textcolor(LIGHTGREEN); printf("Ships are placed!\n\n"); textcolor(WHITE);
    DisplayGrid(0,37);
    gotoXY(44,wherey()); printf("Click Any Key!\n");
}
void SetShip(char name, char data[][6])
{
    position pos;
    position posBloc[2];
    int rotation;
    do
    {
        GetCoord:
        GetCoordinate(&pos.x,&pos.y);
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
// Player 2 functions Definition
void DestroyShips(int player)
{
    position pos;
    gameTime.start = time(&gameTime.start);
    do
    {
        system("cls");
        gotoXY(40,wherey());printf("(destroy the ships)\n\n");
        DisplayGrid(1,37);
        gotoXY(37,wherey());GetCoordinate(&pos.x,&pos.y);
    } while (!MissileLauncher(pos.x,pos.y,9,player));
    system("cls");
    gotoXY(47,wherey()); textcolor(LIGHTGREEN); printf("Good Job!\n\n"); textcolor(WHITE);
    DisplayGrid(1,37);
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
            }
            else
            {
                hits++;
                dataMissile[x][y] = dataShip[x][y];
                //Score
                Player.score += scoreMissile;
                scoreMissile = 36;
            }
        }
        else
        {
            textcolor(RED);
            gotoXY(38,wherey()+1);
            printf("\aThe Box already striked!\n");
            textcolor(WHITE);
            delay(1000);
        }
        if(hits >= nbrCases)
        {
            hits = 0;
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
            }
            else
            {
                hits2++;
                dataMissile2[x][y] = dataShip2[x][y];
                //Score
                Player.score += scoreMissile;
                scoreMissile = 36;
            }
        }
        else
        {
            textcolor(RED);
            gotoXY(38,wherey()+1);
            printf("\aThe Box already striked!\n");
            textcolor(WHITE);
            delay(1000);
        }
        if(hits2 >= nbrCases)
        {
            hits2 = 0;
            return 1;
        }
    }
    return 0;
}
void SetScore()
{
    gameTime.end = time(&gameTime.end);
    Player.time = difftime(gameTime.end,gameTime.start);

    if(Player.time < 10) Player.time += 100;
    else if(Player.time < 30) Player.score += 75;
    else if(Player.time < 60) Player.score += 50;
    else if(Player.time < 100) Player.score += 25;
    else Player.score += 5;

    delay(300);
    gotoXY(40,wherey());printf("****** Player 2 ******\n\n");
    while(1)
    {
        gotoXY(40,wherey());printf("    Nickname : "); fflush(stdin); gets(Player.name);
        DeleteBlankSpaces(Player.name);
        if(strcmp(Player.name,"")!=0) break;
        textcolor(RED); gotoXY(32, wherey()+1); printf("\aError! please enter a valid nickname\n"); textcolor(WHITE);
        delay(1000); printf("\x1b[1F\x1b[2K\x1b[2F\x1b[2K");
    }
}
void GetScore()
{
    delay(500); clrscr();
    gotoXY(40,wherey());printf("****** Scores ******\n\n");
    gotoXY(40,wherey());printf("    %s : %d\n",Player.name, Player.score);
    //Add other score from local DB
    //here...
    printf("\n\n");
    gotoXY(44,wherey()); printf("Click Any Key!\n");
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
        textcolor(RED); printf("\aError! only (1:ON or 0:OFF)"); textcolor(WHITE);
    }while(1);
}
void DarkMode(int on)
{
    if(on) { textbackground(BLACK); return;}
    textbackground(CYAN);
}
//Tools
void InitData(char str[][6],int len,char c)
{
    int i,j;
    
    for(i=0; i<len; i++)
        for(j=0; j<len; j++)
            str[i][j] = c;
}
void GetCoordinate(int *x, int *y)
{
    char *coordinate = (char *) malloc(sizeof(char));
    do
    {
        gotoXY(37,wherey()); printf("Give Coordinate : "); fflush(stdin); gets(coordinate);
        if(CoordinateConverter(x,y,coordinate)) break;
        gotoXY(34,wherey()); textcolor(RED); printf("\aIncorrect Coordinate! (ex: A1)\n"); textcolor(WHITE);
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
void MaximizeOutputWindow(void)
{
    HWND consoleWindow = GetConsoleWindow(); // This gets the value Windows uses to identify your output window 
    ShowWindow(consoleWindow, SW_MAXIMIZE); // this mimics clicking on its' maximize button
}