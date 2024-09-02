import { Server } from 'http';
import { ServerRespond } from './DataStreamer';
import { format } from 'path';

export interface Row {
  price : number;
  buyline : number;
  sellline : number;
  timestamp: string;

};

function formatTimestamp(timestamp: number | bigint): string {
  // Convert the timestamp to a Date object
  const date = new Date(Number(timestamp));

  // Pad the month, day, hour, minute, and second with leading zeros if necessary
  const month = String(date.getMonth() + 1).padStart(2, '0');
  const day = String(date.getDate()).padStart(2, '0');
  const hour = String(date.getHours()).padStart(2, '0');
  const minute = String(date.getMinutes()).padStart(2, '0');
  const second = String(date.getSeconds()).padStart(2, '0');

  // Get the milliseconds and convert to microseconds
  const microseconds = String(date.getMilliseconds())

  // Format the date and time
  return `${date.getFullYear()}-${month}-${day} ${hour}:${minute}:${second}.${microseconds}`;
}

export class DataManipulator {
  static generateRow(serverResponds: ServerRespond[]):Row {
    return{
      price: serverResponds[0]['cPrice'],
      buyline : serverResponds[0]['BuyLine'],
      sellline : serverResponds[0]['SellLine'],
      timestamp: formatTimestamp(serverResponds[0]['updateTimestamp']*10),
    };
    }
}