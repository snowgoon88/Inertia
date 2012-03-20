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

#ifndef __REF_FRAME_H__
#define __REF_FRAME_H__
#include "object.h"

#ifdef HAVE_BOOST
    typedef boost::shared_ptr<class RefFrame> RefFramePtr;
#else
    typedef class RefFrame * RefFramePtr;
#endif


/**
 * A reference frame depicted by 3 axes (X,Y,Z) and a 1/8 of a wiresphere.
 * Main color given by 'fg', sphere color by 'br'.
 *
 */
class RefFrame : public Object {

public:

    /**
     * @name Creation/Destruction
     */
    /**
     * Default constructor
     */
    RefFrame (void);

    /**
     * Destructor
     */
    virtual ~RefFrame (void);
    //@}


    /**
     *  @name Rendering
     */
    /**
     * Render the cube
     */
    virtual void render (void);
    //@}

    /** Angle around Oz */
    float _ang_Oz1;
    /** Angle around Ox */
    float _ang_Ox1;
    /** Angle around Oz */
    float _ang_Oz2;
    /** Nb of points in a quarter circle */
    int _nb_points;
    /** WireSphere */
    float *_pt_sphere;
};

#endif
