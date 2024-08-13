
const express = require('express');
const cors = require('cors');
const { WebSocketServer } = require('ws');
const nng = require('nanomsg');

const app = express();
const PORT = 5000;

app.use(cors()); // Enable CORS
app.use(express.json()); // Parse JSON bodies

let database = [JSON.stringify({
  stock: "ABC",
  top_bid: 1.2,
  top_ask: 1.5,
  timestamp: "1-1-2000",
})];

const server = app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});

const wss = new WebSocketServer({ server });

wss.on('connection', (ws) => {
    console.log("client connected");

    ws.on('message', (message) => {
        if (message == "requestData") {
          console.log("requests1");
          ws.send(JSON.stringify(database));
        }
    });
});

class DataReceiver {
    static API_URL = 'http://localhost:8080/';
    
    constructor() {
        this.sub = nng.socket('sub');
    }

    getData() {
        this.sub.on('data', (msg) => {
            let message = msg.toString();
            database.push(message);
        });
    }
}

const dr = new DataReceiver();
dr.getData();

// Note: The while(true) loop will block the event loop. Consider using a different approach.