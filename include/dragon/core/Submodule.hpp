#pragma once

#include <VkBootstrap.h>
#include "engine.hpp"

#include "aliases.hpp"

namespace Dragon
{
    class Submodule
    {
        public:
            virtual void onAddition(Engine* parent) {}

            virtual void beforeInstanceCreation(Engine* parent) {}
            virtual InstanceBuilder adjustInstanceParams(Engine* parent, InstanceBuilder &previous) {return previous;}
            virtual void afterInstanceCreation(Engine* parent) {}

            virtual void beforePhysicalDeviceSelection(Engine* parent) {}
            virtual PhysicalDeviceSelector adjustPhysicalDeviceParams(Engine* parent, PhysicalDeviceSelector &previous) {return previous;}
            virtual void afterPhysicalDeviceSelection(Engine* parent) {}

            virtual void beforeDeviceCreation(Engine* parent) {}
            virtual DeviceBuilder adjustDeviceParams(Engine* parent, DeviceBuilder &previous) {return previous;}
            virtual void afterDeviceCreation(Engine* parent) {}

            virtual void update(Engine* parent) {}

            virtual void beforeClose(Engine* parent) {}
            virtual void close(Engine* parent) {}
            virtual void afterClose(Engine* parent) {}
    };
} // namespace Dragon
