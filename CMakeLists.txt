cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if (POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
endif (POLICY CMP0091)

# Add cmake modules path (required for Versioning.cmake and git revision description)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

# By default, the version information is extracted from the git index. However,
# we can override this behavior by explicitly setting ADS_VERSION and
# skipping the git checks. This is useful for cases where this project is being
# used independently of its original git repo (e.g. vendored in another project)
if(NOT ADS_VERSION)
    include(GetGitRevisionDescription)
    git_describe(GitTagVersion --tags)
    string(REGEX REPLACE "^([0-9]+)\\..*" "\\1" VERSION_MAJOR "${GitTagVersion}")
    string(REGEX REPLACE "^[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${GitTagVersion}")
    string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${GitTagVersion}")
    set(VERSION_SHORT "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
    set(VERSION_SONAME "${VERSION_MAJOR}")
else()
    string(REGEX MATCHALL "[\.]" VERSION_DOT_MATCHES ${ADS_VERSION})
    list(LENGTH VERSION_DOT_MATCHES VERSION_DOT_COUNT)
    if(VERSION_DOT_COUNT EQUAL 2)
        set(VERSION_SHORT ${ADS_VERSION})
        string(REGEX REPLACE "^([0-9]+)\\..*" "\\1" VERSION_SONAME "${ADS_VERSION}")
        # Set PROJECT_VERSION_* variables for Versioning.cmake
        string(REGEX MATCHALL "[0-9]+" VERSION_PARTS "${ADS_VERSION}")
        list(GET VERSION_PARTS 0 PROJECT_VERSION_MAJOR)
        list(GET VERSION_PARTS 1 PROJECT_VERSION_MINOR)
        list(GET VERSION_PARTS 2 PROJECT_VERSION_PATCH)
    else()
        message(FATAL_ERROR "ADS_VERSION must be in major.minor.patch format, e.g. 3.8.1. Got ${ADS_VERSION}")
    endif()
endif()


project(CsADS LANGUAGES CXX VERSION ${VERSION_SHORT})

option(BUILD_STATIC "Build the static library" OFF)
option(BUILD_EXAMPLES "Build the examples" ON)

function(ads_collect_generated_sources out_var)
    set(ads_generated_sources)
    set(ads_resource_inputs)

    foreach(ads_resource IN LISTS ARGN)
        if(IS_ABSOLUTE "${ads_resource}")
            set(ads_resource_path "${ads_resource}")
        else()
            get_filename_component(ads_resource_path "${ads_resource}" ABSOLUTE BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
        endif()

        get_filename_component(ads_resource_ext "${ads_resource}" EXT)
        get_filename_component(ads_resource_name "${ads_resource}" NAME_WE)

        if(ads_resource_ext STREQUAL ".qrc")
            list(APPEND ads_resource_inputs "${ads_resource_path}")
            list(APPEND ads_generated_sources "${CMAKE_CURRENT_BINARY_DIR}/qrc_${ads_resource_name}.cpp")
        elseif(ads_resource_ext STREQUAL ".ui")
            list(APPEND ads_resource_inputs "${ads_resource_path}")
            list(APPEND ads_generated_sources "${CMAKE_CURRENT_BINARY_DIR}/ui_${ads_resource_name}.h")
        endif()
    endforeach()

    if(ads_resource_inputs)
        COPPERSPICE_RESOURCES(${ads_resource_inputs})
    endif()

    set(${out_var} "${ads_generated_sources}" PARENT_SCOPE)
endfunction()

# Platform directory: auto-detected based on pointer size, or manually set
if(NOT ADS_PLATFORM_DIR)
    if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
        set(ads_PlatformDir "x86")
    else()
        set(ads_PlatformDir "x64")
    endif()
else()
    set(ads_PlatformDir "${ADS_PLATFORM_DIR}")
endif()

add_subdirectory(src)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
	#message(STATUS "Example and demo CMake targets are disabled in this CopperSpice fork until their sources are ported.")
endif()