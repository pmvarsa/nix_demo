/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include <iostream>
#include <memory>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#ifdef DEBUG
#	define NIX_LUA_DEBUG(x) do { std::cerr << x << std::endl; } while (false)
#	define NIX_LUA_DEBUG_CALL do { std::cerr << __FUNCTION__ << std::endl; } while (false)
#else
#	define NIX_LUA_DEBUG(x) do { } while (false)
#	define NIX_LUA_DEBUG_CALL do { } while (false)
#endif

namespace nix {
namespace lua {

/// Helper function to extract the Lua container from the Lua stack.  The
/// pointer returned from this function is only good for getting at the
/// smart pointer that is wrapped in the container, or for deletion by the
/// Lua garbage collector.
///
/// \tparam C The container type that is created to manage the C++ type for Lua.
/// \param L The current Lua state instance.
/// \param i The location in the Lua stack of the object.
/// \param luaTypeStr The type name used in Lua for the C++ object.
/// \return Returns a pointer to the container.
template <typename C>
C * getLuaContainer(lua_State * L, int i, const std::string & luaTypeStr)
{
	C ** ppLuaContainer = static_cast<C **>(luaL_checkudata(L, i, luaTypeStr.c_str()));
	std::string error = luaTypeStr + " expected";
	luaL_argcheck(L, ppLuaContainer != nullptr, i, error.c_str());
	return *ppLuaContainer;
}

/// Helper function to extract the Lua container from the Lua stack. It is
/// assumed that the container is the first (positive) argument on the Lua
/// state stack. The pointer returned from this function is only good for
/// getting at the smart pointer that is wrapped in the container, or
/// for deletion by the Lua garbage collector.
///
/// \tparam C The container type that is created to manage the C++ type for Lua.
/// \param L The current Lua state instance.
/// \param luaTypeStr The type name used in Lua for the C++ object.
/// \return Returns a pointer to the container.
template <typename C>
C * getLuaContainer(lua_State * L, const std::string & luaTypeStr)
{
	return getLuaContainer<C>(L, 1, luaTypeStr);
}

/// Helper function to get the \e self shared_ptr from within the container
/// that is used to manage it.
/// \tparam T The type contained in the shared_ptr that one wants to use.
/// \tparam C The container type that is created to manage the C++ type for Lua.
/// \param L The current Lua state instance.
/// \param i The index in the Lua stack where the object is located.
/// \param luaTypeStr The type name used in Lua for the C++ object.
/// \return Returns a pointer to the container.
template <typename C, typename T>
std::shared_ptr<T> getSelf(lua_State * L, int i, const std::string & luaTypeStr)
{
	auto pLuaContainter = getLuaContainer<C>(L, i, luaTypeStr);
	return pLuaContainter->self;
}

/// Helper function to get the \e self shared_ptr from within the container
/// that is used to manage it. It is assumed that the desired object is at
/// position 1 in the Lua state stack.
/// \tparam T The type contained in the shared_ptr that one wants to use.
/// \tparam C The container type that is created to manage the C++ type for Lua.
/// \param L The current Lua state instance.
/// \param luaTypeStr The type name used in Lua for the C++ object.
/// \return Returns a pointer to the container.
template <typename T, typename C>
std::shared_ptr<T> getSelf(lua_State * L, const std::string & luaTypeStr)
{
	auto pLuaContainter = getLuaContainer<C>(L, luaTypeStr);
	return pLuaContainter->self;
}

/// Create a Lua user data object that encapsulates a shared_ptr. This helper
/// will create the Lua user data, which is just a pointer, allocate the object
/// pointed to by that pointer, and create the shard_ptr that is held by that
/// object.
/// \tparam T The type contained in the shared_ptr that one wants to use.
/// \tparam C The container type that is created to manage the C++ type for Lua.
/// \tparam ArgTypes Types of arguments passed to the call of
///         \c std::make_shared().
/// \param L The current Lua state instance.
/// \param args Arguments passed directly on to \c std::make_shared().
template<typename C, typename T, typename... ArgTypes>
void createSharedUserData(lua_State * L, const ArgTypes... args)
{
	// Create the shared pointer
	auto spObj = std::make_shared<T>(args...);

	// Create the Lua userdata, which is just a pointer to the struct
	// that holds the shared pointer, which we will need to GC later.
	*static_cast<C **>(lua_newuserdata(L, sizeof(C))) = new C(spObj);
}

/// Create a Lua user data object that encapsulates a \c unique_ptr. This helper
/// will create the Lua user data, which is just a pointer, allocate the object
/// pointed to by that pointer, and create the shard_ptr that is held by that
/// object.
/// \tparam T The type contained in the \c unique_ptr that one wants to use.
/// \tparam C The container type that is created to manage the C++ type for Lua.
/// \tparam ArgTypes Types of arguments passed to the call of
///         \c std::make_unique().
/// \param L The current Lua state instance.
/// \param args Arguments passed directly on to \c std::make_unique().
template<typename C, typename T, typename... ArgTypes>
void createUniqueUserData(lua_State * L, const ArgTypes... args)
{
	// No arguments passed - default construct
	auto upObj = std::make_unique<T>(args...);

	// Create the Lua userdata, which is just a pointer to the struct
	// that holds the unique pointer, which we will need to GC later.
	*static_cast<C **>(lua_newuserdata(L, sizeof(C))) = new C(std::move(upObj));
}

} // namespace lua
} // namespace nix

