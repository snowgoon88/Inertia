// -*- coding: utf-8 -*-
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

#ifndef __COORD_ANG_H__
#define __COORD_ANG_H__
#include "object.h"

#ifdef HAVE_BOOST
    typedef boost::shared_ptr<class CoordAng> CoordAngPtr;
#else
    typedef class CoordAng * CoordAngPtr;
#endif


/**
 * An arrow repered by 2 angles in a kind of "rosace".
 *
 */
class CoordAng : public Object {

public:

    /**
     * @name Creation/Destruction
     */
    /**
     * Default constructor
     */
    CoordAng (void);

    /**
     * Destructor
     */
    virtual ~CoordAng (void);
    //@}


    /**
     *  @name Rendering
     */
    /**
     * Render the cube
     */
    virtual void render (void);
    //@}

    /** ratio for internal radius */
    float _radius_ratio;
    /** nb points in a circle */
    int _nb_points;
    /** Exterior circle */
    float *_pt_ext;
    /** Interior circle */
    float *_pt_int;
    /** current 0xy angle */
    float _ang_Oxy;
    /** current Oxz angle */
    float _ang_Oxz;

};

#endif
