#pragma once

namespace mMp {
	class Updateable
	{
	public:
		virtual void update(float seconds) = 0;

		virtual ~Updateable() {
		}
	};
}