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
#include "ref_frame.h"
#include <iostream>
#include "utils.h"

RefFrame::RefFrame (void) : Object()
{
    set_visible (true);
    set_size (1,1,1);
    set_position (0,0,0);
    set_fg_color (1,0,0,1.0);
    set_br_color (0.5,0.5,0.5,1);
    set_bg_color (1,1,1,0.5);
    alpha_ = 1.0f;
    fade_in_delay_ = 0;
    fade_out_delay_ = 0;

    std::ostringstream oss;
    oss << "RefFrame_" << id_;
    set_name (oss.str());

    _nb_points = 6;
    _pt_sphere = new float[((_nb_points+1)*(_nb_points+1))*3];
    // Generate points for the wiresphere
    float alpha, beta;
    for( int i_beta = 0; i_beta <= _nb_points; i_beta++ ) {
     beta = i_beta / (float) _nb_points * M_PI / 2.0; 
      for( int i_alpha = 0; i_alpha <= _nb_points; i_alpha++ ) {
	alpha = i_alpha / (float) _nb_points * M_PI / 2.0; 

	_pt_sphere[(i_beta*_nb_points+i_alpha)*3+0] = cosf(beta)*cosf(alpha);
	_pt_sphere[(i_beta*_nb_points+i_alpha)*3+1] = cosf(beta)*sinf(alpha);
	_pt_sphere[(i_beta*_nb_points+i_alpha)*3+2] = sinf(beta);
      }
    }
}      

RefFrame::~RefFrame (void)
{
  if( _pt_sphere != NULL ) delete [] _pt_sphere;
}

void
RefFrame::render (void)
{
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
    glRotatef( _ang_Oz1, 0,0,1);
    glRotatef( _ang_Ox1, 1,0,0);
    glRotatef( _ang_Oz2, 0,0,1);

    //std::cout << "==== Render RefFrame ==== \n";
    
    // Axes
    glColor4fv (get_fg_color().data);
    glLineWidth (2.0);
    glBegin( GL_LINES ); {
      glVertex3f( 0, 0, 0);
      glVertex3f( 2, 0, 0);
      glVertex3f( 0, 0, 0);
      glVertex3f( 0, 2, 0);
      glVertex3f( 0, 0, 0);
      glVertex3f( 0, 0, 2);
    }
    glEnd();

    // Lines of sphere
    glColor4fv (get_br_color().data);
    glLineWidth (0.5);
    for( int i_beta = 0; i_beta <= _nb_points; i_beta++ ) {
      glBegin( GL_LINE_STRIP );
      for( int i_alpha = 0; i_alpha <= _nb_points; i_alpha++ ) {
	glVertex3f( _pt_sphere[(i_beta*_nb_points+i_alpha)*3+0],
		    _pt_sphere[(i_beta*_nb_points+i_alpha)*3+1],
		    _pt_sphere[(i_beta*_nb_points+i_alpha)*3+2] );
      }
      glEnd();
    }    
    for( int i_alpha = 0; i_alpha <= _nb_points; i_alpha++ ) {
      glBegin( GL_LINE_STRIP );
      for( int i_beta = 0; i_beta <= _nb_points; i_beta++ ) {
	glVertex3f( _pt_sphere[(i_beta*_nb_points+i_alpha)*3+0],
		    _pt_sphere[(i_beta*_nb_points+i_alpha)*3+1],
		    _pt_sphere[(i_beta*_nb_points+i_alpha)*3+2] );
      }
      glEnd();
    }    

    glPopMatrix();
    if (mode == GL_SELECT) {
      glLoadName (0);
    }
    glPopAttrib();
}
