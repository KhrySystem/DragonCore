#pragma once

#include <string>

#include <vulkan/vulkan.h>

#include "queue.hpp"
#include "../result.hpp"

namespace Dragon {
    class Buffer;

    class DGCOREAPI DeviceBuilder {
        private:
            PhysicalDevice* physicalDevice;
            std::vector<const char*> extensions;
            std::vector<const char*> layers;
            VkPhysicalDeviceFeatures features {VK_FALSE};
        public:
            inline DeviceBuilder(PhysicalDevice* physicalDevice) {this->physicalDevice = physicalDevice;}
            void enableExtension(const char* extension);
            void enableExtension(std::string extension);

            Result<Device> build();
    };
    class DGCOREAPI Device {
        private:
            PhysicalDevice* physicalDevice;
            VkDevice device;

            std::vector<Queue> queues;
        public:
            inline operator VkDevice() const {return this->device;};

            Result<Queue> getQueue(QueueFamilyType type);
            inline PhysicalDevice* getPhysicalDevice() {return this->physicalDevice;}

            Result<Buffer> createBuffer();

            void close();

            friend class DeviceBuilder;
    };
}

#include "physical_device.hpp"