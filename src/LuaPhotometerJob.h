/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the PhotometerJob class.                             *
 ***************************************************************************/
#pragma once

#include "lua_includes.h"

#include <PhotometerJob.h>

namespace nix {
namespace lua {

/// Lua/C++ interface helper structure.
///
/// This structure contains just a pointed to the C++ object and a static list
/// of functions that are supported by this instance in the Lua code.
///
/// The Lua bindings are a C API and will not call any constructors or
/// destrctors. As such, we must handle allocation and deallocation manually.
/// Furtherore, it is vital that the C++ objects do not get deallocated when
/// the Lua garbage colletor is run at the end of the script execution.
class LuaPhotometerJob {
	static const luaL_Reg methods[];	///< List of methods supported in Lua
  public:
	/// Create a LuaPhotometerJob object, specifying the unique_ptr that is
	/// used for memory management.
	/// \param pObj Shared pointer to the actual C++ instance.
	LuaPhotometerJob(std::unique_ptr<PhotometerJob> pObj)
	  : self(std::move(pObj)) {}

	/// Shared pointer to the object in C++.
	std::unique_ptr<nix::PhotometerJob> self;

	/// Setup the metatable for this class in the provided Lua state stack.
	/// \param L The Lua state pointer is assumed to not be null.
	static void setupMetatable(lua_State * L) noexcept;

	static const std::string luaType; ///< The name of the type in Lua.
};

namespace job {
extern "C" {

/// Garbage collector for nix.photometer_job Lua types.
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_photometer_job_gc_cmd(lua_State * L);

/// Dump some of the object state to stdout for debugging purposes.
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_photometer_job_dump(lua_State * L);

/// Set whether or not verbose output should be produces.
/// The Lua method expects exactly one boolean parameter. E.g.
/// \code{.lua}
/// my_photometer_job:set_verbose(true)
/// \endcode
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_photometer_job_set_verbose_cmd(lua_State * L);

/// Sets the number of samples rays to be cast per wavelength.  For each
/// incident angle, for each measurement angle, and for each wavelength, this
/// many rays are cast. The Lua method expects exactly one boolean parameter.
/// E.g.
/// \code{.lua}
/// my_photometer_job:set_n(10000)
/// \endcode
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_photometer_job_set_n_cmd(lua_State * L);

/// Set the output file name for the data.
/// The Lua method expects exactly one string parameter. E.g.
/// \code{.lua}
/// my_photometer_job:set_output("foo.csv")
/// \endcode
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_photometer_job_set_output_cmd(lua_State * L);

/// Set the incident angles to measure.
/// The Lua method expects an "array" (i.e. a table with numeric keys) of
/// incident angles.  Each incident angle is itself a table with two keys:
/// polar, and azimuth. E.g.
/// \code{.lua}
/// -- Create an array with only one incident angle
/// incident_angels = {
///     { polar = 0., azimuth = 0. }
/// }
/// my_photometer_job:set_incident_angles(incident_angels)
/// \endcode
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_photometer_job_set_incident_angles_cmd(lua_State * L);

/// Set the wavelength samples to be measured.
/// The Lua method expects an "array" (i.e. a table with numeric keys) of
/// wavelengths specified in nanometres. The wavelengths themselves should be
/// standard Lua numbers and will be converted to a Scalar type.
/// \code{.lua}
/// wavelengths = { 400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 500 }
/// photometer_job:set_wavelengths(wavelengths)
/// \endcode
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_photometer_job_set_wavelengths_cmd(lua_State * L);

/// Set the measurement device to be used.
/// The Lua method expects exactly one CollimatedBeamPhotometer parameter. E.g.
/// \code{.lua}
/// sphere = nix.collector_sphere(true, false)
/// photometer = nix.collimated_beam_photometer()
/// photometer:set_collector_sphere(sphere)
/// photometer_job = nix.photometer_job()
/// photometer_job:set_device(sphere)
/// \endcode
/// After calling \c set_device in Lua, the ownership of the pointer is passed
/// on to the \c photometer_job, and as such, the object is no longer directly
/// accessible from Lua.  Although this certainly seems like a limitation, in
/// practice, one should completely configure the measurement device before
/// making use of it.
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_photometer_job_set_device_cmd(lua_State * L);

/// Set the material to be measured.
/// The Lua method expects exactly one IMaterial parameter. E.g.
/// \code{.lua}
/// material = nix.test1material()
/// photometer_job = nix.photometer_job()
/// photometer_job:set_test1material(material)
/// \endcode
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_photometer_job_set_test1material_cmd(lua_State * L);
int nix_photometer_job_set_diffuse_reflector_material_cmd(lua_State * L);

/// Execute the job. No arguements should be passed to the Lua method.
/// \param L The current Lua State object.
/// \return Returns 0, since there are no objects returned to the Lua caller.
int nix_photometer_job_run_cmd(lua_State * L);

} // extern C

} // namespace job
} // namespace lua
} // namespace nix

