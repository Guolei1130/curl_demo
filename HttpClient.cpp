//
// Created by vipkid on 2018/9/21.
//

#include "HttpClient.h"

HttpClient *HttpClient::sInstance;

HttpClient::HttpClient() {
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    headers = curl_slist_append(headers, "User-Agent: curl");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, string_write);
};

void HttpClient::COMMON_SET(const string &url, char *err, string &res) {
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, url.data());
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, err);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);
}

void HttpClient::addHeaders(list<char *> head) {
    if (head.empty()) {
        return;
    }
    for (list<char *>::const_iterator iter = head.begin(); iter != head.end(); iter++) {
        headers = curl_slist_append(headers, *iter);
    }
}

void HttpClient::GET(const string &url, map<string, string> *fields) {
    char error[CURL_ERROR_SIZE];
    string result;
    string newUrl(url);
    if (fields != nullptr && (!fields->empty())) {
        newUrl += "?";
        for (auto &field : *fields) {
            newUrl += field.first + "=" + field.second + "&";
        }
    }

    COMMON_SET(newUrl, error, result);
    CURLcode code = curl_easy_perform(curl);
    if (code == CURLE_OK) {
        cout << result;
    } else {
        cout << "error";
    }
    curl_easy_cleanup(curl);

}

void HttpClient::POST(const string &url, map<string, string> *formFields) {
    char error[CURL_ERROR_SIZE];
    string result;
    string fields;
    struct curl_httppost *formpost = nullptr;
    struct curl_httppost *lastptr = nullptr;
    if (formFields != nullptr && (!formFields->empty())) {
        for (auto &field : *formFields) {
            curl_formadd(
                    &formpost,
                    &lastptr,
                    CURLFORM_COPYNAME, field.first.data(),
                    CURLFORM_COPYCONTENTS, field.second.data(),
                    CURLFORM_END);
        }
    }
    COMMON_SET(url, error, result);
    curl_easy_setopt(curl, CURLOPT_POST, formpost);
    CURLcode code = curl_easy_perform(curl);
    if (code == CURLE_OK) {
//        callback.onResponse(result);
        cout << result;
    } else {
//        callback.onError(404,string(error));
        cout << "error";
    }
    curl_formfree(formpost);
    curl_easy_cleanup(curl);
}


void HttpClient::POST_BODY(const string &url, map<string, string> *body) {
    char error[CURL_ERROR_SIZE];
    string result;
    string fields;
    string postField("{");
    if (body != nullptr && (!body->empty())) {
        for (auto &field : *body) {
            postField += "\"" + field.first + "\":\"" + field.second + "\",";
        }
        postField = postField.substr(0, postField.length() - 1);
    }
    postField += "}";
    COMMON_SET(url, error, result);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
    CURLcode code = curl_easy_perform(curl);
    if (code == CURLE_OK) {
        cout << result;
    } else {
        cout << "error";
    }
    curl_easy_cleanup(curl);
}

HttpClient::~HttpClient() {
    curl_global_cleanup();
}