/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the SpectrophotometerCollectorSphere class.          *
 ***************************************************************************/
#pragma once

#include "lua_includes.h"

namespace nix {
namespace lua {

/// Interface helper structure for the Lua nix global namespace.
///
/// This structure contains only contains a static list of functions that are
/// available for use in the `nix` namespace in the Lua code.
struct LuaGlobal {
	/// List of methods supported in the Lua `nix` global namespace.
	/// This array contains a Lua function_name to C implementation function
	/// map.  It must be null-terminated.
	static const luaL_Reg methods[];

	/// Specify the number of cores that exist, which may be used to instantiate
	/// a number of thread.
	static unsigned int cores;
};

namespace global {
extern "C" {

/// Create a Lua photometer_job using by instantiating a PhotometerJob C++
/// object.
/// \param L The current Lua State object.
/// \return Returns 1, since the new \c photometer_job has been instantiated.
int nix_photometer_job_cmd(lua_State * L);

/// Create a Lua piecewise_linear_spectrum using by instantiating a
/// PiecewiseLinearSpectrum C++ object. There are three ways to construct a
/// piecewise_linear_spectrum in Lua.  First, with no values.  The creates
/// an empty spectrum, that is akin to a vacuum. E.g.
/// \code{.lua}
///  spectrum = piecewise_linear_spectrum()
/// \endcode
/// Second is to specify four arguments.  These are the name, the low and high
/// values of the range, and a table of values to be uniformly interpolated
/// between the low and high ranges.  Eg.
/// \code{.lua}
/// water_refraction = piecewise_linear_spectrum(
///     'water_n',
///     300, 700,
///     { 1.335, 1.334, 1.333, 1.333, 1.332, 1.332, 1.331, 1.331 }
/// )
/// \endcode
/// The third method is to specify the name, and each \f$ \lambda \f$ / value
/// pair explicitly. E.g.
/// \code{.lua}
/// ice_refraction = piecewise_linear_spectrum(
///     'ice_n',
///     {
///         { 400, 1.3194e+00 },
///         { 410, 1.3185e+00 },
///         -- ...
///         { 700, 1.3069e+00 }
///     }
/// )
/// \endcode
/// \param L The current Lua State object.
/// \return Returns 1, since the new piecewise_linear_spectrum has been
/// instantiated.
int nix_piecewise_linear_spectrum_cmd(lua_State * L);

/// Create a Lua spectrophotometer_collector_sphere object using a C++
/// SpectrophotometerCollectorSphere.  This method expects that the Lua call has
/// been passed exactly either zero or two boolean arguments. The two boolean
/// arguments correspond to the the boolean flags passed to the
/// SpectrophotometerCollectorSphere constructor. E.g.
/// \code{.lua}
/// -- Create an upper hemisphere spectrophotometer_collector_sphere for reflection.
/// sphere = spectrophotometer_collector_sphere(true, false)
///
/// -- Create a fully spherical spectrophotometer_collector_sphere for reflection
/// -- and transmission.
/// sphere = spectrophotometer_collector_sphere()
/// \endcode
/// \param L The current Lua State object.
/// \return Returns 1, since the new spectrophotometer_collector_sphere has been
///         instantiated.
int nix_spectrophotometer_collector_sphere_cmd(lua_State * L);

/// Create a Lua custom_collector_sphere object using a C++
/// CustomCollectorSphere.  This method expects that the Lua call
/// has been passed something.
/// E.g.
/// \code{.lua}
/// -- Create an custom_collector_sphere
/// 
/// sphere = custom_collector_sphere()
///
/// -- Create a fully spherical spectrophotometer_collector_sphere for reflection
/// -- and transmission.
/// sphere = spectrophotometer_collector_sphere()
/// \endcode
/// \param L The current Lua State object.
/// \return Returns 1, since the new spectrophotometer_collector_sphere has been
///         instantiated.
int nix_custom_collector_sphere_cmd(lua_State * L);

/// Create a Lua equal_solid_angles_collector_sphere object using a C++
/// EqualSolidAnglesCollectorSphere.  This method expects that the Lua call
/// has been passed exactly four arguments. E.g.
/// \code{.lua}
/// stacks = 1
/// slices = 1
/// upper = true
/// lower = false
/// sphere = equal_solid_angles_collector_sphere(stacks, slices, upper, lower)
/// \endcode
/// Stacks and slices must be an positive integer number.
/// \param L The current Lua State object.
/// \return Returns 1, since the new equal_solid_angles_collector_sphere has been
///         instantiated.
int nix_equal_solid_angles_collector_sphere_cmd(lua_State * L);

/// Create a Lua collimated_beam_photometer object using a C++
/// CollimatedBeamPhotometer.
/// \param L The current Lua State object.
/// \return Returns 1, since the new collimated_beam_photometer has been instantiated.
int nix_collimated_beam_photometer_cmd(lua_State * L);

/// Create a Lua test1material object using the C++ Test1Material.
/// \param L The current Lua State object.
/// \return Returns 1, since the new test1material has been instantiated.
int nix_test1material_cmd(lua_State * L);

/// Create a Lua diffuse_reflector object using the C++ DiffuseReflector.
/// \param L The current Lua State object.
/// \return Returns 1, since the new diffuse_reflector has been instantiated.
int nix_diffuse_reflector_cmd(lua_State * L);

/// Create a Lua random_spheroid_particle_generator object using the C++
/// RandomSpheroidParticleGenerator class.
/// \code{.lua}
///  gen = nix.random_spheroid_particle_generator(
///          spheroid_warp.prolate, spheroid_warp.oblate,
///          extinction_factor,
///          size_distribution.warping_function,
///          sphericity_distribution.warping_function)
/// \endcode
/// \param L The current Lua State object.
/// \return Returns 1, since the new random_spheroid_particle_generator
/// has been instantiated.
int nix_random_spheroid_particle_generator_cmd(lua_State * L);

/// Create a Lua vacuum_medium object using the C++ VacuumMedium class.
/// \param L The current Lua State object.
/// \return Returns 1, since the new vacuum_medium has been instantiated.
int nix_vacuum_medium_cmd(lua_State * L);

} // extern C
} // namespace global
} // namespace lua
} // namespace nix

