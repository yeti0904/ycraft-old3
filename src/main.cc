
#include "app.hh"
#include "util.hh"

int main(int, char**) {
	#ifndef DEBUG_EXCEPTION
	try {
	#endif
		App app;

		while (app.run) {
			app.Update();
		}
	#ifndef DEBUG_EXCEPTION
	}
	catch (std::exception& error) {
		Util::Error(error.what());
	}
	#endif
	return 0;
}
