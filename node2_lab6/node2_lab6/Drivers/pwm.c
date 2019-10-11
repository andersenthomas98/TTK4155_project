/*
 * pwm.c
 *
 * Created: 11.10.2019 17:27:10
 *  Author: thoander
 */ 


void PWM_init(void) {
	
	// Set PH4 as output for PWM signal
	DDRH |= (1 << DDH3);
	// Set polarity (inverting mode(?(!)))
	TCCR4A |= (1 << COM4A1) | (1 << COM4A0);
	
}


void PWM_set_duty_cycle(int d) {
	
}