#include "../../include/messages.h"
#include "../../include/animation.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>

#define RESET "\033[0m"
#define GOLD  "\033[1;33m"
#define CYAN  "\033[1;36m"
#define GREEN "\033[1;32m"
#define RED   "\033[1;31m"
#define DIM   "\033[2m"

// ── helpers ───────────────────────────────────────────────────────────────────

// ".txt" -> extensão pura | "main.c" -> nome exato | "config" -> parcial
static int is_pure_extension(const char *s) {
    return s[0] == '.' && strlen(s) > 1 && strchr(s + 1, '.') == NULL;
}

static void build_glob(const char *term, char *glob, size_t size) {
    if (is_pure_extension(term))
        snprintf(glob, size, "*%s", term);           // .jpg  -> *.jpg
    else if (strchr(term, '.') != NULL)
        snprintf(glob, size, "%s", term);            // main.c -> main.c
    else
        snprintf(glob, size, "*%s*", term);          // config -> *config*
}

// resolve ~, ./ e caminhos absolutos
static const char *resolve_path(const char *input) {
    static char resolved[1024];

    if (!input) return NULL;

    if (input[0] == '~') {
        const char *home = getenv("HOME");
        if (!home) home = "";
        snprintf(resolved, sizeof(resolved), "%s%s", home, input + 1);
        return resolved;
    }

    if (input[0] == '.') {
        char cwd[512];
        if (getcwd(cwd, sizeof(cwd)))
            snprintf(resolved, sizeof(resolved), "%s/%s", cwd, input + 1);
        else
            snprintf(resolved, sizeof(resolved), "%s", input);
        return resolved;
    }

    return input;
}

// detecta Termux e valida se o storage está disponível
static const char *get_default_base(void) {
    static char path[1024];

    if (getenv("PREFIX")) {
        // ambiente Termux
        const char *home = getenv("HOME");
        if (!home) home = "";

        snprintf(path, sizeof(path), "%s/storage/shared", home);

        struct stat st;
        if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
            return path;

        // storage não foi liberado ainda
        printf(RED "\n  [!] Termux storage not found.\n" RESET);
        printf(DIM "      Run: termux-setup-storage\n\n" RESET);

        // fallback: busca só no home do Termux
        snprintf(path, sizeof(path), "%s", home);
        return path;
    }

    // Linux padrão
    return "/";
}

static void print_result(const char *path_raw) {
    char path[1024];
    strncpy(path, path_raw, sizeof(path) - 1);
    path[sizeof(path) - 1] = '\0';

    size_t len = strlen(path);
    if (len > 0 && path[len - 1] == '\n')
        path[len - 1] = '\0';

    struct stat st;
    if (stat(path, &st) != 0) {
        printf(GREEN "  [?] %s\n" RESET, path);
        return;
    }

    const char *type_label = S_ISDIR(st.st_mode) ? "DIR " : "FILE";
    const char *type_color = S_ISDIR(st.st_mode) ? GOLD   : GREEN;

    char size_buf[32];
    long long sz = (long long)st.st_size;

    if (sz < 1024)
        snprintf(size_buf, sizeof(size_buf), "%lldB", sz);
    else if (sz < 1024 * 1024)
        snprintf(size_buf, sizeof(size_buf), "%.1fK", sz / 1024.0);
    else if (sz < 1024LL * 1024 * 1024)
        snprintf(size_buf, sizeof(size_buf), "%.1fM", sz / (1024.0 * 1024));
    else
        snprintf(size_buf, sizeof(size_buf), "%.1fG", sz / (1024.0 * 1024 * 1024));

    printf("  %s[%s]" RESET " " DIM "%-8s" RESET "  %s\n",
           type_color, type_label, size_buf, path);
}

// ── núcleo ────────────────────────────────────────────────────────────────────

int find_file_ex(const char *term, char type_filter, const char *search_path) {

    find_animation(term);

    char glob[256];
    build_glob(term, glob, sizeof(glob));

    const char *base = search_path ? resolve_path(search_path) : get_default_base();

    // exclusões apenas quando buscando em / no Linux
    const char *exclusions =
        (search_path == NULL && !getenv("PREFIX")) ?
        " -not -path \"/proc/*\""
        " -not -path \"/sys/*\""
        " -not -path \"/dev/*\""
        " -not -path \"/run/*\"" : "";

    char type_flag[16] = "";
    if (type_filter == 'f')
        snprintf(type_flag, sizeof(type_flag), " -type f");
    else if (type_filter == 'd')
        snprintf(type_flag, sizeof(type_flag), " -type d");

    char command[2048];
    snprintf(command, sizeof(command),
             "find \"%s\"%s%s -iname \"%s\" 2>/dev/null",
             base, exclusions, type_flag, glob);

    FILE *fp = popen(command, "r");
    if (!fp) {
        find_fail_messages(4, term);
        return 1;
    }

    printf(CYAN "\n  Term    : " RESET "%s\n", term);
    printf(CYAN "  Pattern : " RESET "%s\n", glob);
    printf(CYAN "  Scope   : " RESET "%s\n", base);
    if (type_filter)
        printf(CYAN "  Filter  : " RESET "%s\n",
               type_filter == 'f' ? "files only" : "directories only");
    printf("\n");

    char path[1024];
    int found = 0, count = 0;

    while (fgets(path, sizeof(path), fp)) {
        found = 1;
        count++;
        print_result(path);
    }

    pclose(fp);
    printf("\n");

    if (!found) {
        find_fail_messages(rand() % 4 + 1, term);
        return 1;
    }

    printf(GREEN "  [✓] %d result(s) found.\n" RESET, count);
    return 0;
}

// ── wrappers públicos ─────────────────────────────────────────────────────────

int find_file(const char *filename) {
    return find_file_ex(filename, 0, NULL);
}

int find_dir(const char *dirname) {
    return find_file_ex(dirname, 'd', NULL);
}