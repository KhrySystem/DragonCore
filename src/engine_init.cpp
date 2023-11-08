#include <dragon/core.hpp>
namespace Dragon {
    void Engine::instanceCreation(const char* appName, uint32_t appVersion, bool requestValidationLayers) {
        for(Submodule* submodule : this->submodules) {
            submodule->beforeInstanceCreation(this);
        }

        InstanceBuilder instanceBuilder;

        for(Submodule* submodule: this->submodules) {
            submodule->adjustInstanceParams(this, instanceBuilder);
        }

        instanceBuilder.setAppName(appName);
        instanceBuilder.setAppVersion(appVersion);
        instanceBuilder.setEngineName(DRAGON_ENGINE_NAME);
        instanceBuilder.setEngineVersion(DRAGON_ENGINE_VERSION);
        instanceBuilder.requireAPIVersion(1, 2, 0);

        if(requestValidationLayers) {
            instanceBuilder.requestValidationLayers();
            instanceBuilder.useDefaultDebugMessenger();
            instanceBuilder.enableValidationLayer("VK_LAYER_KHRONOS_validation");
        }

        auto instanceResult = instanceBuilder.build();
        
        if(!instanceResult) {
            throw fmt::format("Failed to create Vulkan instance. Error: %1%\n", instanceResult.getError().message);
        }
        this->instance = instanceResult.getValue();

        for(Submodule* submodule : this->submodules) {
            submodule->afterInstanceCreation(this);
        }
    }

    void Engine::physicalDeviceSelection() {
        for(Submodule* submodule: this->submodules) {
            submodule->beforePhysicalDeviceSelection(this);
        }

        PhysicalDeviceBuilder physicalDeviceBuilder(this->instance);

        for(Submodule* submodule: this->submodules) {
            submodule->adjustPhysicalDeviceParams(this, physicalDeviceBuilder);
        }

        Result<PhysicalDevice> physicalDeviceResult = physicalDeviceBuilder.buildFirst();

        if(!physicalDeviceResult) {
            throw fmt::format("Failed to pick VkPhysicalDevice. Error: %1%\n", physicalDeviceResult.getError().message);
        }

        this->physicalDevice = physicalDeviceResult.getValue();

        for(Submodule* submodule : this->submodules) {
            submodule->afterPhysicalDeviceSelection(this);
        }
    }

    void Engine::deviceCreation() {
        for(Submodule* submodule : this->submodules) {
            submodule->beforeDeviceCreation(this);
        }

        DeviceBuilder deviceBuilder(&this->physicalDevice);

        for(Submodule* submodule : this->submodules) {
            submodule->adjustDeviceParams(this, deviceBuilder);
        }

        Result<Device> deviceResult = deviceBuilder.build();


        if(!deviceResult) {
            throw fmt::format("Failed to create VkDevice. Error: %1%\n", deviceResult.getError().message);
        }

        this->device = deviceResult.getValue();

        for(Submodule* submodule : this->submodules) {
            submodule->afterDeviceCreation(this);
        }
    }

    void Engine::allocatorCreation() {
        VmaAllocatorCreateInfo allocCreateInfo{};
        allocCreateInfo.vulkanApiVersion = VK_API_VERSION_1_2;
        allocCreateInfo.device = this->device;
        allocCreateInfo.physicalDevice = this->physicalDevice;
        allocCreateInfo.instance = this->instance;

        vmaCreateAllocator(&allocCreateInfo, &this->allocator);
    }

    void Engine::init(EngineCreateInfo &createInfo) {
        this->instanceCreation(createInfo.appName.c_str(), createInfo.appVersion, createInfo.requestValidationLayers);
        this->physicalDeviceSelection();
        this->deviceCreation();
        this->allocatorCreation();
    }
}
