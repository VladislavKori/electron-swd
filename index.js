const hello = require("./build/Release/hello");
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

  win.loadFile("index.html");
};

ipcMain.on("to-bottom", (_) => {
  const hbuf = win.getNativeWindowHandle().readUInt32LE().toString(16);
  console.log(hbuf);

  hello.sayHello(hbuf);
});

app.whenReady().then(() => {
  createWindow();
});
