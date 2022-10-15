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

void Util::Log(const char* format, ...) { // most of this is taken from vsprintf(3)
	size_t n = 0;
	size_t size = 0;
	char*  ret = nullptr;
	va_list ap;

	// Determine required size. 

	va_start(ap, format);
	n = vsnprintf(ret, size, format, ap);
	va_end(ap);

	if (n < 0) {
		return;
	}

	size = n + 1; // One extra byte for '\0'
	ret = (char*) malloc(size);
	if (ret == nullptr) {
		return;
	}

	va_start(ap, format);
	n = vsnprintf(ret, size, format, ap);
	va_end(ap);

	if (n < 0) {
		free(ret);
	    return;
	}
	
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
		GetModuleFileName(nullptr, buffer, sizeof(buffer));
		return std::string(buffer);
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
			ret.push_back(entry.path().string());
		}
	}
	return ret;
}

std::string Util::BaseName(std::string path) {
	size_t pos = path.rfind('/');
	return pos == std::string::npos? path : path.substr(pos + 1);
}

void Util::Error(const char* format, ...) {
	size_t n = 0;
	size_t size = 0;
	char*  ret = nullptr;
	va_list ap;

	// Determine required size. 

	va_start(ap, format);
	n = vsnprintf(ret, size, format, ap);
	va_end(ap);

	if (n < 0) {
		return;
	}

	size = n + 1; // One extra byte for '\0'
	ret = (char*) malloc(size);
	if (ret == nullptr) {
		return;
	}

	va_start(ap, format);
	n = vsnprintf(ret, size, format, ap);
	va_end(ap);

	if (n < 0) {
		free(ret);
	    return;
	}
	
	fprintf(stderr, "[ERROR] %s\n", ret);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR!", ret, nullptr);
	free(ret);
	exit(EXIT_FAILURE);
}

bool Util::IsNumber(std::string str) {
	try {
		stod(str);
	}
	catch (std::exception&) {
		return false;
	}
	return true;
}

std::string Util::CorrectURL(std::string str) {
	std::string ret;

	for (auto& ch : str) {
		switch (ch) {
			case ' ': {
				ret += "%20";
				break;
			}
			default: {
				ret += ch;
			}
		}
	}

	return ret;
}

bool Util::StringEndsWith(std::string base, std::string end) {
	// https://stackoverflow.com/a/2072890/12577005
	if (end.size() > base.size()) {
		return false;
	}
	return std::equal(end.rbegin(), end.rend(), base.rbegin());
}

std::vector <std::string> Util::GetFilesOfType(std::string path, std::string type) {
	auto                      files = Util::GetFilesInDirectory(path);
	std::vector <std::string> ret;

	for (auto& file : files) {
		if (Util::StringEndsWith(file, type)) {
			ret.push_back(file);
		}
	}

	return ret;
}

int Util::RandomRange(int min, int max) {
	return min + rand() % ((max + 1) - min);
}

float Util::FRandomRange(float min, float max) {
	return min + (float) rand() / ((float) ((float) RAND_MAX / (max - min)));
}