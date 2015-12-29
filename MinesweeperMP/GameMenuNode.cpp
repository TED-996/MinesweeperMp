#include "GameMenuNode.h"
#include "GameUi.h"


namespace mMp {
	GameMenuNode::GameMenuNode(Desktop& desktop, Action closeAction)
		: MenuNode(desktop, make_shared<GameUi>(closeAction, desktop)) {
	}
}
