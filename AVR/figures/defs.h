#ifndef DEFS_H_
#define DEFS_H_

#undef		F_CPU
#define 	F_CPU				1000000L
#define 	BAUD				9600L
#define		SET_BIT(reg, bit)	reg |= (1<<bit)
#define		CLR_BIT(reg, bit)	reg &= (~(1<<bit))
#define		INV_BIT(reg, bit)	reg ^= (1<<bit)
#define		LED_PIN				0
#define		TMR_CNTR			50

#endif /* DEFS_H_ */