#pragma once

#include <iostream>
#include <chrono>

namespace nada {

/**
 * @brief Minimalistischer Logger.
 *
 * + out() writes to std::cout
 * + err() writes to std::cerr
 * + debug() writes to std::cout, but only if DEBUG is defined.
 *
 * @example
 * Log::info() << "My " << 2 << "nd car is a " << 3.5 << " ton truck.\n" << Log::flush;
 */
class Log final {

    /**
     * Enum to handle the Log level.
     */
    enum Level {
        LOG_INFO,
        LOG_DEBUG,
        LOG_ERROR
    };

    /**
     * Invisible ctor.
     */
    explicit Log(Level level) : level(level) {}

    /**
     * Log-Level of this logger instance.
     */
    const Level level;

    /**
     * Stream to write to. `std::cout` by default.
     */
    static inline std::ostream* out_stream = &std::cout;

    /// Send an instance of this to a Log to flush its stream.
    struct Flush {};

    /// Send an instance of this to a Log to put a newline flush its stream.
    struct Endl {};

public:

    /// Send this to a Log to flush its stream.
    static const inline Flush flush;

    /// Send this to a Log to put a newline and flush its stream.
    static const inline Endl endl;

    /// Writes to std::cout in debug-builds. Does nothing in all other builds.
    static const Log& debug() noexcept {
        thread_local const Log log(LOG_DEBUG);
        return log;
    }

    /// Use `Log::err() << ...` to write errors to std::cout or your user defined stream.
    static const Log& err() noexcept {
        thread_local const Log log(LOG_ERROR);
        return log;
    }

    /// Use `Log::out() << ...` to write to std::out or your user defined stream.
    static const Log& out() noexcept {
        thread_local const Log log(LOG_INFO);
        return log;
    }

    /**
     * Writes the duration of the function call to Log's stream (only in debug mode).
     * In release mode, the function is simply executed. 
     */
    template <typename T>
    static void benchmark_debug(T&& funktion, const std::string& text) {
        #ifndef NDEBUG
            benchmark(funktion, text);
        #else
            funktion();
        #endif
    }

    /// Calls given function and logs its duration to std::out or given stream.
    template <typename T>
    static void benchmark(T&& funktion, const std::string& text) {
        const auto start = std::chrono::system_clock::now();
        funktion();
        const auto ende = std::chrono::system_clock::now();
        const std::chrono::duration<double> dauer = ende - start;
        *out_stream << text << " Duration: " << dauer.count() << "s\n";
    }

    /**
     * You can provide a user defined `ostream`.
     * Otherwise Log will use `std::cout` by default.
     */
    static void set_output(std::ostream* stream) { out_stream = stream; }

    /**
     * @brief Call this if you want `Log` to write to `std::cout`.
     * 
     * Log does this by default, but you can reset it after you
     * provided a user defined stream with `Log::set_output`.
     */
    static void to_cout() { out_stream = &std::cout; }

    /// Flushes Log's stream.
    const Log& operator<<(const Flush& f) const noexcept {
        (void) f;
        switch (level) {
            case LOG_INFO:
                *out_stream << std::flush;
                break;
            case LOG_ERROR:
                *out_stream << std::flush;
                break;
            case LOG_DEBUG:
                #ifndef NDEBUG
                *out_stream << std::flush;
                #endif
                break;
        }
        return *this;
    }

    /// Does a Newline and Flush.
    const Log& operator<<(const Endl& e) const noexcept {
        (void) e;
        switch (level) {
            case LOG_INFO:
                *out_stream << std::endl;
                break;
            case LOG_ERROR:
                *out_stream << std::endl;
                break;
            case LOG_DEBUG:
                #ifndef NDEBUG
                *out_stream << std::endl;
                #endif
                break;
        }
        return *this;
    }

    /// Logs given item to `std::cout` or a custom stream, if provided.
    template<typename T>
    const Log& operator<<(const T& item) const noexcept {
        switch (level) {
            case LOG_INFO:
                *out_stream << item;
                break;
            case LOG_ERROR:
                *out_stream << item;
                break;
            case LOG_DEBUG:
                #ifndef NDEBUG
                *out_stream << item;
                #endif
                break;
        }
        return *this;
    }

};
}
