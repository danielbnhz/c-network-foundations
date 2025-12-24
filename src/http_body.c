#include "http_body.h"
#include <string.h>

int extract_http_body(const char *request, char *body, int max_len) {
    const char *separator = "\r\n\r\n";
    char *body_start = strstr(request, separator);

    if (!body_start) {
        return -1;
    }

    body_start += strlen(separator);

    strncpy(body, body_start, max_len - 1);
    body[max_len - 1] = '\0';

    return 0;
}
