#pragma once

#include <boost/predef.h>
#include <boost/preprocessor.hpp>
#if BOOST_OS_WINDOWS
    #define VK_USE_PLATFORM_WIN32_KHR
#endif

#include <vulkan/vulkan.hpp>

#include <fmt/core.h>

#include "core/config.hpp"
#include "core/engine.hpp"
#include "core/submodule.hpp"