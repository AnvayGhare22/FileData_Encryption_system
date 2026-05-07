#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stdbool.h>
#include <stddef.h>

void generateRandomKey(char *keyBuffer, size_t length);
bool processFileXOR(const char *inputFile, const char *outputFile, const char *key);
bool processFileShift(const char *inputFile, const char *outputFile, int shift, bool encrypt);

#endif
