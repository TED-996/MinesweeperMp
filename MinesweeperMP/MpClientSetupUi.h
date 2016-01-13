#pragma once
#include "UiComponent.h"
#include "Defines.h"

namespace mMp {
	using namespace std;
	class MpClientSetupUi : public UiComponent
	{
		Action backAction;
		Action1P<string> setNameAction;
		Action1P<int> selectServerAction;

		Box::Ptr mainBox;
		Frame::Ptr nameFrame;
		Entry::Ptr nameEntry;
		Box::Ptr serverBox;

		int serverCount;

	public: 
		MpClientSetupUi(Desktop& desktop, Action backAction, Action1P<string> setNameAction,
			Action1P<int> selectServerAction);

		void addServer(string name);
	protected:
		void initWindow() override;
	private:
		void selectServer(int index);
	};
}
