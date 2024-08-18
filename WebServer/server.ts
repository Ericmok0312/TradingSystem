
import express from 'express'
import cors from 'cors';
import { EventEmitter, WebSocketServer } from 'ws';
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



app.use(cors()); // Enable CORS
app.use(express.json()); // Parse JSON bodies




class Queue<T> {
    private items: T[] = [];

    // Enqueue: Add an item to the end of the queue
    enqueue(item: T): void {
        this.items.push(item);
    }

    // Dequeue: Remove and return the item from the front of the queue
    dequeue(): T | undefined {
        return this.items.shift();
    }

    // Peek: Get the item at the front of the queue without removing it
    peek(): T | undefined {
        return this.items[0];
    }

    // Check if the queue is empty
    isEmpty(): boolean {
        return this.items.length === 0;
    }

    // Get the size of the queue
    size(): number {
        return this.items.length;
    }

    // Clear the queue
    clear(): void {
        this.items = [];
    }
}


const server = app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});

const wss = new WebSocketServer({ server });

const emitter = new EventEmitter();
emitter.setMaxListeners(0);

let database: Queue<ServerRespond> = new Queue<ServerRespond>;


wss.on('connection', (ws) => {
    console.log("Client connected");
    const dr = new DataReceiver();
    ws.on('message', (message: string) => {
            if(!database.isEmpty()){
                ws.send("["+JSON.stringify(database.dequeue())+"]");
            }
            else{
                console.log("empty");
            }
        }
    )
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
        let last:bigint = BigInt(0);
        let cprice:number = 0;
        this.sub.on('message', (msg:Buffer) => {
            const data = msg.toString().split('|');
                const message:ServerRespond = JSON.parse(data[3]); // Adjusted to parse the correct part
                if(message["updateTimestamp"]> last || message["updateTimestamp"]==message["updateTimestamp"]&&message["cPrice"]!=cprice){
                    last = message["updateTimestamp"];
                    cprice = message["cPrice"];
                    database.enqueue(message);
                    console.log(message);
                }

            }
        );
    }
}

