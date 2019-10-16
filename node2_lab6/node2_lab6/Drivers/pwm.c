/*
 * pwm.c
 *
 * Created: 11.10.2019 17:27:10
 *  Author: thoander
 */ 

#include <avr/io.h>

void PWM_init(void) {
	// Set PB5 as output for PWM signal
	DDRB |= (1 << PB6);

	// Set polarity (non inverting) and lower bits for mode 14 (fast PWM)
	TCCR1A |= (1 << COM1B1) | (1 << WGM11);

	// Set upper bits for mode 14 and set prescaler f_osc/8
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	
	// Set input capture register 5 to 40 000 (this should create a compare match every 20 ms)
	ICR1 = 0x9C40;
}

// duty cycle = {0, 100}
void PWM_set_duty_cycle(unsigned int duty_cycle)  {
	if (duty_cycle < 100) {
		uint16_t d = (duty_cycle*0.012 + 0.9)*2000;

		// New duty cycle is automatically set at new period (BOTTOM)
		OCR1B = d;
	} else {
		printf("Error: PWM duty cycle is too large\n\r");
	}

}

