#include <nada/ini.hpp>
#include <nada/str.hpp>
#include <chrono>

std::string nada::Ini::get_value_from_file(const std::string& datei, const std::string& key) {
    const char token = '=';
    thread_local std::unordered_map<std::string, std::unordered_map<std::string, std::string>> ini_cache;
    if (!ini_cache.count(datei)) {
        ini_cache[datei];
        if (std::ifstream in(datei); in.good()) {
            for (std::string zeile; std::getline(in, zeile);) {
                if (zeile.find(token) != std::string::npos) {
                    const std::vector<std::string>& tokens = nada::str::tokenize(zeile, token);
                    if (tokens.size() >= 2) ini_cache[datei][tokens[0]] = tokens[1];
                }
            }
        } 
        //else nada::Log::err() << "misc::" << __func__ <<  datei << " nicht lesbar.\n"; // TODO
    }
    return ini_cache[datei][key];
}

std::vector<std::string>
nada::Ini::get_value_as_vector_from_file(const std::string& datei, const std::string& key, const char token, const std::string& append) {
    std::vector<std::string> tokens = nada::str::tokenize(nada::Ini::get_value_from_file(datei, key), token);
    if (!append.empty()) for (auto& t : tokens) t.append(append);
    return tokens;
}
