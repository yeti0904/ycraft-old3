#ifndef YCRAFT_MENUBASE_HH
#define YCRAFT_MENUBASE_HH

#include "_components.hh"
#include "types.hh"

class MenuBase {
	public:
		// variables
		// functions
		MenuBase();
		virtual void HandleEvent(SDL_Event& event);
		virtual void Reset();
};

#endif
