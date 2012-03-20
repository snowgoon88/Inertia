/*
 * Copyright (C) 2008 Nicolas P. Rougier
 * Modified Alain 2011
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SHIP_H__
#define __SHIP_H__
#include "object.h"

#ifdef HAVE_BOOST
    typedef boost::shared_ptr<class Ship> ShipPtr;
#else
    typedef class Ship * ShipPtr;
#endif


/**
 * A simple spaceship 3D model.
 *
 */
class Ship : public Object {

public:

    /**
     * @name Creation/Destruction
     */
    /**
     * Default constructor
     */
    Ship (void);

    /**
     * Destructor
     */
    virtual ~Ship (void);
    //@}


    /**
     *  @name Rendering
     */
    /**
     * Render the cube
     */
    virtual void render (void);
    //@}

};

#endif
