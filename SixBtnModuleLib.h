#ifndef __SBMLIB_H_
#define __SBMLIB_H_

#include "Arduino.h"

const bool SBM_DBG = true;
const unsigned long debounceInterval = 50;
// const unsigned long inputLockedTimeout = 1000;
const unsigned long inputReadInterval = 100;

/* ****************************************************************************
  Button definitions
  ****************************************************************************/
enum sbm_button {BUTTON_LEFT = 0,
                 BUTTON_RIGHT = 1,
                 BUTTON_UP = 2,
                 BUTTON_DOWN = 3,
                 BUTTON_CENTER = 4,
                 BUTTON_BACK = 5,
                 BUTTON_NONE = 10 };

/* ****************************************************************************
  Button resistance range when using keypad
  ****************************************************************************/
enum buttons_minmax {BLEFT_MIN   = 100, BLEFT_MAX   = 249,
                     BRIGHT_MIN  = 650, BRIGHT_MAX  = 799,
                     BUP_MIN     = 250, BUP_MAX     = 399,
                     BDOWN_MIN   = 500, BDOWN_MAX   = 599,
                     BCENTER_MIN = 400, BCENTER_MAX = 499,
                     BBACK_MIN   = 800, BBACK_MAX   = 899 };

/* ****************************************************************************
  SBMReader:
  
  The SBM Reader listens on activity of the six module buttons.
  ****************************************************************************/
class SBMReader {
  private:
    unsigned long lastReadingTs = 0;
    bool inputs[6] = {false, false, false, false, false, false};
    unsigned long inputsChangeTs[6] = {0, 0, 0, 0, 0, 0};
    
    int inputPin = -1;
    volatile unsigned long lastChangeTs = 0;
    
    unsigned long analyzeLastTs = 0;

    bool isDebounceTimeout (sbm_button b);
  public:
    SBMReader (int inPin);

    sbm_button readButtons ();
};

#endif
