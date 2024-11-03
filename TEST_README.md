## Testing with CTest

`dotenv` includes tests to verify the functionality of loading and retrieving environment variables. These tests are written using **Google Test** and can be run using **CTest**.

### Setting Up Tests

To run the tests, make sure you have **Google Test** installed or use CMake to download it automatically. Here’s an example CMake setup that downloads Google Test as an external dependency for testing purposes.

1. In your project directory, create a `tests/` folder with a `CMakeLists.txt` file.

2. Inside `tests/CMakeLists.txt`, add the following:

   ```cmake
   # Download and configure Google Test
   include(FetchContent)
   FetchContent_Declare(
     googletest
     URL https://github.com/google/googletest/archive/release-1.12.1.zip
   )
   set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
   FetchContent_MakeAvailable(googletest)

   # Create a test executable
   add_executable(test_dotenv test_dotenv.cpp)
   target_link_libraries(test_dotenv gtest_main)
   add_test(NAME dotenvTests COMMAND test_dotenv)
   ```

3. In your main `CMakeLists.txt`, enable testing and add the `tests` directory:

   ```cmake
   enable_testing()
   add_subdirectory(tests)
   ```

### Writing Tests

Create a file `test_dotenv.cpp` inside the `tests` directory to define test cases. Here’s an example:

   ```cpp
   #include "dotenv.h"
   #include <gtest/gtest.h>

   TEST(dotenvTest, LoadFromFile) {
       dotenv env(".env");
       EXPECT_EQ(env.get("DB_HOST", "default_host"), "127.0.0.1");
       EXPECT_EQ(env.get("DB_USER", "default_user"), "admin");
       EXPECT_EQ(env.get("DB_PASSWORD", "default_password"), "secret");
   }

   TEST(dotenvTest, DefaultValues) {
       dotenv env(".env");
       EXPECT_EQ(env.get("NON_EXISTENT_VAR", "default_value"), "default_value");
   }

   int main(int argc, char **argv) {
       ::testing::InitGoogleTest(&argc, argv);
       return RUN_ALL_TESTS();
   }
   ```

### Running Tests with CTest

1. **Build the Project** with CMake, which will automatically set up the test executable:

   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

2. **Run Tests** using CTest:

   ```bash
   ctest
   ```

   CTest will automatically discover and execute the tests, providing a summary of the results.

### Interpreting Results

CTest will display output indicating which tests passed or failed. Each test case will show a success message or provide details if a test failed. This feedback ensures that the `dotenv` library functions as expected across different scenarios.
