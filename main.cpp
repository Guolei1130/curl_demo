#include <iostream>
#include <string>
#include <curl/curl.h>
#include "HttpClient.h"
#include "HttpCallback.h"

using namespace std;

int main() {
    HttpClient *client = HttpClient::getInstance();
    client->GET(string("https://api.github.com/users/Guolei1130"), nullptr);
    return 0;
}


void testJsonString() {
    auto *body = new map<string, string>();
    body->insert(make_pair(string("key1"), string("value1")));
    body->insert(make_pair(string("key2"), string("value2")));
    body->insert(make_pair(string("key3"), string("value3")));
    string postField("{");
    if (!body->empty()) {
        for (auto &field : *body) {
            postField += "\"" + field.first + "\":\"" + field.second + "\",";
        }
        postField = postField.substr(0, postField.length() - 1);
    }
    postField += "}";

    cout << postField;
}