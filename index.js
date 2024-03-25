const path = require("path");
const os = require("os");

const SWD = require('./build/Release/SWD')

module.exports = {
  toBottom: (hwndBuffer) => {
    if (os.type() !== "Windows_NT") {
      throw new Error("This function not avaible on ", os.type());
    } else {
      try {
        const hwndBigInt = BigInt(`0x${hwndBuffer.toString("hex")}`);
        SWD.toBottom(hwndBigInt);
      } catch (err) {
        console.log(err);
        return;
      }
    }
  },
};
