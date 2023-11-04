#pragma once

#include <functional>
#include <vector>

#include <vulkan/vulkan.h>

#include "instance.hpp"
#include "../result.hpp"
#include "queue.hpp"

typedef std::function<uint32_t(VkPhysicalDeviceProperties&, VkPhysicalDeviceFeatures&)> PFN_PhysicalDeviceBuilder_RatingFunc;

namespace Dragon {

    class DGCOREAPI PhysicalDeviceBuilder {
        private:
            Dragon::Instance instance;
            std::vector<PFN_PhysicalDeviceBuilder_RatingFunc> ratingFuncs;
            VkSurfaceKHR surface;
        public:
            PhysicalDeviceBuilder(Instance const& instance);

            inline void addRatingFunction(PFN_PhysicalDeviceBuilder_RatingFunc func) {this->ratingFuncs.push_back(func);}
            inline void setSurface(VkSurfaceKHR &surface) {this->surface = surface;}

            Result<PhysicalDevice> buildFirst();
            std::vector<Result<PhysicalDevice>> buildAll();
    };

    class DGCOREAPI PhysicalDevice {
        private:
            Instance instance;
            VkPhysicalDevice physicalDevice;
            VkPhysicalDeviceProperties properties;
            VkPhysicalDeviceFeatures features;
            std::vector<QueueFamily> queueFamilies;
            uint32_t rating;
        public:
            inline operator VkPhysicalDevice() const {return this->physicalDevice;}

            inline Instance getInstance() {return this->instance;}
            QueueFamily getQueueFamilyByType(QueueFamilyType type);
            QueueFamily getQueueFamilyByIndex(size_t index);

            friend class PhysicalDeviceBuilder;
            friend class Device;
            friend class DeviceBuilder;
    };
}