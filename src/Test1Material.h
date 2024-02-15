/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include <Interval.h>
#include <ISpecimen.h>
#include <Scalar.h>

#include <complex>
#include <memory>
#include <vector>

namespace nix {

class IParticle;
class IParticleGenerator;
class IProperty;
class PiecewiseLinearSpectrum;
class Point3;
class RandomScatterRecord;
class Ray3;
class RayResult;
class Sphere;
class Vector3;

/**
 * Represents a material being invetigated for scattering.
 *
 * A material is represented as a stochastic collection of prolate spheroids
 * that are generated on demand based on characterization data parameters.
 * Particle characterization details are provided in the ParticleDef
 * inner type. This, in turn, contains a collection of CoatingDef objects.
 * The material also contains a collection of MediumDef objects which rerpresent
 * the various media in the pore space between the particles.
 *
 * Layer numbering is not strait forward.  Coatings/layers count outward from
 * the particle starting from zero. So the layer surrouding the particle is
 * layer zero and the first struck layer has the highest index. For n layers,
 * this is n-1. Since handling the interface between the first coating (the one
 * surrounding the particle) and the particle itself is no different than
 * handling the interface between layers, we conceptually consider the particle
 * to be layer -1. Similarly, handling the interface between the interstitial
 * medium and the outermost layer is mathematically the same, the current
 * medium is consider layer n.
 */
class Test1Material : virtual public ISpecimen
{
  public:
	/// Inner type used to associate a medium with its spectral components.
	class MediumDef {
	  public:
		/// The name of the medium.
		std::string name;
		/// Fractional amount of the whole pore space.
		Scalar weight;
		/// Real part of the index of refraction.
		std::shared_ptr<const PiecewiseLinearSpectrum> n;
		/// Imaginary index of refraction. This is the extinction index.
		std::shared_ptr<const PiecewiseLinearSpectrum> k;
		/// Possibly precomputed absorption coefficients. Could be unused, in
		/// which case they are computed on the fly. The absorption coefficient
		/// is computed as \f$ \alpha=\frac{4\pi k}{\lambda} \f$, where \f$k\f$
		/// is the extinction index and \f$\lambda\f$ is the wavelength of
		/// light.
		std::shared_ptr<const PiecewiseLinearSpectrum> alpha;

		/// Construct a MediumDef object.
		/// \param name Give the medium a name for debugging.
		/// \param weight What fraction of the total inter-particle space is
		///        consumed by this medium. The total for all media should sum
		///        to one.
		/// \param n The real part of the index of refraction for the medium.
		/// \param k The complex part of the index of refraction for the medium.
		MediumDef(const std::string & name, Scalar weight,
				  std::shared_ptr<const PiecewiseLinearSpectrum> & n,
				  std::shared_ptr<const PiecewiseLinearSpectrum> & k)
		  : name(name), weight(weight), n(n), k(k) {}

		/// Construct a MediumDef object.
		/// \param name Give the medium a name for debugging.
		/// \param weight What fraction of the total inter-particle space is
		///        consumed by this medium. The total for all media should sum
		///        to one.
		/// \param n The real part of the index of refraction for the medium.
		/// \param k The complex part of the index of refraction for the medium.
		/// \param alpha The absorption coefficient, which can be computed from
		///        k, has been precomputed and is provided.
		MediumDef(const std::string & name, Scalar weight,
				  std::shared_ptr<const PiecewiseLinearSpectrum> & n,
				  std::shared_ptr<const PiecewiseLinearSpectrum> & k,
				  std::shared_ptr<const PiecewiseLinearSpectrum> & alpha)
		  : name(name), weight(weight), n(n), k(k), alpha(alpha) {}

		/// Inglorious hack because vacuum is a global in Mist.
		/// @TODO Kill me please.
		/// \param weight What fraction of the total inter-particle space is
		///        consumed by this medium.
		MediumDef(Scalar weight) : name("vacuum"), weight(weight) { }
	};

	/// Inner type to used to define a particle type.
	class ParticleDef {
	  public:
	  	std::string name;					///< The name of the particle type.
		/// @copydoc MediumDef::n
		std::shared_ptr<const PiecewiseLinearSpectrum> n;
		/// @copydoc MediumDef::k
		std::shared_ptr<const PiecewiseLinearSpectrum> k;
		/// @copydoc MediumDef::alpha
		std::shared_ptr<const PiecewiseLinearSpectrum> alpha;
		Scalar roundness_mean;				///< Mean particle roundness.
		/// @TODO Bad name, it's standard deviation
		Scalar roundness_var;				///< Particle roundness deviation.
		Interval roundness_range;			///< Roundess range.
		Scalar concentration;				///< Fraction of total particles.
		Scalar meanDistance;				///< Distance between particles.
		/// Particle generator to use.
		std::shared_ptr<IParticleGenerator> generator;
	};

	/// Default constructor. After instantiation with this constructor, the
	/// object will \b not be ready for use. Properties must be set manually.
	Test1Material();

	/// Peform the scattering computation. This is the top-level scattering
	/// method that iteratively propagates light through the media and the
	/// particles.  It makes use of the ParticleScatter() method to compute
	/// the scatting though the grains.
	///
	/// @param x The Intersection object contains the Ray3, distance along the
	///          ray and the intersection Point3 on the sample.
	/// @param ss Assumed to have exactly one wavelength. If 0, `true` is
	///           returned; if > 0, `false` is returned.
	/// @param ambient The medium surrounding the sample.
	/// @param[out] sr The resulting scatter record.
	///
	/// @return Returns a RayResult instance that provides detailed information
	///         about what happened to the ray during scattering.
	const RayResult Scatter(const Intersection& x, const SpectralSample& ss,
		const IMedium& ambient, RandomScatterRecord & sr) const override;

	/// Default virtual destructor. No resources to free.
	virtual ~Test1Material() = default;

	/// Set the depth (thickness) of the sample in metres.
	/// \param depth The depth is assumed to be a positive value.
	void setDepth(Scalar /*depth*/) noexcept { }

	/// Get the depth (thickness) of the sample in metres.
	/// \return depth The depth should be a positive value.
	Scalar getDepth() const noexcept { return 0.0; }

	/// Set the types of media that exist between the particles, and their
	/// respective fractional quantities. An std::runtime_error is thrown
	/// if the quantities do not add up to something close to 1.0.
	/// \param media There should be at least one media type defined.
	void setMediaTypes(const std::vector<MediumDef> & media);

	/// Provide access to the media types for debugging output, etc..
	/// \return Returns a list of media types and their fractional quantities.
	const std::vector<MediumDef> & mediaTypes() const noexcept;

	/// Set the particle types that exist between the particles, and their
	/// respective fractional quantities.
	/// \param particles There should be at least one particle type defined.
	void setParticles(const std::vector<ParticleDef> & particles)
		{ _particles = particles; }

	/// Provide access to the particle types for debugging output, etc..
	/// \return Returns a vector of ParticleDef objects.
	const std::vector<ParticleDef> & particles() const noexcept
		{ return _particles; }

	/// Return the name of the string.
	/// @return Simply returns "snow" for the time being.
	std::string & name() const override;

	/// If set, the boundary of the sample is subjected to mirror-like Fresenel
	/// effects.  I.e. at the interface between the ambient medium and the
	/// medium in which the particles are immersed, a Bernoulli trial is
	/// performed to see which media is going to be present.  Then the Fresnel
	/// equations are used to determine if there is a reflection or a
	/// refraction.  If a reflection occurrs, then the interface surface is
	/// considered to be a plane with mirror-like reflection. This creates
	/// spikes in BRDF output, however is correct for some situations, like
	/// when the saturation is 100%.
	///
	/// The default value for this is to be set to `true`.
	/// @param isMirror Set this to true to enable mirror-like interace
	///        reflections.
	void setMirrorInterface(bool isMirror = true);

	/// Returns the state of the Fresenel ambient/material boundary interface.
	/// @return Returns `true` if set, `false` otherwise.
	bool isMirrorInterface();
  private:
	std::vector<MediumDef> _media;
	std::vector<ParticleDef> _particles;
  public:

	/// Set a flag that indicates whether or not the material has a perfect
	/// reflector beneath its surface.
	/// \param hasLowerReflector If true, the material has a perfect reflector
	///        beneath its surface. If false, it has a perfect absorber, or
	///        perhaps another subsurface material.
	void setLowerReflector(bool hasLowerReflector = true);
};

}

