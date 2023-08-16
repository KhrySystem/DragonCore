add_library(dgcore${DragonEngine_VERSION_MAJOR}
    "engine_close.cpp"
    "engine_init.cpp"
    "engine_vk_init.hpp"
    "internal.cpp"
)
target_link_libraries(dgcore${DragonEngine_VERSION_MAJOR} PUBLIC Vulkan::Vulkan glm::glm Boost::any Boost::predef GPUOpen::VulkanMemoryAllocator)
target_include_directories(dgcore${DragonEngine_VERSION_MAJOR} PUBLIC 
    ${_dir}/include;${_dir}/external/glm;${_dir}/external/predef/include;${_dir}/external/VulkanMemoryAllocator/include
)
add_library(Dragon::Core ALIAS dgcore${DragonEngine_VERSION_MAJOR})