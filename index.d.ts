interface IReturnObject {
  toBottom: (hwnd: string) => void;
  initListener: (hwnd: string) => void;
}

declare module "swd" {
  import swd from "../";

  let returnObject = {
    toBottom: swd.toBottom,
    initListener: swd.initListener,
  };

  export = returnObject;
}
