// -*- coding: utf-8 -*-
#ifndef __UTILS_H_
#define __UTILS_H_

#include "math.h"

/** Angle conversion */
float to_deg( float rad );
float to_rad( float deg );
/** Angle Clip to [-M_PI,M_PI]*/
float clip_rad_pi( float rad);
/** Angle Clip to [0,2*M_PI]*/
float clip_rad_2pi( float rad);

#endif
