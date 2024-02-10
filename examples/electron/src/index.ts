import { app, BrowserWindow, ipcMain } from "electron";
import { toBottom } from "electron-swd";

let win: BrowserWindow | null = null;
const createWindow = () => {
  win = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      nodeIntegration: true,
      contextIsolation: false,
    },
  });

  win.loadFile("../index.html");
};

ipcMain.handle("to-bottom", (_) => {
  if (win !== null) {
    toBottom(win.getNativeWindowHandle());
  }
});

app.whenReady().then(() => {
  createWindow();
});

app.on("window-all-closed", () => {
  if (process.platform !== "darwin") app.quit();
});
