#pragma once

#include "config.hpp"

struct DgGPU_T {
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceFeatures physicalDeviceFeatures;
    VkPhysicalDeviceProperties physicalDeviceProperties;
    VkDevice device;
    VkQueue graphicsQueue;

    int32_t score;

    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    VmaAllocator allocator;
};

typedef struct DgGPU_T DgGPU;
