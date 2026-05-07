#include "file_merge.h"
#include <stdio.h>

bool mergeFiles(const char** inputFiles, int fileCount, const char* outputFile) {
    FILE* fout = fopen(outputFile, "wb");
    if (!fout) return false;

    for (int i = 0; i < fileCount; i++) {
        FILE* fin = fopen(inputFiles[i], "rb");
        if (fin) {
            char buffer[4096];
            size_t bytesRead;
            while ((bytesRead = fread(buffer, 1, sizeof(buffer), fin)) > 0) {
                fwrite(buffer, 1, bytesRead, fout);
            }
            fclose(fin);
        } else {
            fclose(fout);
            remove(outputFile);
            return false;
        }
    }
    fclose(fout);
    return true;
}
