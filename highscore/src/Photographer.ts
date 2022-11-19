import { Window } from "win-control";
import robot from "robotjs";
import { sleep } from "./sleep";

class Photographer {
  private findEosUtilityWindow(): Window {
    const window = Window.getByTitle(" EOS 500D");
    if (!window) {
      throw new Error(
        "Could not find Canon EOS Utility. Please turn the bloody camera on."
      );
    }

    return window;
  }

  async takePhoto() {
    const window = this.findEosUtilityWindow();
    
    const windowPosition = window.getDimensions()
    window.setForeground();

    // Move mouse to the EOS Utility Window
    robot.moveMouse(windowPosition.left, windowPosition.top);
    
    // Move mouse to shutter button.
    robot.moveMouse(windowPosition.left + 214, windowPosition.top + 86);

    await sleep(1000);

    robot.mouseToggle("down");

    await sleep(500);

    robot.mouseToggle("up");
  }
}

export { Photographer }
