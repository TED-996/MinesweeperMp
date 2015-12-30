#pragma once
#include <functional>

namespace mMp {
	typedef std::function<void()> Action;
	
	template<typename T>
	using Action1P = std::function<void(T)>;

	namespace ct {
		const int WindowWidth = 800;
		const int WindowHeight = 600;
	}

	enum Direction
	{
		Up,
		UpRight,
		Right,
		DownRight,
		Down,
		DownLeft,
		Left,
		UpLeft
	};
}
