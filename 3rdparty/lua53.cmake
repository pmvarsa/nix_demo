# Followed example from this website:
# https://www.selectiveintellect.net/blog/2016/7/29/using-cmake-to-add-third-party-libraries-to-your-project-1

set (LUA_PREFIX lua53)
set (LUA_URL ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/lua-5.3.4.tar.gz)
set (LUA_URL_MD5 53a9c68bcc0eda58bdc2095ad5cdfc63)

if(UNIX AND NOT APPLE)
	set(BUILD linux)
elseif(UNIX AND APPLE)
	set(BUILD macosx)
endif()

ExternalProject_Add(${LUA_PREFIX}
	PREFIX ${LUA_PREFIX}
	URL ${LUA_URL}
	URL_MD5 ${LUA_URL_MD5}
	CONFIGURE_COMMAND ""
	BUILD_COMMAND make ${BUILD}
	BUILD_IN_SOURCE 1
	INSTALL_COMMAND ""
	LOG_DOWNLOAD 1
	LOG_BUILD 1
)

ExternalProject_Get_Property(${LUA_PREFIX} SOURCE_DIR)
message(STATUS "Source directory of ${LUA_PREFIX} ${SOURCE_DIR}")

set(LUA_RELEASE_DIR ${SOURCE_DIR}/src)
set(LUA_INCLUDE_DIRS ${SOURCE_DIR}/src)
set(LUA_LIBRARY_DIRS ${LUA_RELEASE_DIR})
set(LUA_LIBS lua)

include_directories(${LUA_INCLUDE_DIRS})
link_directories(${LUA_RELEASE_DIR})

