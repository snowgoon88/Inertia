// -*- coding: utf-8 -*-

#include "utils.h"

/****************************************************************** LINE_REPR */
std::string line_repr( Eigen::VectorXf vector, int precision)
{
  std::stringstream ss;

  for( int i=0; i < vector.size(); i++) {
    ss << SETPREC(precision) << (vector)(i) << " ";
  }
  
  return ss.str();
}
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
// ****************************************************************** VEC TO ANG
void ang_from_vec( TVec3 v, float& ang_z1, float& ang_y2 )
{
  // Projection on Oxy
  TVec3 vxy = v;
  vxy(2) = 0;
  if( vxy.norm() > 0.0001 ) {
    // Angle Ox,vxy
    TVec3 ux( 1, 0, 0);
    ang_z1 = acos( ux.dot( vxy ) / vxy.norm() / ux.norm());
    // Check for the right sign
    if( vxy(1) < 0 ) ang_z1 = -ang_z1;
    
    // Angle vxy v
    ang_y2 = - acos( vxy.dot( v ) / v.norm() / vxy.norm() );
    // Check for the right sign
    if( v(2) < 0 ) ang_y2 = -ang_y2;
  }
  else {
    ang_z1 = 0;
    if( v(2) > 0 ) {
      ang_y2 = - M_PI / 2.0;
    }
    else {
      ang_y2 = M_PI / 2.0;
    }
  }
}
/****************************************************************** LINE_REPR */
std::string line_repr( Eigen::VectorXf vector )
{
  std::stringstream ss;

  for( int i=0; i < vector.size(); i++) {
    ss << (vector)(i) << " ";
  }
  ss << ";";
  
  return ss.str();
}
/******************************************************************************/
TwStructMember SVec3Members[] = {
    { "x", TW_TYPE_FLOAT, offsetof(SVec3, x), "Step=0.1" },
    { "y", TW_TYPE_FLOAT, offsetof(SVec3, y), "Step=0.1" },
    { "z", TW_TYPE_FLOAT, offsetof(SVec3, z), "Step=0.1" }
};
// *****************************************************************************
