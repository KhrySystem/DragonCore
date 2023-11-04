#pragma once

#include <vulkan/vulkan.hpp>
#include <map>

namespace Dragon {
    class Queue;

    enum QueueFamilyType {
        GRAPHICS = VK_QUEUE_GRAPHICS_BIT,
        PRESENT = 0x80000000,
        COMPUTE = VK_QUEUE_COMPUTE_BIT,
        TRANSFER = VK_QUEUE_TRANSFER_BIT,
        SPARSE_BINDING = VK_QUEUE_SPARSE_BINDING_BIT,
    #ifdef VK_VERSION_1_1
        PROTECTED = VK_QUEUE_PROTECTED_BIT,
        #ifdef VK_ENABLE_BETA_EXTENSIONS
            VIDEO_DECODE = VK_QUEUE_VIDEO_DECODE_BIT_KHR,
            VIDEO_ENCODE = VK_QUEUE_VIDEO_ENCODE_BIT_KHR,
        #endif
        #ifdef NV_EXTENSIONS
            OPTICAL_FLOW = VK_QUEUE_OPTICAL_FLOW_BIT_NV 
        #endif
    #endif
    };

    class DGCOREAPI QueueFamily {
        private:
            uint32_t id;
            uint32_t flags;
            uint32_t timestampValidBits;
            VkExtent3D minImageTransferGranularity;
            std::vector<Queue> queues;
            uint32_t queueCount;
            float strain = 0;
        public:
            inline uint32_t getID() {return this->id;}
            inline bool isType(QueueFamilyType type) {return this->flags & type;}
            inline uint32_t getTimestampValidBits() {return this->timestampValidBits;}
            inline VkExtent3D getMinImageTransferGranularity() {return this->minImageTransferGranularity;}
            inline uint32_t getQueueCount() {return this->queueCount;}

            friend class PhysicalDevice;
            friend class Queue;
            friend class PhysicalDeviceBuilder;
            friend class DeviceBuilder;
            friend class Device;
    };

    class DGCOREAPI Queue {
        private:
            VkQueue queue;
            QueueFamily queueFamily;
        public:
            inline operator VkQueue() const {return this->queue;}

            inline QueueFamily getQueueFamily() {return this->queueFamily;}

            friend class QueueFamily;
            friend class Device;
    };
}