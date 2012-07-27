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
#include "device.h"
#include <string.h>
#include "printerror.h"

namespace Rapi
{

//-----------------------------------------------------------------------------
ADevice::ADevice ( std::string devName )
{
	printf("ADevice Zhao \n");
  mDeviceName = devName;
  mFgEnabled = false;
  mDataLogger = NULL;
}
//-----------------------------------------------------------------------------
ADevice::~ADevice()
{
}
//-----------------------------------------------------------------------------
void ADevice::startLogging(std::string filename)
{
  PRT_WARN0("This device does not implement logging");
}
//-----------------------------------------------------------------------------
void ADevice::startLogging()
{
  startLogging( "rapi.log");
}
//-----------------------------------------------------------------------------
bool ADevice::isEnabled() const
{
  return mFgEnabled;
}
//-----------------------------------------------------------------------------
std::string ADevice::getName() const
{
  return mDeviceName;
}
//-----------------------------------------------------------------------------
double ADevice::getTimeStamp() const
{
  return mTimeStamp;
}
//-----------------------------------------------------------------------------
CPose3d ADevice::getRelativePose() const
{
  return mRelativePose;
}
//-----------------------------------------------------------------------------
void ADevice::addDataUpdateObserver ( ADataUpdateObserver* observer )
{
  mDataUpdateObserverList.push_back ( observer );
}
//-----------------------------------------------------------------------------
void ADevice::notifyDataUpdateObservers()
{
  ADataUpdateObserver* observer;
  std::list<ADataUpdateObserver*>::iterator it;

  for ( it = mDataUpdateObserverList.begin();
        it != mDataUpdateObserverList.end(); it++ )
  {
    observer = *it;
    observer->newData ( this );
  }
}
//-----------------------------------------------------------------------------


} // namespace
