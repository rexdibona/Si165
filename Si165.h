/*
 * Serial In class. Reads data in through a 74XX165 parallel to serial converter chain.
 *
 * We can daisy chain multiple chips together.
 * The data is read in big endian (first '165 data ends up at the first data location).
 */

#include <inttypes.h>
#include <Arduino.h>

class Si165 {
private:
	uint8_t	_len;	// length of data stream (in bytes)
	uint8_t	_ds;	// Serial data	(chip pin 9)
	uint8_t	_sclk;	// Shift register clock (chip pin 2)
	uint8_t	_pl;	// Load register with parallel data (chip pin 1)
public:
	Si165(uint8_t len, uint8_t ds, uint8_t sclk, uint8_t pl);
	void	read(uint8_t *data);
};
