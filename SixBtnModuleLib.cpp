#include "SixBtnModuleLib.h"

#include "Arduino.h"

/* ****************************************************************************
  Constructor:
  ****************************************************************************/
SBMReader::SBMReader (int inPin, int mode) {
    inputPin = inPin;
    
    pinMode (inPin, mode);
};

/* ****************************************************************************
  setButtonValue: provides the ability to change the button value
  ****************************************************************************/
void SBMReader::setButtonValue (byte btn, unsigned short newButtonValue) {
    if (btn >= 0 && btn < BUTTONS_NUM && newButtonValue <= 1023) {
        buttonValues[btn] = newButtonValue;
    }
};

/* ****************************************************************************
  getButtonValue: returns the currently set button value
  ****************************************************************************/
short SBMReader::getButtonValue (byte btn) {
    if (btn >= 0 && btn < BUTTONS_NUM) {
        return buttonValues[btn];
    } else {
        return -1;
    }
};

/* ****************************************************************************
  setButtonValueRange: provides the ability to change the button value range
  ****************************************************************************/
void SBMReader::setButtonValueRange (unsigned short newRange) {
    valueRange = newRange;
};

/* ****************************************************************************
  getValueRange: returns the currently set button value range
  ****************************************************************************/
unsigned short SBMReader::getButtonValueRange () {
    return valueRange;
};

/* ****************************************************************************
  getValueRange: provides the ability to change the debounce interval
  ****************************************************************************/
void SBMReader::setDebounceInterval (unsigned short newDbInterval) {
    debounceInterval = newDbInterval;
}

/* ****************************************************************************
  getDebounceInterval: returns the currently set button value range
  ****************************************************************************/
unsigned short SBMReader::getDebounceInterval () {
    return debounceInterval;
};
    
/* ****************************************************************************
  setReadInterval: provides the ability to change the input read interval
  ****************************************************************************/
void SBMReader::setReadInterval (unsigned short newReadInterval) {
    inputReadInterval = newReadInterval;
};

/* ****************************************************************************
  getReadInterval: returns the currently set input read interval
  ****************************************************************************/
unsigned short SBMReader::getReadInterval () {
    return inputReadInterval;
};

/* ****************************************************************************
  identifyButton: returns the currently pressed button
  ****************************************************************************/
byte SBMReader::identifyButton (int val) {
    for (unsigned short bsel = 0; bsel < BUTTONS_NUM; bsel++) {
      if (val > buttonValues[bsel] - valueRange &&
          val < buttonValues[bsel] + valueRange) {
        return bsel;
      }
    }
    
    return BUTTON_NONE;
};

/* ****************************************************************************
  readButtons: reads the buttons state and conditionally returns the button
               activated.
  ****************************************************************************/
byte SBMReader::readButtons() {
  const unsigned long long currTs = millis();
  
  if ((currTs - lastReadingTs) >= inputReadInterval) {
    const int readValue = analogRead (inputPin);
    const byte btn = identifyButton (readValue);
    
    lastReadingTs = currTs;
          
    if (lastPressed.btn != btn) {
        if ((currTs - lastPressed.changedTs) >= debounceInterval) {
          // button has changed and is debounced
          if (__SBM_DBG) {
            if (btn != BUTTON_NONE) {
              Serial.print (F("readButtons: readValue: "));
              Serial.println (readValue);
            }
          }
          
          lastPressed.changedTs = currTs;
          lastPressed.btn = btn;
          
          return btn;
        }
    }
    
    lastPressed.btn = btn;
    return BUTTON_NONE;
  }
};
