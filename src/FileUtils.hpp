#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <optional>
#include <string>
#include <vector>

namespace Coro::FileUtils {

std::optional<std::string> Read(const std::string& path) {
    std::ifstream in(path);
    if (in.is_open()) {
        in.unsetf(std::ios::skipws);
        std::string result{};
        std::copy(std::istream_iterator<char>(in),
                  std::istream_iterator<char>(), std::back_inserter(result));

        return result;
    }
    return {};
}

}  // namespace Coro::FileUtils