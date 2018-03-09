/*
 * Project VisualTemp
 * Description: Given a temperature, show a representative colour on the RGB LED
 * Author: @jonogould
 * Date: 2018-03-04
 */

#include "DS18.h"
#include "rgb-controls.h"
using namespace RGBControls;

// Sensor config
DS18 sensor(A0);
Led led(D0, D1, D2, false);

int LASER = D5;
bool laserOn = true;

// Temperature
double temp = 0.0;
double lastTemp = 0.0;

// Colour
Color current(5, 5, 40);
Color white(255, 255, 255);
Color red(255, 0, 0);
Color orange(255, 50, 0);
Color green(50, 255, 5);
Color cyan(0, 255, 255);
Color magenta(255, 0, 255);

// Runs once, on boot
void setup() {
  led.fadeOnce(white, current, 3000);
  pinMode(LASER, OUTPUT);
}

// Runs again and again, as quickly as possible
void loop() {
  if (sensor.read()) {
    temp = sensor.celsius();
    Particle.publish("temp-indoor", String(temp), PRIVATE);
    changeColour(temp);
    lastTemp = temp;
  }

  if (laserOn == true) {
    digitalWrite(LASER, HIGH);
    laserOn = false;
  } else {
    digitalWrite(LASER, LOW);
    laserOn = true;
  }

  delay(5000);
}

// Change the colour of the led based on preset temperatures
void changeColour(double t) {
  Color next(5, 5, 40);

  if (t > 25) {
      next = red;
  }
  else if (t > 23) {
      next = orange;
  }
  else if (t > 21) {
      next = green;
  }
  else if (t > 19) {
      next = cyan;
  }
  else {
      next = magenta;
  }

  led.fadeOnce(current, next, 2000);
  current = next;
}
