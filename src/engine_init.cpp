#pragma once

#include <dragon/core.hpp>

void Dragon::Engine::instanceCreation(const char* appName, uint32_t appVersion, bool requestValidationLayers) {
    for(Dragon::Submodule* submodule : this->submodules) {
        submodule->beforeInstanceCreation(this);
    }

    Dragon::InstanceBuilder instanceBuilder;

    for(Dragon::Submodule* submodule: this->submodules) {
        instanceBuilder = submodule->adjustInstanceParams(this, instanceBuilder);
    }

    instanceBuilder = instanceBuilder.set_app_name(appName)
                                    .set_app_version(appVersion)
                                    .set_engine_name(DRAGON_ENGINE_NAME)
                                    .set_engine_version(DRAGON_ENGINE_VERSION)
                                    .require_api_version(1, 2, 0);

    if(requestValidationLayers) {
        instanceBuilder = instanceBuilder.request_validation_layers().use_default_debug_messenger().enable_layer("VK_LAYER_KHRONOS_validation");
    }

    Dragon::Result<Dragon::Instance> instanceResult = instanceBuilder.build();
    
    if(!instanceResult) {
        throw fmt::format("Failed to create Vulkan instance. Error: %1%\n", instanceResult.error().message());
    }
    this->instance = instanceResult.value();

    for(Dragon::Submodule* submodule : this->submodules) {
        submodule->afterInstanceCreation(this);
    }
}

void Dragon::Engine::physicalDeviceSelection() {
    for(Dragon::Submodule* submodule: this->submodules) {
        submodule->beforePhysicalDeviceSelection(this);
    }

    Dragon::PhysicalDeviceSelector physicalDeviceSelector(this->instance);

    physicalDeviceSelector = physicalDeviceSelector.defer_surface_initialization();

    for(Dragon::Submodule* submodule: this->submodules) {
        physicalDeviceSelector = submodule->adjustPhysicalDeviceParams(this, physicalDeviceSelector);
    }

    Dragon::Result<Dragon::PhysicalDevice> physicalDeviceResult = physicalDeviceSelector.select();

    if(!physicalDeviceResult) {
        throw fmt::format("Failed to pick VkPhysicalDevice. Error: %1%\n", physicalDeviceResult.error().message());
    }

    this->physicalDevice = physicalDeviceResult.value();

    for(Dragon::Submodule* submodule : this->submodules) {
        submodule->afterPhysicalDeviceSelection(this);
    }
}

void Dragon::Engine::deviceCreation() {
    for(Dragon::Submodule* submodule : this->submodules) {
        submodule->beforeDeviceCreation(this);
    }

    Dragon::DeviceBuilder deviceBuilder(this->physicalDevice);

    for(Dragon::Submodule* submodule : this->submodules) {
        deviceBuilder = submodule->adjustDeviceParams(this, deviceBuilder);
    }

    Dragon::Result<Dragon::Device> deviceResult = deviceBuilder.build();


    if(!deviceResult) {
        throw fmt::format("Failed to create VkDevice. Error: %1%\n", deviceResult.error().message());
    }

    this->device = deviceResult.value();

    Dragon::Result<Dragon::Queue> graphicsQueueResult = this->device.get_queue()

    for(Dragon::Submodule* submodule : this->submodules) {
        submodule->afterDeviceCreation(this);
    }
}

void Dragon::Engine::allocatorCreation() {
    VmaAllocatorCreateInfo allocCreateInfo{};
    allocCreateInfo.vulkanApiVersion = VK_API_VERSION_1_2;
    allocCreateInfo.device = this->device.device;
    allocCreateInfo.physicalDevice = this->physicalDevice.physical_device;
    allocCreateInfo.instance = this->instance.instance;

    vmaCreateAllocator(&allocCreateInfo, &this->allocator);
}

void Dragon::Engine::init(EngineCreateInfo &createInfo) {
    this->instanceCreation(createInfo.appName.c_str(), createInfo.appVersion, createInfo.requestValidationLayers);
    this->physicalDeviceSelection();
    this->deviceCreation();
    this->allocatorCreation();
}
