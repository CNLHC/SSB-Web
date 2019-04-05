import React, { Component } from 'react';
import './App.css';
import {Provider} from "react-redux";
import PageSettleRoute from "./Routes/MainRoute";
import configureStore  from './Store/ConfigureStore'
import {BrowserRouter} from "react-router-dom";
import {IRootStore} from "./Typings/TypeRoot";
import {applyMiddleware, createStore} from "redux";
import RootReducers from "./Reducers";
import thunk from "redux-thunk";
import logger from "redux-logger";
import { composeWithDevTools } from 'redux-devtools-extension';

const store = createStore(RootReducers,composeWithDevTools(applyMiddleware(thunk,logger)));

class App extends Component {
  render() {
    return (
        <Provider store={store}>
            <BrowserRouter>
                <PageSettleRoute/>
            </BrowserRouter>
        </Provider>
    );
  }
}

export default App;
