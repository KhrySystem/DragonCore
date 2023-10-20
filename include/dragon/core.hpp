#pragma once


/**
 * @defgroup Core Core Engine
 * This group containst structs and classes from the Dragon::Core module
*/

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
#include "core/vk_enum_string_helper.h"