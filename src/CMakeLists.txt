set (nix_demo_SOURCES
	Array2.h
	CollectorSphere.cpp
	CollectorSphere.h
	CollimatedBeamPhotometer.cpp
	CollimatedBeamPhotometer.h
	DiffuseReflector.cpp
	DiffuseReflector.h
	EqualSolidAnglesCollectorSphere.cpp
	EqualSolidAnglesCollectorSphere.h
	ICollectorSphere.h
	IMedium.h
	Interval.cpp
	Interval.h
	IParticle.h
	IParticleGenerator.h
	ISpecimen.h
	LuaCollimatedBeamPhotometer.cpp
	LuaCollimatedBeamPhotometer.h
	LuaDiffuseReflector.cpp
	LuaDiffuseReflector.h
	LuaEqualSolidAnglesCollectorSphere.cpp
	LuaEqualSolidAnglesCollectorSphere.h
	LuaGlobal.cpp
	LuaGlobal.h
	LuaPhotometerJob.cpp
	LuaPhotometerJob.h
	LuaPiecewiseLinearSpectrum.cpp
	LuaPiecewiseLinearSpectrum.h
	LuaRandomSpheroidParticleGenerator.cpp
	LuaRandomSpheroidParticleGenerator.h
	LuaRunner.h
	LuaRunner.cpp
	LuaSpectrophotometerCollectorSphere.cpp
	LuaSpectrophotometerCollectorSphere.h
	LuaTest1Material.cpp
	LuaTest1Material.h
	LuaVacuumMedium.cpp
	LuaVacuumMedium.h
	lua_includes.h
	main.cpp
	main.h
	PiecewiseLinearSpectrum.cpp
	PiecewiseLinearSpectrum.h
	PhotometerJob.cpp
	PhotometerJob.h
	RandomSpheroidParticleGenerator.cpp
	RandomSpheroidParticleGenerator.h
	RayResult.cpp
	RayResult.h
	Scalar.h
	ScatteringData.cpp
	ScatteringData.h
	SpectralSample.cpp
	SpectralSample.h
	SpectrophotometerCollectorSphere.cpp
	SpectrophotometerCollectorSphere.h
	SphericalCoordinates.cpp
	SphericalCoordinates.h
	Test1Material.cpp
	Test1Material.h
	VacuumMedium.h
	Vector3.cpp
	Vector3.h
)

# Build the nix executable
add_executable (nix_demo ${nix_demo_SOURCES})
add_dependencies (nix_demo ${LUA_PREFIX})

if(UNIX AND NOT APPLE)
target_link_libraries (nix_demo stdc++fs pthread lua dl)
elseif(UNIX AND APPLE)
target_link_libraries (nix_demo boost_system boost_filesystem pthread lua dl)
endif()

# Installs nix in /usr/local/bin
INSTALL (
	TARGETS
		nix_demo
	DESTINATION
		bin
	PERMISSIONS
		OWNER_READ
		OWNER_WRITE
		OWNER_EXECUTE
		GROUP_READ
		GROUP_EXECUTE
		WORLD_READ
		WORLD_EXECUTE
)

