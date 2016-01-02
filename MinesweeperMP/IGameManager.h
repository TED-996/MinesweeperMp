#pragma once
#include "Command.h"
#include "Component.h"

namespace mMp {
	class IGameManager : public Component
	{
	public:
		virtual ~IGameManager() {
		}

		virtual void postCommand(Command command) = 0;
	};
}
