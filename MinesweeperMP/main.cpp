#include "Application.h"
#include <cstdlib>
#include "Board.h"

int main() {
	srand(time(nullptr));

	mMp::Application application;
	application.init();
	application.run();


	return 0;
}
