#include "include/dotenv.h"
#include <iostream>

int main() {
 

    dotenv env(".env");

    // Access variables

    std::string x_apikey  = env.get("X_APIKEY", "defaultxyz");
    std::string y_apikey = env.get("Y_APIKEY", "defaultabc");

    std::string db_host = env.get("DB_HOST", "localhost");
    std::string db_user = env.get("DB_USER", "root");
    std::string db_password = env.get("DB_PASSWORD", "");

    std::cout << "x_apikey: " << x_apikey << std::endl;
    std::cout << "y_apikey: " << y_apikey << std::endl;

    std::cout << "Database Host: " << db_host << std::endl;
    std::cout << "Database User: " << db_user << std::endl;
    std::cout << "Database Password: " << db_password << std::endl;

    return 0;

}
