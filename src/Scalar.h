/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   Hacked from SPLITS by Brad Kimmel                                     *
 ***************************************************************************/
#pragma once

namespace nix {

#define USE_LONG_DOUBLE
//#define USE_DOUBLE
//#define USE_FLOAT

#ifdef USE_LONG_DOUBLE
using Scalar = long double;
#endif

#ifdef USE_DOUBLE
using Scalar = double;
#endif

#ifdef USE_FLOAT
using Scalar = float;
#endif

}

