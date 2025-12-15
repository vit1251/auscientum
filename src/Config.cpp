
#include <string>

#include "fsx.hpp"
#include "xdg.hpp"


std::string GetDbPath() {

    std::string app_name = "myapp";
    std::string data_dir = xdg::get_data_home() + "/" + app_name;

    fsx::ensure_directory(data_dir);

    std::string db_path = data_dir + "/" + "database.db";

    return db_path;
}
