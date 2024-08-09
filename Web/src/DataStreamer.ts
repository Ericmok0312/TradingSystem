export interface Order {
  price: number,
  size: number,
}
export interface ServerRespond {
  stock: string,
  top_bid: Order,
  top_ask: Order,
  timestamp: Date,
}

class DataStreamer {

  static getData(callback: (data: ServerRespond[]) => void): void {
    const socket = new WebSocket('ws://localhost:5000'); // Replace PORT with your actual port number

    socket.onopen = () => {
        console.log('WebSocket connection established');
    };

    socket.onmessage = (event) => {
        callback(JSON.parse(event.data));
        // Handle the received data as needed
    };

    socket.onclose = () => {
        console.log('WebSocket connection closed');
    };

    socket.onerror = (error) => {
        console.error('WebSocket error:', error);
    };
}}

export default DataStreamer;