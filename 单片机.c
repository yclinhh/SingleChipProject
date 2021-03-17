#include<reg51.h>
#include<stdio.h>
#include<absacc.h>
#include<intrins.h>
#define unint unsigned int
#define unchar unsigned char
xdata unsigned char  col_address _at_ 0X8002;           //�е�ַ
xdata unsigned char  key_address _at_ 0x8001;		   //�е�ַ
xdata unsigned char row_low _at_ 0xb002;
xdata unsigned char row_hign _at_ 0xb003;  //�е�ַ
xdata unsigned char col_low _at_ 0xb000;	   //�е�ַ
xdata unsigned char col_hign _at_ 0xb001;

unint array[20];                //����N�ַ��������
unint anum=0; 
unint speed1=10,speed2=20,speed3=30,speed4=20,speed5=10,speed6=20;
unchar n=6,flag=6;				 //flag=0x00,ִ��Ĭ�Ϸ�����flag=0x0f,ѡ���������ѡ��״̬��flag=0x0e,ȷ�ϼ� ;n���ڽ��ռ�ֵ                
unchar speedflag=6;   //�ٶȿ��Ʊ�־
unint choice=0;  //ѡ���ȫ�ֱ�������choiceΪ0������£���ȡ����ֵ�����switch��䣬��Ϊ1��ʱ�򣬲�����switch��䣬��ȡ����ֵ�������飬
                 //����ȡ����ֵΪ0x0e(ȷ�ϼ�)ʱ���¸�ֵchoiceΪ0
unchar mark=1;
unchar matrixnum;//������ʾ�̶�ͼ���л���������
code unchar Font[][32]={
                       {0x00,0x00,0x00,0x00,0x80,0x01,0xC0,0x03,0xE0,0x07,0xF0,0x0F,0xF8,0x1F,0xFC,0x3F,
0xFC,0x3F,0xFE,0x7F,0xFE,0x7F,0xFE,0x7F,0xFE,0x7F,0x7C,0x3E,0x38,0x1C,0x00,0x00,}, 	  //����
                       {0xF0,0xFF,0x60,0xC0,0xC0,0xC0,0x9C,0xC1,0x22,0xC1,0xEA,0xC3,0x02,0xC4,0x06,0xE4,
0x0C,0x60,0x18,0x60,0x90,0x61,0x10,0x70,0x20,0x20,0x40,0x27,0x40,0x29,0xC0,0x30,},	  //��
					   {0x00,0x00,0xF8,0x1F,0x0C,0x30,0xFC,0x3F,0x86,0x61,0xDE,0x7B,0x82,0x41,0xFE,0x7F,
0x06,0x60,0x8C,0x31,0xDA,0x5B,0x62,0x4E,0x27,0xE4,0x22,0x44,0x70,0x0E,0x20,0x04,},	  //��
{0xF9,0x9F,0x01,0x80,0xF3,0xCF,0x07,0xE0,0x1F,0xF8,0x3F,0xFC,0x3F,0xFC,0x3F,0xFC,
0xBF,0xFD,0x07,0xE0,0x7F,0xFE,0x3F,0xFC,0x1F,0xF8,0x1F,0xF8,0x1F,0xF8,0x3F,0xFC,},
                       {0x00,0x00,0x04,0x40,0x18,0x30,0x68,0x2C,0x90,0x12,0x10,0x11,0x20,0x08,0x10,0x10,0x08,0x20,0x04,0x40,0x3E,0xF8,0x40,0x04,0x80,0x02,0x80,0x02,0x00,0x01,0x00,0x01,},
                       {0x00,0x00,0x04,0x40,0x18,0x30,0x78,0x3C,0xF0,0x1E,0xF0,0x1F,0xE0,0x0F,0xF0,0x1F,0xF8,0x3F,0xFC,0x7F,0xFE,0xFF,0xC0,0x07,0x80,0x03,0x80,0x03,0x00,0x01,0x00,0x01,},
					   {0xC0,0x07,0x30,0x18,0x08,0x20,0x04,0x40,0x04,0x40,0x02,0x81,0x82,0x83,0xC2,0x87,0x82,0x83,0x02,0x81,0x04,0x40,0x04,0x40,0x08,0x20,0x30,0x18,0xC0,0x07,0x00,0x00,},
					   {0xC0,0x07,0x30,0x18,0x88,0x23,0x64,0x4C,0x14,0x50,0x12,0x90,0x0A,0xA0,0x0A,0xA0,0x0A,0xA0,0x12,0x90,0x14,0x50,0x64,0x4C,0x88,0x23,0x30,0x18,0xC0,0x07,0x00,0x00,},
					   {0x00,0x00,0x00,0x00,0xC0,0x07,0x60,0x0C,0x30,0x18,0x18,0x30,0x58,0x34,0xD8,0x37,0xD8,0x37,0x58,0x34,0x18,0x30,0x30,0x18,0x60,0x0C,0xC0,0x07,0x00,0x00,0x00,0x00,},
					   {0x00,0x00,0x00,0x00,0x84,0x43,0x68,0x2C,0x10,0x10,0x08,0x20,0x08,0x20,0x04,0x40,0x04,0x40,0x04,0x40,0x08,0x20,0x08,0x20,0x10,0x10,0x68,0x2C,0x84,0x43,0x00,0x00,},
};
code unchar keytable[]=
						 {0x16,0x15,0x14,0xff,
						 0x13,0x12,0x11,0x10,
						 0x0d,0x0c,0x0b,0x0a,
						 0x0e,0x03,0x06,0x09,
						 0x0f,0x02,0x05,0x08,
						 0x00,0x01,0x04,0x07};
void LED1();
void LED2();
void LED3();
void LED4();
void LED5();
void LED6();
void LED7();
void matrix0();
void speedcontrol(unchar a);						 
void (*q[])()={LED1,LED2,LED3,LED4,LED5,LED6,LED7};
void delay(unint delaytime)   //��ʱdelaytime ms
{ 
   unint i,j;
  
   for(i=123;i>0;i--)
      for(j=delaytime;j>0;j--);
	  
}
void flash(unint a)  //����˸����
{  unint i=2;
   while(i--)
   {   if(mark==0) break;
	   P1=0xff;
	   delay(a);
	   P1=0x00;			   
	   delay(a);
   }
   P1=0xff;
}
void LED0()           //Ĭ��ִ�м�������������д������������Ĭ�ϼ���ѭ�����ú���ָ�����飻
{ 	 
	unint j=1,i;
	flash(10);

		for(i=0;i<7;i++)
		{ if(mark==0) break;
		//    matrix0();
		    matrixnum=i;	  //��������¼�������
			(*q[i])();
		}
		j=0;
	
}
void LED1()   //ѭ����ˮ���ٵ���
{	
	unint j=8;
	P1=0x01;
	while(j--)
	{	 if(mark==0)break;
		P1=_crol_(P1,1);
		delay(speed1);
	}
	flash(10);
}
void LED2()				//˳��ȫ������
{
	unint i=8;
	unchar k=0x80,q=0x80;
	P1=k;
	while(i--)
	{	
	    if(mark==0)break;
		P1=k;
		delay(speed2);
		q=_cror_(q,1);
		k=k|q;
	}
}
void LED3()					   //�����߿�ʼѭ����ˮ����
{ unint i=8;
  unchar k=0x80,q=0x01,j;
 
  while(i--)
  {	if(mark==0) break;
    j=k|q;
    P1=j;
	  delay(speed3);
	  k=_cror_(k,1);
	  q=_crol_(q,1);
  }

}
void LED4()					//��˫����˸
{
 unint i=4;
  while(i--)
	{  if(mark==0) break;
		P1=0xaa;
		delay(speed4);
		P1=0x55;
		delay(speed4);
	} 
}
void LED5()				  //ͬɫ��˳�ε���
{
   unint i=2;
   unchar r=0x92,y=0x048,g=0x25;
  while(i--)
  {	  if(mark==0) break;
      P1=r;
	  delay(speed5);
	  P1=g;
	  delay(speed5);
	  P1=y;
	  delay(speed5);
  }
}
void LED6()			
{
	unchar k=0x80,q=0x01,r=0x00;
	unint i=10;
	while(i--)
	{  if(mark==0)break;
		r=k|q|r;
		P1=r;
		delay(speed6);	
		k=_crol_(k,1);
		q=_cror_(q,1);
		if(i==5)
		{  
		   flash(20);
		    r=0x00;
		}
	}
}

void choose()    //ѡ�������
{	
	unint k,j,i=1;
	while(i--)
	{
		for(j=0;j<anum;j++)
		{  if(mark==0) break;
			k=array[j]-1;    //��������ȡ�����淽�������
			matrixnum=k+1;   //��������¼�������
			(*q[k])();     //������ŵ��ú���ָ�������еĺ���
		}
	}
}
void speedcontrol(unchar a)//�ٶȿ��ƺ���
{
	if(a==0x0b)
	{
		switch(flag)
		{
			case 1:if((speed1-5)<10)
				      _nop_();
			       else
							 speed1-=5;break;
			case 2:if((speed2-5)<10)
				      _nop_();
			       else
							 speed2-=5;break;			
			case 3:if((speed3-5)<10)
				      _nop_();
			       else
							 speed3-=5;break;			
			case 4:if((speed4-5)<10)
				      _nop_();
			       else
							 speed4-=5;break;
			case 5:if((speed5-5)<10)
				      _nop_();
			       else
							 speed5-=5;break;			
			case 6:if((speed6-5)<10)
				      _nop_();
			       else
							 speed6-=5;break;
		}
  }
	if(a==0x0c)
	{
				switch(flag)
		{
			case 1: speed1+=5;break;
			case 2: speed2+=5;break;			
			case 3:speed3+=5;break;			
			case 4:speed4+=5;break;
			case 5:speed5+=5;break;			
			case 6:speed6+=5;break;
		}
	}
}
 void matrix()  //������ʾ����
{	unchar i,f;
	unint bitmask,j;
	bitmask=0x01;
	f=flag;
	if(f==0||f==14)
	  f=matrixnum;
	for(i=0;i<16;i++)
	{
	 row_low=0x00;
	 row_hign=0x00;
	 col_low=~Font[f][i*2];
	 col_hign=~Font[f][i*2+1];
	 row_low=bitmask&0xff;
	 row_hign=bitmask>>8;
//		delay(1);
	 for(j=0;j<350;j++);
	 bitmask<<=1;
	}
	col_low=0xff;
	col_hign=0xff;
}

void matrix0()     //�Զ���������ͼ��
{
    unint p,r;
   	unchar i;
	unint j;
	unint bitmask;
	P1=0xff;
	for(p=0;p<322;p+=2)
	{		bitmask=0x01;

			for(i=0;i<16;i++)
			{if(mark==0)return;
			 row_low=0x00;
			 row_hign=0x00;
			  r=i*2+p;
			  if(r>319)
			  r=r%320;
			 col_low=~Font[0][r];
			 col_hign=~Font[0][r+1];
			 row_low=bitmask&0xff;
			 row_hign=bitmask>>8;
			// delay(1);
			 for(j=0;j<100;j++);
			 bitmask<<=1;
			}	
	}
	col_low=0xff;
	col_hign=0xff;
}
unchar testkey()
{
  col_address=0x00;
  return(~key_address&0x0f);
}
unchar getkey()				//����ɨ�躯��
{
  unchar cyc;
  unchar i;
  unchar sign;	//�ް�������ʱ��signΪ0
  i=6;
  cyc=0x20;
  do{								 //����ɨ�裬sign��Ϊ0ʱ�����а�������
     col_address=~cyc;
	   cyc=_cror_(cyc,1);
	   sign=~key_address&0x0f;
		 i--;						  
    }while((i!=0)&&(sign==0));
  if(sign!=0)
  {
   i*=4;
   if(sign==2)
   i+=1;
   else if(sign==4)
   i+=2;
   else if(sign==8)
   i+=3;
   col_address=0x00;
   do
     {delay(10);}
   while(testkey());		   //ÿ����ʱ10ms��ֱ�������ɿ�
   return(keytable[i]);
  }
  else
  return(0xff);				 //�ް������룬����0xff;
}
void functionkey()			//���ܼ�
{	 
					 
			if(!choice)
			{	 mark=1;
					switch(flag)
					{
						
						case 0:LED0();break;
						case 1:LED1();break;
						case 2:LED2();break;
						case 3:LED3();break;
						case 4:LED4();break;
						case 5:LED5();break;
						case 6:LED6();break;
						case 7:flash(200);break;
						case 13:matrix0();break;
						case 14:choose();break;
				//		case 15:P1=0xff;choice=1;break;    //15�ż�Ϊѡ�����������ѡ�������Ϊȫ��״̬����choiceΪ1���˺��ֵflagֱ�Ӵ�������
						default:break;
					}
			}
		  
}
void time1()	interrupt 3
{
	TR1=0;
	col_low=0xff;
	col_hign=0xff;
	row_low=0x00;
	row_hign=0x00;
    
		switch(flag)
	   {
	  case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 14:matrix();break;
        default:break;
	   }
	TH1=0Xd8;
  TL1=0XF0;
	TR1=1;
}


void time0()interrupt 1         
{ 
	  TH0=0XD8;
     TL0=0XF0;
	  if(testkey())
	  {
	     delay(5);
		  if(testkey())
		   {  
		       mark=0;
		      n=getkey();
				 if(n==0x0b||n==0x0c)
					 speedcontrol(n);
				 else
				 {   flag=n;
					  if(!choice&&flag==15)
					  {
					  P1=0xff;
						choice=1; 
						anum=0;//�����ñ��淽���������±�Ϊ0
					  }
					  if(choice&&flag!=15)
					  {
					     if(flag!=14)
						  array[anum++]=flag;     //��ֵ��������       //anumΪȫ�ֱ�������¼���淽�������� 
						 else
						 choice=0;				  //flag=14����⵽ȷ�ϼ�����choice��0��֮������������ٽ�������
						   
					  }			   
	  		 }
			 }
		}
}

void main(void)
{
  TMOD=0X11;
  EA=1;
  ET0=1;
  TR0=1;
  TH0=0XD8;
  TL0=0XF0;
  ET1=1;
  TR1=1;
  TH1=0Xd8;
  TL1=0XB0;
  while(1)		//�����жϷ�ʽÿ10ms���̶�ʱɨ��һ��
  {	   
     functionkey();
   
   }
}