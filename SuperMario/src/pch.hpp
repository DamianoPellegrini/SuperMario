#ifndef _PCH_HPP
#define _PCH_HPP

// === STL ===
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

// === STL Containers ===
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

// === STL Atomics and threading ===
#include <atomic>
#include <future>
#include <mutex>
#include <thread>

// === STL Memory ===
#include <memory>

#include <string>
#include <string_view>
#include <algorithm>
// #include <any>
#include <chrono>
#include <optional>
#include <locale>
#include <limits>
#include <random>
#include <system_error>

// === THIRD PARTY ===
#define VK_ENABLE_BETA_EXTENSIONS
#include <vulkan/vulkan.hpp>
#include "vulkan_extensions.hpp"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

#endif