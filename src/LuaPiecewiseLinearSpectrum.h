/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the Test1Material class.                             *
 ***************************************************************************/
#pragma once

#include "lua_includes.h"

#include <PiecewiseLinearSpectrum.h>

#include <memory>

namespace nix {
namespace lua {

/// Lua/C++ interface helper structure for the PiecewiseLinearSpectrum class.
///
/// This structure contains just a pointer to the C++ object and a static list
/// of functions that are supported by this instance in the Lua code.
class LuaPiecewiseLinearSpectrum {
	static const luaL_Reg methods[];		///< List of methods supported in Lua
  public:
	/// Create a LuaPiecewiseLinearSpectrum object, specifying the shared_ptr
	/// that is used for memory management.
	/// \param pObj Shared pointer to the actual C++ instance.
	LuaPiecewiseLinearSpectrum(std::shared_ptr<PiecewiseLinearSpectrum> pObj)
	  : self(pObj) {}

	/// Pointer to the object in C++.
	std::shared_ptr<nix::PiecewiseLinearSpectrum> self;

	/// Setup the metatable for this class in the provided Lua state stack.
	/// \param L The Lua state pointer is assumed to not be null.
	static void setupMetatable(lua_State * L) noexcept;

	static const std::string luaType; ///< The name of the type in Lua.
};

namespace spectrum {
extern "C" {

/// Dump out some of the contents of the PiecewiseLinearSpectrum instance
/// to standard output for debugging purposes.
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_piecewise_linear_spectrum_dump(lua_State * L);

/// Garbage collect the data that was created for Lua.
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_piecewise_linear_spectrum_gc(lua_State * L);

} // extern C
} // namespace spectrum
} // namespace lua
} // namespace nix

