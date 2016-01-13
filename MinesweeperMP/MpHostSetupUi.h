#pragma once
#include "UiComponent.h"
#include "Defines.h"

namespace mMp {
	using namespace std;
	using namespace sf;

	class MpHostSetupUi : public UiComponent
	{
		Action1P<string> createServerAction;
		Action startGameAction;

		Box::Ptr mainBox;
		Frame::Ptr nameFrame;
		Entry::Ptr nameEntry;
		Box::Ptr playerBox;

	public:
		MpHostSetupUi(Desktop& desktop, Action1P<string> createServerAction, Action startGameAction);

		void addName(string name);
	protected:
		void initWindow() override;
	private:
		void onCreateServer();
	};
}
