#include <dragon/core.hpp>

namespace Dragon {
    PhysicalDeviceBuilder::PhysicalDeviceBuilder(Instance const& instance) {
        this->instance = instance;
    }

    Result<PhysicalDevice> PhysicalDeviceBuilder::buildFirst() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(this->instance, &deviceCount, nullptr);
        if(deviceCount <= 0) {
            ResultError error;
            error.message = "No Vulkan-supported PhysicalDevice was found!";
            error.resultCode = VK_ERROR_UNKNOWN;
            return Result<PhysicalDevice>(error);
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        VkPhysicalDevice bestDevice = VK_NULL_HANDLE;
        uint32_t bestScore = 0;
        VkPhysicalDeviceProperties bestProperties;
        VkPhysicalDeviceFeatures bestFeatures;
        vkEnumeratePhysicalDevices(this->instance, &deviceCount, devices.data());

        for(VkPhysicalDevice device : devices) {
            VkPhysicalDeviceProperties properties;
            vkGetPhysicalDeviceProperties(device, &properties);
            VkPhysicalDeviceFeatures features;
            vkGetPhysicalDeviceFeatures(device, &features);
            uint32_t rating = 0;
            for(auto ratingFunc : this->ratingFuncs) {
                rating *= ratingFunc(properties, features);
            }
            
            if(rating >= bestScore) {
                bestDevice = device;
                bestScore = rating;
                bestProperties = properties;
                bestFeatures = features;
            }
        }

        if(bestScore == 0) {
            ResultError error;
            error.message = fmt::format("Out of {} possible PhysicalDevices, none were deemed allowable to use by this engine's submodules.", deviceCount);
            error.resultCode = VK_ERROR_UNKNOWN;
        }

        uint32_t queueFamilyCount;
        vkGetPhysicalDeviceQueueFamilyProperties(bestDevice, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(bestDevice, &queueFamilyCount, queueFamilies.data());

        PhysicalDevice actual;
        actual.features = bestFeatures;
        actual.instance = this->instance;
        actual.physicalDevice = bestDevice;
        actual.properties = bestProperties;
        actual.rating = bestScore;

        int i = 0;
        for(auto queueFamily : queueFamilies) {
            QueueFamily family;
            family.flags = queueFamily.queueFlags;
            family.id = i;
            family.minImageTransferGranularity = queueFamily.minImageTransferGranularity;
            family.timestampValidBits = queueFamily.timestampValidBits;
            family.queueCount = queueFamily.queueCount;

            VkBool32 presentSupported;
            vkGetPhysicalDeviceSurfaceSupportKHR(bestDevice, i, this->surface, &presentSupported);
            if(presentSupported)
                family.flags += QueueFamilyType::PRESENT;
            
            actual.queueFamilies.push_back(family);
            i++;
        }

        return Result<PhysicalDevice>(actual);
    }

    std::vector<Result<PhysicalDevice>> PhysicalDeviceBuilder::buildAll() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(this->instance, &deviceCount, nullptr);
        if(deviceCount <= 0) {
            ResultError error;
            error.message = "No Vulkan-supported PhysicalDevice was found!";
            error.resultCode = VK_ERROR_UNKNOWN;
            return {Result<PhysicalDevice>(error)};
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        VkPhysicalDevice bestDevice = VK_NULL_HANDLE;
        uint32_t bestScore = 0;
        VkPhysicalDeviceProperties bestProperties;
        VkPhysicalDeviceFeatures bestFeatures;
        vkEnumeratePhysicalDevices(this->instance, &deviceCount, devices.data());

        std::vector<Result<PhysicalDevice>> results;

        for(auto device : devices) {
            VkPhysicalDeviceProperties properties;
            vkGetPhysicalDeviceProperties(device, &properties);
            VkPhysicalDeviceFeatures features;
            vkGetPhysicalDeviceFeatures(device, &features);
            uint32_t rating = 1;
            for(auto ratingFunc : this->ratingFuncs) {
                rating *=  ratingFunc(properties, features);
            }

            if(rating == 0) {
                ResultError error;
                error.message = "This device was deemed unsuitable by this engine's submodules.";
                error.resultCode = VK_ERROR_UNKNOWN;
                results.push_back(Result<PhysicalDevice>(error));
            } else {
                uint32_t queueFamilyCount;
                vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
                std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
                vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

                PhysicalDevice actual;
                actual.features = features;
                actual.instance = this->instance;
                actual.physicalDevice = device;
                actual.properties = properties;
                actual.rating = rating;

                int i = 0;
                for(auto queueFamily : queueFamilies) {
                    QueueFamily family;
                    family.flags = queueFamily.queueFlags;
                    family.id = i;
                    family.minImageTransferGranularity = queueFamily.minImageTransferGranularity;
                    family.timestampValidBits = queueFamily.timestampValidBits;
                    family.queueCount = queueFamily.queueCount;
                    
                    actual.queueFamilies.push_back(family);
                    i++;
                }

                results.push_back(Result<PhysicalDevice>(actual));
            }
        }

        return results;
    }
}