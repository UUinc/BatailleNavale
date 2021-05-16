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
//Player 1
void Player1(void);
void SetShip(char name);
//Player 2
void Player2(void);
int MissileLauncher(int x, int y, int nbrCases);
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
Winner player2;

int darkMode=0; //0 = off - 1 = on
char data[6][6], data2[6][6];
int scoreMissile=36;

int main()
{
    int result;
    
    //Maximize Application in Start
    MaximizeOutputWindow();
    //Game Main Title
    system("title Bataille Navale");

    //Initialize string by spaces
    InitData(data,6,' ');
    InitData(data2,6,' ');

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
                Player1();
                printf("\nShips are placed!\n");
                getch();
                Player2();
                SetScore();
                GetScore();
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

    gotoXY(45,15);printf("1.Play\n");
    gotoXY(45,16);printf("2.How To Play\n");
    gotoXY(45,17);printf("3.Settings\n");
    gotoXY(45,18);printf("0.Exit\n");

    do
    {
        gotoXY(42,20);
        printf("\x1b[2K");//wipe the line
        printf("Choice : ");
        fflush(stdin);
        error = !scanf("%d",&choice);
        error = error || choice > 3 || choice < 0 ? 1 : 0;
        
        if(error)
        {
            gotoXY(40,21);textcolor(RED);printf("\achoice incorrect!");textcolor(WHITE);
            delay(1000);
            //wipe the line
            printf("\x1b[2K");
        }
    } while (error);

    return choice;
}
//Display Matrix 6 x 6
//choice (0==data, 1==data2)
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
            if(!choice)
            {
                grid[i][j] = data[k][l] != '#' ? data[k][l] : ' ';
            }
            else  grid[i][j] = data2[k][l];
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
void Player1()
{
    int i;
    char navire[3]={'A','B','C'};

    for(i=0; i<3; i++)
    {
        system("cls");
        gotoXY(36,wherey());printf("Player 1 (place the ships)\n\n");
        DisplayGrid(0,36);
        gotoXY(36,wherey());SetShip(navire[i]);
    }
    system("cls");
    gotoXY(36,wherey());printf("Player 1 (place the ships)\n\n");
    DisplayGrid(0,36);
}
void SetShip(char name)
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
                printf("Rotation :\n");
                //Vertical Up
                if(pos.x>=2 && data[pos.x-1][pos.y] == ' ' && data[pos.x-2][pos.y] == ' '){ printf(" 0.Vertical Up\n"); available[i++]=0;}
                //Vertical Down
                if(pos.x<4 && data[pos.x+1][pos.y] == ' ' && data[pos.x+2][pos.y] == ' '){ printf(" 1.Vertical Down\n"); available[i++]=1;}
                //Horizontal Right
                if(pos.y<4 && data[pos.x][pos.y+1] == ' ' && data[pos.x][pos.y+2] == ' '){ printf(" 2.Horizontal Right\n"); available[i++]=2;}
                //Horizontal Left
                if(pos.y>=2 && data[pos.x][pos.y-1] == ' ' && data[pos.x][pos.y-2] == ' '){ printf(" 3.Horizontal Left\n"); available[i++]=3;}
                //Diagonal Up
                if(pos.x>=2 && pos.y>=2 && data[pos.x-1][pos.y-1] == ' ' && data[pos.x-2][pos.y-2] == ' '){ printf(" 4.Diagonal Up\n"); available[i++]=4;}
                //Diagonal Down
                if(pos.x<4 && pos.y<4 && data[pos.x+1][pos.y+1] == ' ' && data[pos.x+2][pos.y+2] == ' '){ printf(" 5.Diagonal Down\n"); available[i++]=5;}
                //Diagonal Reverse Down
                if(pos.x<4 && pos.y>=2 && data[pos.x+1][pos.y-1] == ' ' && data[pos.x+2][pos.y-2] == ' '){ printf(" 6.Diagonal Reverse Down\n"); available[i++]=6;}
                //Diagonal Reverse Up
                if(pos.x>=2 && pos.y<4 && data[pos.x-1][pos.y+1] == ' ' && data[pos.x-2][pos.y+2] == ' '){ printf(" 7.Diagonal Reverse Up\n"); available[i++]=7;}
                if(available[0] == -1)
                {
                    // Move to beginning of previous line and Clear entire line
                    textcolor(RED); printf("\x1b[1F\x1b[2K\aimpossible to set a navy here\n"); textcolor(WHITE);
                    goto GetCoord;
                }
                j = i;
                do {
                    getRotation:
                    fflush(stdin);
                    printf("choice : ");
                    if(scanf("%d",&rotation)) break;
                    textcolor(RED); printf("\aError! rotation incorrect\n"); textcolor(WHITE);
                }while(1);
                //check if the rotation selected is available
                for(i=j;i>0;i--) if(rotation == available[i-1]) break;
                if(i) break;
                textcolor(RED); printf("\aError! rotation incorrect\n"); textcolor(WHITE);
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
                textcolor(RED); printf("\n\aYou can't set navy close to other navy\n"); textcolor(WHITE);
            }
            else
            {
                textcolor(RED); printf("\n\aThe ship block is occupied!\n"); textcolor(WHITE);
            }
        }
    }while(1);
}
// Player 2 functions Definition
void Player2()
{
    position pos;
    gameTime.start = time(&gameTime.start);
    do
    {
        system("cls");
        gotoXY(36,wherey());printf("Player 2 (destroy the ships)\n\n");
        DisplayGrid(1,36);
        gotoXY(36,wherey());GetCoordinate(&pos.x,&pos.y);
    } while (!MissileLauncher(pos.x,pos.y,9));
    system("cls");
    gotoXY(36,wherey());printf("Player 2 (destroy the ships)\n\n");
    DisplayGrid(1,36);
}
int MissileLauncher(int x, int y, int nbrCases)
{
    static int hits=0;

    if(data2[x][y] == ' ')
    {
        if(data[x][y] == ' ' || data[x][y] == '#')
        {
            data2[x][y] = 'X';
            //Score
            scoreMissile--; 
        }
        else
        {
            data2[x][y] = data[x][y]; hits++;
            //Score
            player2.score += scoreMissile;
		    scoreMissile = 36;
        }
    }
    else{ textcolor(RED); printf("\n\aThe Box already striked!\n"); textcolor(WHITE); delay(1000);}

    return hits >= nbrCases ? 1 : 0;
}
void SetScore()
{
    gameTime.end = time(&gameTime.end);
    player2.time = difftime(gameTime.end,gameTime.start);

    if(player2.time < 1) player2.time += 100;
    else if(player2.time >= 1 && player2.time < 2) player2.score += 75;
    else if(player2.time >= 2 && player2.time < 3) player2.score += 50;
    else if (player2.time >= 3 && player2.time < 4) player2.score += 25;
    else if(player2.time >= 4 && player2.time < 5) player2.score += 5;

    printf("\n****** Player 2 ******\n\n");
    printf("    Your Name : "); fflush(stdin); gets(player2.name);
}
void GetScore()
{
    printf("\n****** Score ******\n\n");
    printf("    %s : %d\n",player2.name, player2.score);
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
        printf("Give Coordinate : "); fflush(stdin); gets(coordinate);
        if(CoordinateConverter(x,y,coordinate)) break;
        textcolor(RED); printf("\aIncorrect Coordinate! (ex: A1)\n"); textcolor(WHITE);
    }while(1);
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