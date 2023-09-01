add_subdirectory(external/glm)
add_subdirectory(external/predef)
add_subdirectory(external/preprocessor)
add_subdirectory(external/vk-bootstrap)
add_subdirectory(external/VulkanMemoryAllocator)

message(STATUS "Testing for Vulkan...")
find_package(Vulkan REQUIRED QUIET)
message(STATUS "FOUND Vulkan ${Vulkan_VERSION}")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/dragon/core/config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/include/dragon/core/config.hpp)

add_library(dgcore-${DragonEngine_VERSION_MAJOR}
    "src/engine_close.cpp"
    "src/engine_init.cpp"
    "src/engine_vk_init.hpp"
    "src/internal.cpp"
)

target_precompile_headers(dgcore-${DragonEngine_VERSION_MAJOR}
    PUBLIC
        "include/dragon/core/config.hpp"
        "include/dragon/core/engine.hpp"
        "include/dragon/core/gpu.hpp"
        "include/dragon/core/internal.hpp"
        "include/dragon/core/result.hpp"
        "include/dragon/core/vk_procaddr.hpp"
        "include/dragon/core.hpp"
)

target_link_libraries(dgcore-${DragonEngine_VERSION_MAJOR} PUBLIC Vulkan::Vulkan glm::glm Boost::predef Boost::preprocessor GPUOpen::VulkanMemoryAllocator)
target_include_directories(dgcore-${DragonEngine_VERSION_MAJOR} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include;${CMAKE_CURRENT_SOURCE_DIR}/external/glm;${CMAKE_CURRENT_SOURCE_DIR}/external/predef/include;${CMAKE_CURRENT_SOURCE_DIR}/external/VulkanMemoryAllocator/include
)
add_library(Dragon::Core ALIAS dgcore-${DragonEngine_VERSION_MAJOR})

if(${Dragon_BUILD_EXAMPLES})
    add_subdirectory(tools/examples)
endif()