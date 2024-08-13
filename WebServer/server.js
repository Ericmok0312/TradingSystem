"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const express_1 = __importDefault(require("express"));
const cors_1 = __importDefault(require("cors"));
const ws_1 = require("ws");
const nanomsg_1 = __importDefault(require("nanomsg"));
const app = (0, express_1.default)();
const PORT = 5000;
app.use((0, cors_1.default)()); // Enable CORS
app.use(express_1.default.json()); // Parse JSON bodies
let database = [];
const server = app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
const wss = new ws_1.WebSocketServer({ server });
wss.on('connection', (ws) => {
    console.log("Client connected");
    ws.on('message', (message) => {
        if (message === "requestData") {
            ws.send(JSON.stringify(database));
        }
    });
});
class DataReceiver {
    constructor() {
        this.sub = nanomsg_1.default.socket('sub');
        this.sub.reconn(1);
        this.sub.connect("tcp://localhost:8888");
        this.getData();
    }
    getData() {
        console.log("Constructing DataReceiver");
        console.log(this.sub.connected);
        console.log(this.sub.protocol);
        this.sub.on('error', (msg) => {
            console.log(msg);
        });
        this.sub.on('data', (msg) => {
            console.log(msg.toString());
            const data = msg.toString().split('|');
            if (data[0] === "WebApp") {
                const message = JSON.parse(data[1]); // Adjusted to parse the correct part
                database.push(message);
            }
        });
    }
}
DataReceiver.API_URL = "tcp://localhost:8888";
const dr = new DataReceiver();
