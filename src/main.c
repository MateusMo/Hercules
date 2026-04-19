#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "../animation.h"
#include "../messages.h"

#define RESET "\033[0m"
#define RED   "\033[1;31m"

int clear_file(const char *str) {
    hercules_animation(str);

    int result = remove(str);

    if (result == 0) {
        // random success message(1 a 9)
        int msg = rand() % 9 + 1;
        success_messages(msg, str);
    } else {
        // error message
        fail_messages(1, str);
    }

    return result;
}

int main(int argc, char *argv[]) {

    // inicializa aleatoriedade
    srand(time(NULL));

    if (argc < 3) {
        printf("Uso:\n");
        printf("  hercules --clear <arquivo1> [arquivo2 ...]\n");
        return 1;
    }

    if (strcmp(argv[1], "--clear") == 0) {
        int status = 0;

        for (int i = 2; i < argc; i++) {
            int result = clear_file(argv[i]);

            if (result != 0) {
                status = 1;
            }
        }

        return status;
    }

    printf("Unknown command: %s\n", argv[1]);
    return 1;
}