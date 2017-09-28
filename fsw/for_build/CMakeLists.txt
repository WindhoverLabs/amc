
add_airliner_app_def(amc
    FILE AMC
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_version.h
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${PX4_MSGS_DIR}

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

#add_airliner_app_unit_test(AMC-UT
#    UTASSERT
#    SOURCES
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_app_test.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_app_test.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_cds_tbl_test.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_cds_tbl_test.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_cmds_test.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_cmds_test.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_config_tbl_test.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_config_tbl_test.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_testrunner.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_testrunner.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_test_utils.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_test_utils.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ut_px4lib_hooks.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ut_px4lib_hooks.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_app.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_app.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_config_utils.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_events.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_msg.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_tbldefs.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_version.h
#        
#    INCLUDES
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
#)
