import express from "express";
import bodyParser from "body-parser";
import { winner } from "./winner";
import { isValidScore } from "./Score";

const app = express();

app
  .use(bodyParser.json())
  .post("/score", async (req, res, next) => {
    if (isValidScore(req.body)) {
      await winner(req.body);

      res.status(200).json({ ok: true });
    } else {
      res.status(400).json({ ok: false });
    }
  })
  .get("/testscore", async (req, res, next) => {
    await winner({
      name: "Danny Piper",
      score: 32871,
    });

    res.status(200).json({ ok: true });
  });

app.listen(8080);
