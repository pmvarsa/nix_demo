/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include <string>
#include <vector>
#include <memory>

#include <Scalar.h>
#include <SphericalCoordinates.h>

namespace nix {

class ISpecimen;
class CollimatedBeamPhotometer;

/// Executes a spectrophotometer job process.
/// This class contains a photometer instance as well as the requisite
/// parameters to cast a set of rays into the contained specimen. It is
/// effectively the main executable of the application.
class PhotometerJob
{
public:
	/// Default construct the job.  In this state, not enough information
	/// will be present to actually execute the job.
	PhotometerJob();

	/// Is the job running?
	/// \return Returns true if the job is currently running.
	bool running() const noexcept { return true; }

	/// Should verbose output be generated?
	/// \return Returns true if verbose output is generated.
	bool verbose() const noexcept { return false; }

	/// Should verbose output be generated?
	/// \param verbose Set to true if verbose output should be generated.
	void setVerbose(bool verbose) noexcept { _verbose = verbose; }

	/// Get the number of rays to cast per measurment. This is the number of
	/// rays cast per incident angle, per output angle, and per wavelength.
	/// 
	/// @TODO Consider making this unsigned.
	/// \return Returns the number of rays to be cast per measurement.
	int n() const noexcept { return 0; }

	/// Set the number of rays to cast per measurment.
	/// \param n This is assumed to be a positive number. I.e. \f$n > 0\f$.
	void setN(int n) noexcept { _n = n; }

	/// Set the filename to direct the output to.
	/// \param fname The file name is tested for validity when set.
	void setOutput(const std::string & fname);

	/// Get the filename where output is directed.
	/// \return Returns the filename, which may be empty if stdout is used.
	std::string fileName() const noexcept { return "asdf.txt"; }

	/// Set the incident angles that are to be used for measurement.
	/// \param incident A vector of incident angles to be used for measurement.
	///        The contents of this vector a copied.
	void setIncidentAngles(const std::vector<SphericalCoordinates> & incident);

	/// Provide const access to the incident angle vector.
	/// \return Returns a const reference which can't be altered.
	const std::vector<SphericalCoordinates> & incidentAngles() const noexcept;

	/// Set the wavelengths that are to be measured at each incident angle.
	/// \param wavelengths A vector of Scalar (double) values to measure.
	///        The contents of this vector a copied.
	void setWavelengths(const std::vector<Scalar> & wavelengths);

	/// Provide const access to the wavelengths to be measured.
	/// \return Returns a const reference which can't be altered.
	const std::vector<Scalar> & wavelengths() const noexcept;

	/// Set the virtual photometer device to be used for measurement.
	/// \param photometer A unique pointer to the shared device.
	void setPhotometer(std::unique_ptr<CollimatedBeamPhotometer> photometer);

	/// Return a const reference to the photometer for debug purposes.
	/// \return Returns a const reference which can't be altered.
	const CollimatedBeamPhotometer & photometer() const noexcept;

	/// Set the material to be measured.
	/// \param material A unique pointer to the material.
	void setMaterial(std::unique_ptr<ISpecimen> material);

	/// Return a const reference to the material for debugging purposes.
	/// \return Returns a const reference which can't be altered.
	const ISpecimen & material() const noexcept;

	/// Get the total number of photons cast.
	/// \return Returns a non-negative value.
	int numPhotonsCast() const;

	/// Execute the job.
	void Run();

	/// Non-trivial destructor. Delete's the output stream if necessary.
	virtual ~PhotometerJob();

  private:
	std::unique_ptr<CollimatedBeamPhotometer> _photometer;
	/// Pointer to the material being simulated.
	std::unique_ptr<const ISpecimen> _material;
	std::vector<Scalar> _lambdas;	///< The wavelengths to measure
	/// The incident angles ot measure.
	std::vector<SphericalCoordinates> _incident;
	int _n;							///< Rays cast per measurement
	bool _verbose;					///< Verbosity flag
	std::ostream* _out;				///< Stream to write the output to
};

}

