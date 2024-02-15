/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the Test1Material class.                             *
 ***************************************************************************/
#pragma once

#include "lua_includes.h"

#include <Test1Material.h>

namespace nix {
namespace lua {

/// Lua/C++ interface helper structure for the Test1Material.
///
/// This structure contains just a pointer to the C++ object and a static list
/// of functions that are supported by this instance in the Lua code.
class LuaTest1Material {
	static const luaL_Reg methods[]; 	///< List of methods supported in Lua
  public:
  	/// Create a LuaTest1Material object given a unique pointer to the underlying
	/// Test1Material object.
	/// \param pObj The unique pointer to the underlying C++ object.
	LuaTest1Material(std::unique_ptr<Test1Material> pObj)
	  : self(std::move(pObj)) { }

	std::unique_ptr<nix::Test1Material> self; ///< Pointer to the object in C++.

	/// Setup the metatable for this class in the provided Lua state stack.
	/// \param L The Lua state pointer is assumed to not be null.
	static void setupMetatable(lua_State * L) noexcept;

	static const std::string luaType;	///< The type name in Lua
};

namespace material {
extern "C" {

/// Dump out some of the contents of the Test1Material instance
/// to standard output for debugging purposes.
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_test1material_dump(lua_State * L);

/// Set the depth (thickness) of the sample.  Rays travelling beyond this
/// depth are considered to be transmitted. This method expects one Lua number
/// type as an arguement.  This will be converted to a Scalar type for C++.
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_test1material_set_depth(lua_State * L);

/// Set the media types and their fractional occurrence that exist between the
/// particles. Exactly one array-style table should be provided as a parameter
/// to this method.  Each element in the array is itself a table that contains
/// two keys, namely 'material' and 'weight'. E.g.
/// \code{.lua}
/// media = {}
/// table.insert(media, {
///     weight = 0.75,
///     material = 'vacuum'
/// })
/// table.insert(media, {
///     weight = 0.25,
///     material = 'water'
/// })
/// material = nix.test1material()
/// material:set_media(media)
/// \endcode
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_test1material_set_media(lua_State * L);

/// If set, the boundary of the sample is subjected to mirror-like Fresenel
/// effects.  I.e. at the interface between the ambient medium and the
/// medium in which the particles are immersed, a Bernoulli trial is
/// performed to see which media is going to be present.  Then the Fresnel
/// equations are used to determine if there is a reflection or a
/// refraction.  If a reflection occurrs, then the interface surface is
/// considered to be a plane with mirror-like reflection. This creates spikes
/// in BRDF output, however is correct for some situations, like when the
/// saturation is 100%.
///
/// The default is `true`.
///
/// \code{.lua}
/// material = nix.test1material()
/// material:set_mirror(false)
/// \endcode
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_test1material_set_mirror(lua_State * L);

/// Set the list of particles for the material. An array of particle definitions
/// is passed as the only parameter in Lua.  The particles have a complex
/// definition, best described by an example:
/// \code{.lua}
/// -- Import some warping functions
/// local shape = require 'warp.vepraskas_s'
/// local size = require 'warp.uniform'
///
/// -- Import the ice material
/// local ice = require 'materials.ice'
///
/// -- Use the warping functions to creat a particle generator
/// particle_gen = nix.random_spheroid_particle_generator(
///     size.extinction_factor * shape.extinction_factor,
///     size.warping_function,
///     shape.warping_function)
///
/// -- Define just one kind of particle
/// particles = {}
/// particle_fraction = 1.
/// table.insert(particles,
///     concentration = concentration * particle_fraction,
///     name = 'ice',
///     n = ice.refractive_index,
///     k = ice.extinction,
///     alpha = nil,
///     roundness_mean = 0.482,
///     roundness_stdev = 0.072,
///     roundness_range = { 0.2, 0.7 },
///     generator = particle_gen,
///     cloudiness = 0,
///     coatings = {}
/// }
///
/// -- Define the material, and set the particles
/// material = nix.test1material()
/// material:set_particles(particles)
/// \endcode
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_test1material_set_particles(lua_State * L);

/// Set the lower reflector flag to true. By default, the lower boundary is a
/// perfect black absorber. With this value set, the lower boundary becomes a
/// perfect reflector instead. E.g.
/// \code{.lua}
/// -- Create the material
/// material = nix.test1material()
/// material:set_lower_reflector()
/// \endcode
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_test1material_set_lower_reflector(lua_State * L);

/// Garbage collect the struct that contains the Test1Material object reference.
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_test1material_gc(lua_State * L);

} // extern C
} // namespace material
} // namespace lua
} // namespace nix

