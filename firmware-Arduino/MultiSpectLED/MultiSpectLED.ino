#include <SoftPWM.h>   //The library normally uses a 60Hz update rate which is defined in Arduino/hardware/teensy/avr/libraries/SoftPWM/SoftPWM.cpp


#define TWOPI 6.2832
#define PIOVERTWO 1.5708

#define PIN_LED_940 13
#define PIN_LED_850 14
#define PIN_LED_740 15
#define PIN_LED_655 16
#define PIN_LED_627 17
#define PIN_LED_617 18
#define PIN_LED_591 19
#define PIN_LED_568 5
#define PIN_LED_530 6
#define PIN_LED_505 7
#define PIN_LED_470 8
#define PIN_LED_448 9
#define PIN_LED_405 10
#define PIN_LED_367 11
#define PIN_LED_280 12


#define PIN_SEL1 0
#define PIN_SEL2 1
#define PIN_SEL4 2
#define PIN_SEL8 3

#define PIN_BRIGHT1 20
#define PIN_BRIGHT2 21
#define PIN_BRIGHT4 22
#define PIN_BRIGHT8 23

uint8_t led_array_pwm[15];
uint8_t led_array_pins[15] = {PIN_LED_280, PIN_LED_367, PIN_LED_405, PIN_LED_448, PIN_LED_470, PIN_LED_505, PIN_LED_530, PIN_LED_568, PIN_LED_591, PIN_LED_617, PIN_LED_627, PIN_LED_655, PIN_LED_740, PIN_LED_850, PIN_LED_940};
float cur_phase = 0;

void setup() {
  Serial.begin(9600);
  
   SoftPWMBegin();

   pinMode(PIN_SEL1, INPUT_PULLUP);
   pinMode(PIN_SEL2, INPUT_PULLUP);
   pinMode(PIN_SEL4, INPUT_PULLUP);
   pinMode(PIN_SEL8, INPUT_PULLUP);
   pinMode(PIN_BRIGHT1, INPUT_PULLUP);
   pinMode(PIN_BRIGHT2, INPUT_PULLUP);
   pinMode(PIN_BRIGHT4, INPUT_PULLUP);
   pinMode(PIN_BRIGHT8, INPUT_PULLUP);

   clear_all_leds();
}

void loop() {
  uint8_t cur_brightness = map(ReadLEDBrightness(),0,15,10,255);
  uint8_t cur_selection = ReadLEDSelection();
  
  clear_all_leds();
  
  cur_phase = (cur_phase > 7) ? -10 : cur_phase+0.08;
  
  if(cur_selection == 0)
  {
    for(int i = 0; i<15;i++)
      {
        led_array_pwm[i] = 255 * sine_pulse(cur_phase + i);      
      }
  }
  
  if(cur_selection > 0 && cur_selection < 16)
    {
      led_array_pwm[cur_selection-1] = cur_brightness;
    }
  update_leds();
  delay(16);
}




float sine_pulse(float input)  {
  if(input < 0)
    {
      return 0;
    }
  else if(input > TWOPI)
  {
    return 0;
  }
  else
  {
    return (1+sin(input-PIOVERTWO))/2;
  }
}

void update_leds(void)  {
  for(int i = 0; i<15;i++)
   {
    SoftPWMSet(led_array_pins[i], led_array_pwm[i]);
   }
}


void clear_all_leds(void)  {
  for(int i = 0; i<15;i++)
    {
      led_array_pwm[i] = 0;
    }
}


uint8_t ReadLEDSelection(void)  {
  uint8_t result = 0;
  result += !digitalRead(PIN_SEL1)<<0;
  result += !digitalRead(PIN_SEL2)<<1;
  result += !digitalRead(PIN_SEL4)<<2;
  result += !digitalRead(PIN_SEL8)<<3;
  return result; 
}


uint8_t ReadLEDBrightness(void)  {
  uint8_t result = 0;
  result += !digitalRead(PIN_BRIGHT1)<<0;
  result += !digitalRead(PIN_BRIGHT2)<<1;
  result += !digitalRead(PIN_BRIGHT4)<<2;
  result += !digitalRead(PIN_BRIGHT8)<<3;
  return result; 
}
