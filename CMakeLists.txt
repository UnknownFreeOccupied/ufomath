option(UFO_MATH_DOCS     "Generate documentation" OFF)
option(UFO_MATH_TESTING  "Unit testing"           OFF)
option(UFO_MATH_COVERAGE "Test Coverage"          OFF)

add_library(Math INTERFACE)
add_library(UFO::Math ALIAS Math)

target_link_libraries(Math 
	INTERFACE 
		UFO::Utility
)

include(GNUInstallDirs)

target_include_directories(Math 
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

if(UFO_TESTING OR UFO_MATH_TESTING)
  add_subdirectory(tests)
endif()

if(UFO_DOCS OR UFO_MATH_DOCS)
	add_subdirectory(docs)
endif()

install(TARGETS Math EXPORT Math-targets
	COMPONENT Math
	LIBRARY  DESTINATION lib
	ARCHIVE  DESTINATION lib
	RUNTIME  DESTINATION bin
  INCLUDES DESTINATION include
)

install(EXPORT Math-targets
  FILE "Math-targets.cmake"
  NAMESPACE UFO::
  DESTINATION lib/cmake/${PROJECT_NAME}
	COMPONENT Math
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/Math-config-version.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/Math-config.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/Math-config.cmake"
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/Math-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/Math-config-version.cmake"
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  COMPONENT Math
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
	COMPONENT Math
	DESTINATION ${CMAKE_INSTALL_PREFIX}
)