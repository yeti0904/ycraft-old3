#ifndef YCRAFT_CURL_HH
#define YCRAFT_CURL_HH

#include "_components.hh"

class CurlComponents {
	public:
		CURL* handle;

		CurlComponents();
		void        Init();
		void        Free();
		void        Download(std::string url, std::string whereTo);
		std::string Curl(std::string url);
};

#endif