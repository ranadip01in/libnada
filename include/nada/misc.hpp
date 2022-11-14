#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

/// Use this like: `if (static Do_Once _; _)` and the following code is only executed once or use the `NADA_DO_ONCE` macro.
struct Do_Once {
    explicit operator bool() { return std::exchange(b, false); }
    private: bool b = true;
};
/// Use this macro to do: `NADA_DO_ONCE { ... your code ... }` and your code is only executed once.
#define NADA_DO_ONCE if (static Do_Once once_var; once_var)

/// Helpers, that don't fit anywhere else.
namespace nada::misc {

    /// Reads a file with a given path and adds each line to a container via 'push_back'.
    void zeilen_lesen(const std::string& pfad, std::vector<std::string>& liste, uint8_t min_laenge = 2);

    /** 
     * Gives you the amount of milliseconds from a fixed point in time. 
     * Does roughly the same as you'd expect from Java's `System.currentTimeMillis()`.
     */
    unsigned long long millis();

    /**
     * Provides a color (rgb 32 bit) with a green tint at a positive ratio > 1, red tint at < 1.
     * 0 = maximum red; 1 = maximum green.
     * For example get_color_from_ratio(5, 5); gives maximum green (0x00FF00).
     * For example get_color_from_ratio(0, 5); gives maximum red   (0xFF0000).
     * For example get_color_from_ratio(2, 4); gives something roughly in the middle - 0x888800 or so.
     */
    uint32_t get_color_from_ratio(unsigned numerator, unsigned denominator);

    /**
    * Returns all file paths (relative) from a given folder (relative) with a given file extension (case sensitive).
    * @param folder Path to folder.
    * @param extension e.g. "png", "jpg", "dat", "json" etc. (without '.' before that)
    * @note file extension Case-sensitive.
    */
    std::vector<std::string> all_files(const std::string& folder, std::string extension);

    /// Compares via < the objects that are hidden behind their pointers.
    template <typename T>
    bool ptr_compare(const T* o1, const T* o2) { return *o1 < *o2; }

}
