const path = require("path");
const os = require("os");

const SWD = require(path.join(__dirname, "build/Release/SWD.node"));

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
