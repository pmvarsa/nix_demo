/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include <IParticleGenerator.h>
#include <PiecewiseLinearSpectrum.h>
#include <Scalar.h>

#include <Array2.h>

#include <memory>

namespace nix {

/// Generate a random spheroidal particle.
class RandomSpheroidParticleGenerator : public IParticleGenerator
{
  public:

	/// Construct a RandomSpheroidParticleGenerator object that is ready to use.
	/// \param prolateWarp The 2D array used for warping the prolate spheres.
	/// \param oblateWarp The 2D array used for warping the oblate spheres.
	/// \param sizeWarp The warping function for the particle size.
	/// \param sphericityWarp The warping function for the sphericity.
	/// \param avgParticleDistance The average space between the particles. This
	///        is the distance from the exit point of one particle to the entry
	///        point of the next particle.
	RandomSpheroidParticleGenerator(
		const Array2 prolateWarp, const Array2 oblateWarp,
		std::shared_ptr<PiecewiseLinearSpectrum> sizeWarp,
		std::shared_ptr<PiecewiseLinearSpectrum> sphericityWarp,
		Scalar avgParticleDistance);

	IParticle* generate() const;

	/// Get the average distance between the particles.
	/// This is distance from the exit point of one particle to the entry point
	/// of the next particle.
	/// \return Returns the average distance to use between the particles.
	virtual Scalar
	averageParticleDistance() const noexcept { return 0.0; }

	/// Provided const access to the size warp function for debugging.
	/// \return Returns a const pointer.
	std::shared_ptr<const PiecewiseLinearSpectrum>
	sizeWarpFunction() const { return _sizeWarp; }

	/// Provided const access to the sphericity warp function for debugging.
	/// \return Returns a const pointer.
	std::shared_ptr<const PiecewiseLinearSpectrum>
	sphericityWarpFunction() const { return _sphericityWarp; }

	/// There are no resources to destroy.
	virtual ~RandomSpheroidParticleGenerator() = default;

  private:
	/// Size warp function.
	std::shared_ptr<const PiecewiseLinearSpectrum> _sizeWarp;
	/// Sphericity warp function.
	std::shared_ptr<const PiecewiseLinearSpectrum> _sphericityWarp;
};

}

