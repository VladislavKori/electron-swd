"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const electron_1 = require("electron");
const electron_swd_1 = require("electron-swd");
let win = null;
const createWindow = () => {
    win = new electron_1.BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            nodeIntegration: true,
            contextIsolation: false,
        },
    });
    win.loadFile("../index.html");
};
electron_1.ipcMain.handle("to-bottom", (_) => {
    if (win !== null) {
        (0, electron_swd_1.toBottom)(win.getNativeWindowHandle());
    }
});
electron_1.app.whenReady().then(() => {
    createWindow();
});
electron_1.app.on("window-all-closed", () => {
    if (process.platform !== "darwin")
        electron_1.app.quit();
});
