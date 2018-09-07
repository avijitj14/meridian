#include<lpc21xx.h>
#include<string.h>
#include"header.h"
#include"delay.h"

#define rs 1<<16
#define rw 1<<17
#define en 1<<18

void lcd_init(void);
void command(unsigned int);
void command1(unsigned int);
void Data(unsigned char);
void Data1(unsigned char);
void pll_init(void);
void vpb_init(void);
void uart_init(void);
void uart_write(unsigned char x);
char get(void);
unsigned char arr[]={0x02,0x28,0x0e,0x06,0x01,0x80};
unsigned char str[]={"Logged In"};
unsigned char str2[]={"Access Denied"};
unsigned int i;

main()
{
	unsigned char y[5];
	unsigned char ps[]={"water"};
	p0=0x00000005;
	p1=p2=0;
	d0=0xfffffffc;
	d1=0xffffffff;
	
	pll_init();
	vpb_init();
	lcd_init();
	uart_init();
	for(i=0;i<5;i++)
	y[i]=get();
	
	if(strcmp(y,ps)==0)
	{i=0;
	s0=(1<<4)|(1<<7);
	delay_ms(1000);
	c0=(1<<4)|(1<<7);		
	while(str[i]!='\0')
	{
		Data1(str[i++]);
		delay_ms(1000);	
	}
	s0=(1<<5)|(1<<6);
	delay_ms(1000);
	c0=(1<<5)|(1<<6);
}
else
{i=0;
	while(str2[i]!='\0')
	{
		Data1(str2[i++]);
		delay_ms(1000);	
}
}
}
void lcd_init()
{
	for(i=0;i<5;i++)
	{
		command1(arr[i]);
	}
}

void command(unsigned int c)
{
s0=(c<<15);	
c0=rs;
c0=rw;
s0=en;
delay_ms(1000);
c0=en;
c0=(c<<15);	
}

void command1(unsigned int a)
{
unsigned int b;
b=(a & 0xf0);
command(b);
delay_ms(1000);	
b=((a<<4)&0xf0);
command(b);
}

void Data(unsigned char f)
{
	s0=(f<<15);
	s0=rs;
	c0=rw;
	s0=en;
	delay_ms(1000);
	c0=en;
	c0=(f<<15);
}

void Data1(unsigned char d)
{
unsigned char e;
e=(d & 0xf0);
Data(e);
e=((d<<4)&0xf0);
Data(e);
}

void uart_init()
{
	int q;
	
	U0LCR=0x83;
	q=15000000/(16*9600);
	U0DLL=q%256;
	U0DLM=q/256;
	U0LCR=0x03;
}

void uart_write(unsigned char x)
{
	U0THR=x;
	while((U0LSR & 0x40)==0);
		}
	
char get(void)
{
	while((U0LSR&0x01)==0);
	return U0RBR;
}

void pll_init()
{
  PLLCON=0x01;
	PLLCFG=0x24;
	PLLFEED=0xaa;
	PLLFEED=0x55;
	
	while(PLLSTAT&0x400==0)
	{
	  PLLCON=0x03;
	  PLLFEED=0xaa;
		PLLFEED=0x55;
}
}

void vpb_init()
{
	VPBDIV=0x01;
}