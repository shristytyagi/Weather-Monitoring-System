/*

Wind Speed and Temperature Sensor

 Measures temperature input from [TMP36] sensor and calculates 
 Fahrenheit, Celsius, Rankine, and Kelvin temperature values.
 Calculates wind speed based on potentiometer [Simulated Adafruit
 Anemometer (0.4v = 0m/s & 2v = 32.4m/s wind speed)] voltage 
 output. Stores five readings to calculate running averages for
 temperature [Fahrenheit] and wind speed [Miles per hour].
 Stores highest and lowest temperature and wind speed values 
 since the sensor was powered to obtain MIN and MAX values.
 
 Outputs:
 
 LCD Screen:
 Fahrenheit, Celsius, Rankine, Kelvin, and 
 wind speed values.
 
 Serial Monitor:
 Current temperature [Fahrenheit, Celsius, Rankine, and Kelvin],
 wind speed, and "anemometer" [potentiometer] voltage values.
 Average temperature [Fahrenheit] and wind speed [miles per hour]
 values. Minimum and maximum temperature and wind speed values
 since the sensor was powered.
 
 Created 07 Jul 2020
 by Cody Howk


SAMPLE CODING USED:

LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 
 
Smoothing

  Reads repeatedly from an analog input, calculating a running average and
  printing it to the computer. Keeps five readings in an array and continually
  averages them.

  The circuit:
  - analog sensor (potentiometer will do) attached to analog input 0

  created 22 Apr 2007
  by David A. Mellis  <dam@mellis.org>
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Smoothing
 
*/


//-------------------------------------------------------------


// variables

int Celsius = 0;          // Celsius

int Fahrenheit = 0;       // Fahrenheit

int Rankine = 0;		  // Rankine

int Kelvin = 0;			  // Kelvin

float Voltage = 0;		  // Voltage

float Windspeedfloat = 0; // For Serial monitor output

int Windspeedint = 0;	  // For LCD screen output

int Tempmax = 0;		  // Maximum Temperature

int Tempmin = 0;		  // Minimum Temperature

int Windmax = 0;		  // Maximum Wind speed

int Windmin = 0;		  // Minimum Wind speed


// Temperature Average Variables

const int numReadings = 3;      // Desired Average sample size

int readings[numReadings];      // the readings from the analog input

int readIndex = 0;              // the index of the current reading

int total = 0;                  // the running total

int average = 0;                // the average


// Wind speed Average Variables

const int numReadings1 = 3;      // Desired Average sample size

int readings1[numReadings1];     // the readings from the analog input

int readIndex1 = 0;              // the index of the current reading

int total1 = 0;                  // the running total

int average1 = 0;                // the average


// include the library code:

#include <LiquidCrystal.h>


// initialize the library with the numbers of the interface pins

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {

  
  // setting pins to input
  
  pinMode(A0, INPUT);
  
  pinMode(A1, INPUT);
 
  Serial.begin(9600);

  
  // Temperature Average setup
 
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    
  	readings[thisReading] = 0;}
  
  
  // Wind speed Average setup
  
  for (int thisReading1 = 0; thisReading1 < numReadings1; thisReading1++) {
    
    readings1[thisReading1] = 0;}
  
  
  // set up the LCD's number of columns and rows:
 
  lcd.begin(16, 2);


}


void loop() {

  
  // Temperature Average
  
  total = total - readings[readIndex]; // subtract the last reading
  
  readings[readIndex] = Fahrenheit;    // read from the sensor
  
  total = total + readings[readIndex]; // add the reading to the total
  
  readIndex = readIndex + 1;           // advance to the next position in the array

  	
  if (readIndex >= numReadings) {      // if we're at the end of the array...
    
     	 readIndex = 0;}               // ...wrap around to the beginning

  average = total / numReadings;       // calculate the average
  
  
  // Temperature Min/Max
  
  // Minimum
  
  if (readings[readIndex] == 0){
   
	Tempmin=76;}
  
  else if (readings[readIndex]<Tempmin){  // If new reading < old MIN reading...
    
   	Tempmin=readings[readIndex];}         // Set as new MIN
  
  // Maximum
  
  if (readings[readIndex] == 0){
    
	Tempmax=76;}
 
  else if (readings[readIndex]>Tempmax){  // If new reading > old MAX reading...
	
	Tempmax=readings[readIndex];}		  // Set as new MAX
	
  
  // set the cursor to column 0, line 0
  
  lcd.setCursor(0, 0);
   
  
  // Temperature variables set to analog readings
 
  Celsius = -40 + 0.488155 * (analogRead(A0) - 20);   
 
  Fahrenheit = -40 + 0.878679 * (analogRead(A0) - 20); 
  
  
  // Rankine and Kelvin calculated
  
  Rankine = (Fahrenheit + 459.67);
  
  Kelvin = (Celsius + 273.15);
  
 
  // Analog input converted to Voltage
  
  float Voltage = analogRead(A1) * (5.0 / 1023.0);
 
  
  // Voltage converted to MPH
  
  int Windspeedint = (Voltage - 0.4) * 10 * 2.025 * 2.237;     // For LCD screen output
  
  float Windspeedfloat = (Voltage - 0.4) * 10 * 2.025 * 2.237; // For Serial monitor output
  
  
  // Wind speed Average
  
  total1 = total1 - readings1[readIndex1]; // subtract the last reading
  
  readings1[readIndex1] = Windspeedfloat;  // read from the sensor
  
  total1 = total1 + readings1[readIndex1]; // add the reading to the total
  
  readIndex1 = readIndex1 + 1;             // advance to the next position in the array

  if (readIndex1 >= numReadings1) {        // if we're at the end of the array...
    
    readIndex1 = 0;}                       // ...wrap around to the beginning

  average1 = total1 / numReadings1;        // calculate the average
  
  if (Voltage < 0.4){
    
    int average1 = 0;}
  
  // Wind speed Min/Max
  
  // Minimum
  
  if (readings[readIndex] == 0){			
   
    Windmin=999;}  
 
  else if (readings1[readIndex1]<Windmin){
  
   Windmin=readings1[readIndex1];}
	
  // Maximum
  
  if (readings1[readIndex1]>Windmax){		// If new reading > old MAX reading...
    
    Windmax=readings1[readIndex1];}			// Set as new MAX
	
  
  // outputs to LCD
  
  lcd.print("Temps: ");       // Print Temps: to the LCD.
  
  lcd.print(Fahrenheit);      // Fahrenheit value
  
  lcd.print("F ");		      // F symbol
  
  lcd.print(Celsius);	      // Celsius value
  
  lcd.print("C");		      // C symbol
  
  lcd.setCursor(7, 1);        // adjust cursor
  
  lcd.print(Kelvin); 	      // Kelvin value
  
  lcd.print("K ");		      // K symbol
  
  lcd.print(Rankine);         // Rankine value
 
  lcd.print("R");		      // R symbol
  
  lcd.setCursor(3, 1);        // adjust cursor
  
  lcd.print("MPH");		      // MPH symbol
  
  lcd.setCursor(0,1);	      // adjust cursor
 
  if (Voltage < 0.4){         // If Voltage is less than 0.4... 
    
    lcd.print("0");}     	  // print 0 to LCD
  
  else {				      // Otherwise...
    
    lcd.print(Windspeedint);} // Output Windspeed interger
   
  
  // outputs to serial monitor
  
  Serial.println("----------------------------"); // Line
  
  Serial.println(" ");							  
  
  Serial.println("Current Temperature:");  // "Current Temperature"
  
  Serial.println(" ");
  
  Serial.println("Fahrenheit: ");       // "Fahrenheit"    
  
  Serial.print(Fahrenheit);				// Fahrenheit value
  
  Serial.print(" F");                   // F symbol
  
  Serial.println(" ");
  
  Serial.println("Celsius: ");			// "Celsius"
 
  Serial.print(Celsius);				// Celsius value
  
  Serial.print(" C");					// C symbol
 
  Serial.println(" ");
  
  Serial.println("Rankine: ");		    // "Rankine"
  
  Serial.print(Rankine);				// Rankine value
  
  Serial.print(" R");					// R symbol
  
  Serial.println(" ");
  
  Serial.println("Kelvin: ");			// "Kelvin"
  
  Serial.print(Kelvin);					// Kelvin value
  
  Serial.print(" K");				    // K symbol
  
  Serial.println(" ");
  
  Serial.println(" ");
   
  Serial.print("Wind Speed: ");         // "Wind speed"
 
  if (Windspeedfloat <= 0){             // If Wind speed less than or equal to zero...
    
    Serial.print("0.0");}				// Output 0.0
  
  else{									// Otherwise...
    
    Serial.print(Windspeedfloat,1);}	// Output Wind speed value
  
  Serial.println(" MPH");				// MPH symbol
  
  Serial.print("Anemometer Voltage: "); // "Anemometer Voltage"
  
  if (Voltage > 2){						// If Voltage is over 2...
   
    Serial.println("Out of range!");    // Print Message
    
    Serial.println(" ");
    
    Serial.println("Please adjust voltage to 2v - 0.4v");}
  
  else if (Voltage < 0.4){				// If Voltage is less than 0.4...
 
    Serial.println("Out of range!");    // Print Message
    
    Serial.println(" ");
    
    Serial.println("Please adjust voltage to 2v - 0.4v");}
  
  
  else{									// Otherwise...
     
    Serial.print(Voltage);				// Output Voltage value
      
    Serial.println(" V");}				// V symbol
    
  Serial.println(" ");
  
  Serial.println("----------------------------");
  
  Serial.println(" ");
  
  Serial.print("Average Temparature: ");// "Average Temperature"
  
  Serial.print(average);				// Average Temperature value
  
  Serial.println(" F");					// F symbol
  
  delay(1);        						// delay in between reads for stability
  
  Serial.print("Average Wind Speed: "); // "Average Wind Speed:"
  
  if (Voltage < 0.4){	// Wind speed average out of range...
    
    Serial.println("Voltage out of range!");} // Print Message
    
  else {								// Otherwise...
  
  	Serial.print(average1,1);}			// Output Wind Speed Average value to one decimal place
  
  if (Voltage < 0.4){
    
    Serial.println(" ");}
  
  else {Serial.println(" MPH");}		// MPH symbol
  
  Serial.println(" ");
  
  Serial.print("Maximum: ");			// "Maximum"
  
  Serial.print(Tempmax);				// Maximum Temperature value
  
  Serial.print(" F");					// F symbol
 
  Serial.print("     ");
  
  if (Windmax > 73){
    
    Serial.print("0");}
  
  else {Serial.print(Windmax);}			// Maximum Wind Speed value
  
  Serial.println(" MPH");				// MPH symbol
 
  Serial.print("Minimum: ");			// "Minimum"
  
  Serial.print(Tempmin);				// Minimum Temperature value
  
  Serial.print(" F");					// F symbol
  
  Serial.print("     ");
  
  if (Windmin > 73){
    
    Serial.print("0");}
  
  else if (Windmin==999){				// if Wind MIN = initializing value...
  
    Serial.print("0");}					// Output Zero
 
  else if(Windmin < 0){					// Otherwise...
 
    Serial.print("0");}
    
  else {Serial.print(Windmin);}			// Output Minimum Wind Speed value
  
  Serial.println(" MPH");				// MPH symbol
  
  Serial.println(" ");
  
  delay(3000);                          // Wait for 3000 millisecond(s)
  
  
  // clears LCD for loop
  
  lcd.clear();

// END

}
 