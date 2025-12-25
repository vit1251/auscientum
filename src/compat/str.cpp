
#include <string>
#include <sstream>
#include <iomanip>

namespace str {

    bool endsWith(const std::string& str, const std::string& suffix) {
        if (suffix.size() > str.size()) return false;
        return str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    }

    /**
     * Форматирование секунд
     *
     */
    std::string makeDuration(unsigned value) {
        // Шаг 1. Рассчеты
        std::div_t hm = std::div(value, 3600);
        unsigned hours = hm.quot;
        unsigned rem_seconds = hm.rem;
        std::div_t ms = std::div(rem_seconds, 60);
        unsigned minutes = ms.quot;
        unsigned seconds = ms.rem;
        // Шаг 2. Рендеринг
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(2) << hours;
        ss << ":";
        ss << std::setfill('0') << std::setw(2) <<minutes;
        ss << ":";
        ss << std::setfill('0') << std::setw(2) <<seconds;
        return ss.str();
    }

}
