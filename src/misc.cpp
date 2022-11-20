#include <nada/misc.hpp>
#include <nada/str.hpp>

#include <chrono>
#include <filesystem>
#include <unordered_map>

void nada::misc::read_lines(const std::string& pfad, std::vector<std::string>& liste, unsigned min_laenge) {
    std::ifstream in(pfad, std::ios::binary);
    if (in.good()) {
        for (std::string zeile; std::getline(in, zeile);) {
            if (zeile.size() >= min_laenge) {
                nada::str::remove(zeile, '\r'); // Windows workaround
                liste.push_back(zeile);
            }
        }
        //if (liste.empty()) nada::Log::err() << "Keine Elemente in " << pfad << '\n'; //TODO
    }
    //else nada::Log::err() << pfad << " konnte nicht gelesen werden.\n"; //TODO
}

uint32_t nada::misc::get_color_from_ratio(unsigned int zaehler, unsigned int nenner) {
    const float verhaeltnis = static_cast<float>(zaehler) / static_cast<float>(nenner);
    const uint8_t g = std::min(0xFF, static_cast<int>(0xFF * verhaeltnis));
    const uint8_t r = 0xFF - g;
    const uint8_t arr[4] = {r, g, 0x40, 0xFF};
    uint32_t f;
    uint8_t* p = reinterpret_cast<uint8_t*>(&f);
    std::move(&arr[0], &arr[4], p);
    return f;
}

std::vector<std::string> nada::misc::all_files(const std::string& ordner, std::string endung) {
    std::vector<std::string> dateien;
    endung = "." + endung;
    for (const auto& entry : std::filesystem::directory_iterator(ordner)) {
        if (entry.is_regular_file()) {
            const auto& dateiname = entry.path().generic_string();
            if (endung == "." || nada::str::ends_with(dateiname, endung)) dateien.push_back(dateiname);
        }
    }
    return dateien;
}

unsigned long long nada::misc::millis() {
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    return millis.count();
}
