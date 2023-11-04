#pragma once 

#include <vk_mem_alloc.h>
#include <vulkan/vulkan.h>

#include "device.hpp"

namespace Dragon {
    struct DGCOREAPI Buffer {
        public:
            Device device;
            VkBuffer buffer;
            VmaAllocation allocation;
        
            operator VkBuffer() const {return this->buffer;}
            operator VmaAllocation() const {return this->allocation;}

            friend class Device;
    };
}