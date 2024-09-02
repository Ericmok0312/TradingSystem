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
app.use((0, cors_1.default)()); // Enable CORS
app.use(express_1.default.json()); // Parse JSON bodies
class Queue {
    constructor() {
        this.items = [];
    }
    // Enqueue: Add an item to the end of the queue
    enqueue(item) {
        this.items.push(item);
    }
    // Dequeue: Remove and return the item from the front of the queue
    dequeue() {
        return this.items.shift();
    }
    // Peek: Get the item at the front of the queue without removing it
    peek() {
        return this.items[0];
    }
    // Check if the queue is empty
    isEmpty() {
        return this.items.length === 0;
    }
    // Get the size of the queue
    size() {
        return this.items.length;
    }
    // Clear the queue
    clear() {
        this.items = [];
    }
}
const server = app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
const wss = new ws_1.WebSocketServer({ server });
const emitter = new ws_1.EventEmitter();
emitter.setMaxListeners(0);
let database = new Queue;
wss.on('connection', (ws) => {
    console.log("Client connected");
    const dr = new DataReceiver();
    ws.on('message', (message) => {
        if (!database.isEmpty()) {
            ws.send("[" + JSON.stringify(database.dequeue()) + "]");
        }
        else {
            console.log("empty");
        }
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
            database.enqueue(message);
            console.log(message);
        });
    }
}
DataReceiver.API_URL = "tcp://localhost:8888";
