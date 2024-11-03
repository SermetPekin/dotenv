include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_dotenv test_dotenv.cpp)

target_link_libraries(test_dotenv gtest_main)

add_test(NAME dotenvTests COMMAND test_dotenv)
