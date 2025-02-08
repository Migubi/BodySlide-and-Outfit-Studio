#include "LinuxDir.h"

std::string get_exepath() {
    char dir[PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", dir, sizeof(dir)-1);
    if (len != -1) {
      dir[len] = '\0';
      return std::string(dir);
    }
}

std::string get_selfpathBS() {
	std::string selfpath = get_exepath();
  for (int i = 0;i<9;i++ ) {
    selfpath.pop_back();
  }
  return std::string(selfpath);
}

std::string get_selfpathOS() {
	std::string selfpath = get_exepath();
  for (int i = 0;i<13;i++ ) {
    selfpath.pop_back();
  }
  return std::string(selfpath);
}
