/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the CollimatedBeamPhotometer class.                  *
 ***************************************************************************/
#pragma once

#include "lua_includes.h"

#include <CollimatedBeamPhotometer.h>

namespace nix {
namespace lua {

/// Lua/C++ interface helper structure for the CollimatedBeamPhotometer.
///
/// This structure contains just a pointed to the C++ object and a static list
/// of functions that are supported by this instance in the Lua code.
class LuaCollimatedBeamPhotometer
{
	static const luaL_Reg methods[]; 		///< List of methods supported in Lua
  public:
	/// Construct a LuaCollimatedBeamPhotometer given a unique pointer to the
	/// C++ resource.
	/// \param pObj A unique pointer to the fully constructed, underlying object.
	LuaCollimatedBeamPhotometer(
		std::unique_ptr<nix::CollimatedBeamPhotometer> pObj)
	  : self(std::move(pObj)) {}

	/// Pointer to the object in C++.
	std::unique_ptr<nix::CollimatedBeamPhotometer> self;

	/// Setup the metatable for this class in the provided Lua state stack.
	/// \param L The Lua state pointer is assumed to not be null.
	static void setupMetatable(lua_State * L) noexcept;

	static const std::string luaType;	///< Type name in Lua
};

namespace measurement {
extern "C" {

/// Set the collector sphere on the collimated_beam_photometer.
/// The C++ CollimatedBeamPhotometer will own the C++ instance of the 
/// CollectorSphere object. This has the side effect of making the
/// \c collector_sphere unusable in Lua after this call.
/// \param L The Lua state pointer is assumed to not be null.
/// \return Returns 0, since this is a setter and nothing is returned to the
///         Lua caller.
int nix_collimated_beam_photometer_set_collector_sphere(lua_State * L);

/// Set whether or not statistics should be collected for this execution.
/// @param If \c true, statistics will be collected.
/// @return Returns 0, since this is a setter and nothing is returned to the
///         Lua caller.
int nix_collimated_beam_photometer_set_collect_statistics(lua_State * L);

/// Dump some of the contents of the CollimatedBeamPhotometer instance
/// to standard output.
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_collimated_beam_photometer_dump(lua_State * L);

/// Garbage collect the structure that holds the C++ CollimatedBeamPhotometer.
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_collimated_beam_photometer_gc(lua_State * L);

} // extern C
} // namespace measurement
} // namespace lua
} // namespace nix

