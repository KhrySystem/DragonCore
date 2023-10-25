
set(FMT_DOC ${Dragon_BUILD_DEPENDENCY_DOCS})
set(VMA_BUILD_DOCUMENTATION ${Dragon_BUILD_DEPENDENCY_DOCS})

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
    "src/engine.cpp"
)

target_include_directories(dgcore-${DragonEngine_VERSION_MAJOR} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${Vulkan_INCLUDE_DIR}
)
target_link_libraries(dgcore-${DragonEngine_VERSION_MAJOR} PUBLIC 
    Boost::predef
    Boost::preprocessor
    fmt::fmt
    GPUOpen::VulkanMemoryAllocator
    vk-bootstrap
    Vulkan::Vulkan
)

if(BUILD_SHARED_LIBS)
    target_compile_definitions(dgcore-${DragonEngine_VERSION_MAJOR} PUBLIC DRAGON_CORE_DLL)
    target_compile_definitions(dgcore-${DragonEngine_VERSION_MAJOR} PRIVATE DRAGON_CORE_BUILD_DLL)
endif()

add_library(Dragon::Core ALIAS dgcore-${DragonEngine_VERSION_MAJOR})