// Import path and url dependencies
import path from "path";
import { fileURLToPath } from "url";

// Get the directory and file path
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

// Import express, expressWs, and http
import express from "express";
import expressWs from "express-ws";
import http from "http";

// Our port
let port = 3000;

// App and server
let app = express();
let server = http.createServer(app).listen(port);

let keyData = { up: 0, right: 0 };

// Apply expressWs
expressWs(app, server);

app.use(express.static(__dirname + "/public"));

// Get the route /
app.get("/", (req, res) => {
  res.status(200).send("your mum");
});

// This lets the server pick up the '/ws' WebSocket route
app.ws("/input", async function (ws, req) {
  // After which we wait for a message and respond to it
  ws.on("message", async function (msg) {
    let parsedData = JSON.parse(msg);
    keyData = {
      up: parsedData.up || keyData.up,
      right: parsedData.right || keyData.right,
    };

    // If a message occurs, we'll console log it on the server
    console.log(`Key received: (${keyData.up}, ${keyData.right})`);
    // Start listening for messages

    // Send a message back to the client
    ws.send(JSON.stringify(keyData));
  });
});

console.log("Listening on port " + port);
