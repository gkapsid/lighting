#include <Adafruit_NeoPixel.h>
//download from Adafruit web site
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, PIN, NEO_RGB);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  pinMode(7, OUTPUT);
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
//Serial.begin(9600);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  digitalWrite(7, HIGH);
 int sensorValue = analogRead(A0);  
// Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):  
float voltage = sensorValue * (5.0 / 1023.0);  // print out the value you read:  
  //Serial.println(voltage);  
if (voltage <2.5){
  Serial.println(voltage);
  strip.setBrightness(255);
  // Some example procedures showing how to display to the pixels:
  colorWipe(strip.Color(255, 0, 0), 100); // Red
  Serial.println(voltage);
  colorWipe(strip.Color(0, 255, 0), 100); // Green
  Serial.println(voltage);
  colorWipe(strip.Color(0, 0, 255), 100); // Blue
Serial.println(voltage);
  rainbow(250); 
  
}  
else if (voltage>2.5) {
strip.setBrightness(0);
strip.show();
}

}
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
    //int sensorValue = analogRead(A0);  
// Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):  
//float voltage = sensorValue * (5.0 / 1023.0);  // print out the value you read:  
  //Serial.println(voltage);  
    
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;
 
  //Serial.println(voltage);  
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
  /*int sensorValue = analogRead(A0);  
// Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):  
float voltage = sensorValue * (5.0 / 1023.0);  // print out the value you read:  
    
    if (voltage >2.5){
        strip.setBrightness(0);
        break;  
  }*/
    strip.show();
    }
    delay(wait);
    int sensorValue = analogRead(A0);  
// Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):  
float voltage = sensorValue * (5.0 / 1023.0);  // print out the value you read:  
  //Serial.println(voltage);  
    //Serial.println(voltage);
    if (voltage > 2.5){
    break;
  }
  }
}
/*
*/
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
