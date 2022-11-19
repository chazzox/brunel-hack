import { Photographer } from "./Photographer";
import { Spreadsheet } from "./Spreadsheet";

const spreadsheet = new Spreadsheet();
const photographer = new Photographer();

const main = async () => {
  await spreadsheet.init();
  await spreadsheet.addScore({ name: "Danny", score: 100 });
  await photographer.takePhoto();
};

main();
