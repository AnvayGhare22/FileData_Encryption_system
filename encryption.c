#include "encryption.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

void generateRandomKey(char *keyBuffer, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t charsetSize = sizeof(charset) - 1;
    for (size_t i = 0; i < length; i++) {
        keyBuffer[i] = charset[rand() % charsetSize];
    }
    keyBuffer[length] = '\0';
}

bool processFileXOR(const char *inputFile, const char *outputFile, const char *key) {
    FILE *fin = fopen(inputFile, "rb");
    if (!fin) return false;

    FILE *fout = fopen(outputFile, "wb");
    if (!fout) { fclose(fin); return false; }

    size_t keyLen = strlen(key);
    size_t keyIndex = 0;
    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, fin)) > 0) {
        for (size_t i = 0; i < bytesRead; i++) {
            buffer[i] ^= key[keyIndex];
            keyIndex = (keyIndex + 1) % keyLen;
        }
        fwrite(buffer, 1, bytesRead, fout);
    }
    fclose(fin);
    fclose(fout);
    return true;
}

bool processFileShift(const char *inputFile, const char *outputFile, int shift, bool encrypt) {
    FILE *fin = fopen(inputFile, "rb");
    if (!fin) return false;

    FILE *fout = fopen(outputFile, "wb");
    if (!fout) { fclose(fin); return false; }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead;
    
    if (!encrypt) shift = -shift;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, fin)) > 0) {
        for (size_t i = 0; i < bytesRead; i++) {
            buffer[i] = (unsigned char)(buffer[i] + shift);
        }
        fwrite(buffer, 1, bytesRead, fout);
    }
    fclose(fin);
    fclose(fout);
    return true;
}
