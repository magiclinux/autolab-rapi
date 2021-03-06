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

#ifndef RAPIDRIVETRAIN2DOF_H
#define RAPIDRIVETRAIN2DOF_H

#include "device.h"
#include "velocity2d.h"
#include "limit.h"
#include "odometry.h"

namespace Rapi
{

/**
 * Abstract base for a drivetrain with 2 DOF. Note all velocity commands are
 * limited in terms of absolute value and in acceleration. The user has free
 * access to these limits and thereby can disable them at her own risk.
 * The only execption to the limits is emergencyStop().
 * @author Jens Wawerla <jwawerla@sfu.ca>
 */
class ADrivetrain2dof : public ADevice
{
  public:
    /** Default destructor */
    virtual ~ADrivetrain2dof();
    /**
     * Get device type
     * @return device type
     */
    virtual tRapiDeviceType getDeviceType() { return RAPI_DRIVETRAIN2DOF; };
    /**
     * Gets the measured velocity of the robot
     * @return velocity
     */
    virtual CVelocity2d getVelocity() const;
    /**
     * Gets the current velocity command set for the robot
     * @return velocity
     */
    virtual CVelocity2d getVelocityCmd() const;
    /**
     * Sets the velocity and turn rate of the robot
     * @param velocity forward positive, backward negative [m/s]
     * @param turnrate positve counterclockwise, negative clockwise [rad/s]
     */
    virtual void setVelocityCmd( const float velocity, const float turnrate );
    /**
     * Sets the velocity and turn rate of the robot
     * @param velocity forward positive, backward negative [m/s]
     *                 positve counterclockwise, negative clockwise [rad/s]
     */
    virtual void setVelocityCmd( const CVelocity2d velocity );
    /**
     * Sets a rotational speed for the robot
     * @param turnrate positve counterclockwise, negative clockwise [rad/s]
     */
    virtual void setRotationalVelocityCmd( const float turnrate);
    /**
     * Sets a translational speed for the robot
     * @param velocity forward positive, backward negative [m/s]
     */
    virtual void setTranslationalVelocityCmd( const float velocity);
    /**
     * Stops the robot by setting the user command velocities to zero, but
     * obeys the acceleration limits.
     */
    virtual void stop();
    /**
     * Emergency stop the drivetrain, stop at all costs, not obeying any
     * acceleration limits
     */
    virtual void emergencyStop();
    /**
     * Checks if robot is stopped or not
     * @return true if stopped, false otherwise
     */
    virtual bool isStopped() const;
    /**
     * Prints the devices main information
     */
    virtual void print() const;
    /**
     * Checks if the robot got stuck somewhere and is thus stalled
     * @return true if stalled, false otherwise
     */
    virtual bool isStalled() const;
    /**
     * Gives the time since the drive train is stalled
     * @return stalled time [s], or 0 if not stalled
     */
    virtual float stalledSince() const;
    /**
     * Gets the odometry of this drivetrain
     * @return odometry
     */
    virtual COdometry* getOdometry() const;
    /**
     * Gets the upper velocity limits
     * @return limits
     */
    virtual CVelocity2d getUppererVelocityLimit() const { return mUpperVelocityLimit; };
    /**
     * Gets the lower velocity limits
     * @return limits
     */
    virtual CVelocity2d getLowerVelocityLimit() const { return mLowerVelocityLimit; };
    /**
     * Sets the upper velocity limits
     * @param limits
     */
    virtual void setUppererVelocityLimit(CVelocity2d limit);
    /**
     * Sets the lower velocity limits
     * @param limits
     */
    virtual void setLowerVelocityLimit(CVelocity2d limit);
    /**
     * Sets the limit for translational acceleration
     * @param limit [m/s^2]
     */
    virtual void setTranslationalAccelerationLimit(CLimit limit);
    /**
     * Sets the limit for rotational acceleration
     * @param limit [m/s^2]
     */
    virtual void setRotationalAccelerationLimit(CLimit limit);
    /**
     * Gets the limit for translational acceleration
     * @return [m/s^2]
     */
    virtual CLimit getTranslationalAccelerationLimit() const { return mTransAccelLimit; };
    /**
     * Gets the limit for rotational acceleration
     * @return [m/s^2]
     */
    virtual CLimit getRotationalAccelerationLimit() const { return mRotatAccelLimit; };

    /**
     * Gets the name of a gui this device can be visualized
     * @return name of gui
     */
    virtual std::string getGuiName() { return "DrivetrainWidget"; };
    /**
     * Start logging of the devices data to a file. Note there can only be
     * one log file for all devices, hence the first device to enable logging
     * determines the name of the log file.
     * @param filename to log to
     */
    virtual void startLogging(std::string filename);

  protected:
    /** Default constructor
     * @param devName name of device
     */
    ADrivetrain2dof( std::string devName = "ADrivetrain2dof" );
    /**
     * Limits mVelocityCmd to be within mLowerVelocityLimit and mUpperVelocityLimit
     */
    void applyVelocityLimits();
    /**
     * Limits velocity commands to obey acceleration limits
     * @param dt step size [s]
     */
    void applyAccelerationLimits(float dt);
    /** Odometry */
    COdometry* mOdometry;
    /** Velocity command as set by the user */
    CVelocity2d mVelocityUserCmd;
    /** Velocity command after acceleration limits, as send to the robot */
    CVelocity2d mVelocityLimitedCmd;
    /** Velocity measurement */
    CVelocity2d mVelocityMeas;
    /** Upper velocity limit */
    CVelocity2d mUpperVelocityLimit;
    /** Lower velocity limit */
    CVelocity2d mLowerVelocityLimit;
    /** Translational acceleration limit [m/s^2] */
    CLimit mTransAccelLimit;
    /** Rotational acceleration limit [m/s^2] */
    CLimit mRotatAccelLimit;
    /** Flags if robot is stalled somewhere */
    bool mFgStalled;
    /** Stalled timer */
    float mStalledTimer;
};

} // namespace

#endif
