// -*- coding: utf-8 -*-
#ifndef __UTILS_H_
#define __UTILS_H_

#include "math.h"
#include <Eigen/Dense>
// AntTweakBar
#include <AntTweakBar.h>

typedef Eigen::Vector3f TVec3;

// Eigen library for "dense" matrices and vectors
#include <Eigen/Dense>
#include <vector>

#include <string>
#include <iostream>
#include <sstream>

// Précision dans les formats
#include <iomanip>
#define SETPREC(P) std::setiosflags(std::ios::fixed) << std::setprecision(P)

typedef Eigen::Vector2f TVec2;
typedef Eigen::Vector3f TVec3;

/**
 * Return a str line representation of a vector.
 */
std::string line_repr( Eigen::VectorXf vector, int precision=2);

/** Angle conversion */
float to_deg( float rad );
float to_rad( float deg );
/** Angle Clip to [-M_PI,M_PI]*/
float clip_rad_pi( float rad);
/** Angle Clip to [0,2*M_PI]*/
float clip_rad_2pi( float rad);

/** From a TVec3, get 2 first euler angles : 0x->vxy and vxy->v */
void ang_from_vec( TVec3 v, float& ang_z1, float& ang_y2 );

/**
 * Return a str line representation of a vector.
 */
std::string line_repr( Eigen::VectorXf vector );

/** AntTweakBar structure for TVec3 */
// A user defined structure
typedef struct {
  float x; float y; float z;
} SVec3;
//SVec3 elem;  // an element of type MyStruct that we want to add to a tweak bar

// Description of the structure (note that you are not required to describe all members, and that members can be reordered)
extern TwStructMember SVec3Members[];

#endif // __UTILS_H_
