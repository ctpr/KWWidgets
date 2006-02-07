MACRO(KWWidgets_ADD_OUT_OF_SOURCE_TEST 
    test_name 
    project_name 
    src_dir bin_dir 
    exe_name exe_options)

  IF(VTK_WRAP_TCL)

    IF(CMAKE_CONFIGURATION_TYPES)
      FOREACH(var ${CMAKE_CONFIGURATION_TYPES})
        IF(NOT DEFINED FIRST_CONFIGURATION_TYPE)
          SET(FIRST_CONFIGURATION_TYPE "${var}/")
        ENDIF(NOT DEFINED FIRST_CONFIGURATION_TYPE)
      ENDFOREACH(var)
    ENDIF(CMAKE_CONFIGURATION_TYPES)

    ADD_TEST(${test_name} ${CMAKE_CTEST_COMMAND}
      --build-and-test "${src_dir}" "${bin_dir}"
      --build-generator ${CMAKE_GENERATOR}
      --build-makeprogram ${CMAKE_MAKE_PROGRAM}
      --build-project ${project_name}
      --build-options 
      "-DKWWidgets_DIR:PATH=${KWWidgets_BINARY_DIR}" 
      "-DSOV_DIR:PATH=${SOV_DIR}"
      --test-command "${FIRST_CONFIGURATION_TYPE}${exe_name}" "${exe_options}")

  ENDIF(VTK_WRAP_TCL)

ENDMACRO(KWWidgets_ADD_OUT_OF_SOURCE_TEST)