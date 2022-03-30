cmake_minimum_required(VERSION 3.0.0)
project(control_usb_cams VERSION 0.1.0)

include(CTest)
enable_testing()
include_directories(
    inc
    camera_sdks/brandA/include
    camera_sdks/brandB/include
)


file(GLOB SOURCES
	"src/*.cpp"
	"src/*.c"
)

add_executable(control_usb_cams ${SOURCES})

target_link_libraries(control_usb_cams usb-1.0)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
