#pragma once

#include <glad/glad.h>

#include <string>
#include "Core.hpp"

namespace Coro {

class Shader {
   private:
    unsigned _id;
    GLenum _type;
    bool _deleted = false;

   public:
    Shader(const std::string& path, GLenum type);
    ~Shader();
	static Ref<Shader> Make(const std::string& path, GLenum type);

    unsigned GetId() const { return _id; }
    bool IsDeleted() const { return _deleted; }
    void Delete();
};

}  // namespace Coro