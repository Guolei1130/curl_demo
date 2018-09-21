//
// Created by vipkid on 2018/9/21.
//

#ifndef UNTITLED_HTTPCALLBACK_H
#define UNTITLED_HTTPCALLBACK_H

#include <string>

using namespace std;

class HttpCallback {
public:
    void onResponse(const string &result);

    void onError(int httpCode, const string &errorMessage);
};


#endif //UNTITLED_HTTPCALLBACK_H
