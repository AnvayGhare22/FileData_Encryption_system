const { ipcRenderer } = require('electron');

// Navigation Logic
const navLinks = document.querySelectorAll('.nav-links li');
const tabContents = document.querySelectorAll('.tab-content');

navLinks.forEach(link => {
    link.addEventListener('click', () => {
        // Remove active class
        navLinks.forEach(l => l.classList.remove('active'));
        tabContents.forEach(c => c.classList.remove('active'));
        
        // Add active class to clicked
        link.classList.add('active');
        document.getElementById(link.dataset.target).classList.add('active');
    });
});

// File Browsing Logic
async function browseFile(inputId, isSave = false) {
    const options = isSave ? { properties: ['openFile', 'promptToCreate'] } : { properties: ['openFile'] };
    const paths = await ipcRenderer.invoke('open-file-dialog', options);
    if (paths && paths.length > 0) {
        document.getElementById(inputId).value = paths[0];
    }
}

async function browseDirectory(inputId) {
    const paths = await ipcRenderer.invoke('open-dir-dialog');
    if (paths && paths.length > 0) {
        document.getElementById(inputId).value = paths[0];
    }
}

// Utility Function for Displaying Messages
function showMessage(elementId, success, text) {
    const el = document.getElementById(elementId);
    el.classList.remove('hidden');
    el.textContent = text;
    el.className = 'result-msg ' + (success ? 'success-text' : 'error-text');
}

// Encryption Execution
async function runEncryption() {
    const input = document.getElementById('enc-input').value;
    const output = document.getElementById('enc-output').value;
    const method = document.getElementById('enc-method').value;
    const action = document.getElementById('enc-action').value;
    const key = document.getElementById('enc-key').value;

    if (!input || !output || !key) {
        showMessage('enc-result', false, 'Please fill in all fields.');
        return;
    }

    showMessage('enc-result', true, 'Processing...');
    
    const result = await ipcRenderer.invoke('run-command', ['encrypt', input, output, method, action, key]);
    
    if (result.success) {
        showMessage('enc-result', true, 'Success: File has been ' + action + 'ed!');
    } else {
        showMessage('enc-result', false, 'Error: ' + result.output);
    }
}

// Search Execution
async function runSearch() {
    const input = document.getElementById('search-input').value;
    const query = document.getElementById('search-query').value;
    const resultBox = document.getElementById('search-result');

    if (!input || !query) {
        resultBox.classList.remove('hidden');
        resultBox.textContent = 'Please select a file and enter a query.';
        resultBox.style.color = 'var(--error)';
        return;
    }

    resultBox.classList.remove('hidden');
    resultBox.textContent = 'Searching...';
    resultBox.style.color = 'var(--text-main)';

    const result = await ipcRenderer.invoke('run-command', ['search', input, query]);
    
    resultBox.textContent = result.output || 'No results found.';
}

// Merge Execution
let mergeFilesList = [];

async function addMergeFiles() {
    const paths = await ipcRenderer.invoke('open-file-dialog', { properties: ['openFile', 'multiSelections'] });
    if (paths && paths.length > 0) {
        mergeFilesList = mergeFilesList.concat(paths);
        renderMergeList();
    }
}

function renderMergeList() {
    const listEl = document.getElementById('merge-file-list');
    listEl.innerHTML = '';
    mergeFilesList.forEach((file, index) => {
        const div = document.createElement('div');
        div.className = 'file-item';
        // Show just the filename for brevity
        const filename = file.split('\\').pop().split('/').pop();
        div.innerHTML = `<span>${index + 1}. ${filename}</span>`;
        listEl.appendChild(div);
    });
}

async function runMerge() {
    if (mergeFilesList.length < 2) {
        showMessage('merge-result', false, 'Select at least 2 files to merge.');
        return;
    }

    // Ask for output file location via save dialog
    const output = await ipcRenderer.invoke('save-file-dialog', { title: 'Save Merged File As' });
    if (!output) {
        showMessage('merge-result', false, 'Merge cancelled.');
        return;
    }

    showMessage('merge-result', true, 'Merging...');

    const args = ['merge', output, ...mergeFilesList];
    const result = await ipcRenderer.invoke('run-command', args);

    if (result.success) {
        showMessage('merge-result', true, 'Success: Files merged successfully!');
        mergeFilesList = []; // Clear list
        renderMergeList();
    } else {
        showMessage('merge-result', false, 'Error: ' + result.output);
    }
}

// Organizer Execution
async function runOrganizer() {
    const dir = document.getElementById('org-dir').value;

    if (!dir) {
        showMessage('org-result', false, 'Please select a directory.');
        return;
    }

    showMessage('org-result', true, 'Organizing...');

    const result = await ipcRenderer.invoke('run-command', ['organize', dir]);

    if (result.success) {
        showMessage('org-result', true, 'Success: Directory organized!');
    } else {
        showMessage('org-result', false, 'Error: ' + result.output);
    }
}

// Add Enter key support globally for active tab
document.addEventListener('keydown', (e) => {
    if (e.key === 'Enter') {
        const activeTabId = document.querySelector('.nav-links li.active').dataset.target;
        if (activeTabId === 'encrypt-tab') runEncryption();
        else if (activeTabId === 'search-tab') runSearch();
        else if (activeTabId === 'merge-tab') runMerge();
        else if (activeTabId === 'organize-tab') runOrganizer();
    }
});
