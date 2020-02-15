#ifndef __STRINGUTILS_HPP__
#define __STRINGUTILS_HPP__


#include <string>

std::string lastPathElement(const std::string &filename) {
    if (filename.empty()) {
        return {};
    }

    auto len = filename.length();
    auto index = filename.find_last_of("/\\");

    if (index == std::string::npos) {
        return filename;
    }

    if (index + 1 >= len) {

        len--;
        index = filename.substr(0, len).find_last_of("/\\");

        if (len == 0) {
            return filename;
        }

        if (index == 0) {
            return filename.substr(1, len - 1);
        }

        if (index == std::string::npos) {
            return filename.substr(0, len);
        }

        return filename.substr(index + 1, len - index - 1);
    }

    return filename.substr(index + 1, len - index);
}


std::string basenameMC(const std::string &filename) {
  std::string name = lastPathElement(filename);
  size_t lastindex = name.find_last_of(".");
  return name.substr(0, lastindex);
}

#endif /* END __STRINGUTILS_HPP__ */
