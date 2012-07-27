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
#include "localizer2d.h"

namespace Rapi
{

//-----------------------------------------------------------------------------
ALocalizer2d::ALocalizer2d ( std::string devName )
    : ADevice ( devName )
{
	printf("localizer2d zhao\n");
  mCoordinateSystemOffset = CPose2d( 0.0, 0.0, 0.0 );
}
//-----------------------------------------------------------------------------
ALocalizer2d::~ALocalizer2d()
{
}
//-----------------------------------------------------------------------------
void ALocalizer2d::setCoordinateSystemOffset ( CPose2d offset )
{
  mCoordinateSystemOffset = offset;
}
//-----------------------------------------------------------------------------
CPose2d ALocalizer2d::getPose() const
{
//  CPose2d localPose;
//  double angle = mCoordinateSystemOffset.mYaw;
//  localPose.mX = mPose.mX * cos( angle ) + mPose.mY * sin( angle );
//  localPose.mY = -mPose.mX * sin( angle ) + mPose.mY * cos( angle );
//  localPose.mYaw = normalizeAngle( mPose.mYaw - angle );
//  return localPose;
  return mPose;
}
//-----------------------------------------------------------------------------
void ALocalizer2d::setPose( const CPose2d pose )
{ // convert local pose to absolute
//  double angle = -mCoordinateSystemOffset.mYaw;
//  mPose.mX = pose.mX * cos( angle ) + pose.mY * sin( angle );
//  mPose.mY = -pose.mX * sin( angle ) + pose.mY * cos( angle );
//  mPose.mYaw = normalizeAngle( pose.mYaw - angle );
//
// printf("ALocalizer2d::setPose()\n");
  mPose = pose;
}
//-----------------------------------------------------------------------------
void ALocalizer2d::setToZero()
{
  mPose = CPose2d( 0.0, 0.0, 0.0);
}
//-----------------------------------------------------------------------------
void ALocalizer2d::print() const
{
  printf("Localizer2d: ");
  mPose.print();
}
//-----------------------------------------------------------------------------
} // namespace

