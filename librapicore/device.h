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

#ifndef RAPIDEVICE_H
#define RAPIDEVICE_H

#include <stdio.h>
#include <string>
#include <list>
#include "rapitypes.h"
#include "pose3d.h"
#include "dataupdateobserver.h"

namespace Rapi
{

/**
 * Abstract base class for all hardware devices a robot can have, e.g.
 * sensors, actuators, displays etc.
 * @author Jens Wawerla <jwawerla@sfu.ca>
 */
class ADevice
{
  public:
    /** Default destructor */
    virtual ~ADevice();
    /**
     * Get device type
     * @return device type
     */
    virtual tRapiDeviceType getDeviceType() = 0;
    /**
    * Initializes the device
    * @param return 1 if success 0 otherwise
    */
    virtual int init() = 0;
    /**
     * Enables or disables the device
     * @param enable = true to enable, false to disable
     */
    virtual void setEnabled( bool enable ) = 0;
    /**
    * Prints the devices main information
    */
    virtual void print() = 0;
    /**
     * Checks if the device is enabled or not
     * @return true if enabled, false otherwise
     */
    bool isEnabled();
    /**
     * Gets the name of the device
     * @return name of device
     */
    std::string getName();
    /**
     * Gets the time stamp of the last data set
     * @return time stamp
     */
    double getTimeStamp();
    /**
     * Gets the pose of the device relative to its parent
     * @return pose
     */
    CPose3d getRelativePose();
    /**
     * Adds an data update observer to this device. All connected observers
     * are notified in case of newly available data
     * @param observer to be added
     */
    void addDataUpdateObserver(ADataUpdateObserver* observer);

  protected:
    /**
     * Default constructor
     * @param devName name of device
     */
    ADevice( std::string devName );
    /**
     * Notifies all data update observers of newly available data
     */
    void notifyDataUpdateObservers();
    /**
     * Updates the data of the device
     */
    virtual void updateData() = 0;
    /** Flags if device is enabled or not */
    bool mFgEnabled;
    /** Name of device */
    std::string mDeviceName;
    /** Time stamp of last data set */
    double mTimeStamp;
    /** Pose relative to parent of device */
    CPose3d mRelativePose;
    /** List of registered data update observers */
    std::list<ADataUpdateObserver*> mDataUpdateObserverList;
};

} //namespace

#endif