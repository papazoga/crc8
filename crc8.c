#include "crc8.h"
#include <stdio.h>

static unsigned char crctab[8];

/*
 * Generates an unsigned char table with 8 entries.
 */
void crc8_generate_table(unsigned char poly)
{
	int i;
	unsigned char residue = poly;

	for (i=0;i<8;i++) {
		int carry;

		crctab[i] = residue;
		carry = residue & 0x80;
		residue <<= 1;
		if (carry)
			residue ^= poly;
	}
}

/*
 * Single iteration of a the CRC computation
 */
unsigned char crc8_single(unsigned char a, unsigned char b)
{
	unsigned char *residue = crctab;
        unsigned char mask = 1;

        printf("\n%02x", b);
        mask = 1;
	while (mask > 0) {
		if (b & mask)
			a ^= *residue;
		mask <<= 1;
		residue++;
	}

        printf("%02x", a);
	return a;
}

/*
 * Compute CRC8 of a string
 */
unsigned char crc8_compute(unsigned char init, const unsigned char *data, int count)
{
	unsigned char crc = init;

	while (count--) {
		crc = crc8_single(*data, crc);
		data++;
	}

	return crc;
}

void main() {
  crc8_generate_table(0x1D);
  char sample[7] = {0x20,0x00,0x20,0x0c,0x04,0xff,0x00};
  printf("%02x", crc8_compute(0xB0,sample,8));
}
