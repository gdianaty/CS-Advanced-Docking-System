cmake_minimum_required(VERSION 3.16)
project(ads_example_simple VERSION ${VERSION_SHORT}) 
#find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
#find_package(Qt${QT_VERSION_MAJOR} 5.5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(CopperSpice REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(APP_FORMS
   ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.ui
)

COPPERSPICE_RESOURCES(
    ${APP_FORMS}
)

add_executable(SimpleExample 
    main.cpp
    MainWindow.cpp
    ${APP_FORMS}
)

#target_include_directories(SimpleExample PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../src")
#target_link_libraries(SimpleExample PRIVATE qtadvanceddocking-copperspice)
#target_link_libraries(SimpleExample PUBLIC CopperSpice::CsCore CopperSpice::CsGui)

target_link_libraries(SimpleExample PRIVATE
    qtadvanceddocking-copperspice
    CopperSpice::CsCore
    CopperSpice::CsGui
)

set_target_properties(SimpleExample PROPERTIES 
    #AUTOMOC ON
    #AUTORCC ON
    #AUTOUIC ON
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    VERSION ${VERSION_SHORT}
    EXPORT_NAME "Qt Advanced Docking System Simple Example"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${ads_PlatformDir}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${ads_PlatformDir}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${ads_PlatformDir}/bin"
)
