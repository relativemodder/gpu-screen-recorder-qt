cmake_minimum_required(VERSION 3.19)
project(gpu-screen-recorder-qt LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

file(GLOB_RECURSE PROJ_SRC src/*.c*)
file(GLOB_RECURSE PROJ_UI ui/*.ui)
file(GLOB_RECURSE PROJ_H include/*.h*)

qt_add_executable(gpu-screen-recorder-qt
    ${PROJ_SRC}
    ${PROJ_UI}
    ${PROJ_H}
)

target_link_libraries(gpu-screen-recorder-qt
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS gpu-screen-recorder-qt
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET gpu-screen-recorder-qt
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
