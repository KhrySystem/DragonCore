#pragma once

#include <boost/format.hpp>
#include <boost/predef.h>
#if BOOST_OS_WINDOWS
    #define VK_USE_PLATFORM_WIN32_KHR
#endif

#include <vulkan/vulkan.hpp>

#include "core/config.hpp"
#include "core/engine.hpp"
#include "core/submodule.hpp"