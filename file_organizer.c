#include "file_organizer.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>

bool organizeDirectory(const char* targetDir) {
    char searchPath[MAX_PATH];
    snprintf(searchPath, sizeof(searchPath), "%s\\*.*", targetDir);

    WIN32_FIND_DATA fd;
    HANDLE hFind = FindFirstFile(searchPath, &fd);
    if (hFind == INVALID_HANDLE_VALUE) {
        return false;
    }

    do {
        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            const char* ext = strrchr(fd.cFileName, '.');
            if (ext) {
                const char* folderName = "Others";
                if (_stricmp(ext, ".txt") == 0 || _stricmp(ext, ".pdf") == 0 || _stricmp(ext, ".doc") == 0 || _stricmp(ext, ".docx") == 0) {
                    folderName = "Documents";
                } else if (_stricmp(ext, ".jpg") == 0 || _stricmp(ext, ".jpeg") == 0 || _stricmp(ext, ".png") == 0 || _stricmp(ext, ".gif") == 0) {
                    folderName = "Images";
                } else if (_stricmp(ext, ".mp4") == 0 || _stricmp(ext, ".avi") == 0 || _stricmp(ext, ".mkv") == 0) {
                    folderName = "Videos";
                } else if (_stricmp(ext, ".mp3") == 0 || _stricmp(ext, ".wav") == 0) {
                    folderName = "Audio";
                } else if (_stricmp(ext, ".zip") == 0 || _stricmp(ext, ".rar") == 0 || _stricmp(ext, ".7z") == 0) {
                    folderName = "Archives";
                } else if (_stricmp(ext, ".c") == 0 || _stricmp(ext, ".cpp") == 0 || _stricmp(ext, ".h") == 0 || _stricmp(ext, ".py") == 0 || _stricmp(ext, ".js") == 0 || _stricmp(ext, ".html") == 0 || _stricmp(ext, ".css") == 0) {
                    folderName = "Source Code";
                } else if (_stricmp(ext, ".xls") == 0 || _stricmp(ext, ".xlsx") == 0 || _stricmp(ext, ".csv") == 0) {
                    folderName = "Spreadsheets";
                } else if (_stricmp(ext, ".ppt") == 0 || _stricmp(ext, ".pptx") == 0) {
                    folderName = "Presentations";
                } else if (_stricmp(ext, ".exe") == 0 || _stricmp(ext, ".msi") == 0 || _stricmp(ext, ".bat") == 0) {
                    folderName = "Executables";
                } else if (_stricmp(ext, ".ttf") == 0 || _stricmp(ext, ".otf") == 0) {
                    folderName = "Fonts";
                } else if (_stricmp(ext, ".obj") == 0 || _stricmp(ext, ".stl") == 0 || _stricmp(ext, ".fbx") == 0) {
                    folderName = "3D Models";
                }

                char newDirPath[MAX_PATH];
                snprintf(newDirPath, sizeof(newDirPath), "%s\\%s", targetDir, folderName);
                
                CreateDirectory(newDirPath, NULL);

                char oldFilePath[MAX_PATH];
                snprintf(oldFilePath, sizeof(oldFilePath), "%s\\%s", targetDir, fd.cFileName);

                char newFilePath[MAX_PATH];
                snprintf(newFilePath, sizeof(newFilePath), "%s\\%s", newDirPath, fd.cFileName);

                MoveFile(oldFilePath, newFilePath);
            }
        }
    } while (FindNextFile(hFind, &fd));

    FindClose(hFind);
    return true;
}
