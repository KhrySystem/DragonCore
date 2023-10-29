#pragma once

#include <vulkan/vulkan.hpp>
#include "queue.hpp"

namespace Dragon {
    enum QueueFamilyType {
        GRAPHICS,
        COMPUTE,
        TRANSFER,
        SPARSE_BINDING,
        PROTECTED,
        VIDEO_DECODE,
        VIDEO_ENCODE,
        OPTICAL_FLOW
    };

    class QueueFamily {
        private:
            uint32_t id;
            QueueFamilyType type;
            uint32_t        timestampValidBits;
            VkExtent3D      minImageTransferGranularity;
        public:
            inline uint32_t getID() {return this->id;}
            inline QueueFamilyType getType() {return this->type;}
            inline uint32_t getTimestampValidBits() {return this->timestampValidBits;}
            inline VkExtent3D getMinImageTransferGranularity() {return this->minImageTransferGranularity;}


    };
}