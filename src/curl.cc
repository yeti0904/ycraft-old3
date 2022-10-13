#include "curl.hh"
#include "util.hh"

// write function
size_t CurlWriteFunction(char* buf, size_t size, size_t nmemb, void* userp) {
    auto fstream = static_cast <std::ofstream*>(userp);
    fstream->write(buf, nmemb * size);
    return nmemb * size;
}

CurlComponents::CurlComponents():
	handle(nullptr)
{

}

void CurlComponents::Init() {
	if (curl_global_init(CURL_GLOBAL_ALL) != 0) {
		Util::Error("curl_global_init failed");
	}

	handle = curl_easy_init();
	if (!handle) {
		Util::Error("curl_easy_init returned NULL");
	}
	Util::Log("Initialised libcurl");
}

void CurlComponents::Free() {
	curl_easy_cleanup(handle);
	curl_global_cleanup();
	Util::Log("Cleaned up libcurl");
}

void CurlComponents::Download(std::string url, std::string whereTo) {
	std::ofstream fhnd(whereTo);
	std::string   corrected = Util::CorrectURL(url);

	curl_easy_reset(handle);
	curl_easy_setopt(handle, CURLOPT_URL,           Util::CorrectURL(url).c_str());
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, CurlWriteFunction);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA,     &fhnd);
	curl_easy_setopt(handle, CURLOPT_FAILONERROR,   true);

	auto rc = curl_easy_perform(handle);
	if (rc != CURLE_OK) {
		Util::Error(
			"curl_easy_perform failed: %s\nURL: %s",
			curl_easy_strerror(rc), Util::CorrectURL(url).c_str()
		);
	}
	Util::Log("Downloaded to %s", whereTo.c_str());
}