#include <iostream>
#include <curl/curl.h>

int main()
{
	CURL* curl;
	CURLcode res;

	curl = curl_easy_init();
	if (curl == NULL)
	{
		std::cout << "HTTP request failed!";
		return -1;
	}

	curl_easy_setopt(curl, CURLOPT_URL, "https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key=$YOUR_API_KEY");

	res = curl_easy_perform(curl);

	if (res != CURLE_OK)
	{
		std::cout << "Error: " << curl_easy_strerror(res);
		return -1;
	}

	curl_easy_cleanup(curl);

	return 0;
}