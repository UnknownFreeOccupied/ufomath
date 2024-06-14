find_package(Doxygen REQUIRED dot)
if(DOXYGEN_FOUND)
	set(DOXYGEN_PROJECT_NAME "UFOMath")
	# set(DOXYGEN_PROJECT_LOGO )
  # set(DOXYGEN_INPUT "mainpage.md")
  set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${PROJECT_SOURCE_DIR}/README.md")
  set(DOXYGEN_EXCLUDE_PATTERNS "README.md")
  set(DOXYGEN_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/docs")
  set(DOXYGEN_ALIASES "YES")
  # this target will only be built if specifically asked to.
  # run "make docs" to create the doxygen documentation
  doxygen_add_docs(
    docs
		${PROJECT_SOURCE_DIR}/include
    COMMENT "Generate API documentation with Doxygen."
  )
else(DOXYGEN_FOUND)
	message("Doxygen need to be installed to generate the doxygen documentation")
endif(DOXYGEN_FOUND)