#pragma once

#include <vector>
#include <functional>

#include "instance.hpp"
#include "physical_device.hpp"
#include "result.hpp"

namespace Dragon {
    class PhysicalDeviceBuilder {
        private:
            Dragon::Instance instance;
        public:
            PhysicalDeviceBuilder(Instance const& instance);

            void deferSurfaceInitialization();
            void setRatingFunction(std::function<uint32_t(VkPhysicalDeviceProperties&, VkPhysicalDeviceFeatures&)>);

            Result<PhysicalDevice> buildFirst();
            Result<std::vector<PhysicalDevice>> buildAll();
    };
}