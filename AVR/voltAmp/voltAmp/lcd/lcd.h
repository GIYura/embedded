#ifndef LCD_H_
#define LCD_H_

#include "../definitions/defs.h"


uint8_t __swap_nibbles(uint8_t aData);

uint8_t lcdInit(void);
//void lcdPrintChar(uint8_t aChar);
uint16_t lcdPrintChar(uint8_t aChar, FILE *stream);
void lcdSetCursor(uint8_t aString, uint8_t aRow);
void lcdPrintData(uint8_t aString, uint8_t aRow, uint16_t aData);

#endif /* LCD_H_ */