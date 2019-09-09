#include <glad/glad.h>

#include <string>

namespace pge {

class Shader {
   private:
    unsigned _id;
    GLenum _type;
    bool _deleted;

   public:
    Shader(const std::string& path, GLenum type);
    ~Shader();

    const unsigned GetId() const { return _id; }
    const bool IsDeleted() const { return _deleted; }
    void Delete();
};

}  // namespace pge