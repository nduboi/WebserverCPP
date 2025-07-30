# C++ HTTP Web Server 🚀

A lightweight, high-performance HTTP web server built in C++ using Boost.Asio for asynchronous networking and TOML11 for configuration management.

## 🌟 Features

- **HTTP/1.1 Support**: Handles standard HTTP requests (GET, POST, UPDATE, DELETE)
- **Static File Serving**: Efficiently serves static files from a configurable directory
- **Smart Content-Type Detection**: Automatically detects file types including:
  - HTML, CSS, JavaScript
  - Images (JPEG, PNG, GIF, SVG)
  - Documents (PDF)
  - Videos (MP4)
  - Plain text and binary files
- **Configurable via TOML**: Easy configuration through TOML files
- **Error Handling**: Proper HTTP status codes (200, 403, 404, 500)
- **Asynchronous I/O**: Built on Boost.Asio for high performance
- **Cross-Platform**: Compatible with Linux, Windows, and macOS

## 📋 Prerequisites

Before building and running the server, ensure you have:

- **C++20 compatible compiler** (GCC 10+, Clang 10+, or MSVC 2019+)
- **CMake 3.31 or higher**
- **Boost Libraries** (Boost.Asio)
  ```bash
  # Ubuntu/Debian
  sudo apt-get install libboost-all-dev
  
  # CentOS/RHEL/Fedora
  sudo yum install boost-devel
  # or
  sudo dnf install boost-devel
  
  # macOS (with Homebrew)
  brew install boost
  ```

## 🔧 Installation & Build

1. **Clone the repository**:
   ```bash
   git clone <your-repo-url>
   cd webserverCPP
   ```

2. **Create build directory**:
   ```bash
   mkdir build
   cd build
   ```

3. **Configure and build**:
   ```bash
   cmake ..
   make
   ```

   Or using the existing build directory:
   ```bash
   cd my-build-debug
   make
   ```

## ⚙️ Configuration

The server uses a TOML configuration file (`config.toml`) for easy customization.

### Configuration File Structure

Create or modify the `config.toml` file in the project root:

```toml
# Server Configuration
port = 8080                    # Port number the server will listen on
static_root = "./www"          # Directory containing static files to serve
```

### Configuration Parameters

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `port` | integer | 8080 | The port number on which the server listens for incoming connections |
| `static_root` | string | "./www" | Root directory for static files. Can be absolute or relative path |

### Configuration Examples

**Basic Web Server**:
```toml
port = 8080
static_root = "./www"
```

**Custom Port and Directory**:
```toml
port = 3000
static_root = "/var/www/html"
```

**Development Setup**:
```toml
port = 8000
static_root = "./public"
```

### Configuration Notes

- If the configuration file is missing, the server will use default values
- If a configuration key is missing, the server will fall back to the default value for that parameter
- The server will log configuration errors to stderr but continue running with defaults
- Relative paths in `static_root` are resolved relative to the server's working directory

## 🚀 Usage

1. **Start the server**:
   ```bash
   ./nduboiServer
   ```
   
   The server will start and display:
   ```
   Serveur TCP démarré sur le port: 8080. En attente de connexions...
   ```

2. **Access the server**:
   Open your web browser and navigate to:
   ```
   http://localhost:8080
   ```

3. **Serve your files**:
   Place your static files in the `www` directory (or the directory specified in `static_root`)

## 📁 Project Structure

```
webserverCPP/
├── main.cpp                 # Application entry point
├── CMakeLists.txt          # Main CMake configuration
├── config.toml             # Server configuration file
├── README.md               # This file
├── server/                 # Server library source code
│   ├── CMakeLists.txt      # Server library CMake config
│   ├── HttpServer.hpp      # HTTP server class declaration
│   ├── HttpServer.cpp      # HTTP server implementation
│   ├── Utils.hpp           # Utility functions declaration
│   ├── Utils.cpp           # Utility functions implementation
│   └── Exception.hpp       # Custom exception classes
├── www/                    # Default static files directory
│   └── index.html          # Default homepage
└── toml11/                 # TOML parsing library (submodule)
```

## 🔌 API Reference

### HTTP Methods Supported

- **GET**: Retrieve static files
- **POST**: Accepted but not yet implemented
- **UPDATE**: Accepted but not yet implemented  
- **DELETE**: Accepted but not yet implemented

### HTTP Status Codes

- **200 OK**: File successfully served
- **403 Forbidden**: File exists but cannot be read (permission denied)
- **404 Not Found**: Requested file does not exist
- **500 Internal Server Error**: Server encountered an unexpected error

### Content-Type Detection

The server automatically detects and sets appropriate Content-Type headers:

| File Type | Content-Type |
|-----------|--------------|
| HTML | text/html |
| PDF | application/pdf |
| JPEG | image/jpeg |
| PNG | image/png |
| GIF | image/gif |
| SVG | image/svg+xml |
| MP4 | video/mp4 |
| Text files | text/plain |
| Unknown/Binary | application/octet-stream |

## 🛠️ Development

### Building for Development

```bash
# Debug build
mkdir debug-build
cd debug-build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

# Release build
mkdir release-build
cd release-build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

### Code Structure

- **HttpServer**: Main server class handling HTTP requests and responses
- **Utils**: Utility functions for file operations and configuration parsing
- **Exception**: Custom exception classes for error handling

### Adding New Routes

Currently, the server uses a simple routing mechanism in `HttpServer::_getFileUsingRoute()`. To add custom routes:

1. Modify the `_getFileUsingRoute()` method in `HttpServer.cpp`
2. Add your routing logic using a map-based approach for better scalability

## 🐛 Troubleshooting

### Common Issues

1. **Port already in use**:
   ```
   Exception: bind: Address already in use
   ```
   - Change the port in `config.toml`
   - Kill the process using the port: `lsof -ti:8080 | xargs kill`

2. **Permission denied for files**:
   ```
   HTTP 403 Forbidden
   ```
   - Check file permissions: `chmod 644 yourfile.html`
   - Ensure the static_root directory is readable

3. **File not found**:
   ```
   HTTP 404 Not Found
   ```
   - Verify the file exists in the static_root directory
   - Check the file path and spelling

### Debugging

Enable debug output by examining the server logs printed to stdout/stderr.

## 📝 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m ':gitmoji: Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📞 Support

If you encounter any issues or have questions:

1. Check the troubleshooting section above
2. Review the configuration settings
3. Open an issue on GitHub with detailed information about your problem

---

**Made with ❤️ using C++20, Boost.Asio, and TOML11**
