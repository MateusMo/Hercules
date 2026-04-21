#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/messages.h"
#include "../../include/animation.h"

int clear_file(const char *path) {
    hercules_animation(path);

    int result = remove(path);

    if (result == 0) {
        int msg = rand() % 9 + 1;
        success_messages(msg, path);
    } else {
        fail_messages(1, path);
    }

    return result;
}

int clear_dir(const char *path) {
    hercules_animation(path);

    // tenta remover direto (funciona se estiver vazio)
    if (remove(path) == 0) {
        int msg = rand() % 9 + 1;
        dir_success_messages(msg, path);
        return 0;
    }

    // diretório não vazio: usa rm -rf
    char command[1024];
    snprintf(command, sizeof(command), "rm -rf \"%s\"", path);

    int result = system(command);

    if (result == 0) {
        int msg = rand() % 9 + 1;
        dir_success_messages(msg, path);
    } else {
        dir_fail_messages(1, path);
    }

    return result;
}