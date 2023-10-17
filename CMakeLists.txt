find_package(Vulkan REQUIRED QUIET)

add_subdirectory(external/predef)
add_subdirectory(external/preprocessor)
add_subdirectory(external/vk-bootstrap)
add_subdirectory(external/VulkanMemoryAllocator)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/dragon/core/config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/include/dragon/core/config.hpp)

add_library(dgcore-${DragonEngine_VERSION_MAJOR} 
    "src/engine.cpp"
)

target_include_directories(dgcore-${DragonEngine_VERSION_MAJOR} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${Vulkan_INCLUDE_DIR})
target_link_libraries(dgcore-${DragonEngine_VERSION_MAJOR} PUBLIC Boost::predef Boost::preprocessor vk-bootstrap GPUOpen::VulkanMemoryAllocator Vulkan::Vulkan)

add_library(Dragon::Core ALIAS dgcore-${DragonEngine_VERSION_MAJOR})