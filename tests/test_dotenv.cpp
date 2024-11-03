#include "dotenv.h"

#include <gtest/gtest.h>

TEST(dotenvTest, LoadFromFile) {

//    bool isGithubActions = std::getenv("GITHUB_ACTIONS") != nullptr;
    bool isGithubActions = std::getenv("GITHUB_WORKSPACE") != nullptr;


  std::string file_name("../../.env" ) ; 
  if (isGithubActions) {
    file_name  = ".env"  ; 
  } 

    dotenv env(file_name );   

    // Test getting values from .env file
    EXPECT_EQ(env.get("DB_HOST", "default_host"), "127.0.0.1");
    EXPECT_EQ(env.get("DB_USER", "default_user"), "admin");
    EXPECT_EQ(env.get("DB_PASSWORD", "default_password"), "secret");

    // Test getting a missing value with a default
    // EXPECT_EQ(env.get("NON_EXISTENT_VAR", "default_value"), "default_value");
}

TEST(dotenvTest, SetVariable) {
    dotenv env(".env");

    // Set a new variable and retrieve it
    env.set("NEW_VAR", "new_value");
    EXPECT_EQ(env.get("NEW_VAR"), "new_value");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
