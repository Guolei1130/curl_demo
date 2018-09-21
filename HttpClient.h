//
// Created by vipkid on 2018/9/21.
//

#ifndef UNTITLED_HTTPCLIENT_H
#define UNTITLED_HTTPCLIENT_H

#include <curl/curl.h>
#include <string>
#include <list>
#include <map>
#include <iostream>

#include "HttpCallback.h"

static size_t string_write(char *ptr, size_t size, size_t nmemb, string &str) {
    size_t total = size * nmemb;
    if (total) str.append(ptr, total);
    return total;
}

using namespace std;

class HttpClient {

public:
    HttpClient();

    static HttpClient *sInstance;
    CURL *curl;
    curl_slist *headers = nullptr;

    void addHeaders(list<char *> headers);

    void COMMON_SET(const string &url,char* error,string &result);

    void GET(const string &url, map<string, string> *fields);

    void POST(const string &url, map<string, string> *formFields);

    void POST_BODY(const string &url,map<string,string> *body);

    ~HttpClient();

    static HttpClient *getInstance() {
        if (sInstance == nullptr) {
            sInstance = new HttpClient();
        }
        return sInstance;
    };

};


#endif //UNTITLED_HTTPCLIENT_H
