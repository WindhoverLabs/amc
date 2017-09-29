#############################################################################
#
#   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name Windhover Labs, L.L.C. nor the names of its 
#    contributors may be used to endorse or promote products derived 
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
#############################################################################


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

add_airliner_app_unit_test(AMC-UT
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_app_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_app_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_cmds_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_cmds_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_pwm_config_tbl_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_pwm_config_tbl_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_mixer_config_tbl_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_mixer_config_tbl_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_motor_update_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_motor_update_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/amc_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/mixer/ut_MultirotorMixer_hooks.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/mixer/ut_MultirotorMixer_hooks.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/mixer/ut_MultirotorMixer_stubs.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/mixer/ut_MultirotorMixer_stubs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/mixer/ut_Mixer_stubs.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/pwm_limit/ut_pwm_limit_hooks.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/pwm_limit/ut_pwm_limit_hooks.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/pwm_limit/ut_pwm_limit_stubs.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/pwm_limit/ut_pwm_limit_stubs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/ut_amc_custom_hooks.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/ut_amc_custom_hooks.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/ut_amc_custom_stubs.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/ut_amc_custom_stubs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/amc_version.h
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs/
)
