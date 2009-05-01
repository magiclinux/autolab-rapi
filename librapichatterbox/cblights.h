/***************************************************************************
 * Project: RAPI                                                           *
 * Author:  Jens Wawerla (jwawerla@sfu.ca)                                 *
 * $Id: $
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 **************************************************************************/

#ifndef RAPICBLIGHTS_H
#define RAPICBLIGHTS_H

#include "lights.h"
#include "cbdriver.h"

namespace Rapi
{

#define ALL_LEDS -1

typedef enum {DOT_OFF, DOT_ON, DOT_BLINK} t7SegDot;
typedef enum {RED, GREEN, BLUE, YELLOW, WHITE, BLACK} tColor;

/**
 * This class implements control for the rgb leds and the display of chatterbox
 * @author Jens Wawerla <jwawerla@sfu.ca>
 * @version 0.1 - 01/2008
 */
class CCBLights : public ALights
{
  public:
    /**
     * Default constructor
     * @param cbDriver HAL of the chatterbox
     * @param devName name of this device
     */
    CCBLights(CCBDriver* cbDriver, std::string devName);
    /** Default destructor */
    ~CCBLights();
    /**
     * Enables or disables the device 
     * @param enable = true to enable, false to disable 
     */
    virtual void setEnabled(bool enable);
    /**
     * Initializes the device
     * @param return 1 if success -1 otherwise
     */
    virtual int init();
    /**
     * This method gets called by the framework every step to update
     * the sensor data
     */
    virtual void updateData();
    /**
     * Sets a given rgb value for a light, note for none rgb lights
     * just set the red channel and leave the remaining open
     * @param id of light, -1 all leds
     * @param red [0..255]
     * @param green [0..255]
     * @param blue [0..255]
     * @return 1 if successfull, -1 otherwise
     */
    virtual int setLight(int id, unsigned char red,
                         unsigned char green = 0,
                         unsigned char blue = 0);

    /**
     * Sets a color for a given led
     * @param id of light, -1 all leds
     * @param color to be set
     */
    virtual int setLight(int id, tColor color);
    /**
     * Sets the dot of the 7 segment display
     * @param dot status of dot
     * @return 1 if successfull, -1 otherwise
     */
    int set7SegDot(t7SegDot dot);
    /**
     * Prints the devices main information
     */
    virtual void print();
    /**
     * Sets the blinking frequency of a led
     * @param id of led to be set, -1 all leds
     * @param enabled true enables blinking, false disables blinking
     * @param freq to be set [Hz]
     */
    virtual int setBlink(int id, bool enabled, float freq);


  protected:
    typedef struct  {
      float freq;
      int tick;
      bool enabled;
      bool on;
      unsigned char red;
      unsigned char green;
      unsigned char blue;
    } tBlink;

  private:
    /** Chatterbox driver to enable or disable the laser power */
    CCBDriver* mCBDriver;
    /** Blink setting for led */
    tBlink mBlink[5];
    /** Number of rgb leds available */
    unsigned char mNumRbgLeds;
    /** Status of 7 segment dot */
    t7SegDot mDot;
    /** Status of dot */
    tBlink mDotBlink;
};

} // namespace

#endif
