#include <memory>

namespace pge {

template <typename T>
using Ref = std::shared_ptr<T>;
}
