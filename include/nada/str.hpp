#include <vector>
#include <string>
#include <algorithm>
#include <future>

namespace nada { namespace str {

    /**
     * @brief Spaltet einen String `text` in Teile auf. Zerhackt wird dort, wo `char token_sep` auftritt.
     * 
     * @param text Aufzuspaltender Text.
     * @param token_sep Tritt dieser `char` auf, wird an dieser Stelle ein neues Token begonnen.
     * @return std::vector<std::string> Die aufgespaltenden Teile. 
     * @note Nach Aufspaltung enthält keines der Teile mehr den `char token_sep`.
     */
    static std::vector<std::string> tokenize(const std::string& text, const char token_sep) {
        std::vector<std::string> teile;
        teile.reserve(4);
        size_t anfang = 0, ende;
        while ((ende = text.find(token_sep, anfang)) != std::string::npos) {
            teile.push_back(text.substr(anfang, ende - anfang));
            anfang = ende;
            anfang++;
        }
        teile.push_back(text.substr(anfang));
        return teile;
    }

    /**
     * @brief Eine einfache `replace_all`-Methode zum Ersetzen von `char`.
     * Ersetzt alle Vorkomnisse von `alt` in einem String `s` durch `neu`.
     * @param s Zu manipulierender Gesamtstring.
     * @param alt Zu ersetzender `char`.
     * @param neu Einzufügender `char` an den zu ersetzenden Stellen.
     * @note Nutzt 2 Threads bei Strings größer als 1 Mio chars.
     */
    [[gnu::hot]]
    static void replace(std::string& s, char alt, char neu) {
        if (s.size() < 1000000) std::replace(s.begin(), s.end(), alt, neu);
        else {
            const auto laenge = s.end() - s.begin();
            const auto it_mitte = s.begin() + laenge / 2;
            auto t1 = std::async(std::launch::async, [&]() { std::replace(s.begin(), it_mitte, alt, neu); } );
            auto t2 = std::async(std::launch::async, [&]() { std::replace(it_mitte,   s.end(), alt, neu); } );
            t1.get();
            t2.get();
        }
    }

    /**
     * @brief Eine für große Strings optimierte `replace_all`-Methode.
     * Ersetzt alle Vorkomnisse von `alt` in einem String `s` durch `neu`.
     * Bei großen Strings und Ersetzung mit `alt.size() != neu.size()` schneller als
     * die reguläre Replace-Methode: @see replace.
     * @param s Zu manipulierender Gesamtstring.
     * @param alt Zu ersetzender Teilstring.
     * @param neu Einzufügender String an den zu ersetzenden Stellen.
     */
    [[gnu::hot]]
    static void replace(std::string& s, const std::string& alt, const std::string& neu) {
        std::string buffer;
        if (neu.size() > alt.size()) buffer.reserve((size_t)(s.size() * 1.1 + 1));
        else buffer.reserve(s.size());
        size_t last = 0;
        for (size_t find = s.find(alt); find != std::string::npos; find = s.find(alt, last)) {
            buffer.append(s, last, find - last);
            buffer.append(neu);
            last = find + alt.size();
        }
        buffer.append(s.substr(last));
        s.swap(buffer);
    }

    /**
     * @brief Eine `replace_all`-Methode mit Abbruchfunktion.
     * Ersetzt alle Vorkomnisse von `alt` in einem String `s` durch `neu`.
     * @param s Zu manipulierender Gesamtstring.
     * @param alt Zu ersetzender Teilstring.
     * @param neu Einzufügender String an den zu ersetzenden Stellen.
     * @param max Wie oft höchstens ersetzt werden soll (-1 heißt ohne Limit).
     */
    [[gnu::hot]]
    static void replace(std::string& s, const std::string& alt, const std::string& neu, int max) {
        if (max == -1 && alt.size() != neu.size()) { // optimierte Version nutzen (für ungleich große Ersetzungen)
            replace(s, alt, neu); 
            return; 
        } 
        size_t it = 0;
        while (max && (it = s.find(alt, it)) != std::string::npos) {
            s.replace(it, alt.size(), neu);
            it += neu.size();
            if (max > 0) --max;
        }
    }

    /**
     * @brief Liefert den Text, der sich zwischen zwei bestimmten Teilstrings befindet.
     *
     * @param zeile Zu undersuchender Text.
     * @param l_sep 'Linker' Anfang des zu extrahierenden Textausschnitts als `char` oder `std::string`.
     * @param r_sep 'Rechtes' Ende des zu extrahierenden Textausschnitts als `char` oder `std::string`.
     * @return std::string Der extrahierte Textausschnitt. Leer, falls Teilstrings nicht gefunden.
     * @note Der Textausschnitt wird ohne `l_sep` und `r_sep` wiedergegeben.
     */
    template <typename T>
    static std::string get_text_zwischen(std::string zeile, const T& l_sep, const T& r_sep) {
        auto links = zeile.find(l_sep);
        if (links != std::string::npos) {
            ++links;
            const auto rechts = zeile.find(r_sep, links);
            if (rechts != std::string::npos && links < rechts)
                return {zeile.begin() + links, zeile.begin() + rechts};
            else
                return {zeile.begin() + links, zeile.end()};
        }
        return {};
    }

    /**
     * @brief Wandelt einen ANSI-String in nur Kleinbuchstaben um.
     * @param s Zu manipulierender String. 
     * @note Umlaute und Sonderzeichen könnten Probleme machen. (Nur ANSI/ASCII wird garantiert korrekt umgewandelt.)
     */
    static inline void to_lower(std::string& s) {
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    }

    /**
     * @brief Entfernt alle `c` aus `s`.
     * 
     * @param s Zu manipulierender String.
     * @param c Zu entfernender `char`.
     */
    static inline void entferne_alle(std::string&s, char c) {
        s.erase(std::remove(s.begin(), s.end(), c), s.end());
    }

    /**
     * @brief Findet die Position des n. Vorkommens von `f` in `s` (Index beginnt mit 0).
     * Werden beispielsweise die Parameter ("aaaa,bbbb,cccc,dddd,eeee", ",", 2) übergeben,
     * wird 14 zurückgegeben, also die Position des des 3. Kommatas (vgl. `std::string::find`).
     * 
     * @param s Zu durchsuchender String.
     * @param f Zu suchendes Token.
     * @param n Index des Vorkommens.
     * @param start_pos Anfangsposition für die Suche (optional).
     * @return size_t 0-indizierte Position des gefundenen Tokens, vgl. `std::string::find`.
     */
    static inline size_t find(const std::string& s, const std::string& f, unsigned n, size_t start_pos = 0) {
        for (unsigned i = 0; i < n + 1 && start_pos != std::string::npos; ++i) start_pos = s.find(f, start_pos + 1);
        return start_pos;
    }

    /**
     * @brief Findet die Position von String f in String s, jedoch erst nach Vorkommen von String a (in s).
     * Werden beispielsweise die Parameter ("hallo welt und hallo computer", "hallo", "und") übergeben,
     * wird die Position des zweiten "hallo", nämlich das nach dem "und" vorkommt, zurückgegeben.
     * 
     * @param s Zu durchsuchender String.
     * @param f Zusuchender Token (hinter a).
     * @param a Erst ab Vorkommen dieses Tokens in s wird f gesucht.
     * @return size_t Position von f in s hinter a. `std::string::npos`, wenn nicht gefunden.
     */
    static inline size_t find_after(const std::string& s, const std::string& f, const std::string& a) {
        const size_t start_pos = s.find(a);
        if (start_pos != std::string::npos) return s.find(f, start_pos);
        return start_pos;
    }


}}
