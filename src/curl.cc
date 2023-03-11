#include "util.hh"
#include "curl.hh"

#if defined(PLATFORM_VITA)
	#include <psp2/net/net.h>
	#include <psp2/net/netctl.h>
	#include <psp2/net/http.h>
	#include <psp2/io/fcntl.h>
	#include <psp2/sysmodule.h>
#endif


// write function
size_t CurlWriteFunction(char* buf, size_t size, size_t nmemb, void* userp) {
	#if !defined(PLATFORM_VITA)
		auto fstream = static_cast <std::ofstream*>(userp);
		fstream->write(buf, nmemb * size);
		return nmemb * size;
	#else
		size_t written = sceIoWrite(*(int*) userp, buf ,size*nmemb);
  		return written;
	#endif
}

CurlComponents::CurlComponents(): handle(nullptr) {

}

void CurlComponents::Init() {
	#if defined(PLATFORM_VITA)
		sceSysmoduleLoadModule(SCE_SYSMODULE_NET);

		SceNetInitParam netInitParam;
		int size = 1*1024*1024;
		netInitParam.memory = malloc(size);
		netInitParam.size = size;
		netInitParam.flags = 0;
		sceNetInit(&netInitParam);

		sceNetCtlInit();

		sceSysmoduleLoadModule(SCE_SYSMODULE_HTTP);

		sceHttpInit(1*1024*1024);
	#endif

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
	#if defined(PLATFORM_VITA)
		// VITA: Terminate both the NET and HTTP modules
		sceNetCtlTerm();
		sceNetTerm();
		sceSysmoduleUnloadModule(SCE_SYSMODULE_NET);

		sceHttpTerm();
		sceSysmoduleUnloadModule(SCE_SYSMODULE_HTTP);
	#endif

	curl_easy_cleanup(handle);
	curl_global_cleanup();
	Util::Log("Cleaned up libcurl");
}

void CurlComponents::Download(std::string url, std::string whereTo) {
	#if defined(PLATFORM_VITA)
		int fhnd = sceIoOpen(whereTo.c_str(), SCE_O_WRONLY | SCE_O_CREAT, 0777);
	#else
		std::ofstream fhnd(whereTo);
	#endif

	std::string   corrected = Util::CorrectURL(url);

	curl_easy_reset(handle);
	curl_easy_setopt(handle, CURLOPT_URL,           Util::CorrectURL(url).c_str());
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, CurlWriteFunction);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA,     &fhnd);
	curl_easy_setopt(handle, CURLOPT_FAILONERROR,   true);
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(handle, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
	curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT, 10L);
	curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);

	auto rc = curl_easy_perform(handle);
	if (rc != CURLE_OK) {
		Util::Error(
			"curl_easy_perform failed: %s\nURL: %s",
			curl_easy_strerror(rc), Util::CorrectURL(url).c_str()
		);
	}

	Util::Log("Downloaded to %s", whereTo.c_str());

	#if defined(PLATFORM_VITA)
		sceIoClose(fhnd);
	#else
		fhnd.close();
	#endif
}
