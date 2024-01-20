const path = require("path");

const SWD = require(path.resolve(
  __dirname,
  "../packages/electron-swd/build/Release/SWD.node"
));

export default {
  toBottom: SWD.toBottom,
};
