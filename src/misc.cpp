#include <nada/misc.hpp>

#include <chrono>
#include <unordered_map>

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

unsigned long long nada::misc::millis() {
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    return millis.count();
}
