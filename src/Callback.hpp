#pragma once

#include <algorithm>
#include <functional>
#include <vector>

namespace Coro {

template <typename... Args>
class Callback {
   public:
    using Event = std::function<void(Args...)>;

   private:
    std::vector<Event> _events;

   public:
    static size_t GetAddress(Event f) {
        typedef void(fnType)(Args...);
        fnType** fnPointer = f.template target<fnType*>();
        return (size_t)*fnPointer;
    }

    void operator()(Args... args) const {
        for (const auto& event : _events) {
            event(args...);
        }
    }

    Callback<Args...>& operator+=(const Event& rhs) {
        _events.push_back(rhs);
        return *this;
    }

    Callback<Args...>& operator-=(const Event& rhs) {
        auto it = std::find_if(
            _events.begin(), _events.end(), [&](const Event& event) {
                return Callback::GetAddress(event) == Callback::GetAddress(rhs);
            });
        if (it != _events.end()) _events.erase(it);
        return *this;
    }
};

}  // namespace Coro