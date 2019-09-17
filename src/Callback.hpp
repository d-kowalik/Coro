#pragma once

#include <algorithm>
#include <functional>
#include <vector>

namespace pge {

template <typename... Args>
class Callback {
   public:
    using Event = std::function<void(Args...)>;

   private:
    std::vector<Event> _events;

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