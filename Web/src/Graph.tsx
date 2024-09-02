import React, { Component } from 'react';
import { Table, TableData } from '@finos/perspective';
import { ServerRespond } from './DataStreamer';
import { DataManipulator } from './DataManipulator';
import './Graph.css';
import { timeStamp } from 'console';

interface IProps {
  data: ServerRespond[],
}

interface PerspectiveViewerElement extends HTMLElement {
  load: (table: Table) => void,
}
class Graph extends Component<IProps, {}> {
  table: Table | undefined;

  render() {
    return React.createElement('perspective-viewer');
  }

  componentDidMount() {
    // Get element from the DOM.
    const elem = document.getElementsByTagName('perspective-viewer')[0] as unknown as PerspectiveViewerElement;

    const schema = {
      price : "float",
      buyline : "float",
      sellline : "float",
      timestamp :"string",
    };

    if (window.perspective && window.perspective.worker()) {
      this.table = window.perspective.worker().table(schema);
    }
    if (this.table) {
      // Load the `table` in the `<perspective-viewer>` DOM reference.
      elem.load(this.table);
      elem.setAttribute('view', 'y_line');
      //elem.setAttribute('group_by', '"timeStamp"')
      elem.setAttribute('row-pivots', '["timestamp"]');
      elem.setAttribute('columns', '["price", "buyline", "sellline"]');
      elem.setAttribute('aggregates', JSON.stringify({
        price: "avg",
        buyline: "avg",
        sellline : "avg",
        timeStamp: "distinct count"
      }));
      //elem.setAttribute("x_axis", "timestamp");
    }
  }

  componentDidUpdate() {
    if (this.table) {
      this.table.update([
        DataManipulator.generateRow(this.props.data),
      ]as unknown as TableData);

    }
  }
}

export default Graph;
