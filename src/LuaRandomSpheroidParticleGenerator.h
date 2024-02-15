/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the RandomSpheroidParticleGenerator class.           *
 ***************************************************************************/
#pragma once

#include "lua_includes.h"

#include <RandomSpheroidParticleGenerator.h>

namespace nix {
namespace lua {

/// Lua/C++ interface helper structure for the RandomSpheroidParticleGenerator.
///
/// This structure contains just a pointer to the C++ object and a static list
/// of functions that are supported by this instance in the Lua code.
class LuaRandomSpheroidParticleGenerator {
	static const luaL_Reg methods[]; 	///< List of methods supported in Lua
  public:
	/// Create a LuaRandomSpheroidParticleGenerator object, specifying the
	/// shared_ptr that is used for memory management.
	/// \param pGen Shared pointer to the actuall C++ instance.
	LuaRandomSpheroidParticleGenerator(
		std::shared_ptr<RandomSpheroidParticleGenerator> pGen)
	  : self(pGen) {}

	/// Shared pointer to the object in C++.
	std::shared_ptr<nix::RandomSpheroidParticleGenerator> self;

	/// Setup the metatable for this class in the provided Lua state stack.
	/// \param L The Lua state pointer is assumed to not be null.
	static void setupMetatable(lua_State * L) noexcept;

	static const std::string luaType; ///< The name of the type in Lua.
};

namespace material {
extern "C" {

/// Dump out some of the contents of the LuaRandomSpheroidParticleGenerator
/// instance to standard output for debugging purposes.
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_random_spheroid_particle_generator_dump(lua_State * L);

/// Clean up the allocated container that holds the shared pointer to the
/// real C++ object.
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_random_spheroid_particle_generator_gc(lua_State * L);

} // extern C
} // namespace material
} // namespace lua
} // namespace nix

