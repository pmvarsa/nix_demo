/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/

#include "main.h"

#include <iostream>
#include <regex>
#include <stdexcept>
#include <vector>

#ifdef LINUX
/// @TODO This is C++14 code, filesystem is still "experimental".
#	include <experimental/filesystem>
#elif defined(OSX)
#	include <boost/filesystem/convenience.hpp>
#endif

#include "LuaRunner.h"

using namespace std;

void usage(string exe)
{
#ifdef LINUX
	namespace fs = experimental::filesystem;
	auto filePath = fs::path(exe);
	auto exeName = filePath.filename().string();
#elif defined(OSX)
	std::string exeName = boost::filesystem::basename(exe);
#endif
	cout << endl
		 << "  Usage:" << endl
		 << "    " << exeName << " <filename.lua>" << endl
		 << "    " << exeName << " <filename.lua> [options]" << endl
		 << endl
		 << "  Options:" << endl
		 << "    -c <param_file>  The parameter file to be provided to the Lua script." << endl
		 << "    -h               Display this help." << endl
		 << "    -t <integer>     Specify the number of threads to use." << endl
		 << endl;
}

bool parseArgs(int argc, char *argv[], vector<std::string> & args)
{
	// Look for help
	regex r(R"(^-+[hH].*)");
	for (int i=1; i<argc; ++i) {
		if (regex_match(string(argv[i]), r)) {
			args.clear(); // paranoia
			return true;
		}
	}

	// Regex to match a file ending in .lua
	regex lua_extension(R"(.*\.lua$)");
	if (argc < 2) {
		return false;
	} else if(argc % 2 == 0) {
		// Assume file to execute is the first arguement
		if (!regex_match(argv[1], lua_extension)) {
			return false;
		}
		args[0] = argv[1];

		// loop over rest of args
		string paramFile, numThreads;
		for (int x=2; x<argc; x+=2) {
			if (argv[x] == string{"-c"}) {
				paramFile = argv[x+1];
			} else if(argv[x] == string{"-t"}) {
				numThreads = argv[x+1];
			}
		}
		args[1] = paramFile;
		args[2] = numThreads;
		return true;
	}
	return false;
}

int main(int argc, char *argv[])
{
	vector<string> params(3);
	bool ok = parseArgs(argc, argv, params);
	if (!ok) {
		usage(argv[0]);
		return !ok;
	}
	try {
		string fname = params[0];
		nix::lua::LuaRunner runner(fname);
		if (not params[1].empty()) {
			runner.setParams(params[1]);
		}
		int threads { -1 };
		if (not params[2].empty()) {
			threads = stoi(params[2]);
			runner.setThreads(threads);
		}
		cout << "There are " << runner.getThreads()
			 << " threads are available for execution." << endl;
		if (!runner.run()) {
			cerr << "Abnormal program termination." << endl;
		}
	} catch(std::invalid_argument & e) {
		cerr << "Argument error: " << e.what() << endl;
		return 1;
	}
	return 0;
}

