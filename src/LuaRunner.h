/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the RandomSpheroidParticleGenerator class.           *
 ***************************************************************************/
#pragma once

#include <string>

namespace nix {
namespace lua {

/**
 * This class exectues a Lua script.
 *
 * Lua has been chosen because it is easy to embed, has tracing garbage
 * collection, has a simple syntax, and because I already have had an
 * introduction to it from other projects.
 */
class LuaRunner
{
  public:

	/// Create an instance, specifying the file name to execute.
	/// This method does not actually execute the Lua script. It only prepares
	/// the script to be run.
	/// \param fname The file name to execute.
	/// \throws Throws std::invalid_argument if the fname does not exist or is
	///         not readable.
	LuaRunner(const std::string & fname);

	/// Set a file name to be used for loading model parameters. The file
	/// should contain a set of key/value pairs.
	/// \param file The file name to be used.  Nothing is assumed about the
	///        file.  This method will test for existance and readability.
	/// \throws Throws a \c std::invalid_argument error if the parameter file
	///         does not exist or is not readable.
	void setParams(const std::string & file);

	/// Set the number of threads to use.  If this is positive, that many
	/// threads will be set.  If it is negative, that many thread will be
	/// subtracted from the total number of cores available.
	/// \param numThreads If positive, the total number of threads to be made
	///        available. If negative, then subtract this value from the
	///        number of available cores. Any error case are quietly discarded.
	void setThreads(int numThreads);

	/// Return the number of threads that are available for process execution.
	/// Note that the return type of this is different than the parameter
	/// argument for setThreads(int).
	/// \return Returns a number \f$ \ge 1 \f$.
	unsigned int getThreads() const noexcept;

	/// Execute the Lua script.
	/// \return Returns true if the script executed without error.
	bool run();

  private:

	/// Test if a file exists and is readable.
	/// \param file The name of the file to test.
	/// \throws Throws a \c std::invalid_argument error if the parameter file
	///         does not exist or is not readable.
	static void existsAndIsReadable(const std::string & file);

	std::string _fname;			///< Name of Lua file being processed.
	std::string _paramsFile;	///< Name of a file containing key/value pairs.
};

} // namespace lua
} // namespace nix

