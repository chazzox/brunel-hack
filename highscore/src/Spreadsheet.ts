import { GoogleSpreadsheet, GoogleSpreadsheetWorksheet, ServiceAccountCredentials } from "google-spreadsheet";
import { IScore } from "./Score";

class Spreadsheet {
  private scoreSheet: GoogleSpreadsheetWorksheet | null = null;

  private getScoreSheet(): GoogleSpreadsheetWorksheet {
    if (!this.scoreSheet) throw new Error("You have not initialised the spreadsheet system.");
    return this.scoreSheet;
  }

  async init(authData: ServiceAccountCredentials) {
    const doc = new GoogleSpreadsheet(
      "1T04dipNZQAmCCZqYaAwboHIEWYFwX7P24fuiY5x9nPY"
    );

    await doc.useServiceAccountAuth(authData);
    await doc.loadInfo();

    this.scoreSheet = doc.sheetsByTitle["Raw Highscores"];
  }

  async addScore(data: IScore) {
    const scoreSheet = this.getScoreSheet();
    scoreSheet.addRow(data as any);
  }
}

export { Spreadsheet };

