/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include <Scalar.h>

namespace nix {

class IParticle;

/**
 * Interface for particle generation.
 * The only method of substance is generate().
 */
class IParticleGenerator
{
  public:
	/// Generate a new particle.
	/// Memory is allocated by this method that must be freed by the called.
	/// @return A new IParticle is returned.  Null is never returned, but errors
	/// may be thrown.
	virtual IParticle* generate() const = 0;

	/// Get the average distance between the particles.
	/// This is distance from the exit point of one particle to the entry point
	/// of the next particle.
	/// \return Returns the average distance to use between the particles.
	virtual Scalar averageParticleDistance() const noexcept = 0;

	/// Default virtual destructor.
	virtual ~IParticleGenerator() = default;
};

}

