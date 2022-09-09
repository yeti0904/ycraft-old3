#ifndef YCRAFT_UTIL_HH
#define YCRAFT_UTIL_HH

#include "_components.hh"

namespace Util {
	std::string               CurrentTime();
	void                      Log(const char* format, ...);
	std::string               GetExecutableLocation();
	std::string               DirName(std::string path);
	double                    Clamp(double x, double min, double max);
	std::string               Trim(const std::string& str);
	std::vector <std::string> GetFilesInDirectory(std::string path);
	std::string               BaseName(std::string path);
}

#endif
