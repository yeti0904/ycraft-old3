#ifndef YCRAFT__COMPONENTS_HH
#define YCRAFT__COMPONENTS_HH

// macros
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#define PLATFORM_WINDOWS
#elif defined(__APPLE__)
	#define PLATFORM_APPLE
#elif defined(__linux__)
	#define PLATFORM_LINUX
#elif defined(__unix__)
	#define PLATFORM_UNIX
#elif defined(__vita__)
	#define PLATFORM_VITA
#endif

// C standard headers
#include <cstdio>
#include <cstdint>
#include <cmath>
#include <ctime>
#if defined(PLATFORM_WINDOWS)
	#include <winsock2.h>
	#include <windows.h>
#else
	#include <unistd.h>
	#include <sys/stat.h>
	#if defined(PLATFORM_APPLE)
		#include <mach-o/dyld.h>
	#endif
#endif

// C++ standard headers
#include <regex>
#include <array>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <unordered_map>

// C libraries
#include <curl/curl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

// types
typedef uint16_t blockID_t;
typedef uint16_t itemID_t;
typedef uint32_t textureID_t;

// Some systems miss M_PI.

#ifndef M_PI
	#define M_PI   3.14159265358979323846264338327950288
#endif

#endif
