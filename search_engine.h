#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

// Searches for 'query' in 'filePath'. 
// Allocates and returns a formatted string containing the results. 
// The caller is responsible for freeing the returned string.
char* searchFile(const char* filePath, const char* query);

#endif // SEARCH_ENGINE_H
