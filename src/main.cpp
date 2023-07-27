#include <iostream>
#include <string>
#include <curl/curl.h>

// Колбэк-функция для записи полученных данных
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

int main() {
    // Инициализируем библиотеку libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    // Создаем хэндл для выполнения HTTP запроса
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize libcurl." << std::endl;
        return 1;
    }

    // Устанавливаем URL для GET запроса
    std::string url = "https://api.example.com/data";
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Устанавливаем функцию обратного вызова для записи данных
    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Выполняем HTTP GET запрос
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "Failed to perform HTTP request: " << curl_easy_strerror(res) << std::endl;
        return 1;
    }

    // Выводим полученные данные
    std::cout << "Response: " << response << std::endl;

    // Освобождаем ресурсы
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}
