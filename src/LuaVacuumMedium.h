/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the VacuumMedium class.                              *
 ***************************************************************************/
#pragma once

#include "lua_includes.h"

#include <VacuumMedium.h>

namespace nix {
namespace lua {

/// Lua/C++ interface helper structure for the VacuumMedium class.
///
/// This structure contains just a pointer to the C++ object and a static list
/// of functions that are supported by this instance in the Lua code.
class LuaVacuumMedium {
	static const luaL_Reg methods[];		///< List of methods supported in Lua
  public:
	/// Create a LuaVacuumMedium object, specifying the shared_ptr
	/// that is used for memory management.
	/// \param pObj Shared pointer to the actual C++ instance.
	LuaVacuumMedium(std::shared_ptr<VacuumMedium> pObj)
	  : self(pObj) {}

	/// Pointer to the object in C++.
	std::shared_ptr<nix::VacuumMedium> self;

	/// Setup the metatable for this class in the provided Lua state stack.
	/// \param L The Lua state pointer is assumed to not be null.
	static void setupMetatable(lua_State * L) noexcept;

	static const std::string luaType; ///< The name of the type in Lua.
};

namespace media {
extern "C" {

/// Dump out some of the contents of the VacuumMedium instance to standard
/// output for debugging purposes.
/// \param L The current Lua State object. (Not used.)
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_vacuum_medium_dump(lua_State * L);

/// Garbage collect the data that was created for Lua.
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_vacuum_medium_gc(lua_State * L);

} // extern C
} // namespace media
} // namespace lua
} // namespace nix

