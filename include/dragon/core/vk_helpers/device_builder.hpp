#pragma once

#include "device.hpp"
#include "physical_device.hpp"
#include "result.hpp"

namespace Dragon {
    class DeviceBuilder {
        private:
            PhysicalDevice device;
        public:
            DeviceBuilder(PhysicalDevice device);

            Result<Device> build();
    };
}