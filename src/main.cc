#include "app.hh"

int main(void) {
	App app;

	while (app.run) {
		app.Update();
	}

	return 0;
}
