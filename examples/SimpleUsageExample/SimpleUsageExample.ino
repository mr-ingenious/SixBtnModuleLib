#include <SixBtnModuleLib.h>

const int PIN_BUTTONS = 9;

SBMReader inputReader (PIN_BUTTONS, INPUT);

void setup() {
  Serial.begin (9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  inputReader.setReadInterval (100);
  inputReader.setDebounceInterval (200);
  inputReader.setButtonValueRange (40);
  
  Serial.println (F("let's start ...\nsettings: "));
  
  Serial.print (F("debounce interval: "));
  Serial.println (inputReader.getDebounceInterval());
  Serial.print (F("input read interval: "));
  Serial.println (inputReader.getReadInterval());
  Serial.print (F("buttons value range: "));
  Serial.println (inputReader.getButtonValueRange());

  for (unsigned short bsel = 0; bsel < BUTTONS_NUM; bsel++) {
     Serial.print (F("Button #"));
     Serial.print (bsel);
     Serial.print (F(" value setting: "));
     Serial.println (inputReader.getButtonValue(bsel));
  }
}

// --------------------------------------------------------------------------------
void handleButtonEvent (byte btn) {
  switch (btn) {
    case BUTTON_LEFT:
      Serial.println (F("Buttons: [LEFT] triggered"));
      break;
    case BUTTON_RIGHT:
      Serial.println (F("Buttons: [RIGHT] triggered"));
      break;
    case BUTTON_UP:
      Serial.println (F("Buttons: [UP] triggered"));
      break;
    case BUTTON_DOWN:
      Serial.println(F("Buttons: [DOWN] triggered"));
      break;
    case BUTTON_CENTER:
      Serial.println (F("Buttons: [CENTER] triggered"));
      break;
    case BUTTON_BACK:
      Serial.println (F("Buttons: [BACK] triggered"));
      break;
    case BUTTON_NONE:
      // Serial.println (F("Buttons: nothing ..."));
      break;
  }
}

void loop() {
  handleButtonEvent (inputReader.readButtons());
}
