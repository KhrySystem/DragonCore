#include <VkBootstrap.h>

namespace Dragon
{
    template<typename T> using Result = vkb::Result<T>;
    using Instance = vkb::Instance;
    using PhysicalDevice = vkb::PhysicalDevice;
    using Device = vkb::Device;

    using InstanceBuilder = vkb::InstanceBuilder;
    using PhysicalDeviceSelector = vkb::PhysicalDeviceSelector;
    using DeviceBuilder = vkb::DeviceBuilder;

} // namespace Dragon