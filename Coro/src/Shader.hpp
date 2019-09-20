#pragma once

#include <glad/glad.h>

#include <string>

namespace Coro {

class Shader {
   private:
    unsigned _id;
    GLenum _type;
    bool _deleted = false;

   public:
    Shader(const std::string& path, GLenum type);
    ~Shader();

    unsigned GetId() const { return _id; }
    bool IsDeleted() const { return _deleted; }
    void Delete();
};

}  // namespace Coro