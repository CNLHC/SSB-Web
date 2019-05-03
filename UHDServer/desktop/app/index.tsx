import * as React from 'react';
import { render } from 'react-dom';
import { AppContainer } from 'react-hot-loader';
import './app.global.scss';
import Root from "./Root";

const { history,configureStore } = require('./store/configureStore');
const store = configureStore();
import * as mqtt from "mqtt"
import {ICommodity} from "./Typing";
import {ActUpdateCommodityList} from "./components/mqtt/actions";

const client = mqtt.connect('tcp://localhost:1883', {clientId: "UHDClient"});
client.subscribe('UHDChannel')
client.on('message', (topic: any, message: any) => {
    console.log(message.toString())
    const parsed:ICommodity[] = message.toString().split(',').map((e: string) => ({UHDTag: e.split('=')[0]}))
    if(parsed.length>0)
         store.dispatch(ActUpdateCommodityList(parsed))
})


render(
  <AppContainer>
    <Root store={store} history={history} />
  </AppContainer>,
  document.getElementById('root')
);

if ((module as any).hot) {
  (module as any).hot.accept('./Root', () => {
    const NextRoot = require('./Root').default;
    render(
      <AppContainer>
        <NextRoot store={store} history={history} />
      </AppContainer>,
      document.getElementById('root')
    );
  });
}
