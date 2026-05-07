#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encryption.h"
#include "search_engine.h"
#include "file_merge.h"
#include "file_organizer.h"

// Demonstrating Structures as per Syllabus
struct FileOperation {
    char inputFile[256];
    char outputFile[256];
    int operationType;
};

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void handleEncryptionMenu() {
    struct FileOperation op;
    op.operationType = 1;
    char key[256];
    int shift, method, action;

    printf("\n--- File Encryption / Decryption ---\n");
    printf("Enter Input File path: ");
    scanf("%255s", op.inputFile);
    printf("Enter Output File path: ");
    scanf("%255s", op.outputFile);

    printf("Choose Method: 1 for XOR, 2 for Shift: ");
    scanf("%d", &method);

    printf("Choose Action: 1 for Encrypt, 2 for Decrypt: ");
    scanf("%d", &action);

    bool success = false;
    if (method == 1) {
        printf("Enter XOR Key: ");
        scanf("%255s", key);
        success = processFileXOR(op.inputFile, op.outputFile, key);
    } else if (method == 2) {
        printf("Enter Shift Value (integer): ");
        scanf("%d", &shift);
        success = processFileShift(op.inputFile, op.outputFile, shift, action == 1);
    } else {
        printf("Invalid method selected.\n");
        return;
    }

    if (success) {
        printf("Operation completed successfully!\n");
    } else {
        printf("Operation failed. Check file paths.\n");
    }
}

void handleSearchMenu() {
    char filePath[256];
    char query[256];

    printf("\n--- Text File Search Engine ---\n");
    printf("Enter Text File path: ");
    scanf("%255s", filePath);
    printf("Enter word/phrase to search: ");
    scanf("%255s", query);

    char *results = searchFile(filePath, query);
    printf("\n--- Search Results ---\n");
    printf("%s", results);
    
    // Demonstrating Dynamic Memory Allocation and freeing
    free(results);
}

void handleMergeMenu() {
    int count;
    printf("\n--- File Merge Utility ---\n");
    printf("How many files do you want to merge? ");
    scanf("%d", &count);

    if (count < 2) {
        printf("You need at least 2 files to merge.\n");
        return;
    }

    const char **files = (const char **)malloc(count * sizeof(char *));
    for (int i = 0; i < count; i++) {
        char *buffer = (char *)malloc(256 * sizeof(char));
        printf("Enter File %d path: ", i + 1);
        scanf("%255s", buffer);
        files[i] = buffer;
    }

    char outputFile[256];
    printf("Enter Output File path: ");
    scanf("%255s", outputFile);

    if (mergeFiles(files, count, outputFile)) {
        printf("Files merged successfully into %s!\n", outputFile);
    } else {
        printf("File merge failed.\n");
    }

    for (int i = 0; i < count; i++) {
        free((void *)files[i]);
    }
    free(files);
}

void handleOrganizerMenu() {
    char targetDir[256];
    printf("\n--- File Organizer Tool ---\n");
    printf("Enter target directory path to organize: ");
    scanf("%255s", targetDir);

    if (organizeDirectory(targetDir)) {
        printf("Directory organized successfully!\n");
    } else {
        printf("Failed to organize directory. Check if path exists.\n");
    }
}

int main() {
    int choice;

    do {
        printf("\n=========================================\n");
        printf("         FILE UTILITY SYSTEM             \n");
        printf("=========================================\n");
        printf("1. File Encryption / Decryption\n");
        printf("2. Text File Search Engine\n");
        printf("3. File Merge Utility\n");
        printf("4. File Organizer Tool\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                handleEncryptionMenu();
                break;
            case 2:
                handleSearchMenu();
                break;
            case 3:
                handleMergeMenu();
                break;
            case 4:
                handleOrganizerMenu();
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please select between 1-5.\n");
        }
    } while (choice != 5);

    return 0;
}
