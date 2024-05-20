cmake_minimum_required(VERSION 3.5...3.16)

project(ufomath
	VERSION 2.0.0
	DESCRIPTION "The UFO math library"
	LANGUAGES CXX
)

add_library(ufomath INTERFACE)
add_library(UFO::Math ALIAS ufomath)

set_target_properties(ufomath PROPERTIES
	INTERFACE_VERSION ${PROJECT_VERSION}
	INTERFACE_SOVERSION ${PROJECT_VERSION_MAJOR}
	INTERFACE_CXX_STANDARD 17
	INTERFACE_CXX_EXTENSIONS OFF
)

target_include_directories(ufomath INTERFACE
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

target_compile_features(ufomath INTERFACE cxx_std_17)

include(GNUInstallDirs)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Only enable tests when we're the root project
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  add_subdirectory(tests)
endif()

install(TARGETS ufomath
	EXPORT ufomathTargets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(EXPORT ufomathTargets
	FILE "ufomathTargets.cmake"
	NAMESPACE UFO::
	DESTINATION lib/cmake/${PROJECT_NAME}
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
	"${PROJECT_SOURCE_DIR}/cmake/ufomathConfig.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/ufomathConfig.cmake"
	INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/ufomathConfigVersion.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
)

INSTALL(
	FILES
	"${CMAKE_CURRENT_BINARY_DIR}/ufomathConfig.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/ufomathConfigVersion.cmake"
	DESTINATION lib/cmake/${PROJECT_NAME}
)

install(
	DIRECTORY ${PROJECT_SOURCE_DIR}/include/
	DESTINATION include
)