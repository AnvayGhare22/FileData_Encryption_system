#ifndef FILE_MERGE_H
#define FILE_MERGE_H

#include <stdbool.h>

// Combines multiple input files into a single output file.
// Returns true on success, false on failure.
bool mergeFiles(const char** inputFiles, int fileCount, const char* outputFile);

#endif // FILE_MERGE_H
