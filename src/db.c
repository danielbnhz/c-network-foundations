#include "db.h"
#include <sqlite3.h>
#include <stdio.h>
#include <time.h>

static sqlite3 *db = NULL;

int db_init(void) {
    if (sqlite3_open("data.db", &db) != SQLITE_OK) {
        fprintf(stderr, "DB open error: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    const char *schema_sql =
        "CREATE TABLE IF NOT EXISTS posts ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "path TEXT NOT NULL,"
        "body TEXT NOT NULL,"
        "created_at INTEGER NOT NULL"
        ");";

    char *errmsg = NULL;
    if (sqlite3_exec(db, schema_sql, NULL, NULL, &errmsg) != SQLITE_OK) {
        fprintf(stderr, "Schema error: %s\n", errmsg);
        sqlite3_free(errmsg);
        return -1;
    }

    return 0;
}

void db_close(void) {
    if (db) {
        sqlite3_close(db);
        db = NULL;
    }
}

int db_insert_post(const char *path, const char *body) {
    if (!db || !path || !body) {
        return -1;
    }

    const char *sql =
        "INSERT INTO posts (path, body, created_at) "
        "VALUES (?, ?, ?);";

    sqlite3_stmt *stmt = NULL;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Prepare failed: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_text(stmt, 1, path, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, body, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 3, (sqlite3_int64)time(NULL));

    int rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Insert failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    return 0;
}
