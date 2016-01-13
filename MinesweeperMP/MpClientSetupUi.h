#pragma once
#include "UiComponent.h"

namespace mMp {
	class MpClientSetupUi : public UiComponent
	{
	public:
		MpClientSetupUi(Desktop& desktop);

	protected:
		void initWindow() override;
	};
}
