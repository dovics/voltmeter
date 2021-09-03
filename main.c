#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int

sbit START = P2^2;
sbit OE = P2^1;
sbit EOC = P2^0;
sbit CLK = P2^3;

uchar data led[4];

uint data dydata;
uchar code tv[] = {0xfe, 0xfd, 0xfb, 0xf7};
uchar code a[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 
									0x6d, 0x7d, 0x07, 0x7f, 0x6f};
void delay(void) {
	uint i;
	for (i = 0; i < 10; i++);
}

void ledshow(void) {
	uchar k;
	
	dydata = 100 * dydata;
	dydata = dydata / 51;
	led[0] = dydata % 10;
	led[1] = dydata / 10 % 10;
	led[2] = dydata / 100 % 10;
	led[3] = dydata / 1000;
	
	for (k = 0; k < 4; k++) {
		P3 = tv[k];
		P1 = a[led[k]];
		delay();
	}
}

void main() {
    while(1) {
			START = 1;
			START = 0;
			while(EOC == 0);
			OE = 1;
			dydata=P0;
			OE = 0;
			ledshow();
			delay();
		}
}