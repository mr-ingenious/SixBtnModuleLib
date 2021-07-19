#include "SixBtnModuleLib.h"

#include "Arduino.h"

/* ****************************************************************************
  Constructor: 
  ****************************************************************************/
SBMReader::SBMReader () {}

/* ****************************************************************************
  Constructor:
  ****************************************************************************/
SBMReader::SBMReader (int inPin) {
    inputPin = inPin;
}

/* ****************************************************************************
  setInputPin: sets the input pin
  ****************************************************************************/
void SBMReader::setInputPin (int inPin) {
  inputPin = inPin;
}

/* ****************************************************************************
  currentButton: returns the currently pressed button
  ****************************************************************************/
byte SBMReader::currentButton (int val) {
    if (val > BLEFT_MIN   && val < BLEFT_MAX)   { return BUTTON_LEFT;   }
    if (val > BRIGHT_MIN  && val < BRIGHT_MAX)  { return BUTTON_RIGHT;  }
    if (val > BUP_MIN     && val < BUP_MAX)     { return BUTTON_UP;     }
    if (val > BDOWN_MIN   && val < BDOWN_MAX)   { return BUTTON_DOWN;   }
    if (val > BCENTER_MIN && val < BCENTER_MAX) { return BUTTON_CENTER; }
    if (val > BBACK_MIN   && val < BBACK_MAX)   { return BUTTON_BACK;   }
    
    return BUTTON_NONE;
}

/* ****************************************************************************
  readButtons: reads the buttons state and conditionally returns the button
               activated.
  ****************************************************************************/
byte SBMReader::readButtons() {   
  const unsigned long long currTs = millis();
  
  if ((currTs - lastReadingTs) >= inputReadInterval) {
    const int readValue = analogRead (inputPin);
    const byte btn = currentButton (readValue);
    
    lastReadingTs = currTs;
    
    if (lastPressed.btn != btn) {
        if ((currTs - lastPressed.changedTs) >= debounceInterval) {
          // has changed and is debounced
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
    return BUTTON_NONE;
  }
}
