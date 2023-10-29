#pragma once 

#include <vk_mem_alloc.h>
#include <vulkan/vulkan.h>

namespace Dragon {
    struct Buffer {
        VkBuffer buffer;
        VmaAllocation allocation;
    };
}