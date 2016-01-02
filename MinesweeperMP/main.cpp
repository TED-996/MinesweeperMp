#include "Application.h"
#include <cstdlib>
#include <ctime>

int main() {
	srand((unsigned int) time(nullptr));

	mMp::Application application;
	application.init();
	application.run();

	return 0;
}
