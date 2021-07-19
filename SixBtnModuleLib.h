#ifndef __SBMLIB_H_
#define __SBMLIB_H_

#include "Arduino.h"

const bool __SBM_DBG = true;
const unsigned short debounceInterval = 200;
const unsigned short inputReadInterval = 100;

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
  Button resistance range when using keypad
  ****************************************************************************/
enum buttons_minmax {BLEFT_MIN   = 130, BLEFT_MAX   = 180,
                     BUP_MIN     = 310, BUP_MAX     = 350,
                     BCENTER_MIN = 440, BCENTER_MAX = 499,
                     BDOWN_MIN   = 570, BDOWN_MAX   = 595,
                     BRIGHT_MIN  = 710, BRIGHT_MAX  = 750,
                     BBACK_MIN   = 870, BBACK_MAX   = 900 };

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

    byte currentButton (int value);
    
  public:
    SBMReader ();
    SBMReader (int inPin);
    
    void setInputPin (int inPin);
    byte readButtons ();
};

#endif
