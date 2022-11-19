import { Window } from "win-control";
import robot from "robotjs";
import { readdir } from "node:fs/promises";
import path, * as fs from "node:path";
import { sleep } from "./sleep";

class Photographer {
  private readonly WINDOW_TITLE = " EOS 500D";
  private readonly LISTEN_FOLDER = path.join("C:", "gaming");
  private readonly CAMERA_CAPTURE_ATTEMPTS = 5;
  private readonly READ_FOLDER_ATTEMPTS = 10;

  private findEosUtilityWindow(): Window {
    const window = Window.getByTitle(this.WINDOW_TITLE);
    if (!window) {
      throw new Error(
        "Could not find Canon EOS Utility. Please turn the bloody camera on."
      );
    }

    return window;
  }

  async takePhoto() {
    for (let i = 0; i < this.CAMERA_CAPTURE_ATTEMPTS; i++) {
      const window = this.findEosUtilityWindow();

      const windowPosition = window.getDimensions();
      window.setForeground();

      // Move mouse to the EOS Utility Window
      robot.moveMouse(windowPosition.left, windowPosition.top);

      // Move mouse to shutter button.
      robot.moveMouse(windowPosition.left + 214, windowPosition.top + 86);

      await sleep(1000);

      robot.mouseToggle("down");

      await sleep(500);

      robot.mouseToggle("up");

      await sleep(1000);
      for (let j = 0; j < this.READ_FOLDER_ATTEMPTS; j++) {
        await sleep(500);
        const files = await readdir(this.LISTEN_FOLDER);

        for (const file of files) {
          if (file.toLowerCase().endsWith(".jpg")) {
            return path.resolve(this.LISTEN_FOLDER, files[0]);
          }
        }
      }
    }

    throw new Error("Failed to take a photo");
  }
}

export { Photographer };
