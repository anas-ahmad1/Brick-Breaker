#include <iostream>
#include"mygraphics.h"
#include"myconsole.h"
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
using namespace std;

bool hitbrick(int bx1,int bx2,int by1,int by2,int&a,int&b,int&c,int&d,int&score,int xcord[],int ycord[],int brickss[][18],int brickarr[][18],int&lives,int&layers,int&red,int&points,bool&won,int&total);
void drawbricks3(int xcord[],int ycord[],int brickarr[][18]);
void drawoldbricks(int xcord[],int ycord[],int brickarr[][18],int brickss[][18],int layers);
void drawmybat(int x1,int x2,int y1,int y2);
void removeup(COLORREF black,int i,int j,int brickss[][18],int xcord[],int ycord[]);
void removedown(COLORREF black,int i,int j,int brickss[][18],int xcord[],int ycord[]);
void removeleft(COLORREF black,int i,int j,int brickss[][18],int xcord[],int ycord[]);
void removeright(COLORREF black,int i,int j,int brickss[][18],int xcord[],int ycord[]);
int addlayer(int i,int j,int brickss[][18],int&score,int&layers,int xcord[],int ycord[],int&total);
int halflife(int i,int j,int brickss[][18],int&red,int&lives,int&score,int xcord[],int ycord[],int&total);
int adjacentbricks(int i,int j,int brickss[][18],int&score,int xcord[],int ycord[],int&total,int&layers);
int addlife(int i,int j,int brickss[][18],int&lives,int&score,int xcord[],int ycord[],int&total);
int simplehit(int i,int j,int brickss[][18],int&score,int xcord[],int ycord[],int&total);
int brickdecision(int i,int j,int brickarr[][18],int&lives,int&score,int&layers,int brickss[][18],int xcord[],int ycord[],int&red,int&total);
int decidebrick();
void drawcircle(int x1,int y1,int x2,int y2);
void drawtriangle(int x1,int y1,int x2,int y2);
void drawparallelogram(int x1,int y1,int x2,int y2);
void drawrectangle(int x1,int y1,int x2,int y2);
bool decidehighscore(int highscores[20],string scoresnames[20],int score,string name);
void showhighscores();
void savegame(int layers,int lives,int score,int total,int ballmove,int red,int bx1,int bx2,int by1,int by2,int batx1,int batx2,int brickarr[][18],int brickss[][18],bool righthalf,bool lefthalf,bool centre,bool bounceright,bool bounceleft,char balldirection,string playername);
int game(string playername,int gametype);


int main()
{
	srand(15);
	int menuoption,count=0,scorenow,linelen,pos,highscores[20];
	string line,playername,linescore,linename,scoresnames[20];
	bool higher=false;

	COLORREF grey = RGB(128,128,128);
	COLORREF white = RGB(255,255,255);
	COLORREF black = RGB(00,00,00);
	COLORREF text = RGB(64,128,128);
	COLORREF darkgrey = RGB(50,50,50);
	COLORREF green = RGB(0,204,0);
	COLORREF peach = RGB(255,178,102);
	COLORREF yellow = RGB (255,255,0);
	COLORREF red = RGB(255,0,0);

	for(int i=0;i<200;i=i+2)
	{
	COLORREF grey = RGB(i,i,i);
	myDrawTextWithFont(130,90,100,"BRICK BREAKER",grey,black);
	myLine(10,10,760,10,grey);		//Upper horizontal line
	myLine(10,10,10,300,grey);		//Left verical line
	myLine(760,10,760,300,grey);	//Right vertical line
	myLine(10,300,760,300,grey);	//Lower horizontal line
	Sleep(50);
	}
	myDrawText(300,280,10,"Press any key to continue",white,black);
	getch();
	myDrawText(300,280,10,"Press any key to continue",black,black);
	myDrawTextWithFont(130,90,100,"BRICK BREAKER",black,black);

	bool terminate2=false;
	while(terminate2==false)
	{
	myDrawTextWithFont(300,15,70,"MENU",black,text);
	myDrawTextWithFont(60,120,40,"1- Start a New Game",text,black);
	myDrawTextWithFont(60,180,40,"2- Load a Game",text,black);
	myDrawTextWithFont(400,120,40,"3- Check Highscores",text,black);
	myDrawTextWithFont(400,180,40,"4- Read Instructions",text,black);
	myDrawText(200,280,10,"Enter a number to choose its corresponding option",white,black);
	cin>>menuoption;
	system("CLS");
	
		if(menuoption==1)
		{
			int gametype=1;
			HANDLE myconsole=GetStdHandle(STD_OUTPUT_HANDLE);
			COORD mycursor;
			mycursor.X=0;
			mycursor.Y=4;
			SetConsoleCursorPosition(myconsole,mycursor);
			myDrawTextWithFont(10,5,40,"Enter your first name:",black,grey);
			cin>>playername;
			system("CLS");
			scorenow=game(playername,gametype);
			ifstream ScoreReadFile("highscores.txt");
			while(!ScoreReadFile.eof())
			{
				ScoreReadFile>>line;
				scoresnames[count]=line;
				pos=line.find("-");
				linescore=line.substr(0,pos);
				stringstream geek(linescore);
				geek>>highscores[count];
				count++;
			}
			ScoreReadFile.close();
			higher=decidehighscore(highscores,scoresnames,scorenow,playername);
			if(higher==true)
			{
				myDrawTextWithFont(190,100,80,"New High Score!",grey,black);
				ofstream ScoreWriteFile("highscores.txt");
				for(int i=0;i<10;i++)
					ScoreWriteFile<<scoresnames[i]<<std::endl;
				ScoreWriteFile.close();
			}
		_getch();
		system("CLS");
		}	
		else if(menuoption==2)
		{
			string name;
			int gametype=2;
			ifstream ReadPlayerNameFile("playername.txt");
			while(getline(ReadPlayerNameFile,name));
				playername=name;
			ReadPlayerNameFile.close();
			scorenow=game(playername,gametype);
			ifstream ScoreReadFile("highscores.txt");
			while(!ScoreReadFile.eof())
			{
				ScoreReadFile>>line;
				scoresnames[count]=line;
				pos=line.find("-");
				linescore=line.substr(0,pos);
				stringstream geek(linescore);
				geek>>highscores[count];
				count++;
			}
			ScoreReadFile.close();
			higher=decidehighscore(highscores,scoresnames,scorenow,playername);
			if(higher==true)
			{
				myDrawTextWithFont(190,100,80,"New High Score!",grey,black);
				ofstream ScoreWriteFile("highscores.txt");
				for(int i=0;i<10;i++)
					ScoreWriteFile<<scoresnames[i]<<std::endl;
				ScoreWriteFile.close();
			}
		_getch();
		system("CLS");
		}
		else if(menuoption==3)
		{
			showhighscores();
			_getch();
			system("CLS");
		}
		else if(menuoption==4)
		{
			int guide;
			bool terminate1=false;
			while(terminate1==false)
			{
			myDrawTextWithFont(300,15,70,"Guide Menu",black,text);
			myDrawTextWithFont(60,120,40,"1- Bricks and scoring",text,black);
			myDrawTextWithFont(60,180,40,"2- Ball movements",text,black);
			myDrawTextWithFont(550,120,40,"3- Other Instructions",text,black);
			myDrawTextWithFont(550,180,40,"4- Back",text,black);
			myDrawText(260,280,10,"Enter a number to choose its corresponding option",white,black);
			cin>>guide;
			system("CLS");
			if(guide==1)
			{
				myDrawTextWithFont(150,5,40,"There are 5 different bricks in this game",black,white);
				myRect(80,110,140,140,peach,peach);
				myEllipse(105,120,115,130,green,green);
				myDrawText(200,105,40,"--> Hitting this brick adds 1 life if the lives are not already maximum",white,black);
				myDrawText(200,125,40,"--> If the lives are maximum then a score of 10 is added",white,black);
				int size=10;
				myRect(80,190,140,220,peach,peach);
				for(int i=-size;i<size;i++)
				{
					myLine(110,210,110+i,200,red);
				}
				myDrawText(200,185,40,"--> Hitting two of these bricks results in losing 1 life",white,black);
				myDrawText(200,205,40,"--> No score is added/decreased",white,black);
				myRect(80,270,140,300,peach,peach);
				for(int i=12;i<26;i++)
				{	
					myLine((92+i)-7,290,92+i,280,yellow);
				}
				myDrawText(200,265,40,"--> Hitting this brick breaks adjacent bricks too",white,black);
				myDrawText(200,285,40,"--> Score of 10 is added",white,black);
				myRect(80,350,140,380,peach,peach);
				myRect(90,360,130,370,darkgrey,darkgrey);
				myDrawText(200,345,40,"--> Hitting this brick adds a new layer of bricks at the bottom",white,black);
				myDrawText(200,365,40,"--> If there are already max layers then score is reduced by 5",white,black);
				myRect(80,430,140,460,peach,peach);
				myDrawText(200,425,40,"--> Its a simple brick",white,black);
				myDrawText(200,445,40,"--> Hitting it adds a score of 2",white,black);	
				_getch();
				system("CLS");
			}
			else if(guide==2)
			{
				myDrawTextWithFont(150,5,40,"Bat is divided into 5 parts",black,white);
				myRect(200,80,240,110,darkgrey,darkgrey);
				myRect(241,80,280,110,grey,grey);
				myRect(281,80,320,110,white,white);
				myRect(321,80,360,110,grey,grey);
				myRect(361,80,400,110,darkgrey,darkgrey);
				myDrawTextWithFont(40,160,40,"Left Dark Grey:",black,darkgrey);
				myDrawTextWithFont(40,220,40,"Left Grey:",black,grey);
				myDrawTextWithFont(40,280,40,"Mid White:",black,white);
				myDrawTextWithFont(40,340,40,"Right Grey:",black,grey);
				myDrawTextWithFont(40,400,40,"Right Dark Grey:",black,darkgrey);
				myDrawText(270,170,40,"--> Hitting this part moves the ball 60° to the Left",white,black);
				myDrawText(270,230,40,"--> Hitting this part moves the ball 30° to the Left",white,black);
				myDrawText(270,290,40,"--> Hitting this part moves the ball 90° with the bat",white,black);
				myDrawText(270,350,40,"--> Hitting this part moves the ball 30° to the Right",white,black);
				myDrawText(270,410,40,"--> Hitting this part moves the ball 60° to the Right",white,black);
				_getch();
				system("CLS");
			}
			else if(guide==3)
			{
				myDrawTextWithFont(150,5,40,"Other Instructions",black,white);
				myDrawTextWithFont(20,80,20,"• Press 'a' to move your bat to the left",white,black);
				myDrawTextWithFont(20,140,20,"• Press 'd' to move your bat to the right",white,black);
				myDrawTextWithFont(20,200,20,"• To pause the game you can press space bar",white,black);
				myDrawTextWithFont(20,260,20,"• To save a game, first pause the game and then press 's'",white,black);
				myDrawTextWithFont(20,320,20,"• The game starts with 3 lives and you can have maximum of 5 lives",white,black);
				myDrawTextWithFont(20,380,20,"• If the ball falls to the bottom, you lose 1 life",white,black);
				myDrawTextWithFont(20,440,20,"• The game starts with 4 layers of bricks and it can reach up to 7 layers max",white,black);
				_getch();
				system("CLS");
			}
			else if(guide==4)
				terminate1=true;
		}	
	}
		}
	_getch();
	system("pause");
} 


int game(string playername,int gametype)
{
		int layers,lives,complete=0,score,total,points=0,xpoint=-10,ypoint=10;
		bool hitting=false,righthalf,lefthalf,centre,bounceright,bounceleft,fall=false,won;
		char move='1',balldirection;
		int ballmove,red,mid1,mid2,midb;
		int hx1,hx2,hy1,hy2;
		int batx1,batx2,baty1=280,baty2=290;
		int bx1,bx2,by1,by2;
		int brickx1=-10,brickx2=20,bricky1=30,bricky2=40;
		int brickarr[7][18],brickss[7][18],xcord[18],ycord[7];

		if(gametype==1)
		{
			layers=4,lives=3,score=0,total=72,ballmove=0,red=0;
			bx1=380,bx2=390,by1=250,by2=260;
			batx1=350,batx2=420;
			balldirection='d';
			righthalf=false,lefthalf=false,centre=true,bounceright=false,bounceleft=false;

				for(int i=0;i<7;i++)			//Initializing brickss to 0(none broken)
					for(int j=0;j<18;j++)
				{
					brickss[i][j]=0;
				}
		}
		else if(gametype==2)
		{
			string line;
			int count=0;
			ifstream ReadIntVarFile("intvar.txt");
			while(getline (ReadIntVarFile,line))
			{
				stringstream geek(line);
				if(count==0)
					geek>>layers;
				else if(count==1)
					geek>>lives;
				else if(count==2)
					geek>>score;
				else if(count==3)
					geek>>total;
				else if(count==4)
					geek>>ballmove;
				else if(count==5)
					geek>>red;
				count++;
			}
			ReadIntVarFile.close();
			count=0;
			ifstream ReadBallCordFile("ballcord.txt");
			while(getline (ReadBallCordFile,line))
			{
				stringstream geek(line);
				if(count==0)
					geek>>bx1;
				else if(count==1)
					geek>>bx2;
				else if(count==2)
					geek>>by1;
				else if(count==3)
					geek>>by2;
				count++;
			}
			ReadBallCordFile.close();

			count=0;
			ifstream ReadBatCordFile("batcord.txt");
			while(getline (ReadBatCordFile,line))
			{
				stringstream geek(line);
				if(count==0)
					geek>>batx1;
				else if(count==1)
					geek>>batx2;
				count++;
			}
			ReadBatCordFile.close();

			int i=0,j=0;
			ifstream ReadBrickArrFile("brickarr.txt");
			while(getline (ReadBrickArrFile,line))
			{
				stringstream geek(line);
				geek>>brickarr[i][j];
				j++;
				if(j==18)
				{
					i++;
					j=0;
				}
			}
			ReadBrickArrFile.close();

			i=0,j=0;
			ifstream ReadBrickssFile("brickss.txt");
			while(getline (ReadBrickssFile,line))
			{
				stringstream geek(line);
				geek>>brickss[i][j];
				j++;
				if(j==18)
				{
					i++;
					j=0;
				}
			}
			ReadBrickssFile.close();

			count=0;
			ifstream ReadBoolVarFile("boolvar.txt");
			while(getline (ReadBoolVarFile,line))
			{
				bool read;
				if(line=="1")
					read=true;
				else if(line=="0")
					read=false;
				if(count==0)
					righthalf=read;
				else if(count==1)
					lefthalf=read;
				else if(count==2)
					centre=read;
				else if(count==3)
					bounceright=read;
				else if(count==4)
					bounceleft=read;
				count++;
			}
			ReadBoolVarFile.close();

			ifstream ReadCharVarFile("charvar.txt");
			while(getline (ReadCharVarFile,line))
			{
				balldirection=line[0];
			}
			ReadCharVarFile.close();
		}

	HANDLE myconsole=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD mycursor;

	for(int i=0;i<18;i++)			//Initializing x-coordinates of bricks with 40 gap
	{
		xpoint=xpoint+40;
		xcord[i]=xpoint;
	}

	for(int i=0;i<7;i++)			//Initializing y-coordinates of bricks with 20 gap
	{
		ypoint=ypoint+20;
		ycord[i]=ypoint;
	}
	
	COLORREF color;
	COLORREF jade = RGB(0,102,102);
	COLORREF mahroon = RGB(102,0,0);
	COLORREF grey = RGB(128,128,128);
	COLORREF white = RGB(255,255,255);
	COLORREF black = RGB(00,00,00);
											//Drawing Game Rectangle Window
	myLine(10,10,760,10,white);				//Upper horizontal line
	myLine(10,10,10,300,white);				//Left verical line
	myLine(760,10,760,300,white);			//Right vertical line
	myLine(10,300,760,300,white);			//Lower horizontal line

	drawmybat(batx1,batx2,baty1,baty2);		//Drawing bat
	myEllipse(bx1,by1,bx2,by2,white,white);	//Drawing ball
	getch();
	{
				mycursor.X=102;
				mycursor.Y=4;
				SetConsoleCursorPosition(myconsole,mycursor);
				myDrawTextWithFont(790,12,40,"Score",black,grey);
				myDrawTextWithFont(880,12,40,"Lives",black,grey);

													//Drawing game window
				myLine(10,10,760,10,white);			//Upper horizontal line
				myLine(10,10,10,300,white);			//Left verical line
				myLine(760,10,760,300,white);		//Right vertical line
				myLine(10,300,760,300,white);		//Lower horizontal line

													//Drawing Scoreboard
				myLine(780,10,955,10,white);		//Upper horizontal line
				myLine(780,10,780,100,white);		//Left verical line
				myLine(955,10,955,100,white);		//Right vertical line
				myLine(780,100,955,100,white);		//Lower horizontal line


				if(gametype==1)
					drawbricks3(xcord,ycord,brickarr);	//Drawing bricks
				else if(gametype==2)
					drawoldbricks(xcord,ycord,brickarr,brickss,layers);
		}
	while(complete!=1)		//GAME STARTS
	{
		if(lives==1)
		{
			myRect(890,55,930,95,black,black);
			myDrawTextWithFont(900,55,40,"1",grey,black);
		}
		else if(lives==2)
		{
			myRect(890,55,930,95,black,black);
			myDrawTextWithFont(900,55,40,"2",grey,black);
		}
		else if(lives==3)
		{
			myRect(890,55,930,95,black,black);
			myDrawTextWithFont(900,55,40,"3",grey,black);
		}
			else if(lives==4)
		{
			myRect(890,55,930,95,black,black);
			myDrawTextWithFont(900,55,40,"4",grey,black);
		}
		else if(lives==5)
		{
			myRect(890,55,930,95,black,black);
			myDrawTextWithFont(900,55,40,"5",grey,black);
		}

		if(fall==true)
		{
			bx1=380,bx2=390,by1=250,by2=260;				//Drawing ball and bat again if ball falls
			batx1=350,batx2=420,baty1=280,baty2=290;
			fall=false;
		}
		drawmybat(batx1,batx2,baty1,baty2);

		if(gametype==1)
			righthalf=false,lefthalf=false,centre=true,bounceright=false,bounceleft=false;		//Initializing ball movements
		
		while(by2!=300)			//Loop for the ball until it falls
		{
		
			while(kbhit()==false)		//Registers keyboard key for simultaneous movements
			{
				mycursor.X=102;
				mycursor.Y=4;
				SetConsoleCursorPosition(myconsole,mycursor);		//Change cursor position to output score 
				cout<<score;

				myLine(10,10,760,10,white);
				if(balldirection=='d')
				{
					if(bounceleft==true)
					{
						myLine(760,10,760,300,white);	//Right vertical line
						myEllipse(bx1-ballmove,by1+10,bx2-ballmove,by2+10,white,white);
						myEllipse(bx1,by1,bx2,by2,black,black);
						by1=by1+10;
						by2=by2+10;
						bx1=bx1-ballmove;
						bx2=bx2-ballmove;
						if(ballmove==8)
							Sleep(100);
						else
							Sleep(90);
						if(by1==10)
						{
							balldirection='d';
						}
						else if(by2==300)				//hitting bottom
						{
							lives--;
							fall=true;
							break;
						}
						if((by2==baty1 || by2==baty2) && (bx2>batx1 && bx1<batx2))    //hitting bat
						{
							balldirection='u';
							mid1=batx1+28;
							mid2=mid1+14;
							midb=(bx1+bx2)/2;
							if(midb>mid2)
							{
								righthalf=true;
								lefthalf=false;
								bounceright=true;
								bounceleft=false;
								if(midb>(mid2+14))
									ballmove=8;
								else
									ballmove=5;
							}
							else if(midb<mid1)
							{
								lefthalf=true;
								righthalf=false;
								bounceleft=true;
								bounceright=false;
								if(midb<(mid1-14))
									ballmove=8;
								else
									ballmove=5;
							}
							else if(midb>mid1 && midb<mid2)
								ballmove=0;
						}	
						hitting=hitbrick(bx1,bx2,by1,by2,hx1,hx2,hy1,hy2,score,xcord,ycord,brickss,brickarr,lives,layers,red,points,won,total); //Checks if ball hits a brick
						if(hitting==true)
						{
							score=score+points;
							myRect(hx1,hy1,hx2,hy2,black,black); 
							balldirection='u';
							
							hitting=false;
						}
						if(bx2>=760)
						{
							bounceleft=true;
							bounceright=false;
							
						}
						else if(bx1<=10)
						{
							bounceright=true;
							bounceleft=false;
						}
					}
					else if(bounceright==true)
					{
						myLine(10,10,10,300,white);		//Left verical line
						myEllipse(bx1+ballmove,by1+10,bx2+ballmove,by2+10,white,white);
						myEllipse(bx1,by1,bx2,by2,black,black);
						by1=by1+10;
						by2=by2+10;
						bx1=bx1+ballmove;
						bx2=bx2+ballmove;
						if(ballmove==8)
							Sleep(100);
						else
							Sleep(90);
						if(by1==10)
						{
								balldirection='d';
						}
						else if(by2==300)
						{
							lives--;
							fall=true;
							break;
						}
						if((by2==baty1 || by2==baty2) && (bx2>batx1 && bx1<batx2))		//hitting bat
						{
							balldirection='u';
							mid1=batx1+28;
							mid2=mid1+14;
							midb=(bx1+bx2)/2;
							if(midb>mid2)
							{
								righthalf=true;
								lefthalf=false;
								bounceright=true;
								bounceleft=false;
								if(midb>(mid2+14))
									ballmove=8;
								else
									ballmove=5;
							}
							else if(midb<mid1)
							{
								lefthalf=true;
								righthalf=false;
								bounceleft=true;
								bounceright=false;
								if(midb<(mid1-14))
									ballmove=8;
								else
									ballmove=5;
							}
							else if(midb>mid1 && midb<mid2)
								ballmove=0;
					}
					hitting=hitbrick(bx1,bx2,by1,by2,hx1,hx2,hy1,hy2,score,xcord,ycord,brickss,brickarr,lives,layers,red,points,won,total);
					if(hitting==true)
					{
						score=score+points;
						myRect(hx1,hy1,hx2,hy2,black,black); 
						balldirection='u';
					
						hitting=false;
					}	
					if(bx2>=760)
					{
						bounceleft=true;
						bounceright=false;
					}
					else if(bx1<=10)
					{
						bounceright=true;
						bounceleft=false;
					}
				}
				else
				{
					myEllipse(bx1,by1+10,bx2,by2+10,white,white);
					myEllipse(bx1,by1,bx2,by2,black,black);
					by1=by1+10;
					by2=by2+10;
					if(ballmove==8)
							Sleep(100);
						else
							Sleep(90);
					if(by1==10)
					{
						balldirection='d';
					}
					else if(by2==300)
					{
						lives--;
						fall=true;
						break;
					}

					if((by2==baty1 || by2==baty2) && (bx2>batx1 && bx1<batx2))		//hitting bat
					{
						balldirection='u';
						mid1=batx1+28;
							mid2=mid1+14;
							midb=(bx1+bx2)/2;
							if(midb>mid2)
							{
								righthalf=true;
								lefthalf=false;
								bounceright=true;
								bounceleft=false;
								if(midb>(mid2+14))
									ballmove=8;
								else
									ballmove=5;
							}
							else if(midb<mid1)
							{
								lefthalf=true;
								righthalf=false;
								bounceleft=true;
								bounceright=false;
								if(midb<(mid1-14))
									ballmove=8;
								else
									ballmove=5;
							}
							else if(midb>mid1 && midb<mid2)
								ballmove=0;
					}
						hitting=hitbrick(bx1,bx2,by1,by2,hx1,hx2,hy1,hy2,score,xcord,ycord,brickss,brickarr,lives,layers,red,points,won,total);
					if(hitting==true)
					{
						score=score+points;
						myRect(hx1,hy1,hx2,hy2,black,black); 
						balldirection='u';
						
						hitting=false;
					}
					if(bx2>=760)
						{
							bounceleft=true;
							bounceright=false;
						}
						else if(bx1<=10)
						{
							bounceright=true;
							bounceleft=false;
						}
				}
			}
			else if(balldirection=='u')
			{
				if(righthalf==true)
				{
					if(bounceleft==false)
					{
						myLine(10,10,10,300,white);		//Left verical line
						myEllipse(bx1+ballmove,by1-10,bx2+ballmove,by2-10,white,white);
						myEllipse(bx1,by1,bx2,by2,black,black);
						by1=by1-10;
						by2=by2-10;
						bx1=bx1+ballmove;
						bx2=bx2+ballmove;
						if(ballmove==8)
							Sleep(100);
						else
							Sleep(90);
						if(by2==300)
						{
							fall=true;
							
						}
						else if(by1==10)
							balldirection='d';

						hitting=hitbrick(bx1,bx2,by1,by2,hx1,hx2,hy1,hy2,score,xcord,ycord,brickss,brickarr,lives,layers,red,points,won,total);
						if(hitting==true)
						{
							score=score+points;
							myRect(hx1,hy1,hx2,hy2,black,black); 
							balldirection='d';
							
							hitting=false;
						}
						if(bx2>=760)
						{
							bounceleft=true;
							bounceright=false;
						}
						else if(bx1<=10)
						{
							bounceright=true;
							bounceleft=false;
						}
					}
					else if(bounceleft==true)
					{
						myLine(760,10,760,300,white);	//Right vertical line
						myEllipse(bx1-ballmove,by1-10,bx2-ballmove,by2-10,white,white);
						myEllipse(bx1,by1,bx2,by2,black,black);
						by1=by1-10;
						by2=by2-10;
						bx1=bx1-ballmove;
						bx2=bx2-ballmove;
						if(ballmove==8)
							Sleep(100);
						else
							Sleep(90);
						if(by2==300)
						{
							fall=true;
							
						}
						else if(by1==10)
							balldirection='d';
				
							hitting=hitbrick(bx1,bx2,by1,by2,hx1,hx2,hy1,hy2,score,xcord,ycord,brickss,brickarr,lives,layers,red,points,won,total);
						if(hitting==true)
						{
							score=score+points;
							myRect(hx1,hy1,hx2,hy2,black,black); 
							balldirection='d';
							hitting=false;
						}
						if(bx2>=760)
						{
							bounceleft=true;
							bounceright=false;
						}
						else if(bx1<=10)
						{
							bounceright=true;
							bounceleft=false;
						}
					}
				}
				else if(lefthalf==true)
					{
						if(bounceright==false)
						{
							myLine(760,10,760,300,white);	//Right vertical line
							myEllipse(bx1-ballmove,by1-10,bx2-ballmove,by2-10,white,white);
							myEllipse(bx1,by1,bx2,by2,black,black);
							by1=by1-10;
							by2=by2-10;
							bx1=bx1-ballmove;
							bx2=bx2-ballmove;
							if(ballmove==8)
							Sleep(100);
						else
							Sleep(90);
							if(by2==300)
							{
								fall=true;
								
							}
							else if(by1==10)
								balldirection='d';
							
								hitting=hitbrick(bx1,bx2,by1,by2,hx1,hx2,hy1,hy2,score,xcord,ycord,brickss,brickarr,lives,layers,red,points,won,total);
							if(hitting==true)
							{			
								score=score+points;
								myRect(hx1,hy1,hx2,hy2,black,black); 
								balldirection='d';
								hitting=false;
							}
							if(bx2>=760)
							{
								bounceleft=true;
								bounceright=false;
							}
							else if(bx1<=10)
							{
								bounceright=true;
								bounceleft=false;
							}
							}
						else if(bounceright==true)
						{
							myLine(10,10,10,300,white);		//Left verical line
							myEllipse(bx1+ballmove,by1-10,bx2+ballmove,by2-10,white,white);
							myEllipse(bx1,by1,bx2,by2,black,black);
							by1=by1-10;
							by2=by2-10;
							bx1=bx1+ballmove;
							bx2=bx2+ballmove;
							if(ballmove==8)
							Sleep(100);
						else
							Sleep(90);
							if(by2==300)
							{
								fall=true;
								
							}
							else if(by1==10)
								balldirection='d';
							
							hitting=hitbrick(bx1,bx2,by1,by2,hx1,hx2,hy1,hy2,score,xcord,ycord,brickss,brickarr,lives,layers,red,points,won,total);
							if(hitting==true)
							{
								score=score+points;
								myRect(hx1,hy1,hx2,hy2,black,black); 
								balldirection='d';
								hitting=false;
							}
							if(bx2>=760)
							{
								bounceleft=true;
								bounceright=false;
							}
							else if(bx1<=10)
							{
								bounceright=true;
								bounceleft=false;
							}
						}
					}
				else if(centre==true)
					{
					myEllipse(bx1-0,by1-10,bx2-0,by2-10,white,white);
					myEllipse(bx1,by1,bx2,by2,black,black);
					by1=by1-10;
					by2=by2-10;
					if(ballmove==8)
							Sleep(100);
						else
							Sleep(90);
					if(by2==300)
					{
						fall=true;
						
					}
					else if(by1==10)
						balldirection='d';
					
					hitting=hitbrick(bx1,bx2,by1,by2,hx1,hx2,hy1,hy2,score,xcord,ycord,brickss,brickarr,lives,layers,red,points,won,total);
					if(hitting==true)
					{
						score=score+points;
						myRect(hx1,hy1,hx2,hy2,black,black); 
						balldirection='d';
						hitting=false;
					}	
				}
			}
			myLine(10,300,760,300,white);
			if(total==0)
			{
				won=true;
				break;
			}
		}
		if(total==0)
			{
				won=true;
				break;
			}
		move=getch();
		if(move=='a')
		{
			if(batx1-10!=10)
			{
			myRect(batx1,baty1,batx2,baty2,black,black);
			batx1=batx1-10;
			batx2=batx2-10;
			drawmybat(batx1,batx2,baty1,baty2);
			}
		}
		else if(move=='d')
		{
			if(batx2+10!=760)
			{
			myRect(batx1,baty1,batx2,baty2,black,black);
			batx1=batx1+10;
			batx2=batx2+10;
			drawmybat(batx1,batx2,baty1,baty2);
			}
		}
		else if(move==32)
		{
			char option;
			myRect(250,170,520,260,grey,grey);
			myDrawTextWithFont(260,180,30,"Press 's' to save this game",grey,black);
			myDrawTextWithFont(260,220,30,"Press any key to continue",grey,black);
			option=_getch();
			if(option=='s')
				savegame(layers,lives,score,total,ballmove,red,bx1,bx2,by1,by2,batx1,batx2,brickarr,brickss,righthalf,lefthalf,centre,bounceright,bounceleft,balldirection,playername);
			myRect(250,170,520,260,black,black);
		}
	}
	myRect(batx1,baty1,batx2,baty2,black,black);

	if(lives==0)
	{
		myDrawTextWithFont(190,100,100,"GAME OVER!",grey,black);
		complete=1;
		getch();
		system("CLS");
	}
	if(won==true)
	{
		myDrawTextWithFont(190,100,100,"YOU WON!",grey,black);
		complete=1;
		getch();
		system("CLS");
	}
	}
	return score;
}

void savegame(int layers,int lives,int score,int total,int ballmove,int red,int bx1,int bx2,int by1,int by2,int batx1,int batx2,int brickarr[][18],int brickss[][18],bool righthalf,bool lefthalf,bool centre,bool bounceright,bool bounceleft,char balldirection,string playername)
{
	ofstream WriteIntVarFile("intvar.txt");
	WriteIntVarFile<<layers<<std::endl;
	WriteIntVarFile<<lives<<std::endl;
	WriteIntVarFile<<score<<std::endl;
	WriteIntVarFile<<total<<std::endl;
	WriteIntVarFile<<ballmove<<std::endl;
	WriteIntVarFile<<red;
	WriteIntVarFile.close();
	ofstream BallCordFile("ballcord.txt");
	BallCordFile<<bx1<<std::endl;
	BallCordFile<<bx2<<std::endl;
	BallCordFile<<by1<<std::endl;
	BallCordFile<<by2;
	BallCordFile.close();
	ofstream BatCordFile("batcord.txt");
	BatCordFile<<batx1<<std::endl;
	BatCordFile<<batx2;
	BatCordFile.close();

	ofstream BrickArrFile("brickarr.txt");
	for(int i=0;i<4;i++)
		for(int j=0;j<18;j++)
			BrickArrFile<<brickarr[i][j]<<std::endl;
	BrickArrFile.close();

	ofstream BrickssFile("brickss.txt");
	for(int i=0;i<7;i++)
		for(int j=0;j<18;j++)
			BrickssFile<<brickss[i][j]<<std::endl;
	BrickssFile.close();

	ofstream BoolVarFile("boolvar.txt");
	BoolVarFile<<righthalf<<std::endl;
	BoolVarFile<<lefthalf<<std::endl;
	BoolVarFile<<centre<<std::endl;
	BoolVarFile<<bounceright<<std::endl;
	BoolVarFile<<bounceleft;
	BoolVarFile.close();

	ofstream CharVarFile("charvar.txt");
	CharVarFile<<balldirection<<std::endl;
	CharVarFile.close();

	ofstream PlayerNameFile("playername.txt");
	PlayerNameFile<<playername;
	PlayerNameFile.close();
}

void drawmybat(int x1,int x2,int y1,int y2)
{
	COLORREF grey = RGB(128,128,128);
	COLORREF white = RGB(255,255,255);
	COLORREF darkgrey = RGB(50,50,50);
	myRect(x1,y1,x1+14,y2,darkgrey,darkgrey);
	myRect(x1+15,y1,x1+28,y2,grey,grey);
	myRect(x1+29,y1,x1+42,y2,white,white);
	myRect(x1+43,y1,x1+56,y2,grey,grey);
	myRect(x1+55,y1,x1+70,y2,darkgrey,darkgrey);
}

bool hitbrick(int bx1,int bx2,int by1,int by2,int&a,int&b,int&c,int&d,int&score,int xcord[],int ycord[],int brickss[][18],int brickarr[][18],int&lives,int&layers,int&red,int&points,bool&won,int&total)
{
	int x1,y1,x2,y2;
	for(int i=0;i<layers;i++)
	{
		for(int j=0;j<18;j++)
		{
			x1=xcord[j];
			x2=x1+30;
			y1=ycord[i];
			y2=y1+10;
			if((by1==y1 || by2==y1 || by1==y2 || by2==y2) && (bx2>=x1 && bx1<=x2))
			{
				a=x1;
				b=x2; 
				c=y1;
				d=y2;
				if(brickss[i][j]==0)
				{
					brickss[i][j]=1;
					points=brickdecision(i,j,brickarr,lives,score,layers,brickss,xcord,ycord,red,total);
					return true;
				}
			}
		}
	}
}

void drawbricks3(int xcord[],int ycord[],int brickarr[][18])
{
	int num;
	int brickx1,bricky1,brickx2,bricky2;
	COLORREF color;
	COLORREF peach = RGB(255,178,102);
	COLORREF black = RGB(0,0,0);
	color=peach;

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<18;j=j+1)
		{
			brickx1=xcord[j];
			brickx2=brickx1+30;
			bricky1=ycord[i];
			bricky2=bricky1+10;
			num=decidebrick();
			brickarr[i][j]=num;
			if(num==0)
			{
				myRect(brickx1,bricky1,brickx2,bricky2,color,color);	//bricks
				drawrectangle(brickx1,bricky1,brickx2,bricky2);
			}
			else if(num==1)
			{
				myRect(brickx1,bricky1,brickx2,bricky2,color,color);	//bricks
				drawtriangle(brickx1,bricky1,brickx2,bricky2);
			}
			else if(num==2)
			{
				myRect(brickx1,bricky1,brickx2,bricky2,color,color);	//bricks
				drawparallelogram(brickx1,bricky1,brickx2,bricky2);
			}
			else if(num==3)
			{
				myRect(brickx1,bricky1,brickx2,bricky2,color,color);	//bricks
				drawcircle(brickx1,bricky1,brickx2,bricky2);
			}
			else
				myRect(brickx1,bricky1,brickx2,bricky2,color,color);
		}
	}
}

void drawoldbricks(int xcord[],int ycord[],int brickarr[][18],int brickss[][18],int layers)
{
	int num;
	int brickx1,bricky1,brickx2,bricky2;
	COLORREF color;
	COLORREF peach = RGB(255,178,102);
	COLORREF black = RGB(0,0,0);
	color=peach;

	for(int i=0;i<layers;i++)
	{
		for(int j=0;j<18;j=j+1)
		{
			if(brickss[i][j]==0)
			{
				brickx1=xcord[j];
				brickx2=brickx1+30;
				bricky1=ycord[i];
				bricky2=bricky1+10;
				num=brickarr[i][j];
				if(num==0)
				{
					myRect(brickx1,bricky1,brickx2,bricky2,color,color);	//bricks
					drawrectangle(brickx1,bricky1,brickx2,bricky2);
				}
				else if(num==1)
				{
					myRect(brickx1,bricky1,brickx2,bricky2,color,color);	//bricks
					drawtriangle(brickx1,bricky1,brickx2,bricky2);
				}
				else if(num==2)
				{
					myRect(brickx1,bricky1,brickx2,bricky2,color,color);	//bricks
					drawparallelogram(brickx1,bricky1,brickx2,bricky2);
				}
				else if(num==3)
				{
					myRect(brickx1,bricky1,brickx2,bricky2,color,color);	//bricks
					drawcircle(brickx1,bricky1,brickx2,bricky2);
				}
				else
					myRect(brickx1,bricky1,brickx2,bricky2,color,color);
			}
		}	
	}
}

void removeup(COLORREF black,int i,int j,int brickss[][18],int xcord[],int ycord[])
{
		int hx1,hx2,hy1,hy2;
		hx1=xcord[j];			//Removing upper brick
		hx2=hx1+30;
		hy1=ycord[i-1];
		hy2=hy1+10;
		brickss[i-1][j]=1;
		myRect(hx1,hy1,hx2,hy2,black,black);
}

void removedown(COLORREF black,int i,int j,int brickss[][18],int xcord[],int ycord[])
{
		int hx1,hx2,hy1,hy2;
		hx1=xcord[j];			//Removing lower brick
		hx2=hx1+30;
		hy1=ycord[i+1];
		hy2=hy1+10;
		brickss[i+1][j]=1;
		myRect(hx1,hy1,hx2,hy2,black,black);
}

void removeleft(COLORREF black,int i,int j,int brickss[][18],int xcord[],int ycord[])
{
	int hx1,hx2,hy1,hy2;
		hx1=xcord[j-1];			//Removing left brick
		hx2=hx1+30;
		hy1=ycord[i];
		hy2=hy1+10;
		brickss[i][j-1]=1;
		myRect(hx1,hy1,hx2,hy2,black,black);
}

void removeright(COLORREF black,int i,int j,int brickss[][18],int xcord[],int ycord[])
{
		int hx1,hx2,hy1,hy2;
		hx1=xcord[j+1];			//Removing right brick
		hx2=hx1+30;
		hy1=ycord[i];
		hy2=hy1+10;
		brickss[i][j+1]=1;
		myRect(hx1,hy1,hx2,hy2,black,black);
}

int addlayer(int i,int j,int brickss[][18],int&score,int&layers,int xcord[],int ycord[],int&total)
{
	COLORREF color= RGB(255,178,102);
	COLORREF black = RGB(0,0,0);
	int hx1,hx2,hy1,hy2;
	int points;
	int brickx1,bricky1,brickx2,bricky2;
	hx1=xcord[j];
	hx2=hx1+30;
	hy1=ycord[i];
	hy2=hy1+10;
	bool layerbroken=true;
	for(int a=0;a<18;a++)
	{
		if(brickss[layers][a]==0)
			layerbroken=false;
	}
	if(layerbroken==true)
		layers=layers-1;

	if(layers==7)
	{
		points=-5;
		total=total-1;
	}
	else
	{
		total=total+17;
		points=0;
		layers=layers+1;
		for(int a=0;a<18;a++)
		{
			brickx1=xcord[a];
			brickx2=brickx1+30;
			bricky1=ycord[layers-1];
			bricky2=bricky1+10;
			myRect(brickx1,bricky1,brickx2,bricky2,color,color);
		}
		for(int a=0;a<18;a++)
		{
			brickss[layers-1][a]=0;
		}
	}
	return points;
}

int halflife(int i,int j,int brickss[][18],int&red,int&lives,int&score,int xcord[],int ycord[],int&total)
{
	int points;
	COLORREF black = RGB(0,0,0);
	COLORREF grey = RGB(128,128,128);
	int hx1,hx2,hy1,hy2;
	hx1=xcord[j];
	hx2=hx1+30;
	hy1=ycord[i];
	hy2=hy1+10;
	myRect(hx1,hy1,hx2,hy2,black,black);
	red=red+1;
	total=total-1;
	if(red==2)
	{
		lives=lives-1;
		red=0;
		if(lives==1)
		{
			myRect(890,55,930,95,black,black);
			myDrawTextWithFont(900,55,40,"1",grey,black);
		}
		else if(lives==2)
		{
			myRect(890,55,930,95,black,black);
			myDrawTextWithFont(900,55,40,"2",grey,black);
		}
		else if(lives==3)
		{
			myRect(890,55,930,95,black,black);
			myDrawTextWithFont(900,55,40,"3",grey,black);
		}
		else if(lives==4)
		{
			myRect(890,55,930,95,black,black);
			myDrawTextWithFont(900,55,40,"4",grey,black);
		}
		else if(lives==5)
		{
			myRect(890,55,930,95,black,black);
			myDrawTextWithFont(900,55,40,"5",grey,black);
		}
	}
	points=0;
	return points;
}

int adjacentbricks(int i,int j,int brickss[][18],int&score,int xcord[],int ycord[],int&total,int&layers)
{
	int points;
	points=10;
	int breaking=1;
	COLORREF black = RGB(0,0,0);
	if(i==0)
	{
		if(j==0)
		{
			if(brickss[i+1][j]==0)
				breaking=breaking+1;
			if(brickss[i][j+1]==0)
				breaking=breaking+1;
		}
		else if(j==17)
		{
			if(brickss[i+1][j]==0)
				breaking=breaking+1;
			if(brickss[i][j-1]==0)
				breaking=breaking+1;
		}
		else
		{
			if(brickss[i+1][j]==0)
				breaking=breaking+1;
			if(brickss[i][j-1]==0)
				breaking=breaking+1;
			if(brickss[i][j+1]==0)
				breaking=breaking+1;
		}
		removeleft(black,i,j,brickss,xcord,ycord);
		removeright(black,i,j,brickss,xcord,ycord);
		removedown(black,i,j,brickss,xcord,ycord);	
		total=total-breaking;
		
	}
	else if(i==layers)
	{
		if(j==0)
		{
			if(brickss[i-1][j]==0)
				breaking=breaking+1;
			if(brickss[i][j+1]==0)
				breaking=breaking+1;
		}
		else if(j==17)
		{
			if(brickss[i-1][j]==0)
				breaking=breaking+1;
			if(brickss[i][j-1]==0)
				breaking=breaking+1;
		}
		else
		{
			if(brickss[i-1][j]==0)
				breaking=breaking+1;
			if(brickss[i][j-1]==0)
				breaking=breaking+1;
			if(brickss[i][j+1]==0)
				breaking=breaking+1;
		}
		removeleft(black,i,j,brickss,xcord,ycord);
		removeright(black,i,j,brickss,xcord,ycord);
		removeup(black,i,j,brickss,xcord,ycord);	
		total=total-breaking;
	}
	else if(j==0)
	{
		if(brickss[i+1][j]==0)
			breaking=breaking+1;
		if(brickss[i-1][j]==0)
			breaking=breaking+1;
		if(brickss[i][j+1]==0)
			breaking=breaking+1;
		removeright(black,i,j,brickss,xcord,ycord);
		removedown(black,i,j,brickss,xcord,ycord);
		removeup(black,i,j,brickss,xcord,ycord);
		total=total-breaking;
	}
	else if(j==17)
	{
		if(brickss[i+1][j]==0)
			breaking=breaking+1;
		if(brickss[i-1][j]==0)
			breaking=breaking+1;
		if(brickss[i][j-1]==00)
			breaking=breaking+1;
		removeleft(black,i,j,brickss,xcord,ycord);
		removedown(black,i,j,brickss,xcord,ycord);
		removeup(black,i,j,brickss,xcord,ycord);
		total=total-breaking;
	}
	else
	{
		if(brickss[i+1][j]==0)
			breaking=breaking+1;
		if(brickss[i-1][j]==0)
			breaking=breaking+1;
		if(brickss[i][j-1]==0)
			breaking=breaking+1;
		if(brickss[i][j+1]==0)
			breaking=breaking+1;

		removeright(black,i,j,brickss,xcord,ycord);
		removeleft(black,i,j,brickss,xcord,ycord);
		removedown(black,i,j,brickss,xcord,ycord);
		removeup(black,i,j,brickss,xcord,ycord);
		total=total-breaking;
	}
	return points;
}

int addlife(int i,int j,int brickss[][18],int&lives,int&score,int xcord[],int ycord[],int&total)
{
	int points;
	COLORREF black = RGB(0,0,0);
	COLORREF grey = RGB(128,128,128);
	total=total-1;
	if(lives<5)
	{
		lives=lives+1;
		points=0;
	}
	else
		points=10;

	if(lives==1)
		{
			myRect(890,55,930,95,black,black);
			myDrawTextWithFont(900,55,40,"1",grey,black);
		}
	else if(lives==2)
		{
			myRect(890,55,930,95,black,black);
			myDrawTextWithFont(900,55,40,"2",grey,black);
		}
	else if(lives==3)
		{
			myRect(890,55,930,95,black,black);
			myDrawTextWithFont(900,55,40,"3",grey,black);
		}
		else if(lives==4)
		{
			myRect(890,55,930,95,black,black);
			myDrawTextWithFont(900,55,40,"4",grey,black);
		}
		else if(lives==5)
		{
			myRect(890,55,930,95,black,black);
			myDrawTextWithFont(900,55,40,"5",grey,black);
		}
	return points;
}

int simplehit(int i,int j,int brickss[][18],int&score,int xcord[],int ycord[],int&total)
{
	int points;
	total=total-1;
	points=2;
	return points;
}

int brickdecision(int i,int j,int brickarr[][18],int&lives,int&score,int&layers,int brickss[][18],int xcord[],int ycord[],int&red,int&total)
{
	int num;
	int points;
	num=brickarr[i][j];
	if(num==0)
		points=addlayer(i,j,brickss,score,layers,xcord,ycord,total);
	else if(num==1)
		points=halflife(i,j,brickss,red,lives,score,xcord,ycord,total);
	else if(num==2)
		points=adjacentbricks(i,j,brickss,score,xcord,ycord,total,layers);
	else if(num==3)
		points=addlife(i,j,brickss,lives,score,xcord,ycord,total);
	else
		points=simplehit(i,j,brickss,score,xcord,ycord,total);
	return points;
}

void drawcircle(int x1,int y1,int x2,int y2)
{
	COLORREF green = RGB(0,204,0);
	myEllipse(x1+12,y1+2,x2-12,y2-2,green,green);
}

void drawtriangle(int x1,int y1,int x2,int y2)
{
	int size=5;
	COLORREF red = RGB(255,0,0);
	for(int i=-size;i<size;i++)
	{
		myLine(x1+15,y2-2,x1+15+i,y1+2,red);
	}
}

void drawparallelogram(int x1,int y1,int x2,int y2)
{
	COLORREF yellow = RGB (255,255,0);
	for(int i=12;i<18;i++)
	{
		myLine((x1+i)-2,y2-3,x1+i,y1+2,yellow);
	}
}

void drawrectangle(int x1,int y1,int x2,int y2)
{
	COLORREF grey = RGB(50,50,50);
	myRect(x1+5,y1+2,x2-5,y2-2,grey,grey);
}

bool decidehighscore(int highscores[20],string scoresnames[20],int score,string name)
{
	int temp1;
	string temp2;
	bool high=false;
	stringstream ss;  
	ss<<score;  
	string scoring;  
	ss>>scoring;  
	if(score>highscores[9])
	{
		highscores[9]=score;
		scoresnames[9]=scoring + "-" + name;
		high=true;
	}

	for(int i=0;i<10;i++)
	 {
		 for(int j=0;j<10-i;j++)
		 {
			if(highscores[j]<highscores[j+1])
			 {
				 temp1=highscores[j];
				 highscores[j]=highscores[j+1];
				 highscores[j+1]=temp1;
				 temp2=scoresnames[j];
				 scoresnames[j]=scoresnames[j+1];
				 scoresnames[j+1]=temp2;
			 }
		 }
	 }
	return high;
}

void showhighscores()
{
	COLORREF grey = RGB(128,128,128);
	COLORREF black = RGB(00,00,00);
	string scoresnames[20];
	int highscores[20];
	int count=0,len,pos;
	string linescore;
	string line;
	ifstream ScoreReadFile("highscores.txt");
		while(!ScoreReadFile.eof())
		{
			ScoreReadFile>>line;
			len=line.length();
			pos=line.find("-");
			scoresnames[count]=line.substr(pos+1,len-pos);
			linescore=line.substr(0,pos);
			stringstream geek(linescore);
			geek>>highscores[count];
			count++;
		}
		ScoreReadFile.close();
		cout<<endl<<endl<<endl<<endl<<endl;
		for(int i=0;i<10;i++)
			if(i==9)
				cout<<"      "<<i+1<<"-"<<scoresnames[i]<<" : "<<highscores[i];
			else
				cout<<"      "<<i+1<<"-"<<scoresnames[i]<<" : "<<highscores[i]<<endl<<endl;
		myDrawTextWithFont(10,10,40,"Top 10 high scores",grey,black);
		myLine(5,5,270,5,grey);		//Upper horizontal line
		myLine(270,5,270,400,grey);	//Right vertical line
		myLine(5,400,270,400,grey);	//Lower horizontal line
}

int decidebrick()
{
	int num;
	num=rand()%15;
	return num;
}