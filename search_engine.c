#include "search_engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 2048
#define INITIAL_RESULT_SIZE 4096

char* searchFile(const char* filePath, const char* query) {
    FILE* file = fopen(filePath, "r");
    if (!file) {
        return strdup("Error: Could not open the specified file.\r\n");
    }

    size_t currentResultSize = INITIAL_RESULT_SIZE;
    char* results = (char*)malloc(currentResultSize);
    if (!results) {
        fclose(file);
        return strdup("Error: Memory allocation failed.\r\n");
    }
    results[0] = '\0';

    char line[MAX_LINE_LENGTH];
    int lineNumber = 1;
    bool found = false;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, query) != NULL) {
            found = true;
            
            char formattedLine[MAX_LINE_LENGTH + 50];
            snprintf(formattedLine, sizeof(formattedLine), "Line %d: %s", lineNumber, line);

            if (strlen(results) + strlen(formattedLine) + 1 > currentResultSize) {
                currentResultSize *= 2;
                char* temp = (char*)realloc(results, currentResultSize);
                if (!temp) {
                    fclose(file);
                    free(results);
                    return strdup("Error: Memory reallocation failed while building results.\r\n");
                }
                results = temp;
            }
            strcat(results, formattedLine);
            
            if (formattedLine[strlen(formattedLine) - 1] != '\n') {
                 strcat(results, "\r\n");
            }
        }
        lineNumber++;
    }

    fclose(file);

    if (!found) {
        free(results);
        return strdup("No occurrences found.\r\n");
    }

    return results;
}
