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

/**
 * Interface class to access the Brian's overhead camera tracker. Pose
 * measurements are given in the coordinate system set by the
 * coordinate system offset (by default, absolute).
 * @author Jens Wawerla <jwawerla@sfu.ca>
 */
class CAutolabTracker : public ALocalizer2d
{
  public:
    /**
     * Default constructor
     * @param devName name of device
     */
    CAutolabTracker(std::string devName );
    /** Default destructor */
    virtual ~CAutolabTracker();
};

} // namespace
