#pragma once
#include "UiComponent.h"
#include "Defines.h"

namespace mMp {
	using namespace std;
	using namespace sf;

	class MpHostSetupUi : public UiComponent
	{
		Action backAction;
		Action1P<string> createServerAction;
		Action startGameAction;

		Box::Ptr mainBox;
		Frame::Ptr nameFrame;
		Entry::Ptr nameEntry;
		Box::Ptr playerBox;

		bool doCreateServer;

	public:
		MpHostSetupUi(Desktop& desktop, Action backAction, Action1P<string> createServerAction,
			Action startGameAction);

		void addName(string name);

		void update(float seconds) override;
	protected:
		void initWindow() override;
	private:
		void createServer();
		void triggerCreateServer();
	};
}
