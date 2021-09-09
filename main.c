#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int

sbit START = P2^2;
sbit OE = P2^1;
sbit EOC = P2^0;
sbit CLK = P2^3;

sbit LED = P1^1;

uint stop = 0;
uint data dydata;

void delay(void) {
	uint i;
	for (i = 0; i < 1000; i++);
}

void send_byte() {
	SBUF = dydata * 220 / 78;
	while(TI==0)
	TI=0;	
}
void init() {
	SCON = 0x50;
	TMOD = 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	PCON = 0x00;
	//TR1=1;
	REN=1;
	SM0=0;
	SM1=1;
	//EA=1;
	//ES=1;
	
	EA = 1; EX0 = 1; IT0 = 1;
	ES = 1; IP = 0x01;
	TR1 = 1;
}

void main() {
		init();
    while(1) {
			if (stop == 1) {
				LED = 0;
				continue;
			}
			START = 1;
			START = 0;
			while(EOC == 0);
			OE = 1;
			dydata=P0;
			OE = 0;
			send_byte();
			delay();
		}
}

void Serial_INT() interrupt 4 {
	uchar c;
	if (RI == 0) return;
	ES = 0;
	RI = 0;
	c = SBUF;
	stop = 1;
	ES = 1;
	LED = 1;
}