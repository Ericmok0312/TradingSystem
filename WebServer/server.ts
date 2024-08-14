
import express from 'express'
import cors from 'cors';
import { WebSocketServer } from 'ws';
import zmq from 'zeromq';



interface ServerRespond {
    code: string;
    time: string;
    exg: string;
    hPrice: number;
    oPrice: number;
    lPrice: number;
    cPrice: number;
    lcPrice: number;
    pSpread: number;
    volume: bigint;
    turnover: number;
    turnoverRate: number;
    amplitude: number;
    timestamp: bigint;
    sPrice: number;
    conSize: number;
    opInterest: bigint;
    impVolatility: number;
    premium: number;
    delta: number;
    gamma: number;
    vega: number;
    theta: number;
    rho: number;
    lsprice: number;
    position: bigint;
    pChange: bigint;
    updateTimestamp: bigint;
  }
  
  

const app = express();
const PORT = 5000;

let lastaccess = 0;

app.use(cors()); // Enable CORS
app.use(express.json()); // Parse JSON bodies

let database: ServerRespond[] = [];

const server = app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});

const wss = new WebSocketServer({ server });

wss.on('connection', (ws) => {
    console.log("Client connected");

    ws.on('message', (message: string) => {
        ws.send('['+JSON.stringify(database[lastaccess])+']');
        lastaccess+=1;
    });
});

class DataReceiver {
    static API_URL: string = "tcp://localhost:8888";
    sub:zmq.Socket;
    constructor() {
        this.sub = zmq.socket('sub');
        this.sub.connect("tcp://localhost:8888");
        this.sub.subscribe("WebApp");
        this.getData();
    }

    getData() {
        console.log("Constructing DataReceiver");

        this.sub.on('message', (msg:Buffer) => {
            const data = msg.toString().split('|');
                const message = JSON.parse(data[3]); // Adjusted to parse the correct part
                database.push(message);
            }
        );
    }
}

const dr = new DataReceiver();