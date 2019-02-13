//--------------------------------------------------------------//
//						ÂÍÅØÍÈÅ ÔÀÉËÛ							//
//--------------------------------------------------------------//
#include <stdlib.h>
#include <stdio.h>
//#include <avr/interrupt.h>
#include "uart.h"
#include "periph_ini.h"
//--------------------------------------------------------------//
//							ÎÏÐÅÄÅËÅÍÈß							//
//--------------------------------------------------------------//
//--------------------------------------------------------------//
//						ÃËÎÁÀËÜÍÛÅ ÏÅÐÅÌÅÍÍÛÅ					//
//--------------------------------------------------------------//

//--------------------------------------------------------------//
//						ÏÐÎÒÎÒÈÏÛ ÔÓÍÊÖÈÉ						//
//--------------------------------------------------------------//
/*ñîçäàíèå ïîòîêà usart_out òèïà FILE
íàçíà÷åíèå ôóíêöèè usart_putchar äëÿ âûâîäà â ïîòîê*/
FILE usart_output = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE usart_input = FDEV_SETUP_STREAM(NULL, usart_getchar, _FDEV_SETUP_READ);
//--------------------------------------------------------------//
//						ÎÑÍÎÂÍÀß ÔÓÍÊÖÈß						//
//--------------------------------------------------------------//
int main(void)
{
	stdout = &usart_output;
	stdin = &usart_input;
	port_ini();
	usart_ini();
	uint8_t counter = 10;
	char inchar = '0';
//ðèñîâàíèå òðåóãîëüíèêà
/*
*
**
***
****
*****
******
*******
********
*********
**********
*/
	for (uint8_t i = 0; i < counter; i++)
	{
		for (uint8_t j = 0; j < i + 1; j++)
		{
			printf("%c", '*');
		}
		printf("\r");
	}
	printf("\r\r");

//ðèñîâàíèå ïðèÿìîóãîëüíèêà
/*
**********
**********
**********
**********
**********
**********
**********
**********
**********
**********
*/
	uint8_t i = 0;
	while (i < counter){
		uint8_t j = 0;
		while (j < counter){
			printf("%c", '*');
			j++;
		}
		printf("\r");
		i++;
	}
	printf("\r\r");

//ðèñîâàíèå êîíòóðà ïðÿìîóãîëüíèêà
/*
**********
*        *
*        *
*        *
*        *
*        *
*        *
*        *
*        *
**********
*/
	for (uint8_t i = 0; i < counter; i++)
	{
		for (uint8_t j = 0; j < counter; j++)
		{
			if (j == 0 || j == counter-1 || i == 0 || i == counter-1)
			{
				printf("%c", '*');
			}
			else
			{
				printf("%c", ' ');
			}
		}
	printf("\r");
	}
	printf("\r\r");

//ðèñîâàíèå êîíòóðà òðåóãîëüíèêà
/*
*
**
* *
*  *
*   *
*    *
*     *
*      *
*       *
**********
*/
	for (uint8_t i = 0; i < counter; i++)
	{
		for (uint8_t j = 0; j < i + 1; j++)
		{
			if (j == 0 || j == i || i == counter-1)
			{
				printf("%c", '*');
			}
			else
			{
				printf("%c", ' ');
			}
		}
	printf("\r");
	}
	printf("\r\r");

//ðèñîâàíèå ïðÿìîóãîëüíèêà
/*
***********
**       **
* *     * *
*  *   *  *
*   * *   *
*    *    *
*   * *   *
*  *   *  *
* *     * *
**       **
***********
*/
	for (uint8_t i = 0; i < counter; i++)
	{
		for (uint8_t j = 0; j < counter; j++)
		{
			if (j == 0 || j == counter-1 || i == 0 || i == counter-1 || i == j || j == (counter-1)-i)
			{
				printf("%c", '*');
			}
			else
			{
				printf("%c", ' ');
			}
		}
	printf("\r");
	}
	printf("\r\r");

//ðèñîâàíèå ðîìáà
/*
	 *
    ***
   * * *
  *  *  *
 *   *   *
*    *    *
 *   *   *
  *  *  *
   * * *
    ***
     *
*/
	for (uint8_t i = 0; i < counter+1; i++)
	{
		for (uint8_t j = 0; j < counter+1; j++)
		{
			if (i <= 5)
			{
				if (j==counter/2||j==counter/2-i||j==counter/2+i)
				{
					printf("%c", '*');
				}
				else
				{
					printf("%c", ' ');
				}
			}
			else
			{
				if (j==counter/2||j==counter/2-(counter-i)||j==counter/2+(counter-i))
				{
					printf("%c", '*');
				}
				else
				{
					printf("%c", ' ');
				}
			}
		}
	printf("\r");
	}
	printf("\r\r");
//ðèñîâàíèå ðîìáà
/*
	 *
    * *
   *   *
  *     *
 *       *
*         *
 *       *
  *     *
   *   *
    * *
     *
*/
	for (uint8_t i = 0; i < counter+1; i++)
	{
		for (uint8_t j = 0; j < counter+1; j++)
		{
			if (i <= 5)
			{
				if ((j==counter/2&&i==0)||j==counter/2-i||j==counter/2+i)
				{
					printf("%c", '*');
				}
				else
				{
					printf("%c", ' ');
				}
			}
			else
			{
				if ((j==counter/2&&i==counter)||j==counter/2-(counter-i)||j==counter/2+(counter-i))
				{
					printf("%c", '*');
				}
				else
				{
					printf("%c", ' ');
				}
			}
		}
	printf("\r");
	}
	printf("\r\r");

//-----------------------ÄÈÑÏÅÒ×ÅÐ------------------------------//
	while(1)
	{
		printf("%s\r", "Ââåäèòå ÷èñëî îò 0 äî 9");
		scanf("%c", &inchar);
		switch(inchar)
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			printf("%s%c\r", "Âû ââåëè ÷èñëî ", inchar); break;
			default:
			printf("%s\n", "ÎØÈÁÊÀ! Âû ââåëè íåâåðíîå ÷èñëî");
		}
	}
	return 0;
}
