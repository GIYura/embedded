/*
  RX module
  Board: Arduino UNO R3
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define INIT_SUCCESS  0           //
#define INIT_FAILED   1           //
#define RELAY_IN_1    5           //
#define RELAY_IN_2    6           //
#define LED           13          //

RF24 radio(7, 8);                 //CE, CSN
const byte address[6] = "00001";

String strON = "ON";
String strOFF = "OFF";
char text[32] = "";

void gpioInit(void);
void hwTimerInit(void);
void radioInit(void);

typedef enum
{
  SW_TIMER0 = 0,
  SW_TIMER1,
  SW_TIMER2,
  SW_TIMER_NUMBER,
  SW_TIMER_OFR = 255
} SW_TIMER_IDX;

typedef enum
{
  SW_TIMER_EXPIRED = 0,
  SW_TIMER_UNEXPIRED
} SW_TIMER_STATE;

typedef enum
{
  SW_TIMER_DISABLE = 0,
  SW_TIMER_ENABLE
} SW_TIMER_MODE;

uint8_t swTimerInit(SW_TIMER_IDX aTimer0, SW_TIMER_IDX aTimer1, SW_TIMER_IDX aTimer2);
SW_TIMER_IDX enableSwTimer(SW_TIMER_IDX aSwTimerNumber, uint8_t aTicksNumber);
SW_TIMER_IDX disableSwTimer(SW_TIMER_IDX aSwTimerNumber);
SW_TIMER_STATE isSwTimeout(SW_TIMER_IDX aSwTimerNumber);
void swTimerProcess(void);

#pragma pack(push, 1)
typedef struct swTimer TswTimer;

struct swTimer
{
  uint8_t state     : 1;
  SW_TIMER_IDX number;
  uint16_t tNumber;
  swTimer *pNext;
};
#define T_SW_TIMER_SZ sizeof(TswTimer)
#pragma pack(pop)

TswTimer swTimer[SW_TIMER_NUMBER];

typedef enum {
  ON = 0,
  OFF,
  RELAY_STATE_NUMBER
} RELAY_STATE;
RELAY_STATE relayState = RELAY_STATE_NUMBER;

typedef enum {
  ENTRY = 0,
  DO,
  EXIT
} Tsection;

void (*pFunc[])(void) = {relayOn, relayOff};
void setRelayState(RELAY_STATE newState);
RELAY_STATE getRelayState(void);
void fsmInit(void);
void fsmRun(void);
/*
*/
inline SW_TIMER_IDX &operator++(SW_TIMER_IDX &swTimer){
   return swTimer = SW_TIMER_IDX(swTimer + 1);
}
//======================================================================//
//                              SETUP                                   //
//======================================================================//
void setup() {
  Serial.begin(9600);
  radioInit();
  gpioInit();
  fsmInit();
  hwTimerInit();
  swTimerInit(SW_TIMER0, SW_TIMER1, SW_TIMER2);
}

//======================================================================//
//                                LOOP                                  //
//======================================================================//
void loop() {
   enableSwTimer(SW_TIMER1, 1);                                      //20ms
   if (SW_TIMER_EXPIRED == isSwTimeout(SW_TIMER1)) {
     disableSwTimer(SW_TIMER1);
     enableSwTimer(SW_TIMER1, 1);
     fsmRun();
  }
}

//======================================================================//
//                              GPIO INIT                               //
//======================================================================//
void gpioInit(void) {
  pinMode(RELAY_IN_1, OUTPUT);
  pinMode(RELAY_IN_2, OUTPUT);
}

//======================================================================//
//                           RADIO INIT                                 //
//======================================================================//
void radioInit(void) {
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

//======================================================================//
//                        HARDWARE TIMER INIT                           //
//======================================================================//
/*
  Timer 1 - 16 bit
  atmega run at 16 MHz
  Prescaler = 256
  16/256 = 62.5KHz
  62.5KHz * 20ms = 1250;
  TCNT0 = 65536 - 1250 = 64286
*/
void hwTimerInit(void) {
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << CS12);    //prescaler 256
  TCNT1 = 64286;
  TIMSK1 |= (1 << TOIE1);
  interrupts();
}

//======================================================================//
//                                                                      //
//======================================================================//
uint8_t swTimerInit(SW_TIMER_IDX aTimer0, SW_TIMER_IDX aTimer1, SW_TIMER_IDX aTimer2) {
  if ( (aTimer0 < SW_TIMER0) || (aTimer0 > SW_TIMER2)  ||
       (aTimer1 < SW_TIMER0) || (aTimer1 > SW_TIMER2)  ||
       (aTimer2 < SW_TIMER0) || (aTimer2 > SW_TIMER2)
     )
  {
    return INIT_FAILED;
  }
  swTimer[SW_TIMER0].number = aTimer0;
  swTimer[SW_TIMER1].number = aTimer1;
  swTimer[SW_TIMER2].number = aTimer2;
  for(SW_TIMER_IDX swT = SW_TIMER0; swT < SW_TIMER_NUMBER; ++swT){
    swTimer[swT].tNumber = 0;
    disableSwTimer(swT);
  }
  return INIT_SUCCESS;
}

//======================================================================//
//
//======================================================================//
SW_TIMER_IDX enableSwTimer(SW_TIMER_IDX aSwTimerNumber, uint8_t aTicksNumber)
{
  noInterrupts();
  if ( (aSwTimerNumber < SW_TIMER0) || (aSwTimerNumber > SW_TIMER2) || swTimer[aSwTimerNumber].state == SW_TIMER_ENABLE)
  {
    interrupts();
    return SW_TIMER_OFR;
  }
  swTimer[aSwTimerNumber].state = SW_TIMER_ENABLE;
  swTimer[aSwTimerNumber].tNumber = aTicksNumber;
  interrupts();
  return aSwTimerNumber;
}
//======================================================================//
//
//======================================================================//
SW_TIMER_IDX disableSwTimer(SW_TIMER_IDX aSwTimerNumber)
{
  noInterrupts();
  if ( (aSwTimerNumber < SW_TIMER0) || (aSwTimerNumber > SW_TIMER2) )
  {
    interrupts();
    return SW_TIMER_OFR;
  }
  swTimer[aSwTimerNumber].state = SW_TIMER_DISABLE;
  swTimer[aSwTimerNumber].tNumber = 0;
  interrupts();
  return aSwTimerNumber;
}
//======================================================================//
//
//======================================================================//
SW_TIMER_STATE isSwTimeout(SW_TIMER_IDX aSwTimerNumber)
{
  noInterrupts();
  if ( (aSwTimerNumber < SW_TIMER0) || (aSwTimerNumber > SW_TIMER2))
  {
    interrupts();
    return SW_TIMER_STATE(SW_TIMER_OFR);
  }

  if (swTimer[aSwTimerNumber].tNumber == 0)
  {
    interrupts();
    return SW_TIMER_EXPIRED;
  }
  else
  {
    interrupts();
    return SW_TIMER_UNEXPIRED;
  }
}
//======================================================================//
//
//======================================================================//
void swTimerProcess(void)
{
  for (uint8_t i = 0; i < SW_TIMER_NUMBER; i++)
  {
    if ( (swTimer[i].state == SW_TIMER_ENABLE) && (swTimer[i].tNumber != 0) )
    {
      swTimer[i].tNumber--;
    }
  }
}

//======================================================================//
//
//======================================================================//
void relayOn(void) {
  static Tsection section = ENTRY;
  RELAY_STATE currentRelayState = getRelayState();

  switch (section) {
    case ENTRY:
      digitalWrite(RELAY_IN_1, LOW); //turn ON the relay
      section = DO;
      break;

    case DO:
      if(radio.available()){
          radio.read(&text, sizeof(text));
          if(strOFF.equals(text) && currentRelayState == ON){
            section = EXIT;
          }
      }
      break;

    case EXIT:
      setRelayState(OFF);
      section = ENTRY;
      break;

    default: break;

  }
}

//======================================================================//
//
//======================================================================//
void relayOff(void) {
  static Tsection section = ENTRY;
  RELAY_STATE currentRelayState = getRelayState();

  switch (section) {
    case ENTRY:
      digitalWrite(RELAY_IN_1, HIGH); //turn OFF the relay
      section = DO;
      break;

    case DO:
      if(radio.available()){
          radio.read(&text, sizeof(text));
          if(strON.equals(text) && currentRelayState == OFF){
            section = EXIT;
          }
      }
      break;

    case EXIT:
      setRelayState(ON);
      section = ENTRY;
      break;

    default: break;
  }
}

//======================================================================//
//
//======================================================================//
void setRelayState(RELAY_STATE newState) {
  relayState = newState;
}

//======================================================================//
//
//======================================================================//
RELAY_STATE getRelayState(void) {
  return relayState;
}

//======================================================================//
//
//======================================================================//
void fsmInit(void) {
  setRelayState(OFF);
}

//======================================================================//
//
//======================================================================//
void fsmRun(void) {
  RELAY_STATE currentRelayState = getRelayState();
  if(currentRelayState < RELAY_STATE_NUMBER){
    (*pFunc[currentRelayState])(); 
  }
}

//------------------------------------------------------------------------//
//                              TIMER ISR
//------------------------------------------------------------------------//
ISR(TIMER1_OVF_vect)
{
  noInterrupts();
  uint8_t sreg = SREG;
  TCNT1 = 64286;
  swTimerProcess();
  SREG = sreg;
  interrupts();
}
