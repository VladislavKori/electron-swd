"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const electron_1 = require("electron");
const swd_custom_1 = __importDefault(require("swd-custom"));
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
        const hwndBuffer = win.getNativeWindowHandle();
        swd_custom_1.default.toBottom(hwndBuffer);
    }
});
electron_1.app.whenReady().then(() => {
    createWindow();
});
electron_1.app.on("window-all-closed", () => {
    if (process.platform !== "darwin")
        electron_1.app.quit();
});
