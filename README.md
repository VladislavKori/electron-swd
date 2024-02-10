<br />
<div align="center">
    <p>Electron-SWD - Set The Window Down</p>
</div>
<p align="center">
    <b>Electron add-on for setting the window down by z-index</b>
</p>

## Available on

- Windows

## Installation

```
npm install electron-swd
```

## Usage

```js
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
    // get the hwnd Buffer and pass it to the toBottom parameters
    toBottom(win.getNativeWindowHandle());
  }
});

// ...
```

If you want the window to always be set lower than everyone else, create the following code for yourself

```js
win.on("focus", () => {
  toBottom(win.getNativeWindowHandle());
});
```
