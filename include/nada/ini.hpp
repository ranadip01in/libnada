#pragma once

#include "misc.hpp"

namespace nada {
class Ini final {

public:

    explicit Ini(const std::string& ini_path) : ini_file(ini_path) {}

    bool good() const { if (std::ifstream in(ini_file); in.good()) return true; return false; }

    std::string get(const std::string& key, const std::string& fallback = "") {
        const std::string val = get_value_from_file(ini_file, key);
        if (val.empty()) return fallback;
        return val;
    }

    template<typename T>
    T get_int(const std::string& key, T fallback = T{}) {
        const std::string val = get_value_from_file(ini_file, key);
        if (val.empty()) return fallback;
        return std::atoll(val.c_str());
    }

    template<typename T>
    T get_float(const std::string& key, T fallback = T{}) {
        const std::string val = get_value_from_file(ini_file, key);
        if (val.empty()) return fallback;
        return std::atof(val.c_str());
    }

private:

    /**
     * Liefert aus einer INI Datei (mit = als Trennzeichen) den Wert zu gegebenem Schlüssel (key).
     * @note Liefert einen leeren String, bei Lesefehlern und nicht vorhandenen Keys.
     * @note Liefert bei mehrfach vorkommenden Keys den Wert des letzten.
     * @note Verwendet einen Thread-sicheren Cache.
     * @param datei Pfad zur INI-Datei.
     * @param key Auszulesender Schlüssel.
     * @return Wert des Schlüssels.
     */
    static std::string get_value_from_file(const std::string& datei, const std::string& key);

    /**
     * Liefert aus einer INI Datei (mit = als Trennzeichen) die durch `token` getrennte Werte
     * zu gegebenem Schlüssel (key) als `std::vector<std::string>`.
     *
     * @param datei Pfad zur INI-Datei.
     * @param key Schlüssel in der INI, aus der die Werte gelesen werden.
     * @param token Trennzeichen der Werteliste.
     * @param append Ist `append` gegeben, wird dieser Wert allen Strings angehängt.
     * @return Liste der ausgelesenen Werte als String.
     */
    static std::vector<std::string> get_value_as_vector_from_file(const std::string& datei, const std::string& key, const char token, const std::string& append = "");

    std::string ini_file;

};}
