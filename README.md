# 🛡️ File Utility System (CLI & GUI)

[![License: ISC](https://img.shields.io/badge/License-ISC-blue.svg)](https://opensource.org/licenses/ISC)
[![Platform: Windows](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)](#)
[![Tech: C & Electron](https://img.shields.io/badge/Tech-C%20%26%20Electron-brightgreen.svg)](#)

A high-performance, standalone desktop application that combines robust C-powered file utilities with a modern, elegant **Electron GUI**. The system offers military-grade CLI capabilities, lightweight execution, and an beautiful, intuitive glassmorphic user interface.

---

## 📸 System Architecture

The application is architected to utilize **C-programs for heavy-duty file operations** and **Electron (HTML/CSS/JS) for a responsive UI**. Communication happens seamlessly via IPC and standard CLI sub-process command execution.

```mermaid
graph TD
    User([User Interaction]) -->|Click / Input| GUI[Electron Frontend]
    GUI -->|IPC Invoke 'run-command'| MainJS[Electron main.js]
    MainJS -->|spawn execFile| Bin[FileUtility.exe]
    
    subgraph C-Backend [FileUtility.exe (C-Code)]
        Bin -->|Arg: 'encrypt'| Enc[encryption.c]
        Bin -->|Arg: 'search'| Search[search_engine.c]
        Bin -->|Arg: 'merge'| Merge[file_merge.c]
        Bin -->|Arg: 'organize'| Org[file_organizer.c]
    end
    
    Enc -->|Success / Error| Bin
    Search -->|Results / Error| Bin
    Merge -->|Success / Error| Bin
    Org -->|Success / Error| Bin
    
    Bin -->|stdout stream| MainJS
    MainJS -->|IPC Resolve| GUI
    GUI -->|Render Success / Table| User
```

---

## ✨ Features

### 1. 🔑 File Encryption / Decryption
Securely encode and decode sensitive files using customizable cryptographic algorithms:
*   **XOR Method:** Encrypts or decrypts binary stream files using a highly secure, dynamically generated 16-character alphanumeric key.
*   **Shift Method:** Uses a fast, stream-based byte shifting cipher with customizable offset limits to scramble and restore files.

### 2. 🔍 Text File Search Engine
Scan massive text files for specific keywords, phrases, or raw character sequences:
*   Returns accurate, 1-indexed line numbers where the matches occur.
*   Uses dynamic memory allocation (`malloc`/`free`) to handle search buffers efficiently.

### 3. 🗂️ File Merge Utility
Consolidate split files or merge multiple separate files into one unified document:
*   Consolidates an arbitrary number of input paths sequentially.
*   Provides safety buffers to prevent data loss or stream corruption.

### 4. 🧹 Automated File Organizer
Instantly clean up cluttered folders by categorizing files into extension-based directories:
*   **Documents:** `.txt`, `.pdf`, `.docx`, `.xlsx`, `.pptx`, `.csv`
*   **Images:** `.jpg`, `.jpeg`, `.png`, `.gif`, `.bmp`
*   **Audio:** `.mp3`, `.wav`, `.aac`, `.flac`
*   **Videos:** `.mp4`, `.mkv`, `.avi`, `.mov`
*   **Archives:** `.zip`, `.rar`, `.7z`, `.tar`, `.gz`
*   **Programs:** `.exe`, `.msi`, `.bat`, `.sh`

---

## 🛠️ Build & Installation

### Prerequisites
1.  **C-Compiler:** GCC (MinGW for Windows) installed and added to your system `PATH`.
2.  **Node.js:** Active LTS version installed (version 18+ recommended) along with `npm`.

### Backend Compilation (CLI)
To compile the high-performance C executable:
1.  Open your terminal in the repository root directory.
2.  Run the pre-configured build script:
    ```powershell
    .\build.bat
    ```
3.  Upon success, this compiles the source files into `FileUtility.exe`.

### GUI Setup & Run (Electron)
To launch the modern desktop graphical interface:
1.  Install the required node packages:
    ```bash
    npm install
    ```
2.  Launch the Electron dashboard:
    ```bash
    npm start
    ```

---

## 🚀 How to Use

### A. Standalone CLI Version
You can run the program directly in your command prompt or PowerShell:
```powershell
.\FileUtility.exe
```
Simply follow the clean, on-screen console menu to select your desired utility and enter paths.

### B. Command-Line Arguments (Integration Mode)
The executable supports direct CLI argument calling, which is leveraged by the Electron Frontend:
*   **Encryption:** `.\FileUtility.exe encrypt <inputFile> <outputFile> <xor/shift> <encrypt/decrypt> <key>`
*   **Search Engine:** `.\FileUtility.exe search <filePath> <searchQuery>`
*   **Merge Files:** `.\FileUtility.exe merge <outputFile> <file1> <file2> [file3] ...`
*   **Directory Organizer:** `.\FileUtility.exe organize <directoryPath>`

---

## 📁 Repository Structure

```text
├── gui/
│   ├── index.html        # Glassmorphic user dashboard
│   ├── styles.css        # Sleek, premium styling
│   ├── main.js          # Electron backend process & C subprocess execution
│   └── renderer.js      # Frontend interaction logic
├── encryption.c          # Encryption algorithm logic
├── encryption.h          # Encryption header declarations
├── search_engine.c       # Fast file scanning implementation
├── search_engine.h       # Search engine header declarations
├── file_merge.c          # File consolidation logic
├── file_merge.h          # File merge header declarations
├── file_organizer.c      # Extension sorting backend
├── file_organizer.h      # File organizer header declarations
├── main.c                # Central CLI entry point and CLI arg parser
├── build.bat             # Windows GCC compiler batch script
├── forge.config.js       # Electron Forge packaging configuration
├── package.json          # Node project manifest
├── .gitignore            # Clean git configuration
└── README.md             # Premium repository documentation
```

---

## 📄 License
This project is licensed under the **ISC License** - see the LICENSE details for rights and permissions.
