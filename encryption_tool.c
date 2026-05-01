#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define BUFFER_SIZE 4096
#define KEY_LENGTH 16

// Function Prototypes
void clearInputBuffer();
void stripNewline(char *str);
void generateRandomKey(char *keyBuffer, size_t length);
bool processFileXOR(const char *inputFile, const char *outputFile, const char *key);
bool processFileShift(const char *inputFile, const char *outputFile, int shift, bool encrypt);

int main() {
    int choice;
    char inputPath[256];
    char outputPath[256];
    char key[KEY_LENGTH + 1];
    char userKey[256];
    int shiftValue = 42; // Arbitrary shift value for method 2

    // Seed the random number generator
    srand((unsigned int)time(NULL));

    while (1) {
        printf("\n========================================\n");
        printf("    FILE ENCRYPTION & DECRYPTION TOOL   \n");
        printf("========================================\n");
        printf("1. Encrypt File (XOR Method)\n");
        printf("2. Decrypt File (XOR Method)\n");
        printf("3. Encrypt File (Shift Method)\n");
        printf("4. Decrypt File (Shift Method)\n");
        printf("5. Exit\n");
        printf("Select an option: ");

        if (scanf("%d", &choice) != 1) {
            printf("[Error] Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (choice == 5) {
            printf("Exiting application. Goodbye.\n");
            break;
        }

        if (choice >= 1 && choice <= 4) {
            printf("Enter the full path of the source file: ");
            fgets(inputPath, sizeof(inputPath), stdin);
            stripNewline(inputPath);

            printf("Enter the full path for the output file: ");
            fgets(outputPath, sizeof(outputPath), stdin);
            stripNewline(outputPath);
        }

        switch (choice) {
            case 1:
                generateRandomKey(key, KEY_LENGTH);
                printf("\n[ALERT] Generating secure key...\n");
                printf("----------------------------------------\n");
                printf("YOUR ENCRYPTION KEY: %s\n", key);
                printf("SAVE THIS NOW. IT WILL NOT BE STORED.\n");
                printf("----------------------------------------\n");
                
                if (processFileXOR(inputPath, outputPath, key)) {
                    printf("[Success] File encrypted successfully using XOR.\n");
                }
                break;

            case 2:
                printf("Enter your decryption key: ");
                fgets(userKey, sizeof(userKey), stdin);
                stripNewline(userKey);
                
                if (processFileXOR(inputPath, outputPath, userKey)) {
                    printf("[Success] File decrypted successfully using XOR.\n");
                }
                break;

            case 3:
                printf("\n[ALERT] Encrypting using Shift Method (Fixed Key)...\n");
                if (processFileShift(inputPath, outputPath, shiftValue, true)) {
                    printf("[Success] File encrypted successfully using Shift.\n");
                }
                break;

            case 4:
                printf("\n[ALERT] Decrypting using Shift Method...\n");
                if (processFileShift(inputPath, outputPath, shiftValue, false)) {
                    printf("[Success] File decrypted successfully using Shift.\n");
                }
                break;

            default:
                printf("[Error] Invalid selection.\n");
                break;
        }
    }
    return 0;
}

// Empties the stdin buffer to prevent infinite loops on bad input
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// Removes the trailing \n left by fgets
void stripNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Generates a random alphanumeric string
void generateRandomKey(char *keyBuffer, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t charsetSize = sizeof(charset) - 1;
    for (size_t i = 0; i < length; i++) {
        keyBuffer[i] = charset[rand() % charsetSize];
    }
    keyBuffer[length] = '\0';
}

// XOR Encryption/Decryption Core Logic
bool processFileXOR(const char *inputFile, const char *outputFile, const char *key) {
    FILE *fin = fopen(inputFile, "rb");
    if (!fin) {
        printf("[Error] Could not open source file: %s\n", inputFile);
        return false;
    }

    FILE *fout = fopen(outputFile, "wb");
    if (!fout) {
        printf("[Error] Could not create output file: %s\n", outputFile);
        fclose(fin);
        return false;
    }

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

// Shift Encryption/Decryption Core Logic
bool processFileShift(const char *inputFile, const char *outputFile, int shift, bool encrypt) {
    FILE *fin = fopen(inputFile, "rb");
    if (!fin) {
        printf("[Error] Could not open source file: %s\n", inputFile);
        return false;
    }

    FILE *fout = fopen(outputFile, "wb");
    if (!fout) {
        printf("[Error] Could not create output file: %s\n", outputFile);
        fclose(fin);
        return false;
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead;
    
    // Reverse shift if decrypting
    if (!encrypt) {
        shift = -shift;
    }

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