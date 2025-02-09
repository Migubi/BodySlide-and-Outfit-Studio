#include "LinuxDir.h"

std::string get_exepath() {
    char dir[PATH_MAX];                                                 // Char array with size PATH_MAX of <linux/limits.h>
    ssize_t len = ::readlink("/proc/self/exe", dir, sizeof(dir)-1);     // Get path of executable and the length thereof
    if (len != -1) {                                                    // If path has been successfully retrieved return path
      dir[len] = '\0';                                                  // Add null terminator
      return std::string(dir);
    }
    else {                                                              // Throw exeption otherwise
      throw std::runtime_error("get_exepath() error: couldn't get path of executable");
    }
}

std::string get_selfpath() {
    std::string path = get_exepath();
    std::size_t slash_pos = path.find_last_of("/\\");                   // Get position of "/"(Linux) or "\"(windows)
    if (slash_pos == std::string::npos) {                               // Throw exeption
        throw std::runtime_error("find_last_of returned invalid position");
    }
    std::string FinPath = path.substr(0, slash_pos + 1);                // slice of everything after"/" or "\"
    return (FinPath);
}
