/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the RandomSpheroidParticleGenerator class.           *
 ***************************************************************************/

#include "LuaRunner.h"

#include "LuaCollimatedBeamPhotometer.h"
#include "LuaDiffuseReflector.h"
#include "LuaEqualSolidAnglesCollectorSphere.h"
#include "LuaGlobal.h"
#include "LuaPiecewiseLinearSpectrum.h"
#include "LuaPhotometerJob.h"
#include "LuaRandomSpheroidParticleGenerator.h"
#include "LuaSpectrophotometerCollectorSphere.h"
#include "LuaTest1Material.h"

#include <iostream>
#include <stdexcept>

#ifdef LINUX
#	include <experimental/filesystem>
// @TODO Call the filesystem namespace fs until I swtich to C++ 17
namespace fs = std::experimental::filesystem;
#elif defined(OSX)
#	include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#endif

#include "lua_includes.h"

namespace nix {
namespace lua {

LuaRunner::LuaRunner(const std::string & fname)
{
	// Test if the file exists and is readable
	existsAndIsReadable(fname);

	_fname = fname;

	// Change the current working directory to the location of the script
	// This makes using includes a lot easier
	fs::path file_path { fname };
	auto dir = file_path.parent_path();
	if (!dir.empty()) {
		fs::current_path(dir);
	}
}

bool LuaRunner::run()
{
	using namespace std;

	NIX_LUA_DEBUG("Setting up Lua state.");
	
	lua_State * L = luaL_newstate();	// Create a state object
	luaL_openlibs(L);					// Load req'd libraries

	NIX_LUA_DEBUG("Setting up objects exposed to Lua.");

	// Load methods for exposed object types
	LuaSpectrophotometerCollectorSphere::setupMetatable(L);
	LuaEqualSolidAnglesCollectorSphere::setupMetatable(L);
	LuaCollimatedBeamPhotometer::setupMetatable(L);
	LuaPhotometerJob::setupMetatable(L);
	LuaTest1Material::setupMetatable(L);
	LuaDiffuseReflector::setupMetatable(L);
	LuaPiecewiseLinearSpectrum::setupMetatable(L);
	LuaRandomSpheroidParticleGenerator::setupMetatable(L);

	NIX_LUA_DEBUG("Setting up Lua nix global functions.");

	// Load global functions
	luaL_setfuncs(L, LuaGlobal::methods, 0);
	lua_setglobal(L, "nix");

	NIX_LUA_DEBUG("Executing Lua file: " << _fname);

	// Attempt to load the Lua script file
	auto luaErrorCode = luaL_loadfile(L, _fname.c_str());
	if (luaErrorCode != 0) {
		string errorStr { lua_tostring(L, -1) };
		switch (luaErrorCode) {
			case LUA_ERRSYNTAX:
				cerr << "Syntax error in " << _fname << ": " << errorStr << endl;
				break;
			case LUA_ERRMEM:
				cerr << "Memory allocation error loading " << _fname << ": "
					 << errorStr << endl;
				break;
			case LUA_ERRFILE:
				cerr << "Error opening " << _fname << ": " << errorStr << endl;
				break;
			default:
				cerr << "Unknown error with " << _fname << ": " << errorStr << endl;
				break;
		}
		return false;
	}

	// Push the argument onto the stack, if available
	int numArgs = 0;
	if (!_paramsFile.empty()) {
		numArgs = 1;
		lua_pushstring(L, _paramsFile.c_str());
	}

	// Execute the contents of the Lua script file
	luaErrorCode = lua_pcall(L, numArgs, 0, 0);
	if (luaErrorCode != 0) {
		string errorStr { lua_tostring(L, -1) };
		switch (luaErrorCode) {
			case LUA_ERRRUN:
				cerr << "Runtime error executing " << _fname << ": "
					 << errorStr << endl;
				break;
			case LUA_ERRMEM:
				cerr << "Memory allocation error executing " << _fname << ": "
					 << errorStr << endl;
				break;
			default:
				cerr << "Unknown error executing " << _fname << ": "
					 << errorStr << endl;
				break;
		}
		return false;
	}

	NIX_LUA_DEBUG("Closing the interpreter.");

	return true;
}

void LuaRunner::setThreads(int numThreads)
{
	int iCores = static_cast<int>(LuaGlobal::cores);
	if(numThreads < 0 and iCores + numThreads > 0) {
		LuaGlobal::cores += numThreads;
	} else if(numThreads > 0) {
		LuaGlobal::cores = numThreads;
	}
}

unsigned int LuaRunner::getThreads() const noexcept
{
	return LuaGlobal::cores;
}

void LuaRunner::setParams(const std::string & file)
{
	existsAndIsReadable(file);
	_paramsFile = file;
}

void LuaRunner::existsAndIsReadable(const std::string & file)
{
	// Test if the file exists and is readable
	if (!fs::exists(file)) {
		throw std::invalid_argument("File named '" + file + "' does not exist.");
	}

	auto perms = fs::status(file).permissions();
#ifdef LINUX
	if ((perms & fs::perms::owner_read) == fs::perms::none) {
#elif defined(OSX)
	if ((perms & fs::perms::owner_read) == 0) {
#endif
		throw std::invalid_argument(file + " cannot be read.");
	}
}

} // namespace lua
} // namespace nix

