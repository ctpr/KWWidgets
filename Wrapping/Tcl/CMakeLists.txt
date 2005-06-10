# Make sure we have Tcl

IF (NOT TCL_LIBRARY)
  MESSAGE("VTK_WRAP_TCL is ON, but the Tcl library was not found.  Please set TCL_LIBRARY." "Error")
ENDIF (NOT TCL_LIBRARY)

# Configure the Tcl package index files for the build tree.
# You can then point TCLLIBPATH to the Wrapping/Tcl dir in the right
# build directory (so that the right shared lib is loaded)

SET(KWWIDGETS_TCL_LIBNAME_PREFIX "${CMAKE_SHARED_LIBRARY_PREFIX}")
SET(KWWIDGETS_TCL_CONFIGURATION_TYPES ${CMAKE_CONFIGURATION_TYPES})

IF(KWWIDGETS_TCL_CONFIGURATION_TYPES)
  FOREACH(config ${KWWIDGETS_TCL_CONFIGURATION_TYPES})
    SET(KWWIDGETS_TCL_LIBRARY_DIR "${LIBRARY_OUTPUT_PATH}/${config}")
    CONFIGURE_FILE(${KWWidgets_SOURCE_DIR}/Wrapping/Tcl/pkgIndex.tcl.in
                   ${KWWidgets_BINARY_DIR}/Wrapping/Tcl/${config}/pkgIndex.tcl
                   @ONLY IMMEDIATE)
  ENDFOREACH(config)
ELSE(KWWIDGETS_TCL_CONFIGURATION_TYPES)
  SET(KWWIDGETS_TCL_LIBRARY_DIR "${LIBRARY_OUTPUT_PATH}")
  CONFIGURE_FILE(${KWWidgets_SOURCE_DIR}/Wrapping/Tcl/pkgIndex.tcl.in
                 ${KWWidgets_BINARY_DIR}/Wrapping/Tcl/pkgIndex.tcl
                 @ONLY IMMEDIATE)
ENDIF(KWWIDGETS_TCL_CONFIGURATION_TYPES)

# Configure the Tcl package index file for the install tree.
# You can then point TCLLIBPATH to the lib/KWWidgets/tcl dir in the right
# installation directory

IF(UNIX)
  # KWWIDGETS_TCL_LIBRARY_DIR is used to find the library in the bin
  # directory relative to the pkgIndex file located in the lib directory
  SET(KWWIDGETS_TCL_LIBRARY_DIR "[file dirname [file dirname [info script]]]")
ELSE(UNIX)
  SET(KWWIDGETS_TCL_LIBRARY_DIR
      "[file join [file dirname [file dirname [file dirname [file dirname [info script]]]]] bin]")
ENDIF(UNIX)

# We configure a new pkgIndex file that uses KWWIDGETS_TCL_LIBRARY_DIR
# It has to be in Install/Hide so that Tcl does not find it automatically

CONFIGURE_FILE(${KWWidgets_SOURCE_DIR}/Wrapping/Tcl/pkgIndex.tcl.in
               ${KWWidgets_BINARY_DIR}/Wrapping/Tcl/Install/Hide/pkgIndex.tcl
               @ONLY IMMEDIATE)
INSTALL_FILES(${KW_INSTALL_LIB_DIR}/tcl FILES
              ${KWWidgets_BINARY_DIR}/Wrapping/Tcl/Install/Hide/pkgIndex.tcl)