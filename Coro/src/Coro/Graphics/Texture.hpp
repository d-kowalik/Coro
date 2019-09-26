#pragma once

#include <string>

namespace Coro {

class Texture {
   private:
    unsigned _id;

   public:
    Texture(const std::string& path, bool rgba = true);

    unsigned GetId() const { return _id; }
};

}  // namespace Coro