/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include "Scalar.h"

#include <cassert>
#include <cmath>
#include <iosfwd>

namespace nix {

//! 3D Vector
/*!
 * A three dimensional vector.  Vectors are not affected
 * by translations.
 */
class Vector3
{
public:
	Scalar x /*! x component */, y /*! y component */, z /*! z component */;

	/*!
	 * \returns an uninitialized point
	 */
	Vector3()										//! default constructor
	 : x(0.0), y(0.0), z(0.0)
	{ }
	
	Vector3(const Vector3 &v)						//! copy constructor
	 : x(v.x), y(v.y), z(v.z)
	{ }
	
	Vector3(Scalar x, Scalar y, Scalar z)			//! returns the point (x, y, z)
	 : x(x), y(y), z(z)
	{ }
	
	/*!
	 * \param os [in] output stream to write to
	 * \returns os after it has been written to
	 */
	std::ostream& Print(std::ostream& os) const;	//!< prints this vector in readable form
	static const Vector3	ZAxis;					//!< the z direction vector (0, 0, 1)

};

//! prints a vector in readable form
/*!
 * \sa Vector3::Print()
 * \param os [in] output stream to write to
 * \param v [in] vector to write
 * \returns output stream after writing
 */
std::ostream& operator<<(std::ostream &os, const Vector3 &v);

}

