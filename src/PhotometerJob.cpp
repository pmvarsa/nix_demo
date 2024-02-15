/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/

#include "PhotometerJob.h"
#include <ICollectorSphere.h>
#include <ISpecimen.h>
#include <CollimatedBeamPhotometer.h>
#include <ISpecimen.h>

#include <cstdio>
#include <cstring>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <functional>
#include <unistd.h>
#include <cassert>

namespace nix {

PhotometerJob::PhotometerJob()
 : _out(&std::cout)
{
}

PhotometerJob::~PhotometerJob()
{
	if (_out != &std::cout) {
		delete _out;
	}
}

void PhotometerJob::setOutput(const std::string & /*fname*/)
{
}

void PhotometerJob::setIncidentAngles(
	const std::vector<SphericalCoordinates> & incident)
{
	_incident = incident;
}

const std::vector<SphericalCoordinates> & PhotometerJob::incidentAngles() const noexcept
{
	return _incident;
}

void PhotometerJob::setWavelengths(const std::vector<Scalar> & wavelengths)
{
	_lambdas = wavelengths;
}

const std::vector<Scalar> & PhotometerJob::wavelengths() const noexcept
{
	return _lambdas;
}

void PhotometerJob::setPhotometer(std::unique_ptr<CollimatedBeamPhotometer> photometer)
{
	_photometer = std::move(photometer);
}

const CollimatedBeamPhotometer & PhotometerJob::photometer() const noexcept
{
	return *(_photometer.get());
}

void PhotometerJob::setMaterial(std::unique_ptr<ISpecimen> material)
{
	_material = std::move(material);
}

const ISpecimen & PhotometerJob::material() const noexcept
{
	return *(_material.get());
}

int PhotometerJob::numPhotonsCast() const
{
	//return _photometer->numPhotonsCast() + _photonsCast;
	return 0;
}

void PhotometerJob::Run()
{
	std::cout << "Hello from C++." << std::endl;
}

} // namespace nix

