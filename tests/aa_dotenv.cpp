#include "dotenv.h"
#include <gtest/gtest.h>
#include <iostream>
#include <cstdlib>

TEST(LoadEnvTest, CheckEnvironment) {
    // Print all environment variables for debugging
    std::cout << "Environment Variables:" << std::endl;
    extern char **environ;
    for (char **env = environ; *env != nullptr; ++env) {
        std::cout << *env << std::endl;
    }
    SUCCEED();  // Just to mark this test as passed
}
