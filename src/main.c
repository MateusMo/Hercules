#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

#include "../include/messages.h"
#include "../include/animation.h"

int clear_file(const char *path);
int clear_dir(const char *path);
int find_file(const char *filename);
int find_file_ex(const char *term, char type_filter, const char *search_path);

static int is_directory(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0)
        return S_ISDIR(st.st_mode);
    return 0;
}

static void print_usage(void) {
    printf("Usage:\n");
    printf("  hercules --clear <file|dir> [file2|dir2...]\n");
    printf("  hercules --find  <term> [-p <path>] [-t f|d]\n");
    printf("\n");
    printf("--find options:\n");
    printf("  -p <path>   limit search to a specific directory (default: /)\n");
    printf("  -t f        files only\n");
    printf("  -t d        directories only\n");
    printf("\n");
    printf("Examples:\n");
    printf("  hercules --find .txt\n");
    printf("  hercules --find config -p ~/Projects\n");
    printf("  hercules --find main.c -t f\n");
    printf("  hercules --find build  -t d\n");
}

int main(int argc, char *argv[]) {

    srand(time(NULL));

    if (argc < 3) {
        print_usage();
        return 1;
    }

    // ── --clear ───────────────────────────────────────────────────────────────
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

    // ── --find ────────────────────────────────────────────────────────────────
    if (strcmp(argv[1], "--find") == 0) {
        const char *term        = argv[2];
        const char *search_path = NULL;
        char        type_filter = 0;

        // parse flags opcionais após o termo
        for (int i = 3; i < argc; i++) {
            if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
                search_path = argv[++i];
            } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
                i++;
                if (strcmp(argv[i], "f") == 0)
                    type_filter = 'f';
                else if (strcmp(argv[i], "d") == 0)
                    type_filter = 'd';
                else {
                    printf("Unknown type filter: %s (use f or d)\n", argv[i]);
                    return 1;
                }
            } else {
                printf("Unknown option: %s\n", argv[i]);
                print_usage();
                return 1;
            }
        }

        return find_file_ex(term, type_filter, search_path);
    }

    printf("Unknown command: %s\n", argv[1]);
    print_usage();
    return 1;
}