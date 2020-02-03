#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
struct gmdata
{
	char nums[16][3];
	int cr_p;
	int mov;
	int swp;
	double rtm;
}gt;

struct hscore
{
	char p_name[50];
	int scr;
	double ttm;
}hs;

struct hepls
{
	char command[40];
	char desc[300];
}hlp;

int todo=0;
int co_move;
int hswap=1;
int tttime;
double prtm=0;
void calc(int[],int);
void show_help();
int can_move(int,int);
int swap(int[],int,int);
int complete(int []);
void win_main(int);
void win_todo(int);
void exchanges(int,char [][5]);
char *int_inp(int[],char [][5]);
void number_swp(int [],char[][5]);
void show_hs(struct hscore);
void save_score();
void save_scr_scn();
void main()
{
	FILE *f1;
	int cur_pos=0,*pos;
	int num_ar[16],i,j,rn;
	char qu='t',*endptr;
	int cur_on=1,move_dir;
	int cor[5],rs=0;
	char numss[2][5];
	time_t tstart,tends;

	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
	errorcode = graphresult();
	if (errorcode != grOk)
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);
	}

	randomize();

MAIN_WINDOW :
{
	// main window label start
	cur_on=1;
	cleardevice();
	win_main(cur_on);
	while(1)
	{
		move_dir=getch();
		if(move_dir==72 || move_dir==105)
		{
			if(cur_on==1)
			{
				cur_on=4;
				cleardevice();
				win_main(cur_on);
			}
			else
			{
				cur_on--;
				cleardevice();
				win_main(cur_on);
			}
		}
		if(move_dir==80 || move_dir==107)
		{
			if(cur_on==4)
			{
				cur_on=1;
				cleardevice();
				win_main(cur_on);
			}
			else
			{
				cur_on++;
				cleardevice();
				win_main(cur_on);
			}
		}
		if(move_dir==13)
		{
			if(cur_on==4)
			{
				exit(0);
			}
			if(cur_on==1)
			{
				goto RESUME;
			}
			if(cur_on==2)
			{
				goto NEW_GAME;
			}
			if(cur_on==3)
			{
				goto HEIGH_SCORE;
			}
		}

	}
};

RESUME:
{
	//struct gmdata gt;
	FILE *f2;
	rs=0;
	if((f2=fopen("game\\GameData\\game_data.dat","r"))==NULL)
	{
		cleardevice();
		setcolor(RED);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(100,150,500,300);
		settextstyle(1,0,2);
		outtextxy(150,200,"FILE NOT FIND TO READ DATA");
		getch();
		exit(0);
	}
	else
	{
		rs=fread(&gt,sizeof(gt),1,f2);
		fclose(f2);
		if(rs==0)
		{
			cleardevice();
			setcolor(RED);
			setfillstyle(SOLID_FILL,YELLOW);
			bar(100,150,500,300);
			settextstyle(1,0,2);
			outtextxy(200,200,"FILE NOT READ");
			getch();
			goto RESTART;
		}
		else
		{
			for(i=0;i<16;i++)
			{
				num_ar[i]=(int)strtol(gt.nums[i],&endptr,10);
			}
			hswap=gt.swp;
			co_move=gt.mov;
			cur_pos=gt.cr_p;
			prtm=gt.rtm;
		}
	}
	tstart=time(NULL);
	goto START;

};

NEW_GAME:
{
	goto RESTART;
};

HEIGH_SCORE:
{
	if((f1=fopen("game\\GameData\\score.dat","r"))==NULL)
	{
		cleardevice();
		setcolor(RED);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(80,150,600,300);
		settextstyle(7,0,3);
		outtextxy(200,200,"SCORE FILE NOT FOUND");
		getch();
	}
	else
	{
		fread(&hs,sizeof(hs),1,f1);
		fclose(f1);
		show_hs(hs);
	}
	goto MAIN_WINDOW;

};

RESTART:
{

	for(i=0;i<16;i++)
	{
		num_ar[i]=0;
	}
	for(i=0;i<16;i++)
	{
		if(i==9)
		{
			num_ar[i]=0;
			cur_pos=i;
		}
		else
		{
			int ok=0;
			while(ok==0)
			{
				rn=random(16);
				ok=1;
				for(int j=0;j<16;j++)
				{
					if(rn==num_ar[j])
					{
						ok=0;
						break;
					}
				}
			}
			num_ar[i]=rn;
		}
	}
	co_move=0;
	hswap=1;
	tstart=time(NULL);
	prtm=0;
};

START:
{
	int cc,rs;
	while(1)
	{

		cleardevice();
		calc(num_ar,cur_pos);
		cc=getch();
		switch(cc)
		{
			case 72:
			case 105:
				rs=can_move(1,cur_pos);
				if(rs==1)
				{
					cur_pos=swap(num_ar,cur_pos,1);
					co_move++;
				}
				break;
			case 75:
			case 106:
				rs=can_move(2,cur_pos);
				if(rs==1)
				{
					cur_pos=swap(num_ar,cur_pos,2);
					co_move++;
				}
				break;
			case 77:
			case 108:
				rs=can_move(3,cur_pos);
				if(rs==1)
				{
					cur_pos=swap(num_ar,cur_pos,3);
					co_move++;
				}
				break;
			case 80:
			case 107:
				rs=can_move(4,cur_pos);
				if(rs==1)
				{
					cur_pos=swap(num_ar,cur_pos,4);
					co_move++;
				}
				break;
			case 24:
				setcolor(RED);
				setfillstyle(SOLID_FILL,YELLOW);
				bar(10,150,400,300);
				settextstyle(7,0,3);
				outtextxy(200,200,"Do you want to exit (Y/N)?");
				qu=getch();
				if(qu=='y' || qu=='Y')
				{
					struct gmdata gd;
					if((f1=fopen("game\\GameData\\game_data.dat","w+"))==NULL)
					{
						cleardevice();
						setcolor(RED);
						setfillstyle(SOLID_FILL,YELLOW);
						bar(10,150,500,300);
						settextstyle(7,0,3);
						outtextxy(250,225,"FILE NOT FIND TO WRITE DATA");
						getch();

					}
					else
					{
						tends=time(NULL);
						for(i=0;i<16;i++)
						{
							sprintf(gd.nums[i],"%d",num_ar[i]);
						}
						gd.swp=hswap;
						gd.mov=co_move;
						gd.cr_p=cur_pos;
						gd.rtm=difftime(tends,tstart)+prtm;
						rs=fwrite(&gd,sizeof(gd),1,f1);
						fclose(f1);
						if(rs==0)
						{
							cleardevice();
							setcolor(RED);
							setfillstyle(SOLID_FILL,YELLOW);
							bar(10,150,500,300);
							settextstyle(7,0,3);
							outtextxy(100,225,"DATA NOT SAVE TO RESUME");
							getch();

						}
					}
					exit(0);
				}
				break;

			case 18:
				setcolor(RED);
				setfillstyle(SOLID_FILL,YELLOW);
				bar(0,150,400,300);
				settextstyle(7,0,3);
				outtextxy(200,225,"Do you want to restart (Y/N)?");
				qu=getch();
				if(qu=='y' || qu=='Y')
				{
					goto RESTART;
				}
				break;
			case 20:
				if(todo==0)
				{
					todo=1;
				}
				else
				{
					todo=0;
				}
				cc=0;
				break;
			case 8:
				goto HELP;
				//show_help();


		}
		rs=complete(num_ar);
		if(rs==1)
		{
			tends=time(NULL);
			tttime=difftime(tends,tstart);
			cleardevice();
			setcolor(RED);
			setfillstyle(SOLID_FILL,YELLOW);
			bar(100,150,500,300);
			settextstyle(7,0,5);
			outtextxy(300,200,"   DONE   ");
			getch();
			save_score();
			cleardevice();
			setcolor(RED);
			setfillstyle(SOLID_FILL,YELLOW);
			bar(100,150,500,300);
			outtextxy(300,200,"Complete!!");
			settextstyle(7,0,3);
			outtextxy(300,250,"Do you want to restart (Y/N)?");
			qu=getch();
			if(qu=='y' || qu=='Y')
			{
				goto RESTART;
			}
			else
			{
				exit(0);
			}
		}
		if(todo==1)
		{
			goto TODO;
		}
	}

};

TODO:
{
	cleardevice();
	cur_on=1;
	calc(num_ar,cur_pos);
	win_todo(cur_on);
	while(1)
	{
		move_dir=getch();
		if(move_dir==72 || move_dir==105)
		{
			if(cur_on==1)
			{
				cur_on=5;
				cleardevice();
				calc(num_ar,cur_pos);
				win_todo(cur_on);
			}
			else
			{
				cur_on--;
				cleardevice();
				calc(num_ar,cur_pos);
				win_todo(cur_on);
			}
		}
		if(move_dir==80 || move_dir==107)
		{
			if(cur_on==5)
			{
				cur_on=1;
				cleardevice();
				calc(num_ar,cur_pos);
				win_todo(cur_on);
			}
			else
			{
				cur_on++;
				cleardevice();
				calc(num_ar,cur_pos);
				win_todo(cur_on);
			}
		}
		if(move_dir==13)
		{
			todo=0;
			if(cur_on==5)
			{
				goto START;
			}
			if(cur_on==1)
			{
				goto RESTART;
			}
			if(cur_on==2)
			{
				goto NUMBER_SWAP;
			}
			if(cur_on==3)
			{
				goto SAVE_AND_EXIT;
			}
			if(cur_on==4)
			{
				goto HELP;
			}

		}

	}
};

NUMBER_SWAP:
{

	for(i=0;i<2;i++)
	{
		strcpy(numss[i],"");
	}
	cur_on=1;
	while(1)
	{
		cleardevice();
		exchanges(cur_on,numss);
		move_dir=getch();
		if(move_dir==72 || move_dir==105)
		{
			if(cur_on==1)
			{
				cur_on=4;
				cleardevice();
				exchanges(cur_on,numss);
			}
			else
			{
				cur_on--;
				cleardevice();
				exchanges(cur_on,numss);
			}
		}
		if(move_dir==80 || move_dir==107)
		{
			if(cur_on==4)
			{
				cur_on=1;
				cleardevice();
				exchanges(cur_on,numss);
			}
			else
			{
				cur_on++;
				cleardevice();
				exchanges(cur_on,numss);
			}
		}
		if(move_dir==13)
		{
			if(cur_on==4)
			{
				goto START;
			}
			if(cur_on==1)
			{
				cor[0]=10;
				cor[1]=180;
				cor[2]=350;
				cor[3]=220;
				cor[4]=cur_on;
				strcpy(numss[0],int_inp(cor,numss));
			}
			if(cur_on==2)
			{
				cor[0]=10;
				cor[1]=280;
				cor[2]=350;
				cor[3]=320;
				cor[4]=cur_on;
				strcpy(numss[1],int_inp(cor,numss));
			}
			if(cur_on==3)
			{
				if(hswap>0)
				{
					number_swp(num_ar,numss);
				}
				else
				{
					cleardevice();
					setcolor(RED);
					setfillstyle(SOLID_FILL,YELLOW);
					bar(100,150,500,300);
					settextstyle(1,0,2);
					outtextxy(200,200,"YOU HAVE NOT ANY SWAP");
					getch();
				}
				goto START;
			}
		}

	}
};

SAVE_AND_EXIT:
{
	struct gmdata gd;
	if((f1=fopen("game\\GameData\\game_data.dat","w+"))==NULL)
	{
		cleardevice();
		setcolor(RED);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(10,150,500,300);
		settextstyle(7,0,3);
		outtextxy(100,225,"FILE NOT FIND TO SAVE DATA");
		getch();

	}
	else
	{
		tends=time(NULL);
		for(i=0;i<16;i++)
		{
			sprintf(gd.nums[i],"%d",num_ar[i]);
		}
		gd.swp=hswap;
		gd.mov=co_move;
		gd.cr_p=cur_pos;
		gd.rtm=difftime(tends,tstart)+prtm;
		rs=fwrite(&gd,sizeof(gd),1,f1);
		if(rs==0)
		{
			cleardevice();
			setcolor(RED);
			setfillstyle(SOLID_FILL,YELLOW);
			bar(10,150,500,300);
			settextstyle(7,0,3);
			outtextxy(100,225,"NO DATA WRITTEN TO FILE ");
			getch();

		}
		else
		{
			cleardevice();
			setcolor(RED);
			setfillstyle(SOLID_FILL,YELLOW);
			bar(10,150,500,300);
			settextstyle(7,0,3);
			outtextxy(100,225,"DATA SAVE SUCCESSFULLY!!");
			getch();
		}
	}
	fclose(f1);
	exit(0);
};

HELP:
{
	show_help();
	goto START;
};


}

char *char_inp(int cor[5])
{
	int h,q,l,i,t,cr;
	char inp[50];
	char chp[50],*endptr;
	char ch='0';
	char ap[50]="",bp[50],cp[50],dp[50];
	h=cor[0]+10;
	i=cor[1]+10;
	settextstyle(1,HORIZ_DIR,2);

	while(ch!='\r')
	{

		save_scr_scn();
		setcolor(YELLOW);
		setfillstyle(1,RED);
		h=cor[0]+10;
		i=cor[1]+10;
		settextstyle(1,HORIZ_DIR,2);
		bar(cor[0],cor[1],cor[2],cor[3]);
		outtextxy(h,i,ap);
		ch=getch();

			if(ch=='\b')
			{
				strcpy(bp,ap);
				strrev(bp);
				q=strlen(bp)-1;
				i=0;
				while(q>0)
				{
					cp[i]=bp[q];
					i++;
					q--;
				}
				cp[i]='\0';
				strcpy(ap,cp);
			}

			if(ch=='a' || ch=='b'|| ch=='c'|| ch=='d' || ch=='e' || ch=='f'|| ch=='g' || ch=='h'|| ch=='i'|| ch=='j' || ch=='k' || ch=='l' || ch=='m' || ch=='n'|| ch=='o'|| ch=='p' || ch=='q' || ch=='r'|| ch=='s' || ch=='t'|| ch=='u'|| ch=='v' || ch=='w' || ch=='x' || ch=='y' || ch=='z')
			{
				sprintf(chp,"%c",ch);
				strcat(ap,chp);
			}
			if(ch==' ' || ch=='A' || ch=='B'|| ch=='C'|| ch=='D' || ch=='E' || ch=='F'|| ch=='G' || ch=='H'|| ch=='I'|| ch=='J' || ch=='K' || ch=='L' || ch=='M' || ch=='N'|| ch=='O'|| ch=='P' || ch=='Q' || ch=='R'|| ch=='S' || ch=='T'|| ch=='U'|| ch=='V' || ch=='W' || ch=='X' || ch=='Y' || ch=='Z')
			{
				sprintf(chp,"%c",ch);
				strcat(ap,chp);
			}


	 }
	 strcpy(dp,ap);
	 return(dp);
}

void save_scr_scn()
{
		cleardevice();
		settextjustify(0,2);
		setbkcolor(CYAN);
		setcolor(GREEN);
		setfillstyle(SOLID_FILL,BLUE);
		settextstyle(7,0,3);
		bar(100,100,500,300);
		outtextxy(110,130,"ENTER THE PLAYER NAME : ");
		bar(100,200,500,300);

}

void save_score()
{
	struct hscore ohs;
	FILE *f1,*f2;
	int cr[5],l;
	if((f1=fopen("game\\GameData\\score.dat","r+"))==NULL)
	{
		l=0;

	}
	else
	{

		fread(&ohs,sizeof(ohs),1,f1);

		if(ohs.scr>co_move)
		{
			l=0;
		}
		else if(ohs.scr==co_move)
		{
			if(ohs.ttm>=tttime)
			{
				l=0;
			}
			else
			{
				l=1;
			}
		}
		else
		{
			l=1;
		}
	}
	fclose(f1);
	if((f1=fopen("game\\GameData\\score.dat","w+"))==NULL)
	{
		cleardevice();
		setbkcolor(CYAN);
		setcolor(RED);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(100,150,500,300);
		settextstyle(1,0,2);
		outtextxy(150,200,"FILE NOT FIND TO WRITE DATA");
		getch();

	}
	else
	{
		if(l==0)
		{
			cr[0]=100;
			cr[1]=200;
			cr[2]=500;
			cr[3]=300;
			cr[4]=0;
			strcpy(hs.p_name,char_inp(cr));
			hs.ttm=tttime;
			hs.scr=co_move;
			fwrite(&hs,sizeof(hs),1,f1);
			fclose(f1);
			cleardevice();
			setbkcolor(CYAN);
			setcolor(RED);
			setfillstyle(SOLID_FILL,YELLOW);
			bar(100,150,500,300);
			settextstyle(1,0,2);
			outtextxy(200,200,"SCORE SAVE ");
			getch();
			settextjustify(1,1);
		}
	}
}

void number_swp(int ar[16],char inps[2][5])
{
	long num1,num2;
	int n1_p,n2_p,temp,i;
	char *endptr;
	num1=strtol(inps[0],&endptr,10);
	num2=strtol(inps[1],&endptr,10);
	if((num1<1 || num1>15) || (num2<1 || num2>15))
	{
		cleardevice();
		setcolor(RED);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(100,150,500,300);
		settextstyle(1,0,2);
		outtextxy(200,200,"NOT VAILID NUMBERS");
		getch();


	}
	else if(num1==num2)
	{
		cleardevice();
		setcolor(RED);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(100,150,500,300);
		settextstyle(1,0,2);
		outtextxy(150,200,"SAME NUMBER CAN NOT SWAP");
		getch();
	}
	else
	{
		for(i=0;i<16;i++)
		{
			if(ar[i]==num1)
			{
				n1_p=i;
			}
			if(ar[i]==num2)
			{
				n2_p=i;
			}
		}
		temp=ar[n1_p];
		ar[n1_p]=ar[n2_p];
		ar[n2_p]=temp;
		hswap--;
	}
}

void exchanges(int cur,char inps[2][5])
{

	cleardevice();
	setbkcolor(CYAN);
	setcolor(GREEN);
	setfillstyle(SOLID_FILL,BLUE);
	bar(0,0,400,450);

	//title bar
	setcolor(GREEN);
	settextjustify(0,2);
	settextstyle(0,0,3);
	setfillstyle(SOLID_FILL,6);
	bar(0,0,400,30);
	outtextxy(10,5,"NUMBER ARRANGE");
	setfillstyle(SOLID_FILL,RED);
	// exit button location
	bar(370,0,400,30);
	outtextxy(375,5,"X");

	// main menu-bar location
	setfillstyle(SOLID_FILL,WHITE);
	bar(0,30,400,50);

	settextjustify(1,1);
	settextstyle(7,0,2);
	setfillstyle(SOLID_FILL,WHITE);
	setcolor(WHITE);
	outtextxy(200,80,"ENTER THE NUMBERS");
	outtextxy(200,100,"TO EXCHANGE");
	setcolor(YELLOW);

	settextjustify(0,2);
	outtextxy(10,150,"ENTER THE FIRST NUMBER :");
	bar(10,180,350,220);
	setcolor(BLUE);
	outtextxy(20,190,inps[0]);

	outtextxy(10,250,"ENTER THE SECOND NUMBER :");
	bar(10,280,350,320);
	setcolor(BLUE);
	outtextxy(20,290,inps[1]);

	setcolor(RED);
	bar(10,350,200,390);
	outtextxy(60,360,"SUBMIT");
	bar(10,400,200,440);
	outtextxy(60,410,"CANCEL");

	if(cur==1)
	{
		setfillstyle(SOLID_FILL,GREEN);
		bar(10,180,350,220);
		outtextxy(20,190,inps[0]);
	}
	else if(cur==2)
	{
		setfillstyle(SOLID_FILL,GREEN);
		bar(10,280,350,320);
		outtextxy(20,290,inps[1]);
	}
	else if(cur==3)
	{
		setfillstyle(SOLID_FILL,GREEN);
		bar(10,350,200,390);
		outtextxy(60,360,"SUBMIT");
	}
	else
	{
		setfillstyle(SOLID_FILL,GREEN);
		bar(10,400,200,440);
		outtextxy(60,410,"CANCEL");
	}



}

char *int_inp(int cor[5],char inps[2][5])
{
	int h,q,l,i,t=0,cr=cor[4];
	char inp[50];
	char chp[50],*endptr;
	char ch='0';
	char ap[50]="",bp[50],cp[50],dp[50];
	h=cor[0]+10;
	i=cor[1]+10;

	while(ch!='\r')
	{

		cleardevice();
		//screen
		exchanges(cr,inps);
		setcolor(YELLOW);
		settextjustify(1,1);
		settextstyle(7,0,2);
		setfillstyle(1,RED);
		h=cor[0]+10;
		i=cor[1]+10;
		bar(cor[0],cor[1],cor[2],cor[3]);
		outtextxy(h,i,ap);
		ch=getch();

			if(ch=='\b')
			{
				strcpy(bp,ap);
				strrev(bp);
				q=strlen(bp)-1;
				i=0;
				while(q>0)
				{
					cp[i]=bp[q];
					i++;
					q--;
				}
				cp[i]='\0';
				strcpy(ap,cp);
				t--;
			}

			if(ch=='1' || ch=='2' || ch=='3' || ch=='4' || ch=='5' || ch=='6'|| ch=='7'|| ch=='8' || ch=='9' || ch=='0')
			{
				sprintf(chp,"%c",ch);
				strcat(ap,chp);
				t++;
			}
			if(t==2)
			{
				strcpy(dp,ap);
				return(dp);
			}

	 }
	 strcpy(dp,ap);
	 return(dp);
}

void win_todo(int cur)
{
	setfillstyle(SOLID_FILL,WHITE);
	bar(0,50,250,300);
	setcolor(BLUE);
	settextstyle(1,0,2);
	settextjustify(0,1);
	//lines
	rectangle(5,55,245,295);
	line(5,100,245,100);
	line(5,150,245,150);
	line(5,200,245,200);
	line(5,250,245,250);

	outtextxy(10,75,"RESTART    ctrl+R");
	outtextxy(10,125,"NUMBER EX. ctrl+E");
	outtextxy(10,175,"SAVE&EXIT  ctrl+X");
	outtextxy(10,225,"HELP       ctrl+H");
	outtextxy(10,275,"NOTHING");

	if(cur==1)
	{
		setfillstyle(SOLID_FILL,GREEN);
		bar(5,55,245,100);
		setcolor(RED);
		outtextxy(10,75,"RESTART    ctrl+R");
	}
	else if(cur==2)
	{
		setfillstyle(SOLID_FILL,GREEN);
		bar(5,100,245,150);
		setcolor(RED);
		outtextxy(10,125,"NUMBER EX. ctrl+E");
	}
	else if(cur==3)
	{
		setfillstyle(SOLID_FILL,GREEN);
		bar(5,150,245,200);
		setcolor(RED);
		outtextxy(10,175,"SAVE&EXIT  ctrl+X");
	}
	else if(cur==4)
	{
		setfillstyle(SOLID_FILL,GREEN);
		bar(5,200,245,250);
		setcolor(RED);
		outtextxy(10,225,"HELP       ctrl+H");
	}
	else
	{
		setfillstyle(SOLID_FILL,GREEN);
		bar(5,250,245,295);
		setcolor(RED);
		outtextxy(10,275,"NOTHING");
	}

}

void win_main(int cur)
{
	setbkcolor(CYAN);
	setcolor(GREEN);
	setfillstyle(SOLID_FILL,BLUE);
	bar(0,0,400,450);

	//title bar
	setcolor(GREEN);
	settextjustify(0,2);
	settextstyle(0,0,3);
	setfillstyle(SOLID_FILL,6);
	bar(0,0,400,30);
	outtextxy(10,5,"NUMBER ARRANGE");
	setfillstyle(SOLID_FILL,RED);
	// exit button location
	bar(370,0,400,30);
	outtextxy(375,5,"X");

	// main menu-bar location
	setfillstyle(SOLID_FILL,WHITE);
	bar(0,30,400,50);

	setfillstyle(SOLID_FILL,YELLOW);
	bar(0,30,80,50);
	setcolor(GREEN);
	settextstyle(0,0,4);
	settextjustify(0,2);
	//lines
	line(0,150,400,150);
	line(0,250,400,250);
	line(0,350,400,350);

	outtextxy(20,100,"RESUME GAME");
	outtextxy(20,200,"NEW GAME");
	outtextxy(20,300,"HEIGH SCORE");
	outtextxy(20,400,"EXIT");

	if(cur==1)
	{
		setfillstyle(SOLID_FILL,YELLOW);
		bar(0,50,400,150);
		setcolor(RED);
		outtextxy(20,100,"RESUME GAME");
	}
	else if(cur==2)
	{
		setfillstyle(SOLID_FILL,YELLOW);
		bar(0,150,400,250);
		setcolor(RED);
		outtextxy(20,200,"NEW GAME");
	}
	else if(cur==3)
	{
		setfillstyle(SOLID_FILL,YELLOW);
		bar(0,250,400,350);
		setcolor(RED);
		outtextxy(20,300,"HEIGH SCORE");
	}
	else
	{
		setfillstyle(SOLID_FILL,YELLOW);
		bar(0,350,400,450);
		setcolor(RED);
		outtextxy(20,400,"EXIT");
	}

}

int complete(int ar[16])
{
	int i,rt=0;
	for(i=0;i<15;i++)
	{
		if(ar[i]==i+1)
		{
			rt=1;
		}
		else
		{
			rt=0;
			break;
		}
	}
	return rt;
}

int swap(int ar[16],int pos,int to)
{
	int temp;
	if(to==1)
	{
		if(pos==4)
		{
			temp=ar[0];
			ar[0]=ar[pos];
			ar[pos]=temp;
			pos=0;
		}
		else if(pos==5)
		{
			temp=ar[1];
			ar[1]=ar[pos];
			ar[pos]=temp;
			pos=1;
		}
		else if(pos==6)
		{
			temp=ar[2];
			ar[2]=ar[pos];
			ar[pos]=temp;
			pos=2;
		}
		else if(pos==7)
		{
			temp=ar[3];
			ar[3]=ar[pos];
			ar[pos]=temp;
			pos=3;
		}
		else if(pos==8)
		{
			temp=ar[4];
			ar[4]=ar[pos];
			ar[pos]=temp;
			pos=4;
		}
		else if(pos==9)
		{
			temp=ar[5];
			ar[5]=ar[pos];
			ar[pos]=temp;
			pos=5;
		}
		else if(pos==10)
		{
			temp=ar[6];
			ar[6]=ar[pos];
			ar[pos]=temp;
			pos=6;
		}
		else if(pos==11)
		{
			temp=ar[7];
			ar[7]=ar[pos];
			ar[pos]=temp;
			pos=7;
		}
		else if(pos==12)
		{
			temp=ar[8];
			ar[8]=ar[pos];
			ar[pos]=temp;
			pos=8;
		}
		else if(pos==13)
		{
			temp=ar[9];
			ar[9]=ar[pos];
			ar[pos]=temp;
			pos=9;
		}
		else if(pos==14)
		{
			temp=ar[10];
			ar[10]=ar[pos];
			ar[pos]=temp;
			pos=10;
		}
		else if(pos==15)
		{
			temp=ar[11];
			ar[11]=ar[pos];
			ar[pos]=temp;
			pos=11;
		}
		else
		{
		
		}
	}
	if(to==2)
	{
		if(pos==1)
		{
			temp=ar[0];
			ar[0]=ar[pos];
			ar[pos]=temp;
			pos=0;
		}
		else if(pos==5)
		{
			temp=ar[4];
			ar[4]=ar[pos];
			ar[pos]=temp;
			pos=4;
		}
		else if(pos==9)
		{
			temp=ar[8];
			ar[8]=ar[pos];
			ar[pos]=temp;
			pos=8;
		}
		else if(pos==13)
		{
			temp=ar[12];
			ar[12]=ar[pos];
			ar[pos]=temp;
			pos=12;
		}
		else if(pos==2)
		{
			temp=ar[1];
			ar[1]=ar[pos];
			ar[pos]=temp;
			pos=1;
		}
		else if(pos==6)
		{
			temp=ar[5];
			ar[5]=ar[pos];
			ar[pos]=temp;
			pos=5;
		}
		else if(pos==10)
		{
			temp=ar[9];
			ar[9]=ar[pos];
			ar[pos]=temp;
			pos=9;
		}
		else if(pos==14)
		{
			temp=ar[13];
			ar[13]=ar[pos];
			ar[pos]=temp;
			pos=13;
		}
		else if(pos==3)
		{
			temp=ar[2];
			ar[2]=ar[pos];
			ar[pos]=temp;
			pos=2;
		}
		else if(pos==7)
		{
			temp=ar[6];
			ar[6]=ar[pos];
			ar[pos]=temp;
			pos=6;
		}
		else if(pos==11)
		{
			temp=ar[10];
			ar[10]=ar[pos];
			ar[pos]=temp;
			pos=10;
		}
		else if(pos==15)
		{
			temp=ar[14];
			ar[14]=ar[pos];
			ar[pos]=temp;
			pos=14;
		}
		else
		{
		
		}
	}
	if(to==3)
	{
		if(pos==2)
		{
			temp=ar[3];
			ar[3]=ar[pos];
			ar[pos]=temp;
			pos=3;
		}
		else if(pos==6)
		{
			temp=ar[7];
			ar[7]=ar[pos];
			ar[pos]=temp;
			pos=7;
		}
		else if(pos==10)
		{
			temp=ar[11];
			ar[11]=ar[pos];
			ar[pos]=temp;
			pos=11;
		}
		else if(pos==14)
		{
			temp=ar[15];
			ar[15]=ar[pos];
			ar[pos]=temp;
			pos=15;
		}
		else if(pos==0)
		{
			temp=ar[1];
			ar[1]=ar[pos];
			ar[pos]=temp;
			pos=1;
		}
		else if(pos==4)
		{
			temp=ar[5];
			ar[5]=ar[pos];
			ar[pos]=temp;
			pos=5;
		}
		else if(pos==8)
		{
			temp=ar[9];
			ar[9]=ar[pos];
			ar[pos]=temp;
			pos=9;
		}
		else if(pos==12)
		{
			temp=ar[13];
			ar[13]=ar[pos];
			ar[pos]=temp;
			pos=13;
		}
		else if(pos==1)
		{
			temp=ar[2];
			ar[2]=ar[pos];
			ar[pos]=temp;
			pos=2;
		}
		else if(pos==5)
		{
			temp=ar[6];
			ar[6]=ar[pos];
			ar[pos]=temp;
			pos=6;
		}
		else if(pos==9)
		{
			temp=ar[10];
			ar[10]=ar[pos];
			ar[pos]=temp;
			pos=10;
		}
		else if(pos==13)
		{
			temp=ar[14];
			ar[14]=ar[pos];
			ar[pos]=temp;
			pos=14;
		}
		else
		{
		
		}
	}
	if(to==4)
	{
		if(pos==8)
		{
			temp=ar[12];
			ar[12]=ar[pos];
			ar[pos]=temp;
			pos=12;
		}
		else if(pos==9)
		{
			temp=ar[13];
			ar[13]=ar[pos];
			ar[pos]=temp;
			pos=13;
		}
		else if(pos==10)
		{
			temp=ar[14];
			ar[14]=ar[pos];
			ar[pos]=temp;
			pos=14;
		}
		else if(pos==11)
		{
			temp=ar[15];
			ar[15]=ar[pos];
			ar[pos]=temp;
			pos=15;
		}
		else if(pos==0)
		{
			temp=ar[4];
			ar[4]=ar[pos];
			ar[pos]=temp;
			pos=4;
		}
		else if(pos==1)
		{
			temp=ar[5];
			ar[5]=ar[pos];
			ar[pos]=temp;
			pos=5;
		}
		else if(pos==2)
		{
			temp=ar[6];
			ar[6]=ar[pos];
			ar[pos]=temp;
			pos=6;
		}
		else if(pos==3)
		{
			temp=ar[7];
			ar[7]=ar[pos];
			ar[pos]=temp;
			pos=7;
		}
		else if(pos==4)
		{
			temp=ar[8];
			ar[8]=ar[pos];
			ar[pos]=temp;
			pos=8;
		}
		else if(pos==5)
		{
			temp=ar[9];
			ar[9]=ar[pos];
			ar[pos]=temp;
			pos=9;
		}
		else if(pos==6)
		{
			temp=ar[10];
			ar[10]=ar[pos];
			ar[pos]=temp;
			pos=10;
		}
		else if(pos==7)
		{
			temp=ar[11];
			ar[11]=ar[pos];
			ar[pos]=temp;
			pos=11;
		}
		else
		{
		
		}

	}
	return pos;
}

void show_hs(struct hscore th)
{
	char tm[10],tmt[10],p_n[50];
	cleardevice();
	setbkcolor(CYAN);
	setcolor(GREEN);
	settextjustify(1,1);
	setfillstyle(SOLID_FILL,BROWN);
	settextstyle(7,0,3);
	bar(100,20,500,70);
	outtextxy(300,30,"HIGH SCORE");
	settextjustify(0,2);
	setfillstyle(SOLID_FILL,BLUE);
	settextstyle(7,0,3);
	bar(100,70,500,310);
	outtextxy(110,70,"PLAYER NAME : ");
	strcpy(p_n,th.p_name);
	outtextxy(110,110,p_n);
	sprintf(tmt,"%d",th.scr);
	outtextxy(110,150,"TOTAL MOVES : ");
	outtextxy(110,190,tmt);
	sprintf(tm,"%.2lf s",th.ttm);
	outtextxy(110,230,"TOTAL TIME : ");
	outtextxy(110,270,tm);
	getch();
}

int can_move(int ch,int p)
{
	int rt=0;
	if(p==0)
	{
		if(ch==3 || ch== 4)
		{
			rt=1;
		}
		else
		{
			rt=0;
		}
	}
	if(p==1 || p==2)
	{
		if(ch==2 || ch==3 || ch== 4)
		{
			rt=1;
		}
		else
		{
			rt=0;
		}
	}
	if(p==3)
	{
		if(ch==2 || ch== 4)
		{
			rt=1;
		}
		else
		{
			rt=0;
		}
	}
	if(p==4 || p==8)
	{
		if(ch==1 || ch==3 || ch== 4)
		{
			rt=1;
		}
		else
		{
			rt=0;
		}
	}
	if(p==5 || p==6 || p==9 || p==10)
	{
		if(ch==1 || ch==2 || ch==3 || ch== 4)
		{
			rt=1;
		}
		else
		{
			rt=0;
		}
	}
	if(p==7 || p==11)
	{
		if(ch==1 || ch==2 || ch== 4)
		{
			rt=1;
		}
		else
		{
			rt=0;
		}
	}
	if(p==12)
	{
		if(ch==1 || ch==3)
		{
			rt=1;
		}
		else
		{
			rt=0;
		}
	}
	if(p==13 || p==14)
	{
		if(ch==1 || ch==2 || ch==3)
		{
			rt=1;
		}
		else
		{
			rt=0;
		}
	}
	if(p==15)
	{
		if(ch==1 || ch==2)
		{
			rt=1;
		}
		else
		{
			rt=0;
		}
	}
	return rt;
}

void calc(int ar[16],int pos)
{

	char nums[16][3],moved[5],swaps[4];
	int i,x,y,ty,tx;
	for(i=0;i<16;i++)
	{
		if(ar[i]==0)
		{
			sprintf(nums[i]," ");
		}
		else
		{
			sprintf(nums[i],"%d",ar[i]);
		}
	}
	
	setbkcolor(CYAN);
	setcolor(GREEN);
	setfillstyle(SOLID_FILL,BLUE);
	bar(0,0,400,450);

	//title bar
	setcolor(GREEN);
	settextjustify(0,2);
	settextstyle(0,0,3);
	setfillstyle(SOLID_FILL,6);
	bar(0,0,400,30);
	outtextxy(10,5,"NUMBER ARRANGE");
	setfillstyle(SOLID_FILL,RED);
	// exit button location
	bar(370,0,400,30);
	outtextxy(375,5,"X");

	// main menu-bar location
	setfillstyle(SOLID_FILL,WHITE);
	bar(0,30,400,50);

	setfillstyle(SOLID_FILL,YELLOW);
	bar(0,30,80,50);
	setcolor(BLUE);
	settextstyle(0,0,2);
	settextjustify(0,1);
	outtextxy(5,40,"Todo");

	//lines
	setcolor(GREEN);
	line(0,150,400,150);
	line(0,250,400,250);
	line(0,350,400,350);

	line(100,50,100,450);
	line(200,50,200,450);
	line(300,50,300,450);


	setcolor(GREEN);
	settextstyle(0,0,5);

	setcolor(GREEN);
	settextstyle(0,0,5);
	settextjustify(CENTER_TEXT,CENTER_TEXT);

	outtextxy(50,100,nums[0]);
	outtextxy(150,100,nums[1]);
	outtextxy(250,100,nums[2]);
	outtextxy(350,100,nums[3]);

	outtextxy(50,200,nums[4]);
	outtextxy(150,200,nums[5]);
	outtextxy(250,200,nums[6]);
	outtextxy(350,200,nums[7]);

	outtextxy(50,300,nums[8]);
	outtextxy(150,300,nums[9]);
	outtextxy(250,300,nums[10]);
	outtextxy(350,300,nums[11]);

	outtextxy(50,400,nums[12]);
	outtextxy(150,400,nums[13]);
	outtextxy(250,400,nums[14]);
	outtextxy(350,400,nums[15]);

	tx=(pos)%4;
	ty=pos/4;
	x=0+tx*100;
	y=50+ty*100;

	setfillstyle(SOLID_FILL,RED);
	bar(x,y,x+100,y+100);
	
	setcolor(RED);
	settextstyle(0,0,2);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(420,50,639,250);
	outtextxy(530,80,"TOTAL MOVE:");
	sprintf(moved,"%d",co_move);
	outtextxy(530,120,moved);
	
	outtextxy(530,160,"SWAPS:");
	sprintf(swaps,"%d",hswap);
	outtextxy(530,200,swaps);
	
}

void show_help()
{
	int x,y,rs,q=1;
	FILE *f1;
	cleardevice();
	setbkcolor(CYAN);
	setcolor(GREEN);
	setfillstyle(SOLID_FILL,YELLOW);
	settextstyle(7,0,3);
	bar(0,50,250,450);
	setcolor(GREEN);
	setfillstyle(SOLID_FILL,WHITE);
	settextstyle(1,0,2);
	bar(250,50,630,450);

	if((f1=fopen("game\\GameData\\help_cmd.dat","r+"))==NULL)
	{
		setcolor(RED);
		setfillstyle(SOLID_FILL,YELLOW);
		settextstyle(7,0,3);
		bar(50,100,500,300);
		outtextxy(100,225,"FILE NOT FOUND TO READ DATA ");
		getch();
		exit(0);
	}
	else
	{
		setcolor(GREEN);
		setfillstyle(SOLID_FILL,BROWN);
		settextstyle(1,0,3);
		bar(0,0,630,50);
		settextjustify(1,1);
		outtextxy(315,25,"HELP WINDOW");
		settextstyle(1,0,2);

		while(f1)
		{
			x=125;
			y=50+q*30;
			fread(&hlp,sizeof(hlp),1,f1);
			if(feof(f1))
			{
				break;
			}
			setcolor(RED);

			outtextxy(x,y,hlp.command);
			x=440;
			setcolor(BLUE);
			outtextxy(x,y,hlp.desc);
			q++;
		}
		fclose(f1);
		getch();
	}
}

