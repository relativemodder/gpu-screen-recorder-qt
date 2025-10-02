cmake_minimum_required(VERSION 3.19)
project(gpu-screen-recorder-qt LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets DBus)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(LayerShellQt REQUIRED)

file(GLOB_RECURSE PROJ_SRC src/*.cpp)
file(GLOB_RECURSE PROJ_HDR include/*.h*)
file(GLOB_RECURSE PROJ_UI ui/*.ui)

qt_standard_project_setup()


set(CMAKE_AUTOUIC_SEARCH_PATHS 
    ${CMAKE_SOURCE_DIR}/ui
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)

qt_add_executable(${PROJECT_NAME}
    ${PROJ_SRC}
    ${PROJ_HDR}
    ${PROJ_UI}
)


target_link_libraries(gpu-screen-recorder-qt PRIVATE Qt6::Core)
target_include_directories(${PROJECT_NAME} PUBLIC
    include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::DBus
        LayerShellQt::Interface

)

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ${PROJECT_NAME}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
