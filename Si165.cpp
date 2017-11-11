/*
 * Code to deal with the 74XX165 style parallel to serial converters.
 *
 * We are allowed single or multiple chips daisy chained together
 */
#include "Si165.h"

Si165::Si165(uint8_t len, uint8_t ds, uint8_t sclk, uint8_t pl)
{
	_len = len;	// number of chips daisy chained
	_ds = ds;	// data input pin (Q7 ouput from 165)
	_sclk = sclk;	// clock to pin 2 or 15 of '165
	_pl = pl;	// parallel load (active low) pin (1)
	
	pinMode(_ds, INPUT);
	pinMode(_sclk, OUTPUT);
	pinMode(_pl, OUTPUT);
	digitalWrite(_sclk, HIGH);	/* default is HIGH for clocks */
	digitalWrite(_pl, HIGH);	/* default is HIGH for Load */
}

void
Si165::read(uint8_t *data)
{
	digitalWrite(_pl, LOW);		/* load data - clock is HIGH */
	digitalWrite(_pl, HIGH);
	for (uint8_t i = 0; i < _len; i++) {
		uint8_t	d = 0;
		for (uint8_t j = 0; j < 8; j++) {	/* read in a byte */
			d >>= 1;
			digitalWrite(_sclk, LOW);
			if (digitalRead(_ds) == HIGH) {
				d |= 0x80;
			}
			digitalWrite(_sclk, HIGH);	/* and back to HIGH */
		}
		*data++ = d;
	}
}
