/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#include "Test1Material.h"

#include <RayResult.h>

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <type_traits>

// USE_SNELL indicates that simple Snell's law should be used for refraction
// instead of the complex index index of refractions that accounts for
// absorption.
//#define USE_SNELL

namespace nix {

Test1Material::Test1Material()
 : _particles()
{
}

void Test1Material::setMediaTypes(const std::vector<MediumDef> & media)
{
	_media = media;
}

const std::vector<Test1Material::MediumDef> &
Test1Material::mediaTypes() const noexcept
{
	return _media;
}

const RayResult
Test1Material::Scatter(const Intersection & /*x*/, const SpectralSample & /*ss*/,
	const IMedium & /*ambient*/, RandomScatterRecord & /*sr*/) const
{
	return RayResult(Interaction::reflected);
}

std::string & Test1Material::name() const
{
	static std::string name("my materical");
	return name;
}

void Test1Material::setMirrorInterface(bool /*isMirror*/)
{
}

bool Test1Material::isMirrorInterface()
{
	return false;
}

void Test1Material::setLowerReflector(bool /*hasLowerReflector*/)
{
}

} // namespace nix

