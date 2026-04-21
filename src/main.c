#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

#include "../include/messages.h"
#include "../include/animation.h"

// headers dos comandos
int clear_file(const char *path);
int clear_dir(const char *path);
int find_file(const char *filename);
int find_dir(const char *dirname);

static int is_directory(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0)
        return S_ISDIR(st.st_mode);
    return 0;
}

int main(int argc, char *argv[]) {

    srand(time(NULL));

    if (argc < 3) {
        printf("Usage:\n");
        printf("  hercules --clear <file1|dir1> [file2|dir2...]\n");
        printf("  hercules --find <name>\n");
        return 1;
    }

    if (strcmp(argv[1], "--clear") == 0) {
        int status = 0;

        for (int i = 2; i < argc; i++) {
            if (is_directory(argv[i])) {
                if (clear_dir(argv[i]) != 0)
                    status = 1;
            } else {
                if (clear_file(argv[i]) != 0)
                    status = 1;
            }
        }

        return status;
    }

    if (strcmp(argv[1], "--find") == 0) {
        return find_file(argv[2]);
    }

    printf("Unknown command: %s\n", argv[1]);
    return 1;
}