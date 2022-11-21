#pragma once

#include <string>
#include <vector>

namespace nada::fs {

    /// Reads a file with a given path and adds each line to a container via 'push_back'.
    void read_lines(const std::string& pfad, std::vector<std::string>& liste, unsigned min_laenge = 2);
    
    /**
    * Returns all file paths (relative) from this executable's working directory (relative)
     * with a given file extension (case sensitive).
     *
    * @param folder Path to folder. Relative or absolute.
    * @param extension e.g. "png", "jpg", "dat", "json" etc. (without '.' before that). Case sensitive.
    * @note File extension is Case-sensitive.
    * @note Path is given including `folder`. For example: `folder/file.extension`
    * @note '/' characters are used as path separators.
    */
    std::vector<std::string> all_files(const std::string& folder, std::string extension);

}