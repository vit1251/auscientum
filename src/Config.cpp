
#include <string>

#include "fsx.hpp"
#include "xdg.hpp"


std::string GetDbPath() {

    std::string app_name = "auscientum"; // TODO - вынести в константу
    std::string data_dir = xdg::get_data_home() + "/" + app_name;

    fsx::ensure_directory(data_dir);

    std::string db_path = data_dir + "/" + "database.db"; // TODO - вынести в константу

    return db_path;
}
