/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include <Scalar.h>

namespace nix {

class Interval;
class Point3;
class Ray3;
class Vector3;

/// Pure virtual interface for a particle.
class IParticle
{
  public:
	virtual bool GetExitPoint(const Ray3& ray, Scalar &t, Point3& p, Vector3& N) const = 0;
	/// Get a random point on the hemispher of the particle's surface that is in
	/// the direction of \c dir.
	///
	/// @param[out] p Out parameter storing the random point on the particle's
	///               surface.
	/// @param[out] N Out parameter storing the normal at that point.
	/// @param dir The direction of the incoming ray is used to choose a point
	///        on the correct hemisphere of the particle.
	virtual void GetUniformRandomPoint(Point3& p, Vector3& N, const Vector3& dir) const = 0;
	virtual bool intersects(const Ray3& ray, const Interval& I) const = 0;
	virtual bool intersects(const Ray3& ray) const = 0;

	virtual Scalar diameter() const = 0;

	virtual ~IParticle() = default;

};

} // namespace nix

