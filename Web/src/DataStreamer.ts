export interface Order {
  price: number,
  size: number,
}
export interface ServerRespond {
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
  updateTimestamp: number;
}

