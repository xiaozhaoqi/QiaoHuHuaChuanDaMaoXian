#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct ball{
	int x,y;
	int speed;	
}BALL;

void qiaohu(int x1,int x2,double JiFen);
void qiaohuDel(int x1,int x2,double JiFen);
void anjiao(BALL anjiao);
void anjiaoDel(BALL anjiao);
void baobei(BALL baowu);
void baobeiDel(BALL baowu);
void speedup(BALL baowu);
void allkill(BALL baowu);
void speedupDel(BALL baowu);
void allkillDel(BALL baowu);
void game();
void save(char *user,double *score);
int paihangbang();
int End();





int main()
{
    IMAGE back,rule,Start;
	MOUSEMSG mouse,Mouse,MOuse;
	int i=0,x1=100,x2=300,v=5,speed_qiaohu=5,m=1,temp=1,lv=0;
	BALL *baowu,*anjiaoball;
	double JiFen=50,countdown;
	srand( (unsigned int)GetCurrentTime() ); 
	char name[20];
	char endtime[1000];
	InputBox(name,20,"�������û�������Enter������\n");
	printf("�������Ѷ�ϵ��\n���޴���2����Ȼ��\n���ִ�С���Ѷ������\n");
	scanf("%d",&lv);
	initgraph(800, 600);
	graphdefaults();
	loadimage(&rule,_T("IMAGE"), _T("rule"),800,600);
	putimage(0,0,800,600,&rule,0,0,SRCINVERT);
    setbkmode(TRANSPARENT);
    clock_t start,end;  
    graphdefaults();
//���ܴ���
	while(1)
	{
restart:
		game();
        baowu=(BALL*)malloc(lv*sizeof(BALL));
		anjiaoball=(BALL*)malloc(lv*sizeof(BALL));
     	for(i=2;i<lv;i++)//����Ͱ���������Դ���
		{ 
			baowu[i].y=rand()%250+250;
	    	baowu[i].x=650-rand()%100;
			baowu[i].speed=2;
		}
        for(i=0;i<2;i++)//����Ͱ���������Դ���
		{ 
			baowu[i].y=rand()%250+250;
	    	baowu[i].x=1500-rand()%100;
			baowu[i].speed=3;
		}

      	for(i=0;i<lv;i++)
		{
	        anjiaoball[i].y=rand()%250+250;
			anjiaoball[i].x=650-rand()%100;
			anjiaoball[i].speed=2;
		}

	    BeginBatchDraw();
		if(MouseHit())
			{
			     mouse=GetMouseMsg();
			}
        if((mouse.uMsg==WM_LBUTTONDOWN)&&(mouse.x<800)&&(mouse.x>720)&&(mouse.y>20)&&(mouse.y<50))
		{
			cleardevice();
			start = clock();
			graphdefaults();
			setfillcolor(BLACK);
			solidrectangle(300,300,600,500);
	        while(1)
			{
	change:				
			setbkmode(TRANSPARENT);//����ͼƬ����
			graphdefaults();
			loadimage(&back,_T("IMAGE"), _T("back"),800,600);
			putimage(0,0,800,600,&back,0,0,SRCPAINT);
			if(MouseHit())
			{
			     Mouse=GetMouseMsg();
			}
			if((Mouse.uMsg==WM_LBUTTONDOWN)&&(Mouse.x<800)&&(Mouse.x>720)&&(Mouse.y>140)&&(Mouse.y<170))//��������ť�˳�����
			{
				return 1;
			}

			if((Mouse.uMsg==WM_LBUTTONDOWN)&&(Mouse.x<800)&&(Mouse.x>720)&&(Mouse.y>80)&&(Mouse.y<110))//��ͣ��������ť
			{
				FlushMouseMsgBuffer();
		    	EndBatchDraw();
				graphdefaults();
            	setorigin(720,90);
				setbkmode(TRANSPARENT);
             	settextcolor(RED);
	            settextstyle(20, 10, _T("����"));
              	char jixu[] = "�Ҽ�����";
                outtext(jixu);
				graphdefaults();
			    setorigin(0,300);
				setbkmode(TRANSPARENT);
             	settextcolor(RED);
             	settextstyle(30, 20, _T("����"));
				char jixu1[] = "��Ϸ����ͣ�����Ҽ����������ť";
				outtext(jixu1);
				while(Mouse.uMsg!=WM_RBUTTONDOWN)
				{
					Mouse=GetMouseMsg();
				}
				cleardevice();
				graphdefaults();
            	setorigin(720,90);
				setbkmode(TRANSPARENT);
               	settextcolor(RED);
              	settextstyle(20, 10, _T("����"));
              	char zanting[] = "�����ͣ";
                outtext(zanting);
				BeginBatchDraw();
				
			}	
			for(i=0;i<lv;i++)
			{ 
		       	baowu[i].x-=baowu[i].speed;
			}

           	for(i=0;i<lv;i++)
			{
	    		anjiaoball[i].x-=anjiaoball[i].speed;
			}
			end = clock();
		    graphdefaults();
	        qiaohu(x1,x2,JiFen);
			for(i=2;i<lv;i++)
			{ 
			    baobei(baowu[i]);
			}

         	for(i=0;i<lv;i++)
			{
				anjiao(anjiaoball[i]);
			}
	        speedup(baowu[0]);
	    	allkill(baowu[1]);
	      	graphdefaults();
	        game();
	      	Sleep(10);
		  	graphdefaults();
    	    FlushBatchDraw();
	      	setlinecolor(BLACK);
          	setfillcolor(BLACK);
			solidrectangle(0,0,800,600);
	        game();
	       	qiaohuDel(x1,x2,JiFen);
			for(i=2;i<lv;i++)
			{ 
			    baobeiDel(baowu[i]);
			}

         	for(i=0;i<lv;i++)
			{
	            anjiaoDel(anjiaoball[i]);
			}
	      	speedupDel(baowu[0]);
			allkillDel(baowu[1]);
            graphdefaults();  
	      	if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)//��Ϸ�а�Esc��ʱ�˳�����
			     return 1;
		    if(kbhit()) //�����ɻ��ƶ�
			{
				if((x1<=720)&&(x2<=440)&&(x2>=90)&&(x1>=0))
				{
			         if(GetAsyncKeyState(38) & 0x8000)
		                 	x2=x2-speed_qiaohu;
		             if(GetAsyncKeyState(37) & 0x8000)
		 	             	x1=x1-speed_qiaohu;
			         if(GetAsyncKeyState(40) & 0x8000)
                            x2=x2+speed_qiaohu;
		           	 if(GetAsyncKeyState(39) & 0x8000)
			            	x1=x1+speed_qiaohu;
				}
		        else
				{
			         if(x1>=720)
			             x1=720;
		        	 if(x1<=0)
				         x1=0;
		        	 if(x2>=440)
			             x2=440;
		    	     if(x2<=90)
			     	     x2=90;
				}
			}
			//������ѭ��
			for(i=2;i<lv;i++)
			{
	           if(sqrt((x1+65-baowu[i].x)*(x1+65-baowu[i].x)+(x2+65-baowu[i].y)*(x2+65-baowu[i].y))<60)
			   {
				JiFen=JiFen+10;
			    baowu[i].x=650-rand()%250;
				baowu[i].y=rand()%250+250;
			   } 
			}
			for(i=0;i<lv;i++)
			{
	            if(sqrt((x1+65-anjiaoball[i].x)*(x1+65-anjiaoball[i].x)+(x2+65-anjiaoball[i].y)*(x2+65-anjiaoball[i].y))<60)
				{
				    JiFen=JiFen-10;
			    	anjiaoball[i].x=650;
                    anjiaoball[i].y=rand()%250+250;
				}
			}
            if(sqrt((x1+65-baowu[0].x)*(x1+65-baowu[0].x)+(x2+65-baowu[0].y)*(x2+65-baowu[0].y))<60)
			{
		        baowu[0].x=2000;
				baowu[0].y=rand()%250+250;
				speed_qiaohu+=1;
			}
	        if(sqrt((x1+65-baowu[1].x)*(x1+65-baowu[1].x)+(x2+65-baowu[1].y)*(x2+65-baowu[1].y))<60)
			{
				JiFen=JiFen+100*(lv-2);
				baowu[1].x=3000;
				baowu[1].y=rand()%250+250;
                for(i=2;i<lv;i++)
		           baowu[i].x=650;
			}


			for(i=0;i<lv;i++)//���������˶�
			{
	    		if(baowu[i].x<0)
				{
					if(i==1)
						baowu[1].x=3000;
					if(i==0)
						baowu[0].x=2500;
					baowu[i].x=650;
					baowu[i].y=rand()%250+250;
				}
				if(anjiaoball[i].x<0)
				{
					anjiaoball[i].x=650;
					anjiaoball[i].y=rand()%250+250;
				}
			}
		 
	    	char jifen[1000];
	    	sprintf(jifen,"%6f",JiFen);
			char count[1000];double time,wintime;    //��ʱ����
			time=((double)end-start)/CLK_TCK;
			countdown=(double)60-time;
			sprintf(count,"%4f",countdown);
			if(JiFen<1)                 //��Ϸʧ�ܽ���
			{
				EndBatchDraw();
				while(temp==1)
				{
                    save(name,&JiFen);
			    	temp++;
				}
				End();
				if(MessageBox(NULL,TEXT("��սʧ�ܣ��Ƿ�����һ�֣�"),TEXT("ʤ���˱��ҳ���"),MB_OKCANCEL)==IDOK)
				{  
						x1=200;
					x2=200;
					JiFen=50;
				    goto restart;
				}
				else
					return 1;
			}
			if(MouseHit())
			{
			     MOuse=GetMouseMsg();
			}
			if((MOuse.uMsg==WM_LBUTTONDOWN)&&(MOuse.x<800)&&(MOuse.x>720)&&(MOuse.y>210)&&(MOuse.y<240))//�����Ѷ�
			{
				for(i=0;i<lv;i++)
				{
					anjiaoball[i].speed+=1;
				}
				goto change;
			}
		    if((MOuse.uMsg==WM_LBUTTONDOWN)&&(MOuse.x<800)&&(MOuse.x>720)&&(MOuse.y>270)&&(MOuse.y<300))//�����Ѷ�
			{
				for(i=0;i<lv;i++)
				{
                    baowu[i].speed+=1;
				}
				goto change;
			}
		
			if(time<60)
			{
				
                graphdefaults();
            	settextcolor(WHITE);
             	settextstyle(40, 20, _T("����"));
		        char jieshu5[] = "�յ㵹��ʱ��";
		     	setorigin(0,550);
                outtext(jieshu5);
                outtext(count);
		        graphdefaults();
				wintime=time;
				sprintf(endtime,"%4f",wintime);
			}

			if(time>60&&JiFen>0)                    //��Ϸͨ�ؽ���
			{
				IMAGE c;
			
				EndBatchDraw();
				while(temp==1)
				{
                    save(name,&JiFen);
			    	temp++;
				}
		    	End();
				Sleep(5000);
				closegraph();
                initgraph(800, 600);
				loadimage(&c,_T("IMAGE"), _T("c"));
	            putimage(550,150,247,340,&c,0,0,SRCINVERT);
				graphdefaults();

				setorigin(250,50);
				settextcolor(RED);
				settextstyle(60,40,_T("����"),10,10,1000,false,false,false);
				char jieshu1[] = "��ս�ɹ�";
                outtext(jieshu1);
                graphdefaults();
				settextstyle(40,20, _T("����"));
				char jieshu2[] = "���ּ���ͳ�ƣ�";
				setorigin(100,175);
                outtext(jieshu2);
                graphdefaults();
				settextstyle(40,20, _T("����"));
				char jieshu3[] = "�÷֣�";
				setorigin(100,225);
                outtext(jieshu3);
				outtext(jifen);
				graphdefaults();
				settextstyle(40,20, _T("����"));
				char jieshu4[] = "�û�����";
				setorigin(100,275);
                outtext(jieshu4);
                outtext(name);
				graphdefaults();
				settextstyle(40,20, _T("����"));
				char jieshu6[] = "ͨ����ʱ��";
		     	setorigin(100,325);
                outtext(jieshu6);
                outtext(endtime);
		        graphdefaults();
				Sleep(1000);
				if(MessageBox(NULL,TEXT("��Ϸͨ�أ���������սһ�¸��߷�����"),TEXT("*********You win*********"),MB_OKCANCEL)==IDOK)
				{  
					x1=200;
					x2=200;
					JiFen=50;
				    goto restart;
				}
				else
					return 1;

			}
        	graphdefaults();//������ֵ��ʾ����
        	rectangle(700,450,800,480);
	        graphdefaults();
			setbkmode(TRANSPARENT);
			setbkcolor(BLACK);
           	settextcolor(LIGHTMAGENTA);
        	settextstyle(20, 10, _T("����"));
	        setorigin(710,460);
	    	outtext(jifen);
    	    graphdefaults();//�û�����ʾ����
           	rectangle(700,360,800,390);
          	graphdefaults();
			setbkcolor(BLACK);
			setbkmode(TRANSPARENT);
        	settextcolor(LIGHTMAGENTA);
         	settextstyle(20, 10, _T("����"));
            setorigin(710,370);
            outtext(name);
			}
        }
	 
	}

}


int End()
{
	IMAGE qiaohu;
	initgraph(800, 600);
	paihangbang();
	graphdefaults();
	loadimage(&qiaohu,_T("IMAGE"), _T("b"),800,600);
	putimage(0,0,800,600,&qiaohu,0,0,SRCINVERT);
    return 1;
}


void save(char *user,double *score)//��Ϸ���ݴ���
{
	FILE *fp;
	time_t timep;  
    struct tm *p;  
    time(&timep);  
    p = gmtime(&timep); //��������ʱ��
    fp = fopen("user.txt","a");
	fprintf(fp,"%s\n",user);
	fprintf(fp,"�ɼ���%d",(int)*score);
	fprintf(fp,"��,��Ϸʱ�䣺%d��%d��%d��%dʱ%d��%d��\n",1900+p->tm_year,1+p->tm_mon,p->tm_mday,8+p->tm_hour,p->tm_min,p->tm_sec);
	fclose(fp);
}

int paihangbang()//���а�
{
	typedef struct data
	{
		char name[20];
        char score[200];
	}data;
	FILE *fp;
	data n[300];
	int i=0;
	if((fp = fopen("user.txt","r"))==NULL)
		return 1;
	while(i<20)
	{
	     fgets(n[i].name,20,fp);
         fgets(n[i].score,200,fp);
		 i++;
	}
	graphdefaults();
	i=0;
	while(i<20){
		graphdefaults();
    	settextcolor(GREEN);
    	settextstyle(20, 10, _T("����"));
	    setorigin(50,50+25*i);
        outtext(n[i].name);
		graphdefaults();
    	settextcolor(RED);
    	settextstyle(20, 10, _T("����"));
		setorigin(150,50+25*i);
    	outtext(n[i].score);
		i++;
	}
	return 1;
}


//ͼ�ν���
void game()
{
	graphdefaults();//��ʼ
	setorigin(720,30);	
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(20, 10, _T("����"));
	char s1[] = "���ҿ�ʼ";
    outtext(s1);
    graphdefaults();//��ͣ
	setorigin(720,90);
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(20, 10, _T("����"));
	char s2[] = "�����ͣ";
    outtext(s2);
    graphdefaults();//����
	setorigin(720,150);		
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(20, 10, _T("����"));
	char s3[] = "�������";
    outtext(s3);
	graphdefaults();//�Ѷ�
	setorigin(720,210);		
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(20, 10, _T("����"));
	char s6[] = "�����Ѷ�";
    outtext(s6);
	graphdefaults();//����
	setorigin(720,270);		
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(20, 10, _T("����"));
	char s7[] = "�����Ѷ�";
    outtext(s7);
	graphdefaults();//�û���
	setorigin(725,350);		
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(20, 10, _T("����"));
	char s4[] = "�û���";
   	outtext(s4);
	graphdefaults();//����
	setorigin(735,420);
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(20, 10, _T("����"));
	char s5[] = "����";	
   	outtext(s5);


}

void qiaohu(int x1,int x2,double JiFen)//�ɻ�
{
	int blood;
	blood=(int)JiFen/5.0;
	IMAGE tiger,tiger1;
	setlinecolor(BLACK);
	setfillcolor(BLACK);	
	 fillcircle(x1+65,x2+65,65);
	loadimage(&tiger1,_T("IMAGE"), _T("tiger1"),132,132);
	putimage(x1,x2,132,132,&tiger1,0,0,SRCINVERT);
    graphdefaults();
	setfillcolor(LIGHTRED);
	setlinecolor(LIGHTRED);
	if(JiFen<750)
        fillrectangle(x1,x2-30,x1+blood,x2-40);
	else
		fillrectangle(x1,x2-30,x1+150,x2-40);
	graphdefaults();
}
void qiaohuDel(int x1,int x2,double JiFen)
{
	int blood;
	blood=(int)JiFen/5.0;
	setlinecolor(BLACK);
	setfillcolor(BLACK);
    fillcircle(x1+65,x2+65,65);
    graphdefaults();
	setfillcolor(BLACK);
	setlinecolor(BLACK);	
    if(JiFen<750)
        fillrectangle(x1,x2-30,x1+blood,x2-40);
	else
		fillrectangle(x1,x2-30,x1+150,x2-40);
	graphdefaults();
}
void anjiao(BALL anjiao)//����
{
	setlinecolor(BROWN);
    setfillcolor(BROWN);
	setbkmode(TRANSPARENT);
	settextcolor(LIGHTRED);
	settextstyle(16, 8, _T("����"));
	fillcircle(anjiao.x,anjiao.y,20);
    setorigin(anjiao.x-10,anjiao.y);
	char s1[] = "����";
    outtext(s1);
	graphdefaults();
}
void anjiaoDel(BALL anjiao)
{
    setlinecolor(BLACK);
	setfillcolor(BLACK);
  	fillcircle(anjiao.x,anjiao.y,20);
	graphdefaults();
}
void baobei(BALL baowu)//����
{
	graphdefaults();
	setlinecolor(RED);
    setfillcolor(RED);
	fillcircle(baowu.x ,baowu.y ,30);
	setorigin(baowu.x-10 ,baowu.y );
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(16, 8, _T("����"));
	char s1[] = "����";
    outtext(s1);
	graphdefaults();
}
void baobeiDel(BALL baowu)
{
	graphdefaults();
	setlinecolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(baowu.x ,baowu.y ,30);
	graphdefaults();
}


void speedup(BALL baowu)//������
{
	graphdefaults();
		setlinecolor(RED);
    setfillcolor(RED);
	fillcircle(baowu.x ,baowu.y ,20);
	setorigin(baowu.x-10 ,baowu.y );
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(16, 8, _T("����"));
	char s1[] = "����";
    outtext(s1);
	graphdefaults();
}
void speedupDel(BALL baowu)
{
	graphdefaults();
	setlinecolor(BLACK);
	setfillcolor(BLACK);
    fillcircle(baowu.x ,baowu.y ,20);
	graphdefaults();
}



void allkill(BALL baowu)//����
{
	graphdefaults();
		setlinecolor(RED);
    setfillcolor(RED);
	fillcircle(baowu.x ,baowu.y ,10);
	setorigin(baowu.x-10 ,baowu.y );
	setbkmode(TRANSPARENT);
	settextcolor(LIGHTBLUE);
	settextstyle(16, 8, _T("����"));
	char s1[] = "����";
    outtext(s1);
	graphdefaults();
}
void allkillDel(BALL baowu)
{
	graphdefaults();
	setlinecolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(baowu.x ,baowu.y ,10);
	graphdefaults();
}
