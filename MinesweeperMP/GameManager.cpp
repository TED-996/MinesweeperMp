#include "GameManager.h"

namespace mMp
{
	GameManager::GameManager(Action1P<UiEvent> postUiEventAction)
		: postUiEventAction(postUiEventAction) {
	}

	void GameManager::postCommand(Command command) {
	}
}
