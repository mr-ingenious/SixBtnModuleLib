#ifndef __SBMLIB_H_
#define __SBMLIB_H_

#include "Arduino.h"

/* ****************************************************************************
  default settings
  ****************************************************************************/
const bool __SBM_DBG = true;
const unsigned short __STD_DEBOUNCE_INTERVAL = 200;
const unsigned short __STD_INPUT_READ_INTERVAL = 100;
const unsigned short __STD_BVAL_RANGE = 30;

/* ****************************************************************************
  MODULE LAYOUT
  *****************************************************************************

                
                +------> Ucc (e.g. +3.3 V)
                |
                | +----> Ua (connect to analog pin on Arduino)
                | |
                | | +--> GND
                | | |
             +--O-O-O----------------------------------+
             |                                         |
             |               +---------+               |
             |               |         |               |
             |               |   UP    |               |
             |               |         |               |
             |               +---------+               |
             |                                         |
             |  +---------+  +---------+  +---------+  |
             |  |         |  |         |  |         |  |
             |  |  LEFT   |  | CENTER  |  |  RIGHT  |  |
             |  |         |  |         |  |         |  |
             |  +---------+  +---------+  +---------+  |
             |                                         |
             |               +---------+  +---------+  |
             |               |         |  |         |  |
             |               |  DOWN   |  |  BACK   |  |
             |               |         |  |         |  |
             |               +---------+  +---------+  |
             |                                         |
             +-----------------------------------------+

   ****************************************************************************/



/* ****************************************************************************
  Button definitions
  ****************************************************************************/
enum sbm_button {BUTTON_NONE = 0,
                 BUTTON_LEFT = 1,
                 BUTTON_RIGHT = 2,
                 BUTTON_UP = 4,
                 BUTTON_DOWN = 8,
                 BUTTON_CENTER = 16,
                 BUTTON_BACK = 32 };

/* ****************************************************************************
  Button resistance middle value
  ****************************************************************************/
enum buttons_mval {BLEFT_MVAL   = 120,
                   BUP_MVAL     = 300,
                   BCENTER_MVAL = 450,
                   BDOWN_MVAL   = 580,
                   BRIGHT_MVAL  = 730,
                   BBACK_MVAL   = 880};

/* ****************************************************************************
  struct for storage of relevant button trigger event information
  ****************************************************************************/
struct sbm_btnInfo {
    byte btn = BUTTON_NONE;
    unsigned long long changedTs = 0;
};

/* ****************************************************************************
  SBMReader:
  
  The SBM Reader listens on activity of the six module buttons.
  ****************************************************************************/
class SBMReader {
  private:
    unsigned long long lastReadingTs = 0;
    sbm_btnInfo lastPressed;
    int inputPin = -1;
    unsigned short valueRange = __STD_BVAL_RANGE;
    unsigned short inputReadInterval = __STD_INPUT_READ_INTERVAL;
    unsigned short debounceInterval = __STD_DEBOUNCE_INTERVAL;

    byte identifyButton (int value);
    
  public:
    SBMReader ();
    SBMReader (int inPin, int mode);

    byte readButtons ();
    void setButtonValueRange (unsigned short newRange);
    unsigned short getButtonValueRange ();
    
    void setDebounceInterval (unsigned short newDbInterval);
    unsigned short getDebounceInterval ();
    
    void setReadInterval (unsigned short newReadInterval);
    unsigned short getReadInterval ();
};

#endif
