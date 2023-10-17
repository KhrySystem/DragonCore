#include <dragon/core.hpp>
#ifndef NDEBUG
#include <iostream>
#include <format>
#endif

bool Dragon::Engine::addSubmodule(Dragon::Submodule* submodule) {
    this->submodules.push_back(submodule);

    return true;
}

void Dragon::Engine::init(EngineCreateInfo &createInfo) {
    for(Dragon::Submodule* submodule : this->submodules) {
        submodule->beforeInstanceCreation(this);
    }

    Dragon::InstanceBuilder instanceBuilder;

    for(Dragon::Submodule* submodule: this->submodules) {
        instanceBuilder = submodule->adjustInstanceParams(this, instanceBuilder);
    }

    instanceBuilder = instanceBuilder.set_app_name(createInfo.appName.c_str())
                                    .set_app_version(createInfo.appVersion)
                                    .set_engine_name(DRAGON_ENGINE_NAME)
                                    .set_engine_version(DRAGON_ENGINE_VERSION)
                                    .require_api_version(1, 2, 0);

    if(createInfo.requestValidationLayers) {
        instanceBuilder = instanceBuilder.request_validation_layers().use_default_debug_messenger().enable_layer("VK_LAYER_KHRONOS_validation");
    }

    Dragon::Result<Dragon::Instance> instanceResult = instanceBuilder.build();
    
    if(!instanceResult) {
        throw std::format("Failed to create Vulkan instance. Error: {}\n", instanceResult.error().message());
    }
    this->instance = instanceResult.value();

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
        throw std::format("Failed to pick VkPhysicalDevice. Error: {}\n", physicalDeviceResult.error().message());
    }

    this->physicalDevice = physicalDeviceResult.value();

    for(Dragon::Submodule* submodule : this->submodules) {
        submodule->afterPhysicalDeviceSelection(this);
    }

    for(Dragon::Submodule* submodule : this->submodules) {
        submodule->beforeDeviceCreation(this);
    }

    Dragon::DeviceBuilder deviceBuilder(this->physicalDevice);

    for(Dragon::Submodule* submodule : this->submodules) {
        deviceBuilder = submodule->adjustDeviceParams(this, deviceBuilder);
    }

    Dragon::Result<Dragon::Device> deviceResult = deviceBuilder.build();

    if(!deviceResult) {
        throw std::format("Failed to create VkDevice. Error: {}\n", deviceResult.error().message());
    }

    this->device = deviceResult.value();

    for(Dragon::Submodule* submodule : this->submodules) {
        submodule->afterDeviceCreation(this);
    }
}

void Dragon::Engine::update() {
    for(Dragon::Submodule* submodule : this->submodules) {
        submodule->update(this);
    }
}

void Dragon::Engine::close() {
    vkb::destroy_device(this->device);
    vkb::destroy_instance(this->instance);
}

Dragon::Engine::~Engine() {
    for(Dragon::Submodule* submodule : this->submodules) {
        submodule->beforeClose(this);
    }
    for(Dragon::Submodule* submodule : this->submodules) {
        submodule->close(this);
    }
    this->close();
    for(Dragon::Submodule* submodule : this->submodules) {
        submodule->afterClose(this);
    }
}