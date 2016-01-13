#pragma once
#include <functional>

namespace mMp {
	typedef std::function<void()> Action;
	
	template<typename T>
	using Action1P = std::function<void(T)>;

	namespace ct {
		const int WindowWidth = 800;
		const int WindowHeight = 600;
		const int TcpPort = 57415;
		const int UdpPort = TcpPort + 1;
	}

	enum class Direction
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
