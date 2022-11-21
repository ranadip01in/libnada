#include <nada/time.hpp>

#include <thread>
#include <chrono>

unsigned long long nada::time::millis() {
    const auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    return millis.count();
}

void nada::time::sleep(unsigned millis) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}
