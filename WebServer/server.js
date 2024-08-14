"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const express_1 = __importDefault(require("express"));
const cors_1 = __importDefault(require("cors"));
const ws_1 = require("ws");
const zeromq_1 = __importDefault(require("zeromq"));
const app = (0, express_1.default)();
const PORT = 5000;
let lastaccess = 0;
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
        ws.send('[' + JSON.stringify(database[lastaccess]) + ']');
        lastaccess += 1;
    });
});
class DataReceiver {
    constructor() {
        this.sub = zeromq_1.default.socket('sub');
        this.sub.connect("tcp://localhost:8888");
        this.sub.subscribe("WebApp");
        this.getData();
    }
    getData() {
        console.log("Constructing DataReceiver");
        this.sub.on('message', (msg) => {
            const data = msg.toString().split('|');
            const message = JSON.parse(data[3]); // Adjusted to parse the correct part
            database.push(message);
        });
    }
}
DataReceiver.API_URL = "tcp://localhost:8888";
const dr = new DataReceiver();
