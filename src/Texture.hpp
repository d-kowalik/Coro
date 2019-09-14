#pragma once

#include <string>

namespace pge {

class Texture {
   private:
    unsigned _id;

   public:
    Texture(const std::string& path, bool rgba = true);

    inline unsigned GetId() const { return _id; }
};

}  // namespace pge