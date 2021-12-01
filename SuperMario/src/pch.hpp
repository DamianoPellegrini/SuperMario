#ifndef _PCH_HPP
#define _PCH_HPP

// === STL ===
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

// === STL Containers ===
// #include <array>
#include <bitset>
// #include <deque>
// #include <forward_list>
// #include <list>
// #include <map>
// #include <queue>
// #include <set>
// #include <stack>
// #include <unordered_map>
// #include <unordered_set>
#include <vector>
#include <iterator>
#include <initializer_list>
// #include <tuple>

// === STL Atomics and threading ===
// #include <atomic>
// #include <condition_variable>
#include <future>
// #include <mutex>
// #include <thread>

// === STL Memory ===
#include <new>
#include <memory>
#include <span>

#include <string>
#include <string_view>
#include <algorithm>
// #include <any>
#include <chrono>
#include <functional>
// #include <optional>
// #include <locale>
#include <limits>
#include <random>
// #include <ratio>
// #include <complex>
// #include <regex>
// #include <stdexcept>
// #include <system_error>

// === THIRD PARTY ===
#include <vulkan/vulkan.h>
//#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

#endif