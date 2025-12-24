#include "log.h"
#include <stdio.h>
#include <time.h>

void log_post_sql(const char *path, const char *body) {
    time_t now = time(NULL);
    fprintf(stderr,
        "[%ld] SQL INSERT posts (path='%s', body='%s')\n",
        now,
        path,
        body
    );
}
