/* Takes 4 float values; one is an error value between negatiive one and one,
while the others are constants which control the exact function of the code.
Returns a float indicative of the necessary correction to reduce error.*/

#include "PID.h"
PID_Class::PID_Class() {
}
PID_Class::~PID_Class() {
}

float PID_Class::PID(float error, float KP, float KI, float KD) {
	printf ("Error = %f / KP = %f / KI = %f / KD = %F \n", error, KP, KI, KD);
	float delta_err;
	float p_out;
	float i_out;
	float d_out;
	float output;
	
	static float integral_err;
	static float prev_err;
	
	delta_err = prev_err - error;
	integral_err += error;
	
	if (integral_err > 1.0)
		integral_err = 1.0;
	if (integral_err < -1.0)
		integral_err = -1.0;
	
	p_out = error * KP;
	i_out = integral_err * KI;
	d_out = delta_err * KD;
	
	output = p_out + i_out + d_out;
	
	if (output > 1.0)
		output = 1.0;
	if (output < -1.0)
		output = -1.0;
	
	prev_err = error;
	printf ("Output = %f /n", output);
	return output;
}
