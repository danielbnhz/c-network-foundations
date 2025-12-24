#include "http_request.h"
#include <stdio.h>
#include <string.h>

int parse_http_request(const char *raw, http_request_t *req) {
    if (!raw || !req) {
        return -1;
    }

    // Parse the request line: METHOD PATH VERSION
    int matched = sscanf(
        raw,
        "%7s %255s %15s",
        req->method,
        req->path,
        req->version
    );

    if (matched != 3) {
        return -1;
    }

    return 0;
}
