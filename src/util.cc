#include "util.hh"

std::string Util::CurrentTime() {
	time_t rawtime;
	struct tm* timeinfo;
	
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	
	char buffer[80];
	strftime(buffer, 80, "%H:%M:%S", timeinfo);
	
	return std::string(buffer);
}

void Util::Log(const char* format, ...) {
	va_list args;
	va_start(args, format);
	
	char* ret;
	vasprintf(&ret, format, args);
	
	va_end(args);
	
	printf("[%s] %s\n", CurrentTime().c_str(), ret);
	free(ret);
}

std::string Util::GetExecutableLocation() {
	char buffer[1024];
	#if defined(PLATFORM_LINUX)
		ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer));
		if (len != -1) {
			buffer[len] = '\0';
			return std::string(buffer);
		}
	#elif defined(PLATFORM_APPLE)
		uint32_t size = sizeof(buffer);
		if (_NSGetExecutablePath(buffer, &size) == 0) {
			return string(buffer);
		}
	#elif defined(PLATFORM_WINDOWS)
		GetModuleFileName(NULL, buffer, sizeof(buffer));
		return string(buffer);
	#endif
	
	return "";
}

std::string Util::DirName(std::string path) {
	return path.substr(0, path.rfind('/'));
}

double Util::Clamp(double x, double min, double max) {
	return std::max(min, std::min(x, max));
}

std::string Util::Trim(const std::string& str) {
	// an improved version of this https://stackoverflow.com/a/58773060
	return std::regex_replace(str, std::regex("^ +| +$"),"");
}

std::vector <std::string> Util::GetFilesInDirectory(std::string path) {
	std::vector <std::string> ret;
	for (auto& entry : std::filesystem::directory_iterator(path)) {
		if (entry.is_regular_file()) {
			ret.push_back(entry.path());
		}
	}
	return ret;
}

std::string Util::BaseName(std::string path) {
	size_t pos = path.rfind('/');
	return pos == std::string::npos? path : path.substr(pos + 1);
}
