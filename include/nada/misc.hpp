#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

/// Benutzung z.B. so: `if (static Do_Once _; _)`
struct Do_Once {
    explicit operator bool() { return std::exchange(b, false); }
    private: bool b = true;
};
#define NADA_DO_ONCE if (static Do_Once once_var; once_var)

/// Helfermethoden, die sonst in keine Kategorie passen.
namespace nada::misc {

    /// Liest eine Datei mit gegebenem Pfad ein und fügt jede Zeile in einen Container via `push_back` hinzu.
    void zeilen_lesen(const std::string& pfad, std::vector<std::string>& liste, uint8_t min_laenge = 2);

    /// Sowas wie `System.currentTimeMillis()` aus Java.
    unsigned long long millis();

    /**
     * Liefert eine Farbe mit Grünstich bei positivem Verhältnis > 1, Rotstich bei < 1.
     * 0 = maximal rot; 1 = maximal grün.
     */
    uint32_t get_farbe_nach_verhaeltnis(unsigned zaehler, unsigned nenner);

    /**
     * Liefert alle Dateipfade (relativ) aus gegebenem Ordner (relativ) mit gegebener Dateiendung (Case-Sensitiv).
     * @param endung z.B. "png", "jpg", "dat", "json" usw. (ohne '.' davor)
     * @note Dateiendung Case-sensitiv.
     */
    std::vector<std::string> alle_dateien(const std::string& ordner, std::string endung);

    /// Vergleicht via < die Objekte, die sich hinter ihren Zeigern verbergen.
    template <typename T>
    bool ptr_compare(const T* o1, const T* o2) { return *o1 < *o2; }

}
