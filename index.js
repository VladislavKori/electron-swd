const SWD = require("./build/Release/SWD");
const { BrowserWindow, app, ipcMain } = require("electron");

// console.log(hello.sayHello("sdfg"));
let win;

const createWindow = () => {
  win = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      nodeIntegration: true,
      contextIsolation: false,
      webSecurity: false,
    },
  });

  win.on("ready-to-show", () => {
    const hbuf = win.getNativeWindowHandle().readUInt32LE().toString(16);
    SWD.toBottom(hbuf);
    SWD.initListener(hbuf);
  });

  win.loadFile("index.html");
};

ipcMain.on("to-bottom", (_) => {
  const hbuf = win.getNativeWindowHandle().readUInt32LE().toString(16);
  SWD.toBottom(hbuf);
});

app.whenReady().then(() => {
  createWindow();
});
