#pragma once
#include "MenuNode.h"
#include "Application.h"

namespace mMp {
	class GameMenuNode : public MenuNode
	{
	public:
		GameMenuNode(Desktop& desktop, Action closeAction);
	};
}
