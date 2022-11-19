module "win-control" {
  enum AncestorFlags {
    PARENT,
    ROOT,
    ROOTOWNER,
  }

  enum WindowStates {
    HIDE,
    SHOWNORMAL,
    SHOWMINIMIZED,
    MAXIMIZE,
    SHOWMAXIMIZED,
    SHOWNOACTIVATE,
    SHOW,
    MINIMIZE,
    SHOWINNOACTIVE,
    SHOWNA,
    RESTORE,
    SHOWDEFAULT,
    FORCEMINIMIZE,
  }

  enum SWP {
    NOSIZE,
    NOMOVE,
    NOZORDER,
    NOREDRAW,
    NOACTIVATE,
    DRAWFRAME,
    FRAMECHANGED,
    SHOWWINDOW,
    HIDEWINDOW,
    NOCOPYBITS,
    NOOWNERZORDER,
    NOREPOSITION,
    NOSENDCHANGING,
    DEFERERASE,
    ASYNCWINDOWPOS,
  }

  interface IProcessorInfo {
    windowText: string;
    pid: number;
    path: string;
  }

  interface IWIndowDimensions {
    left: number;
    right: number;
    top: number;
    bottom: number;
  }

  class Window {
    static getByPid(pid: number): Window | undefined;
    static getForeground(): Window;
    static getByClassName(className: string): Window | undefined;
    static getByTitle(title: string): Window | undefined;

    constructor(hwnd: number) {}

    getParent(): Window;
    getAncestor(kindOfAncestor: AncestorFlags): Window;
    getProcessInfo(): IProcessorInfo;
    getPid(): number;
    getClassName(): string;
    getTitle(): string;
    exists(): boolean;
    isVisible(): boolean;
    getDimensions(): IWIndowDimensions;
    moveRelative(dx: number, dy: number, dw: number, dh: number): boolean;
    setShowStatus(state: WindowStates): boolean;
    setPosition(
      hwndInsertAfter: number,
      x: number,
      y: number,
      cx: number,
      cy: number,
      uFlags: SWP
    ): boolean;
    setForeground(): boolean;
    close(): boolean;
    getHwnd(): number;
  }

  export { Window, SWP, WindowStates, AncestorFlags };
}
