
// Include the Adafruit NeoPixel Library
#include <Adafruit_NeoPixel.h>

// LED Connection Pin
int LEDPIN = 6;

// Number of LEDs in the NeoPixel Strip
int NUMPIXELS = 25;

// Initialize the NeoPixel strip
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

// Define the force senstive resistor pin
#define FORCE_SENSOR_PIN A0

// Vibration Motor pins
int motorPin1 = 3;
int motorPin2 = 4; 

// Controls the interval the vibration motor vibrates
int delayVal = 1000;

// Setup
void setup()
{
  // Set the motor pins to output
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  // Begin the serial port
  Serial.begin(9600);

  // Turn the NeoPixel ON
  pixels.begin();
}

// Loop
void loop()
{

  int analogReading = analogRead(FORCE_SENSOR_PIN);

  Serial.print(analogReading); 

    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, HIGH);

  // As the pressure increases, vibrate the motors for longer by controlling the delayVal
  if (analogReading < 50){
    // Apply the flower pattern lights to the LEDs
    showColors(1);
    delayVal = 100;  
  }else if (analogReading < 200){
    // Apply the flower pattern lights to the LEDs
    showColors(2);
    delayVal = 250;
  }else if (analogReading < 500){
    // Apply the flower pattern lights to the LEDs
    showColors(3);
    delayVal = 500;
  }else if (analogReading < 800){ 
    // Apply the flower pattern lights to the LEDs
    showColors(4);
    delayVal = 750;
  }else{  
    // Show the rainbow effect
    rainbow(1);
    delayVal = 1000; 
  }

  pixels.show(); 
  
  delay(delayVal); 

  digitalWrite(motorPin1, LOW); 
  digitalWrite(motorPin2, LOW); 

  delay(delayVal); 
}

// From the Adafruit, strandtest example
// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 1 complete loop through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this loop:
  for(long firstPixelHue = 0; firstPixelHue < 1*65536; firstPixelHue += 256) {
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
    pixels.rainbow(firstPixelHue);
    // Above line is equivalent to:
    // strip.rainbow(firstPixelHue, 1, 255, 255, true);
    pixels.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Custom function to show lights, each petal has a different color
// Multiple value controls the brightness
void showColors(int multiple){
  // Set the brightness of the color using the multiple value.
  int colorValue = multiple * 50;

  // Set the colors of the first two LEDs
  pixels.setPixelColor(0, pixels.Color(colorValue,0,colorValue));
  pixels.setPixelColor(1, pixels.Color(colorValue,colorValue,0));

  // First petal
  for(int i = 2; i < 4; i++){
    pixels.setPixelColor(i, pixels.Color(colorValue,0,0));   
  }

  // Second petal
  for(int i = 4; i < 7; i++){
    pixels.setPixelColor(i, pixels.Color(0,0,colorValue));   
  }

  // Third petal
  for(int i = 7; i < 9; i++){
    pixels.setPixelColor(i, pixels.Color(0,colorValue,0));   
  }

  // Fourth petal
  for(int i = 9; i < 11; i++){
    pixels.setPixelColor(i, pixels.Color(colorValue,0,colorValue));   
  }

  // Fifth petal
  for(int i = 11; i < 14; i++){
    pixels.setPixelColor(i, pixels.Color(colorValue,colorValue,colorValue));   
  }

  // Inner circle of the flower
  for(int i = 14; i < 25; i++){
    pixels.setPixelColor(i, pixels.Color(colorValue,colorValue,0));   
  }  
}
