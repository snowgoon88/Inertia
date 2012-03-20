// -*- coding: utf-8 -*-

#include "utils.h"

/*******************************************************************CONVERSION*/
float to_deg( float rad )
{
  float deg = fmod( (rad * 180.0 / M_PI), 360.0);
  if( deg > 180.0) deg = deg - 360.0;
  if( deg < -180.0) deg = deg + 360.0;
  return deg;
}
float to_rad( float deg )
{
  float rad = fmod( (deg * M_PI / 180.0), 2*M_PI);
  if( rad > M_PI) rad = rad - (2*M_PI);
  if( rad < -M_PI) rad = rad + (2*M_PI);
  return rad;
}
float clip_rad_pi( float rad )
{
  float res = fmod( rad, 2*M_PI);
  if( res > M_PI) res = res - (2*M_PI);
  if( res < -M_PI) res = res + (2*M_PI);
  return res;
}
float clip_rad_2pi( float rad )
{
  float res = fmod( rad, 2*M_PI);
  if( res > 2 * M_PI) res = res - (2*M_PI);
  if( res < 0) res = res + (2*M_PI);
  return res;
}
/******************************************************************************/
