#include <stdio.h>

#define RESET "\033[0m"
#define RED   "\033[1;31m"
#define GREEN "\033[1;32m"
#define GOLD  "\033[1;33m"
#define CYAN  "\033[1;36m"

void success_messages(int message, const char *str) {
    switch (message) {
        case 1:
            printf(GREEN "[✓] File removed with the strength of Hercules: %s\n" RESET, str);
            break;

        case 2:
            printf(GOLD "[⚡] Divine cleansing complete: %s no longer exists.\n" RESET, str);
            break;

        case 3:
            printf(CYAN "[☀] The gods approve the removal of: %s\n" RESET, str);
            break;

        case 4:
            printf(GREEN "[✔] A demigod-worthy task: %s eliminated.\n" RESET, str);
            break;

        case 5:
            printf(GOLD "[🏛] The temple is cleaner after removing: %s\n" RESET, str);
            break;

        case 6:
            printf(CYAN "[🌀] Nothing resists Hercules’ will: %s has been erased.\n" RESET, str);
            break;

        case 7:
            printf(GREEN "[✓] Mission accomplished: %s destroyed.\n" RESET, str);
            break;

        case 8:
            printf(GOLD "[⚔] Enemy defeated: %s shall not return.\n" RESET, str);
            break;

        case 9:
            printf(CYAN "[☁] Only ashes remain of: %s\n" RESET, str);
            break;

        default:
            printf(GREEN "[✓] Operation completed: %s\n" RESET, str);
            break;
    }
}

void fail_messages(int message, const char *str) {
    switch (message) {
        case 1:
            printf(RED "[✗] Failed to remove: %s\n" RESET, str);
            break;

        case 2:
            printf(RED "[☠] Not even Hercules could destroy: %s\n" RESET, str);
            break;

        case 3:
            printf(RED "[⚠] The gods prevented removal of: %s\n" RESET, str);
            break;

        case 4:
            printf(RED "[✗] File protected by the Titans: %s\n" RESET, str);
            break;

        case 5:
            printf(RED "[🔥] Attempt failed, %s remains intact.\n" RESET, str);
            break;

        case 6:
            printf(RED "[⛓] Chains prevent destruction of: %s\n" RESET, str);
            break;

        case 7:
            printf(RED "[💀] Fate denied for: %s\n" RESET, str);
            break;

        case 8:
            printf(RED "[⚡] Insufficient power to eliminate: %s\n" RESET, str);
            break;

        case 9:
            printf(RED "[🗿] %s remains unshaken.\n" RESET, str);
            break;

        default:
            printf(RED "[✗] Error processing: %s\n" RESET, str);
            break;
    }

    perror("Reason");
}