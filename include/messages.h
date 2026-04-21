#ifndef HERCULES_MESSAGES_H
#define HERCULES_MESSAGES_H

// Arquivo
void success_messages(int message, const char *str);
void fail_messages(int message, const char *str);

// Diretório
void dir_success_messages(int message, const char *str);
void dir_fail_messages(int message, const char *str);

// Find
void find_success_messages(int message, const char *str);
void find_fail_messages(int message, const char *str);

#endif // HERCULES_MESSAGES_H