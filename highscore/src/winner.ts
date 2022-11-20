import { Storage } from "@google-cloud/storage";
import { ServiceAccountCredentials } from "google-spreadsheet";
import { readFile, rm } from "node:fs/promises";
import { Photographer } from "./Photographer";
import { IPartialScore } from "./Score";
import { Spreadsheet } from "./Spreadsheet";

const spreadsheet = new Spreadsheet();
const photographer = new Photographer();
const storage = new Storage({ keyFilename: "./serviceAccount.json" });

const winner = async (partialScore: IPartialScore) => {
  const authFile = await readFile("./serviceAccount.json", {
    encoding: "utf-8",
  });
  const authData = JSON.parse(authFile);

  let file = await photographer.takePhoto();
  console.log(file);

  const newFilename = Date.now().toString(10) + ".jpg";

  await storage.bucket("highscore-members").upload(file, {
    destination: newFilename,
  });

  console.log(newFilename);

  await rm(file);

  await spreadsheet.init(authData as ServiceAccountCredentials);
  await spreadsheet.addScore({
    ...partialScore,
    photograph: `https://storage.googleapis.com/highscore-members/${newFilename}`,
    image: "=IMAGE(INDIRECT(ADDRESS(ROW(),COLUMN()-1)))",
    timestamp: Date.now(),
  });
};

export { winner }
