#ifndef DB_H
#define DB_H

int db_init(void);
int db_insert_post(const char *path, const char *body);
void db_close(void);

#endif
