cmake_minimum_required(VERSION 3.14.0)

option(SDK_SOURCE_DIR "the source directory of your vst sdk, THIS IS REQUIRED")

if(NOT SDK_SOURCE_DIR)
    message( FATAL_ERROR "You need to provide a VST SDK Source directory via -DSDK_SOURCE_DIR." )
endif()

set(vst3sdk_SOURCE_DIR ${SDK_SOURCE_DIR})

project(trig_distort)

add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(${PROJECT_NAME}
  controller.cpp
  factory.cpp
  processor.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    sdk
)

if(SMTG_MAC)
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.12)
    smtg_set_bundle(${PROJECT_NAME}
        BUNDLE_IDENTIFIER horse_club
        INFOPLIST "${CMAKE_CURRENT_LIST_DIR}/resource/Info.plist" PREPROCESS
    )
    smtg_set_debug_executable(${PROJECT_NAME}
        "/Applications/VST3PluginTestHost.app"
        "--pluginfolder;$(BUILT_PRODUCTS_DIR)"
    )
elseif(SMTG_WIN)
    target_sources(${PROJECT_NAME} PRIVATE 
        resource/win32resource.rc
    )
    if(MSVC)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    
        smtg_set_debug_executable(${PROJECT_NAME}
            "$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
            "--pluginfolder \"$(OutDir)/\""
        )
    endif()
endif()