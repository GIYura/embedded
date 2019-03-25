/*
TX module
Board: Arduino NANO
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define BUTTON_PIN  2

RF24 radio(7, 8);

const byte address[6] = "00001";
const char msgON[] = "ON";
const char msgOFF[] = "OFF";

typedef enum{
  SUCCESS = 0,
  FAILED,
}T_INIT_STATE;

typedef enum{
  PRESSED = 0,
  NOT_PRESSED,
  OUT_OF_RANGE
}T_BUTTON_STATE;

void setButtonState(T_BUTTON_STATE newState);
T_BUTTON_STATE getButtonState(void);
T_BUTTON_STATE buttonState = OUT_OF_RANGE;

T_INIT_STATE fsmInit(void);
void fsmRun(void);

void sendOn(void);
void sendOff(void);
void (*pFunc[])(void) = {sendOn, sendOff};

T_INIT_STATE gpioInit(void);

//======================================================================//
//                              SETUP                                   //
//======================================================================//
void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  byte systemState = 0xff;
  systemState |= gpioInit();
  systemState |= fsmInit();
}

//======================================================================//
//                                LOOP                                  //
//======================================================================//
void loop() {
  fsmRun();
}

/************************************************************************
                              FUNCTIONS
*************************************************************************/
//======================================================================//
//                                                                      //
//======================================================================//
void setButtonState(T_BUTTON_STATE newState){
  if(newState < OUT_OF_RANGE){
    buttonState = newState;
  }
}

//======================================================================//
//                                                                      //
//======================================================================//
T_BUTTON_STATE getButtonState(void){
  return buttonState;
}

//======================================================================//
//                                                                      //
//======================================================================//
T_INIT_STATE gpioInit(void){
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), BUTTON_ISR, CHANGE);
  return SUCCESS;
}

//======================================================================//
//                                                                      //
//======================================================================//
T_INIT_STATE fsmInit(void){
  setButtonState(NOT_PRESSED);  
  return SUCCESS;
}

//======================================================================//
//                                                                      //
//======================================================================//
void fsmRun(void){
  T_BUTTON_STATE currentButtonState = getButtonState();
  if(currentButtonState < OUT_OF_RANGE){
    (*pFunc[currentButtonState])();
  }
}

//======================================================================//
//                                                                      //
//======================================================================//
void sendOn(void){
  radio.write(&msgON, sizeof(msgON));
}

//======================================================================//
//                                                                      //
//======================================================================//
void sendOff(void){
  radio.write(&msgOFF, sizeof(msgOFF));
}

//======================================================================//
//                                                                      //
//======================================================================//
void BUTTON_ISR(){
  T_BUTTON_STATE bSt = getButtonState();
  switch(bSt){
    case NOT_PRESSED:
      setButtonState(PRESSED);
    break;

    case PRESSED:
      setButtonState(NOT_PRESSED);
    break;

    default: break;
  }
}
