#include "VandelayEngine.h"


// Converter function
float VanConvert(float i, int f, int t)
{
	float r;
	
	// Foot
	if(f == 0 && t == 1) // Foot to Kilometer
		r = (i * 0.3048) / 1000;
	else if(f == 0 && t == 2) // Foot to Meter
		r = i * 0.3048;
	else if(f == 0 && t == 3) // Foot to Mile(US)
		r = i / 5263.16;
	// Kilometer
	else if(f == 1 && t == 0) // Kilometer to Foot
		r = (i * 3.2808) * 1000;
	else if(f == 1 && t == 2) // Kilometer to Meter
		r = i * 1000;
	else if(f == 1 && t == 3) // Kilometer to Mile(US)
		r = i * 0.6214;
	// Meter
	else if(f == 2 && t == 0) // Meter to Foot
		r = i * 3.2808;
	else if(f == 2 && t == 1) // Meter to Kilometer
		r = i / 1000;
	else if(f == 2 && t == 3) // Meter to Mile(US)
		r = (i / 1000) * 0.6214;
	// Mile(US)	
	else if(f == 3 && t == 0) // Mile(US) to Foot
		r = i * 5263.16;
	else if(f == 3 && t == 1) // Mile(US) to Kilometer
		r = i * 1.609;
	else if(f == 3 && t == 2) // Mile(US) to Meter
		r = (i * 1.609) * 1000;
	// Horsepower
	else if(f == 4 && t == 5) // Horsepower to Kilowatt
		r = i * 0.7457;
	// Kilowatt
	else if(f == 5 && t == 4) // Kilowatt to Horsepower
		r = i * 1.3410;
	// Celsius
	else if(f == 6 && t == 7) // Celsius to Fahrenheit
		r = (i * 1.8) + 32.0;
	// Fahrenheit
	else if(f == 7 && t == 6) // Fahrenheit to Celsius
		r = (i - 32.0) *5.0 / 9.0;
	// Gallon
	else if(f == 8 && t == 9) // Gallon(US) to Litre
		r = i * 3.7854;
	// Litre
	else if(f == 9 && t == 8) // Litre to Gallon(US)
		r = i * 0.2642;
	// Kilogram
	else if(f == 10 && t == 11) // Kilogram to Pound
		r = i * 2.2046;
	// Pound
	else if(f == 11 && t == 10) // Pound to Kilogram
		r = i * 0.4536;
	
	// Else
	else
		r = 0.0;
	
	return r;
}
