#ifndef HERCULES_COMMANDS_H
#define HERCULES_COMMANDS_H

int clear_file(const char *path);
int clear_dir(const char *path);

int find_file(const char *filename);
int find_dir(const char *dirname);
int find_file_ex(const char *term, char type_filter, const char *search_path);

#endif // HERCULES_COMMANDS_H