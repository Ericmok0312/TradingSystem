
import express from 'express'
import cors from 'cors';
import { WebSocketServer } from 'ws';
import nng from 'nanomsg';


const app = express();
const PORT = 5000;

app.use(cors()); // Enable CORS
app.use(express.json()); // Parse JSON bodies

let database: any[] = [];

const server = app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});

const wss = new WebSocketServer({ server });

wss.on('connection', (ws) => {
    console.log("Client connected");

    ws.on('message', (message: string) => {
        if (message === "requestData") {
            ws.send(JSON.stringify(database));
        }
    });
});

class DataReceiver {
    static API_URL: string = "tcp://localhost:8888";
    sub:nng.Socket;
    constructor() {
        this.sub = nng.socket('sub');
        this.sub.reconn(1);
        this.sub.connect("tcp://localhost:8888");
        this.getData();
    }

    getData() {
        console.log("Constructing DataReceiver");
        console.log(this.sub.connected);
        console.log(this.sub.protocol);
        this.sub.on('error',(msg)=>{
            console.log(msg);
        })


        this.sub.on('data', (msg: Buffer) => {
            console.log(msg.toString());
            const data = msg.toString().split('|');
            if (data[0] === "WebApp") {
                const message = JSON.parse(data[1]); // Adjusted to parse the correct part
                database.push(message);
            }
        });
    }
}

const dr = new DataReceiver();