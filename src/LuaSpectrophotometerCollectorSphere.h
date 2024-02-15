/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the SpectrophotometerCollectorSphere class.          *
 ***************************************************************************/
#pragma once

#include "lua_includes.h"

#include <SpectrophotometerCollectorSphere.h>

namespace nix {
namespace lua {

/// Lua/C++ interface helper structure for the SpectrophotometerCollectorSphere.
///
/// This structure contains just a pointer to the C++ object and a static list
/// of functions that are supported by this instance in the Lua code.
///
/// The Lua bindings are a C API and will not call any constructors or
/// destrctors. As such, we must handle allocation and deallocation manually.
/// Furtherore, it is vital that the C++ objects do not get deallocated when
/// the Lua garbage colletor is run at the end of the script execution.
class LuaSpectrophotometerCollectorSphere {
	static const luaL_Reg methods[]; 	///< List of methods supported in Lua
  public:
	/// Construct the container with the unique pointer already allocated.
	/// \param pObj A unique pointer to an fully constructed C++
	///        SpectrophotometerCollectorSphere object.
	LuaSpectrophotometerCollectorSphere(
		std::unique_ptr<SpectrophotometerCollectorSphere> pObj)
	  : self(std::move(pObj)) { }

	/// Pointer to the object in C++.
	std::unique_ptr<nix::SpectrophotometerCollectorSphere> self;

	/// Setup the metatable for this class in the provided Lua state stack.
	/// \param L The Lua state pointer is assumed to not be null.
	static void setupMetatable(lua_State * L) noexcept;

	static const std::string luaType; ///< The name of the type in Lua.
};

namespace measurement {
extern "C" {

/// Garbage collector for nix.spectrophotometer_collector_sphere Lua types.
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_spectrophotometer_collector_sphere_gc_cmd(lua_State * L);

/// Dump out all the contents of the SpectrophotometerCollectorSphere instance
/// to standard output.
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_spectrophotometer_collector_sphere_dump(lua_State * L);

} // extern C
} // namespace measurement
} // namespace lua
} // namespace nix

