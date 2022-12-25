#ifndef YCRAFT_UTIL_HH
#define YCRAFT_UTIL_HH

#include "_components.hh"
#include "types.hh"

namespace Util {
	std::string               CurrentTime();
	void                      Log(const char* format, ...);
	std::string               GetExecutableLocation();
	std::string               DirName(std::string path);
	double                    Clamp(double x, double min, double max);
	std::string               Trim(const std::string& str);
	std::vector <std::string> GetFilesInDirectory(std::string path);
	std::string               BaseName(std::string path);
	void                      Error(const char* format, ...);
	bool                      IsNumber(std::string str);
	std::string               CorrectURL(std::string str);
	bool                      StringEndsWith(std::string base, std::string end);
	std::vector <std::string> GetFilesOfType(std::string path, std::string type);
	int                       RandomRange(int min, int max);
	float                     FRandomRange(float min, float max);
	size_t                    Distance(Vec2 start, Vec2 end);
	std::tm*                  CurrentTimeInfo();
}

#endif
