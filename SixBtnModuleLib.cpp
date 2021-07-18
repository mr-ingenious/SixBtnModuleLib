#include "Arduino.h"

#include "SixBtnModuleLib.h"

/* ****************************************************************************
  Constructor: 
  ****************************************************************************/
SBMReader::SBMReader (int inPin) {
  inputPin = inPin;
}

/* ****************************************************************************
  isDebounceTimeout: checks whether debounce timeout exceeded. 
  ****************************************************************************/
bool SBMReader::isDebounceTimeout (sbm_button b) {
  return (millis() - inputsChangeTs[b]) >= debounceInterval;
}

/* ****************************************************************************
  readButtons: reads the buttons state and conditionally returns the button
               activated.
  ****************************************************************************/
sbm_button SBMReader::readButtons() {
  unsigned long currTs = millis();
  if ((currTs - lastReadingTs) >= inputReadInterval) {
    /* Serial.print("millis: ");
      Serial.print(millis());
      Serial.print(", lastReadingTs:");
      Serial.print(lastReadingTs);
      Serial.print(", inputReadInterval: ");
      Serial.println(inputReadInterval); */

    int val = analogRead (inputPin);
    lastReadingTs = currTs;
    
    if ((val > BLEFT_MIN) &&
        (val < BLEFT_MAX) &&
        (inputs[BUTTON_LEFT] == false) &&
        isDebounceTimeout (BUTTON_LEFT)) {
      inputs[BUTTON_LEFT] = true;
      inputsChangeTs[BUTTON_LEFT] = currTs;

      if (SBM_DBG) {
        Serial.print (F("Buttons: LEFT - raw value="));
        Serial.println (val);
      }

      return BUTTON_LEFT;
    } else if ((val > BRIGHT_MIN) &&
               (val < BRIGHT_MAX) &&
               (inputs[BUTTON_RIGHT] == false) &&
               isDebounceTimeout (BUTTON_RIGHT)) {
      inputs[BUTTON_RIGHT] = true;
      inputsChangeTs[BUTTON_RIGHT] = currTs;

      if (SBM_DBG) {
        Serial.print (F("Buttons: RIGHT - raw value="));
        Serial.println (val);
      }

      return BUTTON_RIGHT;
    } else if ((val > BUP_MIN) &&
               (val < BUP_MAX) &&
               (inputs[BUTTON_UP] == false) &&
               isDebounceTimeout (BUTTON_UP)) {
      inputs[BUTTON_UP] = true;
      inputsChangeTs[BUTTON_UP] = currTs;

      if (SBM_DBG) {
        Serial.print (F("Buttons: UP - raw value="));
        Serial.println (val);
      }

      return BUTTON_UP;
    } else if ((val > BDOWN_MIN) &&
               (val < BDOWN_MAX) &&
               (inputs[BUTTON_DOWN] == false) &&
               isDebounceTimeout (BUTTON_DOWN)) {
      inputs[BUTTON_DOWN] = true;
      inputsChangeTs[BUTTON_DOWN] = currTs;

      if (SBM_DBG) {
        Serial.print (F("Buttons: DOWN - raw value="));
        Serial.println (val);
      }

      return BUTTON_DOWN;
    } else if ((val > BCENTER_MIN) &&
               (val < BCENTER_MAX) &&
               (inputs[BUTTON_CENTER] == false) &&
               isDebounceTimeout (BUTTON_CENTER)) {
      inputs[BUTTON_CENTER] = true;
      inputsChangeTs[BUTTON_CENTER] = currTs;

      if (SBM_DBG) {
        Serial.print (F("Buttons: CENTER - raw value="));
        Serial.println (val);
      }

      return BUTTON_CENTER;
    } else if ((val > BBACK_MIN) &&
               (val < BBACK_MAX) &&
               (inputs[BUTTON_BACK] == false) &&
               isDebounceTimeout (BUTTON_BACK)) {
      inputs[BUTTON_BACK] = true;
      inputsChangeTs[BUTTON_BACK] = currTs;

      if (SBM_DBG) {
        Serial.print (F("Buttons: BACK - raw value="));
        Serial.println (val);
      }

      return BUTTON_BACK;
    } else {
      /* if (val < 960) {
        Serial.print("Buttons: raw value=");
        Serial.println (val);
      } */
      // Serial.println("Buttons: resetting all buttons");
      for ( int bselect = 0; bselect < 7; bselect++) {
        inputs[bselect] = false;
        inputsChangeTs[bselect] = currTs;
      }
      return BUTTON_NONE;
    }
  }
}
