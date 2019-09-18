#include <memory>

namespace Coro {

template <typename T>
using Ref = std::shared_ptr<T>;
}
