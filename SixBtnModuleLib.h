#ifndef __SBMLIB_H_
#define __SBMLIB_H_

#include "Arduino.h"

/* ****************************************************************************
  default settings
  ****************************************************************************/
const bool __SBM_DBG = false;

const unsigned short __STD_DEBOUNCE_INTERVAL = 200;
const unsigned short __STD_INPUT_READ_INTERVAL = 100;
const unsigned short __STD_BVAL_RANGE = 30;

// default button values
const unsigned short __BLEFT_MVAL   = 120;
const unsigned short __BUP_MVAL     = 300;
const unsigned short __BCENTER_MVAL = 450;
const unsigned short __BDOWN_MVAL   = 580;
const unsigned short __BRIGHT_MVAL  = 730;
const unsigned short __BBACK_MVAL   = 880;

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
const unsigned short BUTTONS_NUM = 6;

enum sbm_button {BUTTON_LEFT = 0,
                 BUTTON_UP = 1,
                 BUTTON_CENTER = 2,
                 BUTTON_DOWN = 3,
                 BUTTON_RIGHT = 4,
                 BUTTON_BACK = 5,
                 BUTTON_NONE = 10 };
                 
enum sbm_button_alt {BUTTON_1 = 0,
                     BUTTON_2 = 1,
                     BUTTON_3 = 2,
                     BUTTON_4 = 3,
                     BUTTON_5 = 4,
                     BUTTON_6 = 5 };

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

    unsigned short buttonValues[BUTTONS_NUM] = {__BLEFT_MVAL,
                                                __BUP_MVAL,
                                                __BCENTER_MVAL,
                                                __BDOWN_MVAL,
                                                __BRIGHT_MVAL,
                                                __BBACK_MVAL};

    byte identifyButton (int value);
    
  public:
    SBMReader (int inPin, int mode);

    void setButtonValue (byte btn, unsigned short newButtonValue);
    short getButtonValue (byte btn);
    
    void setButtonValueRange (unsigned short newRange);
    unsigned short getButtonValueRange ();
    
    void setDebounceInterval (unsigned short newDbInterval);
    unsigned short getDebounceInterval ();
    
    void setReadInterval (unsigned short newReadInterval);
    unsigned short getReadInterval ();
    
    byte readButtons ();
};

#endif
