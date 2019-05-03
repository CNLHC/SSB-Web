import * as React from 'react';

import { Provider } from 'react-redux';
import { ConnectedRouter } from 'connected-react-router';
import QYFramework from "./pages/Framework";
import Mqtt from "./components/mqtt";

interface IRootType {
  store: any
  history: any
};


console.log("In constructor")

export default function Root({ store, history }: IRootType) {
  return (
    <Provider store={store}>
      <Mqtt>
          <ConnectedRouter history={history}>
              <QYFramework/>
          </ConnectedRouter>
      </Mqtt>
    </Provider>
  );
}
