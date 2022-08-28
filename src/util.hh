#ifndef YCRAFT_UTIL_HH
#define YCRAFT_UTIL_HH

#include "_components.hh"

namespace Util {
	std::string CurrentTime();
	void        Log(const char* format, ...);
	std::string GetExecutableLocation();
	std::string DirName(std::string path);
	double      Clamp(double x, double min, double max);
}

#endif
