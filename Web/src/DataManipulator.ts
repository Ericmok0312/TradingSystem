import { Server } from 'http';
import { ServerRespond } from './DataStreamer';

export interface Row {
  price : number;
  timestamp: bigint;
  high_price : number;
  low_price : number;
};


export class DataManipulator {
  static generateRow(serverResponds: ServerRespond[]):Row {
    return{
      price: serverResponds[0]['cPrice'],
      timestamp: serverResponds[0]['timestamp'],
      high_price: serverResponds[0]['hPrice'],
      low_price: serverResponds[0]['lPrice']
    };
    }
}
