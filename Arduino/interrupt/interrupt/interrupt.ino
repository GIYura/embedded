/*
   Timer interrupt
   (timer speed (Hz)) = (Arduino clock speed (16MHz)) / prescaler
*/

const int ledPin1 = 8;
static byte state1 = LOW;

const int ledPin2 = 13;
static byte state2 = HIGH;

//
typedef enum {
  TIMER_0,
  TIMER_1,
  TIMER_2,
  TIMER_NUMBER
} timer_idx_t;

//
typedef enum {
  ACTIVE,
  DISACTIVE,
  EXPIRED,
  UNEXPIRED,
  INVALID
} timer_state_t;

class SwTimer {
    timer_state_t state;
    uint32_t ticks;
  public:
    SwTimer(uint32_t);
    ~SwTimer(void);

    timer_state_t setState(timer_state_t);
    timer_state_t getState(void);
    uint32_t getTicks(void);
    void setTicks(uint32_t);

    timer_state_t isTimeOut(void);
    friend void process(SwTimer*);
};

//
timer_state_t SwTimer::setState(timer_state_t newState) {
  if (newState == ACTIVE || newState == DISACTIVE) {
    this->state = newState;
    return this->state;
  }
  return INVALID;
}

//
timer_state_t SwTimer::getState(void) {
  return this->state;
}

//
uint32_t SwTimer::getTicks(void) {
  return this->ticks;
}

//
void SwTimer::setTicks(uint32_t t) {
  this->ticks = t;
}

//
SwTimer::SwTimer(uint32_t t) {
  this->state = ACTIVE;
  this->ticks = t;
}

//
SwTimer::~SwTimer(void) {
  this->state = DISACTIVE;
  this->ticks = 0;
}

//
timer_state_t SwTimer::isTimeOut(void) {
  if (getState() == ACTIVE) {
    return getTicks() ? UNEXPIRED : EXPIRED;
  }
  return INVALID;
}

//
void process(SwTimer* swT) {
  if (swT->state == ACTIVE) {
    if (swT->ticks != 0) {
      swT->ticks--;
    }
  }
}

static SwTimer *timer0 = new SwTimer(250);
static SwTimer *timer1 = new SwTimer(50);

// SETUP
void setup() {
  //set up TIMER2
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  TIMSK2 |= (1 << TOIE2);                       //timer interrupt enable
  TCCR2B |= (1 << CS22) | (1 << CS20);          //prescaler = 125 KHz (timer speed = 8us)


}

//MAIN LOOP
void loop() {
  if (timer0->isTimeOut() == EXPIRED) {
    timer0->setTicks(250);
    state1 = !state1;
    digitalWrite(ledPin1, state1);
  }

  if (timer1->isTimeOut() == EXPIRED) {
    timer1->setTicks(50);
    state2 = !state2;
    digitalWrite(ledPin2, state2);
  }
}

//
ISR(TIMER2_OVF_vect) {
  static int counter = 1;
  if (!counter--) {
    counter = 1;
    process(timer0);
    process(timer1);
  }
}
