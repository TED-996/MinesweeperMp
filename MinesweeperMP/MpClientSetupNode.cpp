#include "MpClientSetupNode.h"
#include "MpClientSetupUi.h"

namespace mMp {
	MpClientSetupNode::MpClientSetupNode(Desktop& sfgDesktop)
		: MenuNode(sfgDesktop, make_shared<MpClientSetupUi>(sfgDesktop)){
	}

}
