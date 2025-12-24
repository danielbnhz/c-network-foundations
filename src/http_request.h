#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#define MAX_METHOD   8
#define MAX_PATH     256
#define MAX_VERSION  16

typedef struct {
    char method[MAX_METHOD];
    char path[MAX_PATH];
    char version[MAX_VERSION];
} http_request_t;

/**
 * Parses an HTTP request line.
 * Returns 0 on success, -1 on failure.
 */
int parse_http_request(const char *raw, http_request_t *req);

#endif
