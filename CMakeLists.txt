cmake_minimum_required(VERSION 3.5...3.16)

project(ufomath
	VERSION 2.0.0
	DESCRIPTION "The UFO math library"
	LANGUAGES CXX
)

option(UFO_TESTING  "Unit testing build" OFF)
option(UFO_COVERAGE "Test coverage" OFF)
option(UFO_DOCS     "Documentation build" OFF)

add_subdirectory(1stparty)

add_library(Math INTERFACE)
add_library(UFO::Math ALIAS Math)

set_target_properties(Math PROPERTIES
	INTERFACE_VERSION ${PROJECT_VERSION}
	INTERFACE_SOVERSION ${PROJECT_VERSION_MAJOR}
	INTERFACE_CXX_STANDARD 17
	INTERFACE_CXX_EXTENSIONS OFF
)

target_link_libraries(Math INTERFACE UFO::Utility)

target_include_directories(Math INTERFACE
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

target_compile_features(Math INTERFACE cxx_std_17)

include(GNUInstallDirs)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

if(UFO_TESTING)
  add_subdirectory(tests)
endif()

if(UFO_DOCS)
	add_subdirectory(docs)
endif()

install(TARGETS Math
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