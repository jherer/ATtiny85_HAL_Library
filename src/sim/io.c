#include "sim/io.h"

// TIMER COMMON
uint8_t TIMSK = 0;

// TIMER0
uint8_t TCCR0A = 0;
uint8_t TCCR0B = 0;
uint8_t TCNT0 = 0;
uint8_t OCR0A = 0;
uint8_t OCR0B = 0;

// TIMER1
uint8_t TCCR1 = 0;
uint8_t GTCCR = 0;
uint8_t TCNT1 = 0;
uint8_t OCR1A = 0;
uint8_t OCR1B = 0;
uint8_t OCR1C = 0;

// GPIO
uint8_t PORTB = 0;
uint8_t PINB = 0;
uint8_t DDRB = 0;

// STATUS
uint8_t SREG = 0;