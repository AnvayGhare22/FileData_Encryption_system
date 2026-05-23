const { app, BrowserWindow, ipcMain, dialog } = require('electron');
const { execFile } = require('child_process');
const path = require('path');

function createWindow() {
    const win = new BrowserWindow({
        width: 1000,
        height: 700,
        title: "FileUtility System",
        webPreferences: {
            nodeIntegration: true,
            contextIsolation: false
        },
        autoHideMenuBar: true
    });

    win.loadFile(path.join(__dirname, 'index.html'));
}

app.whenReady().then(createWindow);

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') app.quit();
});

ipcMain.handle('open-file-dialog', async (event, options) => {
    const result = await dialog.showOpenDialog(options);
    return result.filePaths;
});

ipcMain.handle('open-dir-dialog', async (event) => {
    const result = await dialog.showOpenDialog({ properties: ['openDirectory'] });
    return result.filePaths;
});

ipcMain.handle('save-file-dialog', async (event, options) => {
    const result = await dialog.showSaveDialog(options);
    return result.filePath;
});

ipcMain.handle('run-command', (event, args) => {
    return new Promise((resolve) => {
        const exePath = app.isPackaged 
            ? path.join(process.resourcesPath, 'FileUtility.exe') 
            : path.join(__dirname, '..', 'FileUtility.exe');
        execFile(exePath, args, (error, stdout, stderr) => {
            let outputStr = stdout || "";
            if (error && !outputStr) {
                resolve({ success: false, output: error.message });
                return;
            }
            if (outputStr.includes('GUI_ERROR')) {
                resolve({ success: false, output: outputStr.replace('GUI_ERROR:', '').trim() });
            } else {
                resolve({ success: true, output: outputStr.replace('GUI_SUCCESS', '').trim() });
            }
        });
    });
});
