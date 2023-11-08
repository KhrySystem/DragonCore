#include <dragon/core.hpp>

namespace Dragon {
    Result<Device> DeviceBuilder::build() {
        Device output;
        std::vector<VkDeviceQueueCreateInfo> queueInfos;

        float queuePriority = 1.0f;
        
        std::vector<float> priorities(1, queuePriority);

        for(auto queueFamily : this->physicalDevice->queueFamilies) {
            if(queueFamily.queueCount > priorities.size()) {
                priorities.resize(queueFamily.queueCount, queuePriority);
            }

            VkDeviceQueueCreateInfo createInfo{};
            createInfo.queueCount = queueFamily.queueCount;
            createInfo.queueFamilyIndex = queueFamily.id;
            createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;

            queueInfos.push_back(createInfo);
        }

        float* pPriorities = priorities.data();

        for(VkDeviceQueueCreateInfo& queueInfo : queueInfos) {
            queueInfo.pQueuePriorities = pPriorities;
        }

        VkDeviceCreateInfo createInfo{};
        createInfo.enabledExtensionCount = this->extensions.size();
        createInfo.enabledLayerCount = this->layers.size();
        createInfo.pEnabledFeatures = &this->features;
        //createInfo.pNext
        createInfo.ppEnabledExtensionNames = this->extensions.data();
        createInfo.ppEnabledLayerNames = this->layers.data();
        createInfo.pQueueCreateInfos = queueInfos.data();
        createInfo.queueCreateInfoCount = queueInfos.size();
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        VkResult result = vkCreateDevice(this->physicalDevice->physicalDevice, &createInfo, nullptr, &output.device);
        if(result != VK_SUCCESS) {
            ResultError error;
            error.message = fmt::format("Creating a logical device failed with {}", string_VkResult(result));
            error.resultCode = result;
            return Result<Device>(error);
        }
        output.physicalDevice = this->physicalDevice;
        return Result<Device>(output);
    }

    Result<Queue> Device::getQueue(QueueFamilyType type) {
        std::vector<QueueFamily> possibleQueueFamilies;

        for(auto queueFamily : this->physicalDevice->queueFamilies) {
            if(queueFamily.isType(type)) possibleQueueFamilies.push_back(queueFamily);
        }

        if(possibleQueueFamilies.size() == 0) {
            std::string val;
            switch(type) {
                case GRAPHICS: val = "QueueFamilyType::GRAPHICS"; break;
                case COMPUTE: val = "QueueFamilyType::COMPUTE"; break;
                case PROTECTED: val = "QueueFamilyType::PROTECTED"; break;
                case SPARSE_BINDING: val = "QueueFamilyType::SPARSE_BINDING"; break;
                case TRANSFER: val = "QueueFamilyType::TRANSFER"; break;
            }

            ResultError error;
            error.message = fmt::format("No queue families out of {} were of type {}", this->physicalDevice->queueFamilies.size(), val);
            error.resultCode = VK_ERROR_UNKNOWN;
            return Result<Queue>(error);
        }

        QueueFamily leastStressed = possibleQueueFamilies[0];

        for(auto queueFamily : possibleQueueFamilies) {
            if(queueFamily.strain < leastStressed.strain) {
                leastStressed = queueFamily;
            }
        }
        uint32_t queueToPick = (int)(leastStressed.strain * leastStressed.queueCount) % leastStressed.queueCount;

        if(leastStressed.queues.size() == leastStressed.queueCount) {
            leastStressed.strain += 1 / leastStressed.queueCount;
            return Result<Queue>(leastStressed.queues[queueToPick]);
        } else if(leastStressed.queues.size() <= leastStressed.queueCount) {
            Queue queue;
            vkGetDeviceQueue(this->device, leastStressed.id, queueToPick, &queue.queue);
            queue.queueFamily = leastStressed;
            leastStressed.queues.push_back(queue);
            leastStressed.strain += 1 / leastStressed.queueCount;
            return Result<Queue>(queue);
        }
        ResultError error;
        error.message = fmt::format("Somehow, you managed to create more queues than were allowed ({} out of {}) on QueueFamily {}", leastStressed.queues.size(), leastStressed.queueCount, leastStressed.id);
        error.resultCode = VkResult::VK_ERROR_NOT_PERMITTED_KHR;
        return Result<Queue>(error);
    }

    void DeviceBuilder::enableExtension(const char* extension) {
        for(auto alreadyEnabled : this->extensions) {
            if(strcmp(alreadyEnabled, extension) == 0) {
                return;
            }
        }
        this->extensions.push_back(extension);
    }

    void DeviceBuilder::enableExtension(std::string extension) {
        this->enableExtension(extension.c_str());
    }

    void Device::close() {
        vkDestroyDevice(this->device, nullptr);
    }
}