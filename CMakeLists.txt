
set(FMT_DOC ${Dragon_BUILD_DEPENDENCY_DOCS})
set(FMT_TEST OFF)
set(VMA_BUILD_DOCUMENTATION ${Dragon_BUILD_DEPENDENCY_DOCS})

set(FMT_INSTALL ${Dragon_INSTALL})

set(_shared ${BUILD_SHARED_LIBS})
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(external/fmt)
add_subdirectory(external/predef)
add_subdirectory(external/preprocessor)
add_subdirectory(external/vk-bootstrap)
add_subdirectory(external/VulkanMemoryAllocator)
set(BUILD_SHARED_LIBS ${_shared})
unset(_shared)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/dragon/core/config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/include/dragon/core/config.hpp)

add_library(dgcore-${DragonEngine_VERSION_MAJOR} 
    "src/engine_core.cpp"
    "src/engine_init.cpp"
    "src/internal.cpp"
)

target_include_directories(dgcore-${DragonEngine_VERSION_MAJOR} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${Vulkan_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(dgcore-${DragonEngine_VERSION_MAJOR} PUBLIC 
    $<BUILD_INTERFACE:
        Boost::predef
        Boost::preprocessor
        fmt::fmt
        vk-bootstrap
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
    target_compile_definitions(dgcore-${DragonEngine_VERSION_MAJOR} PUBLIC DRAGON_CORE_DLL)
    target_compile_definitions(dgcore-${DragonEngine_VERSION_MAJOR} PRIVATE DRAGON_CORE_BUILD_DLL)
endif()

add_library(Dragon::Core ALIAS dgcore-${DragonEngine_VERSION_MAJOR})

if(Dragon_INSTALL)
    include(cmake/install.cmake)
endif()