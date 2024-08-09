import React, { Component } from 'react';
import DataStreamer, { ServerRespond } from './DataStreamer';
import Graph from './Graph';
import './App.css';

interface IState {
  data: ServerRespond[],
  showGraph: boolean,
}

class App extends Component<{}, IState> {
  socket: WebSocket | null;
  
  constructor(props: {}) {
    super(props);
    this.state = {
      data: [],
      showGraph: false,
    };
    this.socket = null;
  }

  componentDidMount() {
    this.setupWebSocket();
  }

  setupWebSocket() {
    this.socket = new WebSocket('ws://localhost:5000'); // Replace PORT with your actual port number

    this.socket.onopen = () => {
      console.log('WebSocket connection established');
    };

    this.socket.onmessage = (event) => {
      const data: ServerRespond[] = JSON.parse(event.data);
      this.setState({
        data: data,
        showGraph: true,
      });
      console.log(data);
    };

    this.socket.onclose = () => {
      console.log('WebSocket connection closed');
    };

    this.socket.onerror = (error) => {
      console.error('WebSocket error:', error);
    };
  }

  requestData() {
    let x = 0;
    const interval = setInterval(() => {
        if (this.socket) {
            this.socket.send("requestData");
        }
        x++;
        if (x >= 1000) {
            clearInterval(interval);
        }
    }, 100);
}
    
  

  renderGraph() {
    if (this.state.showGraph) {
      return <Graph data={this.state.data} />;
    }
  }

  render() {
    return (
      <div className="App">
        <header className="App-header">
          Bank Merge & Co Task 3
        </header>
        <div className="App-content">
          <button className="btn btn-primary Stream-button" onClick={() => this.requestData()}>
            Start Streaming Data
          </button>
          <div className="Graph">
            {this.renderGraph()}
          </div>
        </div>
      </div>
    );
  }
}

export default App;