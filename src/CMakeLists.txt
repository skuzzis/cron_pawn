include(AMXConfig)
include(AddSAMPPlugin)

set(SAMP_SDK_ROOT "${PROJECT_SOURCE_DIR}/lib/samp-plugin-sdk")
find_package(SAMPSDK REQUIRED)
set(CRON_ROOT "${PROJECT_SOURCE_DIR}/lib/libcron")

include_directories(
	${SAMPSDK_INCLUDE_DIR}
    ${CRON_ROOT}
)

add_samp_plugin(cron_pawn
	${SAMPSDK_DIR}/amxplugin.cpp
	${SAMPSDK_DIR}/amxplugin2.cpp
	${SAMPSDK_DIR}/amx/getch.c
    ${CRON_ROOT}/libcron/src/CronClock.cpp
    ${CRON_ROOT}/libcron/src/CronData.cpp
    ${CRON_ROOT}/libcron/src/CronRandomization.cpp
    ${CRON_ROOT}/libcron/src/CronSchedule.cpp
    ${CRON_ROOT}/libcron/src/Task.cpp
    common/common.hpp
    natives/natives.hpp
    natives/natives.cpp
    utilities/utilities.hpp
    utilities/utilities.cpp
    main.cpp
    plugin.def
)