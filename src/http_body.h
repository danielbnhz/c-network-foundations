#ifndef HTTP_BODY_H
#define HTTP_BODY_H

int extract_http_body(const char *request, char *body, int max_len);

#endif
