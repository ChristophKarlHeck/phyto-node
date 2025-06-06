#
# Phyto Node Project
#
cmake_minimum_required(VERSION 3.19)
cmake_policy(VERSION 3.19)

# Enable OPENOCD upload method for NUCLEO_WB55RG
file(COPY ${CMAKE_SOURCE_DIR}/scripts/config/NUCLEO_WB55RG.cmake
     DESTINATION ${CMAKE_SOURCE_DIR}/third-party/mbed-os/targets/upload_method_cfg)


# Initialize Mbed OS build system. 
# Note: This block must be before the project() call.
set(MBED_APP_JSON_PATH ${CMAKE_SOURCE_DIR}/mbed_app.json5)
# set(CUSTOM_TARGETS_JSON_PATH custom_targets.json) # If you need a custom target, use this line to specify the custom_targets.json

include(third-party/mbed-os/tools/cmake/app.cmake) # Load Mbed CE toolchain file and basic build system

# If you need any custom upload method configuration for your target, do that here

add_subdirectory(third-party/mbed-os) # Load Mbed OS build targets.  Must be added before any other subdirectories

add_subdirectory(third-party/flatbuffers # Flatbuffers for wrapping the serial communication with Rasperry pi
${CMAKE_CURRENT_BINARY_DIR}/flatbuffers-build
EXCLUDE_FROM_ALL)

project(PhytoNode CXX) # TODO: change this to your project name

set(SOURCES 
     ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/adc/AD7124.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/interfaces/ReadingQueue.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/Conversion.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/MbedStatsWrapper.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/utils.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/serial_mail_sender/SerialMailSender.cpp
)

add_executable(PhytoNode ${SOURCES})

# Enable logging with the desired log level
target_compile_definitions(PhytoNode PRIVATE 
    ENABLE_LOGGING           # Enable logging system
    LOG_LEVEL_TRACE       # Set logging level to INFO
)

target_link_libraries(PhytoNode PUBLIC
     mbed-os # Can also link to mbed-baremetal here
     # mbed-ble # only needed when BLE is used
     flatbuffers
     ) 

###GENRAL###
target_include_directories(PhytoNode
     PUBLIC 
          ${CMAKE_CURRENT_SOURCE_DIR}/include
          ${CMAKE_CURRENT_SOURCE_DIR}/third-party/flatbuffers/include   
)

###GENRAL####
mbed_set_post_build(PhytoNode) # Must call this for each target to set up bin file creation, code upload, etc


###GENRAL###
mbed_finalize_build() # Make sure this is the last line of the top-level buildscript