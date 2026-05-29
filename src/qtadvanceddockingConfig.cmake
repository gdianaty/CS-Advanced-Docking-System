include(CMakeFindDependencyMacro)
find_dependency(CopperSpice REQUIRED COMPONENTS Core Gui Xml)
include("${CMAKE_CURRENT_LIST_DIR}/adsTargets.cmake")