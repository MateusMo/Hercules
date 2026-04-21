#include "../../include/messages.h"
#include "../../include/animation.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

#define RESET "\033[0m"
#define GOLD  "\033[1;33m"
#define CYAN  "\033[1;36m"
#define GREEN "\033[1;32m"
#define DIM   "\033[2m"

// ── helpers ───────────────────────────────────────────────────────────────────

// ".txt"      -> extensão pura
// "config"    -> sem extensão (busca parcial)
// "config.c"  -> nome com extensão (match exato)
static int is_pure_extension(const char *s) {
    return s[0] == '.' && strlen(s) > 1 && strchr(s + 1, '.') == NULL;
}

static void build_glob(const char *term, char *glob, size_t size) {
    if (is_pure_extension(term)) {
        snprintf(glob, size, "*%s", term);          // .txt  -> *.txt
    } else if (strchr(term, '.') != NULL) {
        snprintf(glob, size, "%s", term);           // main.c -> main.c (exato)
    } else {
        snprintf(glob, size, "*%s*", term);         // config -> *config*
    }
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

    const char *type_label;
    const char *type_color;

    if (S_ISDIR(st.st_mode)) {
        type_label = "DIR ";
        type_color = GOLD;
    } else {
        type_label = "FILE";
        type_color = GREEN;
    }

    // tamanho legível
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

// type_filter: 'f' = só arquivos, 'd' = só dirs, 0 = ambos
// search_path: NULL = busca em / com exclusões padrão
int find_file_ex(const char *term, char type_filter, const char *search_path) {

    find_animation(term);

    char glob[256];
    build_glob(term, glob, sizeof(glob));

    const char *base = search_path ? search_path : "/";

    const char *exclusions =
        search_path ? "" :
        " -not -path \"/proc/*\""
        " -not -path \"/sys/*\""
        " -not -path \"/dev/*\""
        " -not -path \"/run/*\""
        " -not -path \"/snap/*/\"";

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
    int found = 0;
    int count = 0;

    while (fgets(path, sizeof(path), fp)) {
        found = 1;
        count++;
        print_result(path);
    }

    pclose(fp);
    printf("\n");

    if (!found) {
        int msg = rand() % 4 + 1;
        find_fail_messages(msg, term);
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