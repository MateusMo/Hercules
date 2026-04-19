#include <stdio.h>

#define RESET "\033[0m"
#define RED   "\033[1;31m"
#define GREEN "\033[1;32m"
#define GOLD  "\033[1;33m"
#define CYAN  "\033[1;36m"

void success_messages(int message, const char *str) {
    switch (message) {
        case 1:
            printf(GREEN "[✓] Arquivo removido com a força de Hércules: %s\n" RESET, str);
            break;

        case 2:
            printf(GOLD "[⚡] Limpeza divina concluída: %s não existe mais.\n" RESET, str);
            break;

        case 3:
            printf(CYAN "[☀] Os deuses aprovam a remoção de: %s\n" RESET, str);
            break;

        case 4:
            printf(GREEN "[✔] Trabalho digno de um semideus: %s eliminado.\n" RESET, str);
            break;

        case 5:
            printf(GOLD "[🏛] O templo está mais limpo após remover: %s\n" RESET, str);
            break;

        case 6:
            printf(CYAN "[🌀] Nada resiste à vontade de Hércules: %s foi apagado.\n" RESET, str);
            break;

        case 7:
            printf(GREEN "[✓] Missão cumprida: %s destruído.\n" RESET, str);
            break;

        case 8:
            printf(GOLD "[⚔] Inimigo derrotado: %s não retornará.\n" RESET, str);
            break;

        case 9:
            printf(CYAN "[☁] Cinzas restam de: %s\n" RESET, str);
            break;

        default:
            printf(GREEN "[✓] Operação concluída: %s\n" RESET, str);
            break;
    }
}

void fail_messages(int message, const char *str) {
    switch (message) {
        case 1:
            printf(RED "[✗] Falha ao remover: %s\n" RESET, str);
            break;

        case 2:
            printf(RED "[☠] Nem Hércules conseguiu destruir: %s\n" RESET, str);
            break;

        case 3:
            printf(RED "[⚠] Os deuses impediram a remoção de: %s\n" RESET, str);
            break;

        case 4:
            printf(RED "[✗] Arquivo protegido pelos titãs: %s\n" RESET, str);
            break;

        case 5:
            printf(RED "[🔥] Tentativa falhou, %s permanece intacto.\n" RESET, str);
            break;

        case 6:
            printf(RED "[⛓] Correntes impedem a destruição de: %s\n" RESET, str);
            break;

        case 7:
            printf(RED "[💀] Destino negado para: %s\n" RESET, str);
            break;

        case 8:
            printf(RED "[⚡] Energia insuficiente para eliminar: %s\n" RESET, str);
            break;

        case 9:
            printf(RED "[🗿] %s permanece inabalável.\n" RESET, str);
            break;

        default:
            printf(RED "[✗] Erro ao processar: %s\n" RESET, str);
            break;
    }

    perror("Motivo");
}