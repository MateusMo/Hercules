#include "../../include/messages.h"
#include "../../include/animation.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Busca genérica: arquivos e diretórios com o nome dado
int find_file(const char *filename) {

    find_animation(filename);

    char command[512];
    snprintf(command, sizeof(command),
             "find ~ -name \"%s\" 2>/dev/null", filename);

    FILE *fp = popen(command, "r");
    if (!fp) {
        find_fail_messages(4, filename);
        return 1;
    }

    char path[1024];
    int found = 0;

    while (fgets(path, sizeof(path), fp)) {
        found = 1;

        int msg = rand() % 5 + 1;
        find_success_messages(msg, path);
    }

    pclose(fp);

    if (!found) {
        int msg = rand() % 4 + 1;
        find_fail_messages(msg, filename);
        return 1;
    }

    return 0;
}


int find_dir(const char *dirname) {
    return find_file(dirname);
}