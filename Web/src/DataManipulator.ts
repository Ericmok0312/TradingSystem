import { ServerRespond } from './DataStreamer';

export interface Row {
  price : number;
  timestamp: bigint;
  high_price : number;
  low_price : number;
};


// export class DataManipulator {
//   static generateRow(serverResponds: ServerRespond[]):Row {
//     const priceABC = (serverResponds[0].top_ask.price + serverResponds[0].top_bid.price)/2;
//     const priceDEF = (serverResponds[1].top_ask.price + serverResponds[1].top_bid.price)/2
//     const ratio = priceABC/priceDEF;
//     const upper = 1+0.05;
//     const lower = 1-0.05;
//     return{
//       price_abc: priceABC,
//       price_def: priceDEF,
//       ratio,
//       timestamp: serverResponds[0].timestamp > serverResponds[1].timestamp ? serverResponds[0].timestamp : serverResponds[1].timestamp,
//       upper_bound: upper,
//       lower_bound: lower,
//       trigger_alert: (ratio>upper || ratio<lower)? ratio : undefined
//     };
//     }
//}
