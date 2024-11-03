# dotenv

**dotenv** is a simple, header-only C++ library for loading environment variables from a `.env` file, similar to `dotenv` in other languages. This library allows you to set and retrieve environment variables in C++ projects without needing any external dependencies.

## Features

- Loads environment variables from a `.env` file in `KEY=VALUE` format.
- Provides functions to retrieve variables with an optional default value.
- Allows setting environment variables programmatically in the current process.
- Works across platforms (Windows, Linux, macOS).

## Installation

Since `dotenv` is a header-only library, there's no need to compile or link any external files. Simply download or clone this repository and include `dotenv.h` in your project.

## Usage

To use `dotenv`, include the `dotenv.h` header file in your C++ project. Here’s a quick example.

### Example `.env` File

Create a `.env` file with some environment variables. For example:

```
# .env
DB_HOST=127.0.0.1
DB_USER=admin
DB_PASSWORD=secret
```

### Example Code

In your C++ code, include `dotenv.h` and use `dotenv` to load and retrieve environment variables.

```cpp
#include "dotenv.h"
#include <iostream>

int main() {
    dotenv env(".env");  // Load variables from .env file

    // Retrieve variables with default values if they are not set
    std::string db_host = env.get("DB_HOST", "localhost");
    std::string db_user = env.get("DB_USER", "root");
    std::string db_password = env.get("DB_PASSWORD", "");

    std::cout << "Database Host: " << db_host << std::endl;
    std::cout << "Database User: " << db_user << std::endl;
    std::cout << "Database Password: " << db_password << std::endl;

    // Set a new environment variable within this process
    env.set("NEW_VAR", "new_value");
    std::cout << "New Variable: " << env.get("NEW_VAR") << std::endl;

    return 0;
}
```

### Compilation

Since `dotenv` is a header-only library, you don’t need to link any additional files. Compile your program as usual:

```bash
g++ main.cpp -o main
```

### How It Works

1. **Load from `.env`**: `dotenv env(".env");` loads environment variables from the specified `.env` file.
2. **Retrieve with Defaults**: `env.get("DB_HOST", "localhost");` retrieves the `DB_HOST` variable, or returns `"localhost"` if `DB_HOST` is not set.
3. **Set New Variables**: `env.set("NEW_VAR", "new_value");` sets a new variable within the current process.

### Platform Compatibility

`dotenv` uses `_putenv_s` on Windows and `setenv` on Unix-like systems to set environment variables. This ensures cross-platform compatibility, allowing you to use the same code on Windows, macOS, and Linux.


## Testing

For information on setting up and running tests for `dotenv`, please refer to the [Testing Instructions](TEST_README.md).


## License

This project is licensed under the MIT License - see the `LICENSE` file for details.

## Contributing

Contributions are welcome! Feel free to fork this repository and submit a pull request for any bug fixes or new features.

---

This `README.md` provides everything needed for someone to understand and use `dotenv` as a header-only library in their C++ project. Let me know if you’d like to add more details or sections!
