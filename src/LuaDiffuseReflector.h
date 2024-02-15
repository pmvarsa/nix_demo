/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the DiffuseReflector class.                          *
 ***************************************************************************/
#pragma once

#include "lua_includes.h"
#include "DiffuseReflector.h"

namespace nix {
namespace lua {

/// Lua/C++ interface helper structure for the DiffuseReflector.
///
/// This structure contains just a pointer to the C++ object and a static list
/// of functions that are supported by this instance in the Lua code.
class LuaDiffuseReflector {
	static const luaL_Reg methods[]; 	///< List of methods supported in Lua
  public:
  	/// Create a LuaDiffuseReflector object given a unique pointer to the
	/// underlying DiffuseReflector object.
	/// \param pObj The unique pointer to the underlying C++ object.
	LuaDiffuseReflector(std::unique_ptr<DiffuseReflector> pObj)
	  : self(std::move(pObj)) { }

	std::unique_ptr<nix::DiffuseReflector> self; ///< Pointer to the object in C++.

	/// Setup the metatable for this class in the provided Lua state stack.
	/// \param L The Lua state pointer is assumed to not be null.
	static void setupMetatable(lua_State * L) noexcept;

	static const std::string luaType;	///< The type name in Lua
};

namespace material {
extern "C" {

/// Dump out some of the contents of the DiffuseReflector instance
/// to standard output for debugging purposes.
/// \param L The current Lua State object (unused).
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_diffuse_reflector_dump(lua_State * L);

/// Garbage collect the struct that contains the DiffuseReflector object
/// reference.
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_diffuse_reflector_gc(lua_State * L);

} // extern C
} // namespace material
} // namespace lua
} // namespace nix

