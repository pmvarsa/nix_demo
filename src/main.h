/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/

#pragma once

#include <string>
#include <vector>

/// Print the application usage.
/// \param exe The full path to the executable as found in \c argv[0].
void usage(std::string exe);

/// Parse the command line arguments.
/// \param argc The \c argc passed into \c main.
/// \param argv The \c argv passed into main.
/// \param args This vector will be populated with the relevant data to run
///        the application.  It will be empty if no arguments were run, or if
///        \a -h was passed in as an argument. It will contain one value if a
///        \c .lua file was specified to run.  It will be contain two values if
///        both a file was specified to run, and the \a -c command line
///        argument was specified with a parameter file.
/// \return Returns true if everything is OK, false if there is an issue with
///         the specified command line arguments.
static bool parseArgs(int argc, char *argv[], std::vector<std::string> & args);

/*! \mainpage
 *
 * \section sec_intro Introduction
 *
 * Welcome to the source code for the SPLITSnow model. This model is based on
 * the SPLITS model. However, the code was restructured significantly, the
 * <a href="https://www.tcl.tk/">Tcl</a> interpreter was replaced with a
 * <a href="https://www.lua.org/">Lua</a> interpreter, and a completely new
 * characterization method was employed. The Lua library used to implement the
 * interpreter is provided as an external project that is built first as a
 * depencency, so there is no need to download or install any extra packages.
 * Documentation is not provided for the Lua library, only for the bindings that
 * make use of it.
 *
 * The build system for this project is generated using
 * <a href="https://cmake.org/">CMake</a>. First, the Lua library is built, then
 * the Nix project, itself, is built. Dependencies have been created so you can
 * make use of parallel builds. For example, you can execute a command such as
 * the following to build more quickly:
 * \code{.sh}
 *  make -j8
 * \endcode
 *
 * The name of the executable and the namespaces have also been changed for
 * various reasons. For the most part, this was just done as a natural part of
 * the development process.  Nix is Latin for "snow."
 *
 * \section sec_navigation Source Code Navigation
 *
 * The code is organized into various namespaces.  The bulk of the code has been
 * placed under the \ref nix namespace. All of the Lua bindings have been placed
 * under the \ref nix::lua namespace. The \ref nix::lua namespace is further
 * subdivided by area. These extra namespace subdivisions are useful since the
 * Lua bindings are a C API, and hence code is not logically organized into
 * classes.
 *
 * The entry point to the application is, obviously, \ref main, which calls
 * \ref parseArgs to parse the command line arguements. However, the
 * principal class used to launch the Lua interpreter is
 * \ref nix::lua::LuaRunner. The actual casting of photons is implemented in the
 * \ref nix::CollimatedBeamPhotometer class, which makes use of the
 * \ref nix::ScatterEventThreadBody for multi-threading.
 *
 * Many of the classes are supporting class and mathematical libraries. These
 * include \ref nix::SpectrophotometerCollectorSphere to collect spectrometric
 * responses and \ref nix::EqualSolidAnglesCollectorSphere to collect BSDF
 * responses.  Perhaps of particular interest is the \ref nix::Optics class,
 * which implements the geometric optics used for simulation.
 *
 * The material implementation is provided in the \ref nix::Test1Material class.
 * This class is reliant upon the \ref nix::RandomSpheroidParticleGenerator
 * class to generate new \ref nix::SpheroidParticle instances. The bulk of the
 * logic is implementated in these classes.
 */

