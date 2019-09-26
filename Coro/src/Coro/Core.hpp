#pragma once

#include <memory>

namespace Coro {

	template <typename T>
	using Ref = std::shared_ptr<T>;
	
	template <typename T, typename ...Args>
	Ref<T> MakeRef(Args... args) {
		return std::make_shared<T>(args...);
	}
}
