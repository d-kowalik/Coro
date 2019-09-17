#pragma once

#include <vector>

#include <algorithm>
#include <functional>

namespace pge {

template <typename... Args>
class Callback {
   public:
    using Event = std::function<void(Args...)>;

   private:
    std::vector<Event> _events;

    template <typename T, typename... U>
    size_t GetAddress(std::function<T(U...)> f) {
        typedef T(fnType)(U...);
        fnType** fnPointer = f.template target<fnType*>();
        return (size_t)*fnPointer;
    }

   public:
    void operator()(Args... args) const {
        for (const auto& event : _events) {
            event(args...);
        }
    }

    Callback<Args...>& operator+=(const Event& rhs) {
        _events.push_back(rhs);
        return *this;
    }
};

}  // namespace pge