#pragma once
#include<SFML/Graphics.hpp>

namespace mMp {
	using namespace sf;

	class Drawable
	{
	public:
		virtual ~Drawable() {
		}

		virtual void draw(RenderTarget &renderTarget, RenderStates renderStates) = 0;
	};
}
