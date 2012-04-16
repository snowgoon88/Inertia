// -*- coding: utf-8 -*-
#ifndef __UTILS_H_
#define __UTILS_H_

#include "math.h"

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

#endif
