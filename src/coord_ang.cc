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
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.

 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "coord_ang.h"
#include <iostream>
#include "utils.h"

CoordAng::CoordAng (void) : Object()
{
    set_visible (true);
    set_size (1,1,1);
    set_position (0,0,0);
    set_fg_color (0,1,0,.5);
    set_br_color (0,1,0,1);
    set_bg_color (0,1,0,.5);
    alpha_ = 1.0f;
    fade_in_delay_ = 0;
    fade_out_delay_ = 0;

    std::ostringstream oss;
    oss << "CoordAng_" << id_;
    set_name (oss.str());

    _radius_ratio = 0.2;
    _nb_points = 36;
    _ang_Oxy = M_PI/ 4.0;
    _ang_Oxz = M_PI/ 3.0;

    // Generate points for the circle
    _pt_ext = new float[_nb_points*3];
    _pt_int = new float[_nb_points*3];
    for( int ipt=0; ipt < _nb_points; ipt++ ) {
      _pt_ext[ipt*3+0] = 1.0 * cos( (ipt / (float) _nb_points) * 2 * M_PI );
      _pt_ext[ipt*3+1] = 1.0 * sin( (ipt / (float) _nb_points) * 2 * M_PI );
      _pt_ext[ipt*3+2] = 0.0;

      _pt_int[ipt*3+0] = (1.0 - _radius_ratio ) * _pt_ext[ipt*3+0];
      _pt_int[ipt*3+1] = (1.0 - _radius_ratio ) * _pt_ext[ipt*3+1];
      _pt_int[ipt*3+2] = (1.0 - _radius_ratio ) * _pt_ext[ipt*3+2];
    }
}

CoordAng::~CoordAng (void)
{
  if( _pt_ext != NULL ) delete [] _pt_ext;
  if( _pt_int != NULL ) delete [] _pt_int;
}

void
CoordAng::render (void)
{
  int i;

    compute_visibility();
    if (not get_visible()) return;

    GLint mode;
    glGetIntegerv (GL_RENDER_MODE, &mode);

    glEnable (GL_LINE_SMOOTH);


    if (mode == GL_SELECT) {
        glLoadName (id_);
    }

    glPushMatrix();
    glScalef (get_size().x, get_size().y, get_size().z);
    glTranslatef (get_position().x, get_position().y, get_position().z);

    //std::cout << "==== Render CoordAng ==== \n";
    
    // Lines of circle
    glColor4fv (get_br_color().data);
    glLineWidth (2.0);
    glBegin( GL_LINE_STRIP );
    for ( i=0; i<_nb_points; i++) {
      glVertex3f( _pt_ext[i*3+0], _pt_ext[i*3+1], _pt_ext[i*3+2] ); 
    } 
    glVertex3f( _pt_ext[0+0], _pt_ext[0+1], _pt_ext[0+2] ); 
    glEnd();

    // 0xy_angle
    int upper_limit = (int) ceill( _ang_Oxy / (2 * M_PI) * _nb_points );
    //std::cout << "upper=" << upper_limit << "\n";

    glPushAttrib (GL_ENABLE_BIT);
    glDisable (GL_TEXTURE_2D);
    glDisable (GL_LIGHTING);
    glDisable (GL_CULL_FACE);
 
    glColor4fv( get_bg_color().data );
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
    glPolygonOffset (1, 1);
    glEnable (GL_POLYGON_OFFSET_FILL);
    glBegin( GL_QUAD_STRIP );
    for( int i=0; i < upper_limit; i++ ) {
      glVertex3f( _pt_int[i*3+0], _pt_int[i*3+1], _pt_int[i*3+2] );
      glVertex3f( _pt_ext[i*3+0], _pt_ext[i*3+1], _pt_ext[i*3+2] );
    }
    glEnd();
    glPopAttrib ();

    glColor4fv (get_br_color().data);
    glBegin( GL_LINE_STRIP );
    glVertex3f( _pt_ext[0+0], _pt_ext[0+1], _pt_ext[0+2] );
   
    for ( i=0; i< upper_limit; i++) {
      glVertex3f( _pt_int[i*3+0], _pt_int[i*3+1], _pt_int[i*3+2] );
      //std::cout << "INT " << _pt_int[i*3+0] << " " << _pt_int[i*3+1] << " " << _pt_int[i*3+2] << "\n";
      //std::cout << "EXT " << _pt_ext[i*3+0] << " " << _pt_ext[i*3+1] << " " << _pt_ext[i*3+2] << "\n";
    } 
    glVertex3f( _pt_ext[(i-1)*3+0], _pt_ext[(i-1)*3+1], _pt_ext[(i-1)*3+2] );
    glEnd();

    // Rotate for the second angle
    glPushMatrix();
    glRotatef( to_deg( (upper_limit-1) * 2 * M_PI / (float) _nb_points ),
	       0, 0, 1.0 );
    glRotatef( 90.0, 1, 0, 0 );
    glColor4fv (get_br_color().data);
    glLineWidth (2.0);
    glBegin( GL_LINE_STRIP );
    for ( i=0; i<_nb_points; i++) {
      glVertex3f( _pt_ext[i*3+0], _pt_ext[i*3+1], _pt_ext[i*3+2] ); 
    } 
    glVertex3f( _pt_ext[0+0], _pt_ext[0+1], _pt_ext[0+2] ); 
    glEnd();

    // 0xz_angle
    upper_limit = (int) ceill( _ang_Oxz / (2 * M_PI) * _nb_points );
    //std::cout << "upper=" << upper_limit << "\n";

    glPushAttrib (GL_ENABLE_BIT);
    glDisable (GL_TEXTURE_2D);
    glDisable (GL_LIGHTING);
    glDisable (GL_CULL_FACE);
 
    glColor4fv( get_bg_color().data );
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
    glPolygonOffset (1, 1);
    glEnable (GL_POLYGON_OFFSET_FILL);
    glBegin( GL_QUAD_STRIP );
    for( i=0; i < upper_limit; i++ ) {
      glVertex3f( _pt_int[i*3+0], _pt_int[i*3+1], _pt_int[i*3+2] );
      glVertex3f( _pt_ext[i*3+0], _pt_ext[i*3+1], _pt_ext[i*3+2] );
    }
    glEnd();
    glPopAttrib ();

    glColor4fv (get_br_color().data);
    glBegin( GL_LINE_STRIP );
    for ( i=0; i< upper_limit; i++) {
      glVertex3f( _pt_int[i*3+0], _pt_int[i*3+1], _pt_int[i*3+2] );
      //std::cout << "INT " << _pt_int[i*3+0] << " " << _pt_int[i*3+1] << " " << _pt_int[i*3+2] << "\n";
      //std::cout << "EXT " << _pt_ext[i*3+0] << " " << _pt_ext[i*3+1] << " " << _pt_ext[i*3+2] << "\n";
    } 
    glVertex3f( _pt_ext[(i-1)*3+0], _pt_ext[(i-1)*3+1], _pt_ext[(i-1)*3+2] );
    glVertex3f( 0, 0, 0);
    glEnd();
    glPopMatrix();

    glPopMatrix();
    if (mode == GL_SELECT) {
      glLoadName (0);
    }
    glPopAttrib();
}
