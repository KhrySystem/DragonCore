
set(FMT_DOC ${Dragon_BUILD_DEPENDENCY_DOCS})
set(FMT_TEST OFF)
set(VMA_BUILD_DOCUMENTATION ${Dragon_BUILD_DEPENDENCY_DOCS})

set(FMT_INSTALL ${Dragon_INSTALL})

set(_shared ${BUILD_SHARED_LIBS})
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(external/fmt)
add_subdirectory(external/predef)
add_subdirectory(external/preprocessor)
add_subdirectory(external/VulkanMemoryAllocator)
set(BUILD_SHARED_LIBS ${_shared})
unset(_shared)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/dragon/core/config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/include/dragon/core/config.hpp)

set(VMA_LIB_NAME vma-3)
set(CORE_LIB_NAME dgcore-${DragonEngine_VERSION_MAJOR})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tools/enum_string_helper.py tools/enum_string_helper.py)
execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/enum_string_helper.py ${Vulkan_INCLUDE_DIR}/vulkan ${CMAKE_CURRENT_SOURCE_DIR}/include/dragon/core/vk_helpers/vk_enum_string_helper.h OUTPUT_VARIABLE output ERROR_VARIABLE error)
message(STATUS ${output})
message(STATUS ${error})

add_library(${VMA_LIB_NAME} STATIC
    "src/vma.cpp"
)

add_library(dgcore-${DragonEngine_VERSION_MAJOR}
    "src/device.cpp"
    "src/engine_core.cpp"
    "src/engine_init.cpp"
    "src/instance.cpp"
    "src/physical_device.cpp"
)

target_include_directories(${CORE_LIB_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${Vulkan_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_include_directories(${VMA_LIB_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${Vulkan_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(${CORE_LIB_NAME} PUBLIC 
    $<BUILD_INTERFACE:
        Boost::predef
        Boost::preprocessor
        fmt::fmt
        Vulkan::Vulkan
        Vulkan::Headers
        GPUOpen::VulkanMemoryAllocator
        ${VMA_LIB_NAME}
    >
    $<INSTALL_INTERFACE:
        fmt::fmt
        Vulkan::Vulkan
        Vulkan::Headers
        ${VMA_LIB_NAME}
    >
)
target_link_libraries(${VMA_LIB_NAME} PUBLIC 
    $<BUILD_INTERFACE:
        Boost::predef
        Boost::preprocessor
        fmt::fmt
        Vulkan::Vulkan
        Vulkan::Headers
        GPUOpen::VulkanMemoryAllocator
    >
    $<INSTALL_INTERFACE:
        fmt::fmt
        Vulkan::Vulkan
        Vulkan::Headers
    >
)

if(BUILD_SHARED_LIBS)
    target_compile_definitions(${CORE_LIB_NAME} PUBLIC DRAGON_CORE_DLL)
    target_compile_definitions(${CORE_LIB_NAME} PRIVATE DRAGON_CORE_BUILD_DLL)

    if(UNIX)
        target_link_options(${CORE_LIB_NAME} PUBLIC -Wall -Werror -fpic)
    endif()
endif()

add_library(Dragon::Core ALIAS ${CORE_LIB_NAME})

if(Dragon_INSTALL)
    include(cmake/install.cmake)
endif()