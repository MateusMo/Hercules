#include <stdio.h>

#define RESET "\033[0m"
#define RED   "\033[1;31m"
#define GREEN "\033[1;32m"
#define GOLD  "\033[1;33m"
#define CYAN  "\033[1;36m"

// ─── Arquivo: sucesso/falha ───────────────────────────────────────────────────

void success_messages(int message, const char *str) {
    switch (message) {
        case 1:  printf(GREEN "[✓] File removed with the strength of Hercules: %s\n" RESET, str); break;
        case 2:  printf(GOLD  "[⚡] Divine cleansing complete: %s no longer exists.\n" RESET, str); break;
        case 3:  printf(CYAN  "[☀] The gods approve the removal of: %s\n" RESET, str); break;
        case 4:  printf(GREEN "[✔] A demigod-worthy task: %s eliminated.\n" RESET, str); break;
        case 5:  printf(GOLD  "[🏛] The temple is cleaner after removing: %s\n" RESET, str); break;
        case 6:  printf(CYAN  "[🌀] Nothing resists Hercules' will: %s has been erased.\n" RESET, str); break;
        case 7:  printf(GREEN "[✓] Mission accomplished: %s destroyed.\n" RESET, str); break;
        case 8:  printf(GOLD  "[⚔] Enemy defeated: %s shall not return.\n" RESET, str); break;
        case 9:  printf(CYAN  "[☁] Only ashes remain of: %s\n" RESET, str); break;
        default: printf(GREEN "[✓] Operation completed: %s\n" RESET, str); break;
    }
}

void fail_messages(int message, const char *str) {
    switch (message) {
        case 1:  printf(RED "[✗] Failed to remove: %s\n" RESET, str); break;
        case 2:  printf(RED "[☠] Not even Hercules could destroy: %s\n" RESET, str); break;
        case 3:  printf(RED "[⚠] The gods prevented removal of: %s\n" RESET, str); break;
        case 4:  printf(RED "[✗] File protected by the Titans: %s\n" RESET, str); break;
        case 5:  printf(RED "[🔥] Attempt failed, %s remains intact.\n" RESET, str); break;
        case 6:  printf(RED "[⛓] Chains prevent destruction of: %s\n" RESET, str); break;
        case 7:  printf(RED "[💀] Fate denied for: %s\n" RESET, str); break;
        case 8:  printf(RED "[⚡] Insufficient power to eliminate: %s\n" RESET, str); break;
        case 9:  printf(RED "[🗿] %s remains unshaken.\n" RESET, str); break;
        default: printf(RED "[✗] Error processing: %s\n" RESET, str); break;
    }

    perror("[system]");
}

// ─── Diretório: sucesso/falha ─────────────────────────────────────────────────

void dir_success_messages(int message, const char *str) {
    switch (message) {
        case 1:  printf(GREEN "[✓] Directory razed to the ground: %s\n" RESET, str); break;
        case 2:  printf(GOLD  "[⚡] The realm has been purged: %s is no more.\n" RESET, str); break;
        case 3:  printf(CYAN  "[☀] Olympus rejoices — %s has been swept away.\n" RESET, str); break;
        case 4:  printf(GREEN "[✔] The labyrinth collapsed: %s obliterated.\n" RESET, str); break;
        case 5:  printf(GOLD  "[🏛] The pillars fell: %s wiped from existence.\n" RESET, str); break;
        case 6:  printf(CYAN  "[🌀] Not a stone remains of: %s\n" RESET, str); break;
        case 7:  printf(GREEN "[✓] The Augean stables are clean: %s removed.\n" RESET, str); break;
        case 8:  printf(GOLD  "[⚔] Hercules cleared the path: %s is gone.\n" RESET, str); break;
        case 9:  printf(CYAN  "[☁] Dust and legend: %s has vanished.\n" RESET, str); break;
        default: printf(GREEN "[✓] Directory removed: %s\n" RESET, str); break;
    }
}

void dir_fail_messages(int message, const char *str) {
    switch (message) {
        case 1:  printf(RED "[✗] Failed to remove directory: %s\n" RESET, str); break;
        case 2:  printf(RED "[☠] Even the gods cannot flatten: %s\n" RESET, str); break;
        case 3:  printf(RED "[⚠] The Titans guard this realm: %s\n" RESET, str); break;
        case 4:  printf(RED "[✗] The labyrinth stands defiant: %s\n" RESET, str); break;
        case 5:  printf(RED "[🔥] Hercules retreats — %s endures.\n" RESET, str); break;
        case 6:  printf(RED "[⛓] The directory is bound by fate: %s\n" RESET, str); break;
        case 7:  printf(RED "[💀] Destiny denied its destruction: %s\n" RESET, str); break;
        case 8:  printf(RED "[⚡] Insufficient power to raze: %s\n" RESET, str); break;
        case 9:  printf(RED "[🗿] %s stands unshaken.\n" RESET, str); break;
        default: printf(RED "[✗] Error removing directory: %s\n" RESET, str); break;
    }

    perror("[system]");
}

// ─── Find: sucesso/falha ──────────────────────────────────────────────────────

void find_success_messages(int message, const char *str) {
    switch (message) {
        case 1:  printf(GREEN "[🔍] Location discovered: %s" RESET, str); break;
        case 2:  printf(GOLD  "[📍] Hercules has found it: %s" RESET, str); break;
        case 3:  printf(CYAN  "[🧭] Path revealed: %s" RESET, str); break;
        case 4:  printf(GREEN "[✓] Target located: %s" RESET, str); break;
        case 5:  printf(GOLD  "[🏹] Search complete, found: %s" RESET, str); break;
        default: printf(GREEN "[FOUND] %s" RESET, str); break;
    }
}

void find_fail_messages(int message, const char *str) {
    switch (message) {
        case 1:  printf(RED "[❌] Nothing found for: %s\n" RESET, str); break;
        case 2:  printf(RED "[🌑] Even Hercules cannot locate: %s\n" RESET, str); break;
        case 3:  printf(RED "[🕳] Lost in the abyss: %s\n" RESET, str); break;
        case 4:  printf(RED "[⚠] Search failed for: %s\n" RESET, str); break;
        default: printf(RED "[NOT FOUND] %s\n" RESET, str); break;
    }

    perror("[find]");
}